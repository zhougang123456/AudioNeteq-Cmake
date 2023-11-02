cmake_minimum_required(VERSION 3.23)

project(webrtc-neteq)

add_definitions(-DRTC_DISABLE_LOGGING)
add_definitions(-DWEBRTC_USE_BUILTIN_ISAC_FIX)
add_definitions(-DRTC_DISABLE_TRACE_EVENTS)
add_definitions(-DRTC_DISABLE_METRICS)
add_definitions(-DRTC_DISABLE_CHECK_MSG)
add_definitions(-DWEBRTC_USE_BUILTIN_OPUS)

if (CMAKE_HOST_WIN32)
add_definitions(-DWEBRTC_WIN)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()
if (CMAKE_HOST_UNIX)
add_definitions(-DWEBRTC_LINUX)
add_definitions(-DWEBRTC_POSIX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -O2 -Wall -fPIC -fno-rtti")  #设置c++的编译选项
endif ()

set (
    DIR_CLINK_WEBRTC_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/audio-neteq.cc
    # absl
    ${CMAKE_CURRENT_SOURCE_DIR}/absl/base/internal/throw_delegate.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/absl/strings/ascii.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/absl/strings/match.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/absl/strings/string_view.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/absl/strings/internal/memutil.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/absl/types/bad_optional_access.cc
    # rtc_base
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/checks.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/logging.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/time_utils.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/system_time.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/string_encode.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/zero_memory.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/string_to_number.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/experiments/field_trial_parser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/experiments/struct_parameters_parser.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/experiments/field_trial_list.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/experiments/field_trial_units.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/strings/audio_format_to_string.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/rtc_base/strings/string_builder.cc
    # system_wrappers
    ${CMAKE_CURRENT_SOURCE_DIR}/system_wrappers/source/clock.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/system_wrappers/source/field_trial.cc
    # api
    ${CMAKE_CURRENT_SOURCE_DIR}/api/rtp_headers.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/rtp_packet_info.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio/audio_frame.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio/channel_layout.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio_codecs/audio_format.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio_codecs/builtin_audio_decoder_factory.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio_codecs/audio_decoder.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio_codecs/L16/audio_decoder_L16.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/neteq/custom_neteq_factory.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/neteq/default_neteq_controller_factory.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/neteq/neteq.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/neteq/tick_timer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/units/data_rate.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/units/data_size.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/units/time_delta.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/units/frequency.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/units/timestamp.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/video/color_space.cc
    # common_audio
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/vad/webrtc_vad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/vad/vad_core.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/vad/vad_filterbank.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/vad/vad_gmm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/vad/vad_sp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/third_party/spl_sqrt_floor/spl_sqrt_floor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/complex_fft.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/copy_set_operations.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/division_operations.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/auto_corr_to_refl_coef.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/lpc_to_refl_coef.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/refl_coef_to_lpc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/ilbc_specific_functions.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/levinson_durbin.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/get_scaling_square.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/min_max_operations.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/vector_scaling_operations.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/auto_correlation.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/get_hanning_window.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/sqrt_of_one_minus_x_squared.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/randomization_functions.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/spl_sqrt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/energy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/filter_ar.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/filter_ma_fast_q12.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/filter_ar_fast_q12.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/downsample_fast.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/complex_bit_reverse.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/resample_48khz.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/resample.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/resample_fractional.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/resample_by_2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/resample_by_2_internal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/splitting_filter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/dot_product_with_scale.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/spl_init.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/spl_inl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common_audio/signal_processing/cross_correlationC.c
    # modulde/audiocoding
    # modulde/audiocoding/neteq
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/accelerate.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/audio_multi_vector.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/audio_vector.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/background_noise.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/buffer_level_filter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/comfort_noise.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/cross_correlation.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/decision_logic.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/decoder_database.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/default_neteq_factory.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/delay_manager.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/dsp_helper.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/dtmf_buffer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/dtmf_tone_generator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/expand_uma_logger.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/expand.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/histogram.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/merge.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/nack_tracker.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/neteq_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/normal.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/packet_buffer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/packet.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/post_decode_vad.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/preemptive_expand.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/random_vector.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/red_payload_splitter.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/relative_arrival_delay_tracker.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/reorder_optimizer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/statistics_calculator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/sync_buffer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/time_stretch.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/timestamp_scaler.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/neteq/underrun_optimizer.cc
    # modulde/audiocoding/codecs
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/legacy_encoded_audio_frame.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/cng/webrtc_cng.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/pcm16b/pcm16b.c
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/pcm16b/pcm16b_common.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/pcm16b/audio_decoder_pcm16b.cc
    # opus
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio_codecs/opus/audio_decoder_opus.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/api/audio_codecs/opus/audio_decoder_multi_channel_opus.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/opus/audio_coder_opus_common.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/opus/audio_decoder_multi_channel_opus_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/opus/audio_decoder_opus_impl.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/audio_coding/codecs/opus/opus_interface.cc
    CACHE INTERNAL "clink werbrtc source dir"
)

add_library(${PROJECT_NAME} SHARED ${DIR_CLINK_WEBRTC_SRCS})

add_subdirectory(third_party/opus)

if (CMAKE_HOST_WIN32)
target_link_libraries(
            ${PROJECT_NAME} 
            winmm.lib
            ${CMAKE_CURRENT_SOURCE_DIR}/build/third_party/opus/$(Configuration)/opus.lib
)
endif ()

add_dependencies(${PROJECT_NAME} opus)

target_include_directories(
            ${PROJECT_NAME} 
            PUBLIC 
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opus/include
)

add_executable(test 
               ${CMAKE_CURRENT_SOURCE_DIR}/test_neteq.c
	       )

if (CMAKE_HOST_WIN32)
target_link_libraries(test 
					  winmm.lib 
					  ${CMAKE_CURRENT_SOURCE_DIR}/build/$(Configuration)/webrtc-neteq.lib)
set_target_properties(test PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_CURRENT_SOURCE_DIR}/build/$(Configuration)")
endif ()

if (CMAKE_HOST_UNIX)
target_link_libraries(test
                      webrtc-neteq
                      )
endif ()

target_include_directories(
            test 
            PUBLIC 
            ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(test ${PROJECT_NAME})