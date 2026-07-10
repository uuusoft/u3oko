# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-list.cmake

include("${U3_PATH_ROOT}/modules/mlog/_make/modules-log.cmake")
include("${U3_PATH_ROOT}/modules/mevents/_make/modules-events.cmake")
include("${U3_PATH_ROOT}/modules/mhttp/_make/modules-http.cmake")

if(U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_PATH_ROOT}/modules/mstorage/_make/modules-storage.cmake")
  include("${U3_PATH_ROOT}/modules/mdata/_make//modules-mdata.cmake")
  include("${U3_PATH_ROOT}/modules/mgui/_make/modules-gui.cmake")
  include("${U3_PATH_ROOT}/modules/musers/_make/modules-musers.cmake")
  include("${U3_PATH_ROOT}/modules/mandroid_native/_make/modules-android-native-lib.cmake")
  #include("${U3_PATH_ROOT}/modules/u3_ai/_make//modules-ai.cmake")
endif()

# after all modules and libs for U3_LIBS_OUR_VARIABLE_LIST
include("${U3_PATH_ROOT}/modules/mappl/_make/modules-appl.cmake")
