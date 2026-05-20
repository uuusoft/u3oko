# author      Erashov Anton erashov2026@proton.me
# date        24.08.2024
# copyright   Erashov A.I.
# file        env-command-line-vals.cmake

set(U3_USE_COMMERCIAL_PART TRUE CACHE BOOL "use comercial parts")
set(U3_CPP_STANDARD "c++20" CACHE STRING "type cpp stardard c++17, c++20, c++23, c++26")
set(U3_SANITY_BUILD_TYPE "none" CACHE STRING "type sanity build [none/memory/ub/thread/address/etc]")
set(U3_URL_TO_EXTERNAL_LIBS_SRC http://192.168.88.211:8011/repository/u3soft/3rd-libs/src CACHE STRING "path to src")
set(U3_URL_TO_EXTERNAL_LIBS_BIN http://192.168.88.211:8011/repository/u3soft/3rd-libs/bin CACHE STRING "path to bin")
set(U3_FORCE_COMPILE_ALL_EXT_LIBS FALSE CACHE BOOL "force recompile ext libs")
set(U3_FORCE_USE_EXT_SOURCE_FOR_EXT_LIBS FALSE CACHE BOOL "force get external source for ext libs")
set(U3_FORCE_USE_LOCAL_SOURCE_FOR_EXT_LIBS FALSE CACHE BOOL "force get local source for ext libs")
set(U3_TARGET_PROPERTY_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE STRING "mvsc  runtime")
set(U3_BUILD_MODULES_AS_LIBS FALSE CACHE BOOL "default build as dll/so/dylib")
set(U3_USE_GIT_HASH_FOR_MARK_BUILD FALSE CACHE BOOL "use git hash for mark build")

set(U3_DBG_EXTERNAL_LIB_SKIP_SQLITE FALSE CACHE BOOL "debug skip sqlite")
set(U3_DBG_EXTERNAL_LIB_SKIP_DLIB FALSE CACHE BOOL "debug skip dlib")
set(U3_DBG_STOP_AFTER_DUMP_VARS FALSE CACHE BOOL "debug flag")
set(U3_DBG_STOP_BEFORE_COMPILE_EXT_LIBS FALSE CACHE BOOL "debug flag")
set(U3_DBG_FORCE_COMPILE_AT_BEGIN_ALL_EXT_LIBS FALSE CACHE BOOL "debug flag")

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "build type [Debug/Release/ReleaseWithDeb/etc]")
set(CMAKE_COMPILE_WARNING_AS_ERROR FALSE CACHE BOOL "warning as errors")
set(CMAKE_MESSAGE_LOG_LEVEL AUTHOR_WARNING CACHE STRING "cmake level log")
set(CMAKE_VERBOSE_MAKEFILE FALSE CACHE BOOL "cmake debug")
