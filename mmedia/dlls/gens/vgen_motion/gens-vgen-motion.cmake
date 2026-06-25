# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        gens-vgen-motion.cmake

u3_add_target_dylib(
  TARGET_NAME
  vgen_motion-vgd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/gens/vgen_motion/source
  OUTPUT_NAME
  vgd_vgen_motion
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
