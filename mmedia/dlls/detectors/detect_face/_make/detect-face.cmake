# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        detect-face.cmake

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_DARWIN})
  message(NOTICE "${U3_MARK_TODO} add support dlib for Darwin")
  return()
endif()

set(U3_LOCAL_DETECT_FACE_LIB_EXTENDED_LIBS turbo_jpeg-lib dbufs-dll)
#set(U3_LOCAL_DETECT_FACE_LIB_EXTENDED_LIBS optim-lib turbo_jpeg-lib dbufs-dll)
set(U3_LOCAL_DETECT_FACE_LIB_DEPEND_TARGETS turbo_jpeg-util dbufs-dll)

if(U3_DBG_EXTERNAL_LIB_SKIP_DLIB)
  set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DU3_SKIP_DLIB=1)
else()
  if(NOT U3_DBG_FORCE_COMPILE_AT_BEGIN_ALL_EXT_LIBS)
    include("./build/cmake/libs/dlib/u3-dlib-lib.cmake")
  endif()
  set(U3_LOCAL_DETECT_FACE_LIB_DEPEND_TARGETS ${U3_LOCAL_DETECT_FACE_LIB_DEPEND_TARGETS} dlib-util)
  set(U3_LOCAL_DETECT_FACE_LIB_EXTENDED_LIBS ${U3_LOCAL_DETECT_FACE_LIB_EXTENDED_LIBS} dlib-lib)
endif()

set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DU3_LIBS_ENABLE_DETECT_FACE_VDD=1)

u3_add_target_dylib(
  TARGET_NAME
  detect-face-vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/detectors/detect_face
  OUTPUT_NAME
  vdd_detect_face
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  ${U3_LOCAL_DETECT_FACE_LIB_EXTENDED_LIBS}
  DEPEND_TARGETS
  dbufs-dll
  ${U3_LOCAL_DETECT_FACE_LIB_DEPEND_TARGETS})

target_include_directories(detect-face-vdd SYSTEM PRIVATE "${U3_INCLUDE_DIR_EXTERNAL_LIB_DLIB}")
target_include_directories(detect-face-vdd SYSTEM PRIVATE "${U3_INCLUDE_DIR_EXTERNAL_LIB_TURBO_JPEG}")
