# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        dlls-list.cmake

include("${U3_BUILD_PATH_TO_LIBS}/dlls/doptim/_make/generics-doptim.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/devents/_make/generics-devents.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/base_id/_make/generics-base-id.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/convertors/all2rgb/_make/convertors-all2rgb.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/convertors/all2hsl/convertors-all2hsl.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/terminals/video_sender/_make/terminals-video-sender.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/detectors/detect_move/_make/detectors-move.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/detectors/detect_face/_make/detect-face.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_conv3_11/gens-vgen-conv3_11.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_diff/lib/_make/gens-vgen-diff-lib.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_diff/_make/gens-vgen-diff.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_mops/lib/_make/gens-vgen-mops-lib.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_mops/_make/gens-vgen-mops.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_motion/gens-vgen-motion.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/utils/vec2image/utils-vec2image.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/vgen_lib/_make/gen-lib-source-dlls.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/gen_vgen/gen-vgen-source-dlls.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/v4l2_vgen/_make/v4l2-vgen-source-dlls.cmake")

if(U3_USE_COMMERCIAL_PART)
  include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/desk_vgen/desk-vgen-source-dlls.cmake")
  include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/fake_vgen/fake-vgen-source-dlls.cmake")
  include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/dshow_vgen/_make/dshow-vgen-source-dlls.cmake")
  include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/pict_vgen/_make/pict-vgen-source-dlls.cmake")
  include("${U3_BUILD_PATH_TO_LIBS}/dlls/sources/android_vgen/_make/android-vgen-source-dlls.cmake")
  #include( "${U3_BUILD_PATH_TO_LIBS}/dlls/sources/rasp_vgen/_make/rasp-vgen-sources-dlls.cmake" )
endif()

include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/codec_funcs/_make/lib-funcs-codecs-dlls.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/codec_gen/_make/codec-gen-codecs-dlls.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_gen/vcodec-gen-codecs-dlls.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_mjpg/_make/vcodec-mjpg-codecs-dlls.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_x264/_make/vcodec-x264-codecs-dlls.cmake")

if(U3_USE_COMMERCIAL_PART)
  include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_va/_make/vcodec-va-codecs-dlls.cmake")
  include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_x265/_make/vcodec-x265-codecs-dlls.cmake")
  #include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_android/_make/vcodec-android-codecs-dlls.cmake")
  #include("${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_test/_make/vcodec-test-codecs-dlls.cmake")
endif()

include("${U3_BUILD_PATH_TO_LIBS}/dlls/filter_noise/freq_domain/filter-freq-domain.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/filter_noise/space/_make/filter-space-domain.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/filter_noise/time/_make/filter-time-domain.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/uplifters/vcorrect/_make/uplifterss-vcorrect.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/uplifters/vgradient/uplifterss-vgradient.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/scales/flow/scales-flow.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/dlls/scales/fixed/scales-fixed.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/dlls/mixers/mix_multiplier/mixers-mix-mulltiplier.cmake")
