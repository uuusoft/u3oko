# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        dlls-list.cmake

include("${U3_PATH_ROOT}/dlls/doptim/generics-doptim.cmake")
include("${U3_PATH_ROOT}/dlls/devents/generics-devents.cmake")
include("${U3_PATH_ROOT}/dlls/base_id/generics-base-id.cmake")

include("${U3_PATH_ROOT}/dlls/convertors/all2rgb/convertors-all2rgb.cmake")
include("${U3_PATH_ROOT}/dlls/convertors/all2hsl/convertors-all2hsl.cmake")

include("${U3_PATH_ROOT}/dlls/terminals/video_sender/terminals-video-sender.cmake")

include("${U3_PATH_ROOT}/dlls/detectors/detect_move/detectors-move.cmake")
include("${U3_PATH_ROOT}/dlls/detectors/detect_face/detect-face.cmake")

include("${U3_PATH_ROOT}/dlls/gens/vgen_conv3_11/gens-vgen-conv3_11.cmake")
include("${U3_PATH_ROOT}/dlls/gens/vgen_diff/lib/gens-vgen-diff-lib.cmake")
include("${U3_PATH_ROOT}/dlls/gens/vgen_diff/gens-vgen-diff.cmake")
include("${U3_PATH_ROOT}/dlls/gens/vgen_mops/lib/gens-vgen-mops-lib.cmake")
include("${U3_PATH_ROOT}/dlls/gens/vgen_mops/gens-vgen-mops.cmake")
include("${U3_PATH_ROOT}/dlls/gens/vgen_motion/gens-vgen-motion.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dlls/utils/vec2image/utils-vec2image.cmake")
endif ()

include("${U3_PATH_ROOT}/dlls/sources/vgen_lib/gen-lib-source-dlls.cmake")
include("${U3_PATH_ROOT}/dlls/sources/gen_vgen/gen-vgen-source-dlls.cmake")
include("${U3_PATH_ROOT}/dlls/sources/v4l2_vgen/v4l2-vgen-source-dlls.cmake")
include("${U3_PATH_ROOT}/dlls/sources/fake_vgen/fake-vgen-source-dlls.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dlls/sources/desk_vgen/desk-vgen-source-dlls.cmake")
  include("${U3_PATH_ROOT}/dlls/sources/dshow_vgen/dshow-vgen-source-dlls.cmake")
  include("${U3_PATH_ROOT}/dlls/sources/pict_vgen/pict-vgen-source-dlls.cmake")
  include("${U3_PATH_ROOT}/dlls/sources/android_vgen/android-vgen-source-dlls.cmake")
  #include( "${U3_PATH_ROOT}/dlls/sources/rasp_vgen/rasp-vgen-sources-dlls.cmake" )
endif ()

include("${U3_PATH_ROOT}/dlls/codecs/codec_funcs/lib-funcs-codecs-dlls.cmake")
include("${U3_PATH_ROOT}/dlls/codecs/codec_gen/codec-gen-codecs-dlls.cmake")
include("${U3_PATH_ROOT}/dlls/codecs/vcodec_gen/vcodec-gen-codecs-dlls.cmake")
include("${U3_PATH_ROOT}/dlls/codecs/vcodec_mjpg/vcodec-mjpg-codecs-dlls.cmake")
include("${U3_PATH_ROOT}/dlls/codecs/vcodec_x264/vcodec-x264-codecs-dlls.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  #include("${U3_PATH_ROOT}/dlls/codecs/vcodec_va/vcodec-va-codecs-dlls.cmake")
  #include("${U3_PATH_ROOT}/dlls/codecs/vcodec_x265/vcodec-x265-codecs-dlls.cmake")
  #include("${U3_PATH_ROOT}/dlls/codecs/vcodec_android/vcodec-android-codecs-dlls.cmake")
  #include("${U3_PATH_ROOT}/dlls/codecs/vcodec_test/vcodec-test-codecs-dlls.cmake")
endif ()

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dlls/noisez/freq_domain/filter-freq-domain.cmake")
endif ()

include("${U3_PATH_ROOT}/dlls/noisez/space/filter-space-domain.cmake")
include("${U3_PATH_ROOT}/dlls/noisez/time/filter-time-domain.cmake")

include("${U3_PATH_ROOT}/dlls/uplifters/vcorrect/uplifterss-vcorrect.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dlls/uplifters/vgradient/uplifterss-vgradient.cmake")

  include("${U3_PATH_ROOT}/dlls/scales/flow/scales-flow.cmake")
  include("${U3_PATH_ROOT}/dlls/scales/fixed/scales-fixed.cmake")

  include("${U3_PATH_ROOT}/dlls/mixers/mix_multiplier/mixers-mix-mulltiplier.cmake")
endif ()
