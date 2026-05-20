# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        vcodec-mjpg-codecs-dlls.cmake

u3_add_target_dylib(
  TARGET_NAME
  vcodec_mjpg_vvd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_mjpg
  OUTPUT_NAME
  vvd_vcodec_mjpg
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
  turbo_jpeg-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)

target_include_directories(vcodec_mjpg_vvd SYSTEM PRIVATE "${U3_INCLUDE_DIR_EXTERNAL_LIB_TURBO_JPEG}")
