# author      Erashov Anton erashov2026@proton.me, erashov2021@gmail.com
# date        01.01.2017
# copyright   Erashov A.I.
# file        libs-list.cmake

# move to CMakeLists.txt
#include( "${U3_PATH_ROOT}/libs/proxy/_make/libs-proxy.cmake" )

include("${U3_PATH_ROOT}/libs/utility/_make/libs-utility.cmake")

include("${U3_PATH_ROOT}/libs/bufs/_make/libs-dbufs.cmake")

include("${U3_PATH_ROOT}/libs/link/_make/libs-links-link.cmake")
include("${U3_PATH_ROOT}/libs/ilink/_make/libs-links-ilink.cmake")

include("${U3_PATH_ROOT}/libs/events/_make/libs-events-events.cmake")
include("${U3_PATH_ROOT}/libs/events_base/_make/libs-events-base.cmake")
include("${U3_PATH_ROOT}/libs/events_log/_make/libs-events-log.cmake")
include("${U3_PATH_ROOT}/libs/events_media/_make/libs-events-media.cmake")
include("${U3_PATH_ROOT}/libs/events_msg/_make/libs-events-msg.cmake")
include("${U3_PATH_ROOT}/libs/events_gui/_make/libs-events-gui.cmake")
include("${U3_PATH_ROOT}/libs/events_http/_make/libs-events-http.cmake")
include("${U3_PATH_ROOT}/libs/events_storage/_make/libs-events-storage.cmake")
include("${U3_PATH_ROOT}/libs/events_user/_make/libs-events-user.cmake")

include("${U3_PATH_ROOT}/libs/core/_make/libs-cores-core.cmake")
include("${U3_PATH_ROOT}/libs/icore/_make/libs-cores-icore.cmake")

include("${U3_PATH_ROOT}/libs/properties/_make/libs-properties-properties.cmake")
include("${U3_PATH_ROOT}/libs/iproperties/_make/libs-properties-iproperties.cmake")

include("${U3_PATH_ROOT}/libs/optims/optim/_make/libs-optims-optim.cmake")
include("${U3_PATH_ROOT}/libs/optims/optim_convert/_make/libs-optims-convert-optim-gen-convert.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_s16bit_generic/_make/libs-optims-s16bit-optim-s16bit-generic.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_convert/_make/libs-optims-s16bit-optim-convert.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_bits/_make/libs-optims-s16bit-optim-bits.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_block/_make/libs-optims-s16bit-optim-block.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_conv/_make/libs-optims-s16bit-optim-conv.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_filter/_make/libs-optims-s16bit-optim-filter.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_freq/_make/libs-optims-s16bit-optim-freq.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_gen/_make/libs-optims-s16bit-optim-gen.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_statistics/_make/libs-optims-s16bit-optim-statistics.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_motion/_make/libs-optims-s16bit-optim-motion.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_ops/_make/libs-optims-s16bit-optim-ops.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_scale/_make/libs-optims-s16bit-optim-scalec.cmake")
