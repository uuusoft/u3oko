# author      Erashov Anton erashov2026@proton.me, erashov2021@gmail.com
# date        01.01.2017
# copyright   Erashov A.I.
# file        libs-list.cmake

# move to CMakeLists.txt
#include( "${U3_BUILD_PATH_TO_LIBS}/libs/proxy/_make/libs-proxy.cmake" )

include("${U3_BUILD_PATH_TO_LIBS}/libs/helpers/_make/libs-helpers.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/libs/bufs/_make/libs-dbufs.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/libs/link/_make/libs-links-link.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/ilink/_make/libs-links-ilink.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/libs/events/_make/libs-events-events.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/ievents/_make/libs-events-ievents.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/ilog_events/_make/libs-events-ilog-events.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/imdata_events/_make/libs-events-imdata-events.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/ievents_events/_make/libs-events-ievents-events.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/igui_events/_make/libs-events-igui-events.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/ihttp_events/_make/libs-events-ihttp-events.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/istorage_events/_make/libs-events-istorage-events.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/libs/core/_make/libs-cores-core.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/icore/_make/libs-cores-icore.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/libs/properties/_make/libs-properties-properties.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/iproperties/_make/libs-properties-iproperties.cmake")

include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/optim/_make/libs-optims-optim.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/optim_convert/_make/libs-optims-convert-optim-gen-convert.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_s16bit_generic/_make/libs-optims-s16bit-optim-s16bit-generic.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_convert/_make/libs-optims-s16bit-optim-convert.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_bits/_make/libs-optims-s16bit-optim-bits.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_block/_make/libs-optims-s16bit-optim-block.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_conv/_make/libs-optims-s16bit-optim-conv.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_filter/_make/libs-optims-s16bit-optim-filter.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_freq/_make/libs-optims-s16bit-optim-freq.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_gen/_make/libs-optims-s16bit-optim-gen.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_statistics/_make/libs-optims-s16bit-optim-statistics.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_motion/_make/libs-optims-s16bit-optim-motion.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_ops/_make/libs-optims-s16bit-optim-ops.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/libs/optims/s16bit/optim_scale/_make/libs-optims-s16bit-optim-scalec.cmake")
