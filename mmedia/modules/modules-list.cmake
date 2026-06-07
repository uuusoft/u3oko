# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-list.cmake

include("${U3_BUILD_PATH_TO_LIBS}/modules/uuu_log/_make/modules-log.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/modules/uuu_storage/_make/modules-storage.cmake")

if(U3_COMMERCIAL_PART EQUAL 1)
    include("${U3_BUILD_PATH_TO_LIBS}/modules/u3_events/_make/modules-events.cmake")
    include("${U3_BUILD_PATH_TO_LIBS}/modules/uuu_http/_make/modules-http.cmake")
    include("${U3_BUILD_PATH_TO_LIBS}/modules/uuu_mdata/_make//modules-mdata.cmake")
    #include("${U3_BUILD_PATH_TO_LIBS}/modules/u3_ai/_make//modules-ai.cmake")

    message(NOTICE "${U3_MARK_TODO}disable gui")
    # disabled
    # include( "${U3_BUILD_PATH_TO_LIBS}/modules/uuu_gui/_make/modules-gui.cmake" )
    include("${U3_BUILD_PATH_TO_LIBS}/modules/uuu_android_native_lib/_make/modules-android-native-lib.cmake")
endif()

# after all modules and libs for U3_LIBS_OUR_VARIABLE_LIST
include("${U3_BUILD_PATH_TO_LIBS}/modules/uuu_appl/_make/modules-appl.cmake")
