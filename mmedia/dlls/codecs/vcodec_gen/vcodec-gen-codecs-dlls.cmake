# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        vcodec-gen-codecs-dlls.cmake
# U3_COMMERCIAL_PART

u3_add_target_dylib(
  TARGET_NAME
  vcodec_gen-vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/codecs/vcodec_gen/source
  OUTPUT_NAME
  vdd_vcodec_gen
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  codec_gen-lib
  codec_funcs-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
