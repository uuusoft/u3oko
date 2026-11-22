# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        libs-list.cmake

# move to CMakeLists.txt
#include( "${U3_PATH_ROOT}/libs/proxy/libs-proxy.cmake" )

include("${U3_PATH_ROOT}/libs/utility/libs-utility.cmake")

include("${U3_PATH_ROOT}/libs/bufs/libs-dbufs.cmake")

include("${U3_PATH_ROOT}/libs/link/libs-links-link.cmake")
include("${U3_PATH_ROOT}/libs/ilink/libs-links-ilink.cmake")

include("${U3_PATH_ROOT}/libs/events/libs-events-events.cmake")
include("${U3_PATH_ROOT}/libs/events_base/libs-events-base.cmake")
include("${U3_PATH_ROOT}/libs/events_log/libs-events-log.cmake")
include("${U3_PATH_ROOT}/libs/events_media/libs-events-media.cmake")
include("${U3_PATH_ROOT}/libs/events_msg/libs-events-msg.cmake")
include("${U3_PATH_ROOT}/libs/events_gui/libs-events-gui.cmake")
include("${U3_PATH_ROOT}/libs/events_http/libs-events-http.cmake")
include("${U3_PATH_ROOT}/libs/events_storage/libs-events-storage.cmake")
include("${U3_PATH_ROOT}/libs/events_user/libs-events-user.cmake")

include("${U3_PATH_ROOT}/libs/core/libs-cores-core.cmake")
include("${U3_PATH_ROOT}/libs/icore/libs-cores-icore.cmake")

include("${U3_PATH_ROOT}/libs/properties/libs-properties-properties.cmake")
include("${U3_PATH_ROOT}/libs/iproperties/libs-properties-iproperties.cmake")

include("${U3_PATH_ROOT}/libs/optims/optim/libs-optims-optim.cmake")
include("${U3_PATH_ROOT}/libs/optims/optim_convert/libs-optims-convert-optim-gen-convert.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_s16bit_generic/libs-optims-s16bit-optim-s16bit-generic.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_convert/libs-optims-s16bit-optim-convert.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_bits/libs-optims-s16bit-optim-bits.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_block/libs-optims-s16bit-optim-block.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_conv/libs-optims-s16bit-optim-conv.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_filter/libs-optims-s16bit-optim-filter.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_freq/libs-optims-s16bit-optim-freq.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_gen/libs-optims-s16bit-optim-gen.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_statistics/libs-optims-s16bit-optim-statistics.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_motion/libs-optims-s16bit-optim-motion.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_ops/libs-optims-s16bit-optim-ops.cmake")
include("${U3_PATH_ROOT}/libs/optims/s16bit/optim_scale/libs-optims-s16bit-optim-scalec.cmake")

set(U3_LINK_EVENTS_LIBS
    events_user-lib
    events_gui-lib
    events_media-lib
    events_storage-lib
    events_http-lib
    events_msg-lib
    events_log-lib
    events_base-lib
    events-lib
)

set(U3_LINK_BASE_LIBS
    properties-lib
    bufs-lib
    core-lib
    link-lib
    utility-lib
)

set(U3_LINK_IBASE_LIBS
    icore-lib
    ilink-lib
    iproperties-lib
)
