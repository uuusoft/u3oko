# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        gens-vgen-conv3_11.cmake

u3_add_target_dylib(
  TARGET_NAME
  vgen_conv3_11-vgd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_conv3_11/source
  OUTPUT_NAME
  vgd_vgen_conv3_11
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
