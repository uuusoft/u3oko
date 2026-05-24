# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        generics-base-id.cmake

u3_add_target_dylib(
  TARGET_NAME
  base_id-vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/base_id
  OUTPUT_NAME
  vdd_base_id
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
