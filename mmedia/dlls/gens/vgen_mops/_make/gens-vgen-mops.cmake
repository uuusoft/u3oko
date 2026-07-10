# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        gens-vgen-mops.cmake

u3_add_target_dylib(
  TARGET_NAME
  vgen_mops-vgd
  SOURCE_PATH
  ${U3_PATH_ROOT}/dlls/gens/vgen_mops
  OUTPUT_NAME
  vgd_vgen_mops
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  vgen_mops-vgd-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)

add_dependencies(vgen_mops-vgd vgen_mops-vgd-lib)
