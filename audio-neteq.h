#ifndef _AUDIO_NETEQ_H_
#define _AUDIO_NETEQ_H_

#ifdef __cplusplus
extern "C" {
#endif
	typedef struct NeteqContext NeteqContext;
#ifdef WEBRTC_WIN
	__declspec (dllexport) NeteqContext* init_neteq(int sample_rate, int channels, int encode_type);
	__declspec (dllexport) void clear_neteq(NeteqContext* context);
	__declspec (dllexport) int neteq_insert_packet(NeteqContext* context, int seq_no, int timestamp, short* data, int samples, int encode_type, int size);
	__declspec (dllexport) int neteq_get_audio(NeteqContext* context, short* data);
	__declspec (dllexport) int neteq_get_delay_time(NeteqContext* context, int timestamp);
	__declspec (dllexport) int neteq_get_last_operator(NeteqContext* context);
	__declspec (dllexport) void neteq_set_max_delay(NeteqContext* context, int delay);
	__declspec (dllexport) void neteq_set_max_speed(NeteqContext* context, double speed);
	__declspec (dllexport) void neteq_get_nack_list(NeteqContext* context, int round_trip_time);
#else
	extern NeteqContext* init_neteq(int sample_rate, int channels, int encode_type);
	extern void clear_neteq(NeteqContext* context);
	extern int neteq_insert_packet(NeteqContext* context, int seq_no, int timestamp, short* data, int samples, int encode_type, int size);
	extern int neteq_get_audio(NeteqContext* context, short* data);
	extern int neteq_get_delay_time(NeteqContext* context, int timestamp);
	extern int neteq_get_last_operator(NeteqContext* context);
	extern void neteq_set_max_delay(NeteqContext* context, int delay);
	extern void neteq_set_max_speed(NeteqContext* context, double speed);
	extern void neteq_get_nack_list(NeteqContext* context, int round_trip_time);
#endif
#ifdef __cplusplus
};
#endif

#endif // _AUDIO_NETEQ_H_
