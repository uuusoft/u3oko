#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/doptim/_make/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/devents/_make/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/base_id/_make/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/convertors/all2rgb/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/convertors/all2hsl/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/terminals/video_sender/_make/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/detectors/detect_move/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/detectors/detect_face/_make/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_conv3_11/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_diff/lib/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_diff/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_mops/lib/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_mops/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/gens/vgen_motion/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/utils/vec2image/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/vgen_lib/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/gen_vgen/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/desk_vgen/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/fake_vgen/CMakeLists.txt" )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
  include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/windows_dshow_vgen/_make/CMakeLists.txt" )
endif()

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/android_java_vgen/_make/CMakeLists.txt" )
  #include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/android_openmax_vgen/_make/CMakeLists.txt" )
endif()

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry" )
  include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/raspberry_openmax_vgen/_make/CMakeLists.txt" )
endif()

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/codec_functs/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/codec_gen/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_gen/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_test/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_mjpg/_make/CMakeLists.txt" )
#include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_x265/_make/CMakeLists.txt" )
#include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_x265/_make/CMakeLists.txt" )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_media_android/_make/CMakeLists.txt" )
endif()

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/filter_noise/freq_domain/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/filter_noise/space/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/filter_noise/time/_make/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/uplifters/vcorrect/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/uplifters/vgradient/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/scales/flow/CMakeLists.txt" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/mixers/mix_multiplier/CMakeLists.txt" )
