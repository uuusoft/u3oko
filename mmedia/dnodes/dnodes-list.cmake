# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        dnodes-list.cmake

#include("${U3_PATH_ROOT}/utils/doptim/utils-doptim.cmake")
#include("${U3_PATH_ROOT}/dnodes/devents/-utils-devents.cmake")
include("${U3_PATH_ROOT}/dnodes/base_id/-generics-base-id.cmake")

include("${U3_PATH_ROOT}/dnodes/convertors/all2rgb/-convertors-all2rgb.cmake")
include("${U3_PATH_ROOT}/dnodes/convertors/all2hsl/-convertors-all2hsl.cmake")

include("${U3_PATH_ROOT}/dnodes/terminals/video_sender/-terminals-video-sender.cmake")

include("${U3_PATH_ROOT}/dnodes/detectors/detect_move/-detectors-move.cmake")
include("${U3_PATH_ROOT}/dnodes/detectors/detect_face/-detect-face.cmake")

include("${U3_PATH_ROOT}/dnodes/gens/vgen_conv3_11/-gens-vgen-conv3_11.cmake")
include("${U3_PATH_ROOT}/dnodes/gens/vgen_diff/lib/-gens-vgen-diff-lib.cmake")
include("${U3_PATH_ROOT}/dnodes/gens/vgen_diff/-gens-vgen-diff.cmake")
include("${U3_PATH_ROOT}/dnodes/gens/vgen_mops/lib/-gens-vgen-mops-lib.cmake")
include("${U3_PATH_ROOT}/dnodes/gens/vgen_mops/-gens-vgen-mops.cmake")
include("${U3_PATH_ROOT}/dnodes/gens/vgen_motion/-gens-vgen-motion.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dnodes/utils/vec2image/-utils-vec2image.cmake")
endif ()

include("${U3_PATH_ROOT}/dnodes/sources/vgen_lib/-gen-lib-source-dnodes.cmake")
include("${U3_PATH_ROOT}/dnodes/sources/gen_vgen/-gen-vgen-source-dnodes.cmake")
include("${U3_PATH_ROOT}/dnodes/sources/v4l2_vgen/-v4l2-vgen-source-dnodes.cmake")
include("${U3_PATH_ROOT}/dnodes/sources/fake_vgen/-fake-vgen-source-dnodes.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dnodes/sources/desk_vgen/-desk-vgen-source-dnodes.cmake")
  include("${U3_PATH_ROOT}/dnodes/sources/dshow_vgen/-dshow-vgen-source-dnodes.cmake")
  include("${U3_PATH_ROOT}/dnodes/sources/pict_vgen/-pict-vgen-source-dnodes.cmake")
  include("${U3_PATH_ROOT}/dnodes/sources/android_vgen/-android-vgen-source-dnodes.cmake")
  #include( "${U3_PATH_ROOT}/dnodes/sources/rasp_vgen/-rasp-vgen-sources-dnodes.cmake" )
endif ()

include("${U3_PATH_ROOT}/dnodes/codecs/codec_funcs/-lib-funcs-codecs-dnodes.cmake")
include("${U3_PATH_ROOT}/dnodes/codecs/codec_gen/-codec-gen-codecs-dnodes.cmake")
include("${U3_PATH_ROOT}/dnodes/codecs/vcodec_gen/-vcodec-gen-codecs-dnodes.cmake")
include("${U3_PATH_ROOT}/dnodes/codecs/vcodec_mjpg/-vcodec-mjpg-codecs-dnodes.cmake")
include("${U3_PATH_ROOT}/dnodes/codecs/vcodec_x264/-vcodec-x264-codecs-dnodes.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  #include("${U3_PATH_ROOT}/dnodes/codecs/vcodec_va/-vcodec-va-codecs-dnodes.cmake")
  #include("${U3_PATH_ROOT}/dnodes/codecs/vcodec_x265/-vcodec-x265-codecs-dnodes.cmake")
  #include("${U3_PATH_ROOT}/dnodes/codecs/vcodec_android/-vcodec-android-codecs-dnodes.cmake")
  #include("${U3_PATH_ROOT}/dnodes/codecs/vcodec_test/-vcodec-test-codecs-dnodes.cmake")
endif ()

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dnodes/noisez/freq_domain/-filter-freq-domain.cmake")
endif ()

include("${U3_PATH_ROOT}/dnodes/noisez/space/-filter-space-domain.cmake")
include("${U3_PATH_ROOT}/dnodes/noisez/time/-filter-time-domain.cmake")

include("${U3_PATH_ROOT}/dnodes/uplifters/vcorrect/-uplifterss-vcorrect.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/dnodes/uplifters/vgradient/-uplifterss-vgradient.cmake")

  include("${U3_PATH_ROOT}/dnodes/scales/flow/-scales-flow.cmake")
  include("${U3_PATH_ROOT}/dnodes/scales/fixed/-scales-fixed.cmake")

  include("${U3_PATH_ROOT}/dnodes/mixers/mix_multiplier/-mixers-mix-mulltiplier.cmake")
endif ()
