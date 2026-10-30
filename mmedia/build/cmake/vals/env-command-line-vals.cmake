# author      Erashov Anton erashov2026@proton.me
# date        24.08.2024
# copyright   Erashov A.I.
# file        env-command-line-vals.cmake

set(U3_USE_COMMERCIAL_PART TRUE CACHE BOOL "use comercial parts")
set(U3_CPP_STANDARD "c++23" CACHE STRING "type cpp stardard c++17, c++20, c++23, c++26")
set(U3_SANITY_BUILD_TYPE "none" CACHE STRING "type sanity build [none/memory/ub/thread/address/etc]")
set(U3_USE_BOOST_SERIALIZTION FALSE CACHE BOOL "use boost serialization")

set(U3_HOST_NAME "localhost" CACHE STRING "host name")
set(U3_HOST_PORT "8011" CACHE STRING "host port")
set(U3_3RDLIBS_URL_SRC "http://${U3_HOST_NAME}:${U3_HOST_PORT}/src" CACHE STRING "local path to src")
set(U3_3RDLIBS_URL_BIN "http://${U3_HOST_NAME}:${U3_HOST_PORT}/bin" CACHE STRING "local path to bin")

set(U3_FORCE_RECOMPILE_3RDLIBS FALSE CACHE BOOL "force recompile 3rd libs")
set(U3_FORCE_USE_EXTURL_3RDLIBS FALSE CACHE BOOL "force get external source code for 3rd libs")
set(U3_FORCE_USE_LOCURL_3RDLIBS FALSE CACHE BOOL "force get local source code for 3rd libs")

set(U3_TARGET_PROPERTY_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "mvsc runtime")
set(U3_BUILD_MODULES_AS_LIBS FALSE CACHE BOOL "build module configuration, default as dll/so/dylib")
set(U3_USE_GIT_HASH_FOR_MARK_BUILD FALSE CACHE BOOL "use git hash for mark build for prodaction release yuopta")

#set(U3_DBG_EXTLIB_SKIP_SQLITE FALSE CACHE BOOL "debug skip sqlite")
#set(U3_DBG_EXTLIB_SKIP_DLIB FALSE CACHE BOOL "debug skip dlib")
set(U3_DBG_STOP_AFTER_DUMP_VARS FALSE CACHE BOOL "debug flag")
set(U3_DBG_STOP_BEFORE_COMPILE_EXTLIBS FALSE CACHE BOOL "debug flag")
set(U3_DBG_COMPILE_AT_BEGIN_EXTLIBS TRUE CACHE BOOL "debug flag")

set(U3_BUILD_TESTING FALSE CACHE BOOL "build with google tests")

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "build type aka Debug/Release/ReleaseWithDeb/etc")
set(CMAKE_COMPILE_WARNING_AS_ERROR FALSE CACHE BOOL "warning as errors")
set(CMAKE_MESSAGE_LOG_LEVEL AUTHOR_WARNING CACHE STRING "cmake level log")
set(CMAKE_VERBOSE_MAKEFILE FALSE CACHE BOOL "cmake debug")
#set(CMAKE_MESSAGE_LOG_LEVEL TRACE CACHE STRING "cmake level log")
#set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "cmake debug")
