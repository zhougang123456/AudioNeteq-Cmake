#include "api/audio/audio_frame.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "modules/audio_coding/codecs/pcm16b/pcm16b.h"
#include "modules/audio_coding/neteq/default_neteq_factory.h"
#include "system_wrappers/include/clock.h"
#include "api/neteq/neteq.h"
#include "audio-neteq.h"

using namespace webrtc;
using webrtc::NetEq;

#ifdef __cplusplus
extern "C" {
#endif

    struct NeteqContext {
        std::unique_ptr<NetEq> neteq_;
    };

    NeteqContext* init_neteq(int sample_rate, int channels, int encode_type)
    {   
        NeteqContext* context = (NeteqContext* )malloc(sizeof(NeteqContext));
        if (nullptr == context) {
            return nullptr;
        }
        memset(context, 0, sizeof(NeteqContext));
        NetEq::Config config;
        config.sample_rate_hz = sample_rate;
        webrtc::Clock* clock = webrtc::Clock::GetRealTimeClock();
        auto audio_decoder_factory = CreateBuiltinAudioDecoderFactory();
        context->neteq_ = DefaultNetEqFactory().CreateNetEq(config, audio_decoder_factory, clock);
        if (context->neteq_ == nullptr) {
            return nullptr;
        }
        if (!context->neteq_->RegisterPayloadType(encode_type, SdpAudioFormat("l16", sample_rate, channels, { {"stereo", "0"} }))) {
            return nullptr;
        }
        context->neteq_->EnableNack(128);
        return context;
    }
    void clear_neteq(NeteqContext* context) {
        if (context != nullptr) {
            context->neteq_->FlushBuffers();
            context->neteq_.reset();
            context->neteq_ = nullptr;
            free(context);
        }
    }
    int neteq_insert_packet(NeteqContext* context, int seq_no, int timestamp, short* data, int samples)
    {   
        if (context) {
            size_t payload_len = WebRtcPcm16b_Encode(data, samples * 2, (uint8_t*)data);
            RTPHeader rtp_info;
            rtp_info.sequenceNumber = seq_no;
            rtp_info.timestamp = timestamp;
            rtp_info.ssrc = 0x1234;
            rtp_info.payloadType = 97;
            rtp_info.markerBit = 0;
            if (context->neteq_->InsertPacket(rtp_info, rtc::ArrayView<const uint8_t>((uint8_t*)data, payload_len)) == -1) {
                return -1;
            }
            return 0;
        }
        return -1;
    }
    int neteq_get_audio(NeteqContext* context, short* data)
    {
        if (context) {
            AudioFrame out_frame;
            bool muted;
            if (context->neteq_->GetAudio(&out_frame, &muted) == -1) {
                return 0;
            }
            memcpy(data, out_frame.data(), out_frame.samples_per_channel_ << out_frame.num_channels_);
            return out_frame.samples_per_channel_;
        }
        return 0;
    }
    int neteq_get_delay_time(NeteqContext* context, int timestamp) {
        if (context && context->neteq_->GetPlayoutTimestamp() 
            && timestamp > context->neteq_->GetPlayoutTimestamp().value()) {
            return (timestamp - context->neteq_->GetPlayoutTimestamp().value()) / 480 * 10;
        }
        return 0;
    }
    int neteq_get_last_operator(NeteqContext* context) {
        if (context) {
            return context->neteq_->LastOperation();
        }
        return -1;
    }
    void neteq_set_max_delay(NeteqContext* context, int delay)
    {
        if (context) {
            context->neteq_->SetMaximumDelay(delay);
            //neteq_->SetMaximumPacketNumber(delay / 10);
        }
    }
    void neteq_set_max_speed(NeteqContext* context, double speed)
    {
        if (context) {
            context->neteq_->SetMaxSpeed(speed);
        }
    }
    void neteq_get_nack_list(NeteqContext* context, int round_trip_time)
    {
        if (context) {
            std::vector<uint16_t> list = context->neteq_->GetNackList(round_trip_time);
        }
    }

#ifdef __cplusplus
};
#endif
