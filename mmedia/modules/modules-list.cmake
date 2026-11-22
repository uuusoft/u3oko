# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-list.cmake

include("${U3_PATH_ROOT}/modules/mlog/modules-log.cmake")
include("${U3_PATH_ROOT}/modules/mevents/modules-events.cmake")
include("${U3_PATH_ROOT}/modules/mhttp/modules-http.cmake")

if (U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/modules/mstorage/modules-storage.cmake")
  include("${U3_PATH_ROOT}/modules/mdata//modules-mdata.cmake")
  include("${U3_PATH_ROOT}/modules/mgui/modules-gui.cmake")
  include("${U3_PATH_ROOT}/modules/musers/modules-musers.cmake")
  include("${U3_PATH_ROOT}/modules/mandroid_native/modules-android-native-lib.cmake")
  include("${U3_PATH_ROOT}/modules/mai//modules-ai.cmake")
endif ()

# after all modules and libs for U3_SELECTED_LIBS_VARIABLE_LIST
include("${U3_PATH_ROOT}/modules/mappl/modules-appl.cmake")
