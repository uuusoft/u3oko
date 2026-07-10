# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        gen-vgen-source-dlls.cmake

u3_add_target_dylib(
  TARGET_NAME
  gen_vgen-vsd
  SOURCE_PATH
  ${U3_PATH_ROOT}/dlls/sources/gen_vgen/source
  OUTPUT_NAME
  vsd_gen_vgen
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
