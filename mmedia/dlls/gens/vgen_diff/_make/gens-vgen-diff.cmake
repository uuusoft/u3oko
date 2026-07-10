# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        gens-vgen-diff.cmake

u3_add_target_dylib(
  TARGET_NAME
  vgen_diff-vgd
  SOURCE_PATH
  ${U3_PATH_ROOT}/dlls/gens/vgen_diff
  OUTPUT_NAME
  vgd_vgen_diff
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  #optim-lib
  vgen_diff-vgd-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)

add_dependencies(vgen_diff-vgd vgen_diff-vgd-lib)
