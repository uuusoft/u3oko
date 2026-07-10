# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        detectors-move.cmake

u3_add_target_dylib(
  TARGET_NAME
  vdetect1-vdd
  SOURCE_PATH
  ${U3_PATH_ROOT}/dlls/detectors/detect_move
  OUTPUT_NAME
  vdd_detect_move
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  vgen_diff-vgd-lib
  vgen_mops-vgd-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
