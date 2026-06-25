# author      Erashov Anton erashov2026@proton.me
# date        20.02.2026
# copyright   Erashov A.I.
# file        v4l2-vgen-source-dlls.cmake

if(NOT ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} AND NOT ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} AND NOT ${U3_SYSTEM_NAME} STREQUAL
                                                                                                                             ${U3_SYSTEM_NAME_ORANGE_PI})
  message(WARNING "Unsupported OS received " ${U3_SYSTEM_NAME})
  return()
endif()

if(NOT U3_DBG_COMPILE_AT_BEGIN_EXTLIBS)
  include("./build/cmake/libs/libv4l2cpp/u3-libv4l2cpp-lib.cmake")
endif()

u3_add_target_dylib(
  TARGET_NAME
  v4l2_vgen-vss
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/sources/v4l2_vgen
  OUTPUT_NAME
  vss_v4l2_vgen
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  gen_lib-lib
  v4l2cpp-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)

target_include_directories(v4l2_vgen-vss PUBLIC "${U3_INCLUDE_DIR_EXTLIB_V4L2CPP}")
