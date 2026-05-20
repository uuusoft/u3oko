# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        uplifterss-vgradient.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

u3_add_target_dylib(
  TARGET_NAME
  vgradient_vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/uplifters/vgradient/source
  OUTPUT_NAME
  vdd_vgradient
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
