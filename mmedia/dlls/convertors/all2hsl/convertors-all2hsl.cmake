# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        convertors-all2hsl.cmake

u3_add_target_dylib(
  TARGET_NAME
  hsl-vcd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/convertors/all2hsl/source
  OUTPUT_NAME
  vcd_all2hsl
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
