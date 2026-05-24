# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        23.08.2018
# copyright   Erashov A.I.
# file        vcodec-x264-codecs-dlls.cmake

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
  #message(WARNING "Unsupported OS received " ${U3_SYSTEM_NAME})
  #return()
endif()

if(NOT U3_DBG_FORCE_COMPILE_AT_BEGIN_ALL_EXT_LIBS)
  include("./build/cmake/libs/openh264/u3-openh264-lib.cmake")
endif()

u3_add_target_dylib(
  TARGET_NAME
  vcodec_x264_vvd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_x264
  OUTPUT_NAME
  vvd_vcodec_x264
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  #optim-lib
  #optim_s16bit_generic-lib
  #optim_freq-lib
  codec_gen-lib
  codec_funcs-lib
  openh264-lib
  dbufs-dll
  DEPEND_TARGETS
  openh264-util)

#message(FATAL_ERROR "U3_INCLUDE_DIR_EXTERNAL_LIB_OPENH264=${U3_INCLUDE_DIR_EXTERNAL_LIB_OPENH264}")
target_include_directories(vcodec_x264_vvd SYSTEM PRIVATE "${U3_INCLUDE_DIR_EXTERNAL_LIB_OPENH264}")
