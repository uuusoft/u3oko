# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        fake-vgen-source-dlls.cmake

u3_add_target_dylib(
  TARGET_NAME
  fake_vgen-vss
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/sources/fake_vgen/source
  OUTPUT_NAME
  vss_fake_vgen
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  gen_lib-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
