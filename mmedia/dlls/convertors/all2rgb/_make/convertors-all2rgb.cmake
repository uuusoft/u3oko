# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        convertors-all2rgb.cmake

u3_add_target_dylib(
  TARGET_NAME
  all2rgb-vcd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/convertors/all2rgb
  OUTPUT_NAME
  vcd_all2rgb
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  optim-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
