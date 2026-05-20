# author      Erashov Anton erashov2026@proton.me
# date        29.08.2024
# copyright   Erashov A.I.
# file        u3-android-specific.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

include(./build/cmake/toolchains/android.cmake)

message(NOTICE "ANDROID_ABI=${ANDROID_ABI}")
message(NOTICE "ANDROID_ARM_MODE=${ANDROID_ARM_MODE}")
message(NOTICE "ANDROID_PLATFORM=${ANDROID_PLATFORM}")
message(NOTICE "ANDROID_STL=${ANDROID_STL}")
message(NOTICE "ANDROID_NDK=${ANDROID_NDK}")
#message(FATAL_ERROR "DEBUG STOP")

set(U3_BUILD_MODULES_AS_LIBS 1 CACHE BOOL "force for Android" FORCE)
set(U3_LIBS_SYSTEM_STATIC_LIST ${U3_LIBS_SYSTEM_STATIC_LIST} camera2ndk mediandk)
set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DANDROID_ABI=${ANDROID_ABI} -DANDROID_ARM_MODE=${ANDROID_ARM_MODE} -DU3_OS_ANDROID=1)
set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -std=${U3_CPP_STANDARD})

set(U3_SHARED_LINK_OPTIONS_CPP
    ${U3_SHARED_LINK_OPTIONS_CPP}
    -ldl
    ${android-cpufeatures-lib}
    android
    ${android-app-glue-lib}
    ${android-log-lib})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(U3_PREFIX_LIB_NAME lib)
set(U3_SUFFIX_LIB_NAME a)
set(U3_SUFFIX_DLL_NAME so)
set(U3_ANDROID_NDK_LIB_PATH "%{ANDROID_NDK}/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/lib/aarch64-linux-android")
#set( U3_SHARED_COMPILE_DEF_CPP         ${U3_SHARED_COMPILE_DEF_CPP}        "-DBOOST_INTERPROCESS_SHARED_DIR_PATH=\"/sdcard\"" )
#set( U3_SHARED_COMPILE_DEF_CPP         ${U3_SHARED_COMPILE_DEF_CPP}        "BOOST_INTERPROCESS_SHARED_DIR_FUNC")

find_library(android-log-lib log REQUIRED)
find_library(android-jnigraphics-lib jnigraphics REQUIRED)

include_directories(${ANDROID_NDK}/sources/android/native_app_glue)
add_library(android-app-glue-lib STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

include_directories(./ndk_helper ${ANDROID_NDK}/sources/android/cpufeatures)
add_library(android-cpufeatures-lib STATIC ${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c)

include_directories("${U3_BUILD_PATH_TO_LIBS}/../")

message(NOTICE "${U3_MARK_REFACT} merge directories for android and othes")
file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/appls/u3oko/android/app/src/main/assets/service#0")
file(COPY "${CMAKE_SOURCE_DIR}/assets/xmls/templates" DESTINATION "${CMAKE_SOURCE_DIR}/appls/u3oko/android/app/src/main/assets/service#0")

file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/appls/u3oko/android/app/src/main/assets/templates")
file(COPY "${CMAKE_SOURCE_DIR}/assets/xmls/templates" DESTINATION "${CMAKE_SOURCE_DIR}/appls/u3oko/android/app/src/main/assets")
