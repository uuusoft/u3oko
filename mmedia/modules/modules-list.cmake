# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-list.cmake

include("${U3_BUILD_PATH_TO_LIBS}/modules/mlog/_make/modules-log.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/modules/mstorage/_make/modules-storage.cmake")

if(U3_COMMERCIAL_PART EQUAL 1)
    include("${U3_BUILD_PATH_TO_LIBS}/modules/mevents/_make/modules-events.cmake")
    include("${U3_BUILD_PATH_TO_LIBS}/modules/mhttp/_make/modules-http.cmake")
    include("${U3_BUILD_PATH_TO_LIBS}/modules/mdata/_make//modules-mdata.cmake")
    include("${U3_BUILD_PATH_TO_LIBS}/modules/mandroid_native/_make/modules-android-native-lib.cmake")
    include( "${U3_BUILD_PATH_TO_LIBS}/modules/mgui/_make/modules-gui.cmake" )
    #include("${U3_BUILD_PATH_TO_LIBS}/modules/u3_ai/_make//modules-ai.cmake")
endif()

# after all modules and libs for U3_LIBS_OUR_VARIABLE_LIST
include("${U3_BUILD_PATH_TO_LIBS}/modules/mappl/_make/modules-appl.cmake")
