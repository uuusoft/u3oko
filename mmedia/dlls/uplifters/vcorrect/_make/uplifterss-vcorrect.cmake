# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        uplifterss-vcorrect.cmake

u3_add_target_dylib(
  TARGET_NAME
  vcorrect_vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/uplifters/vcorrect
  OUTPUT_NAME
  vdd_vcorrect
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  #optim-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
