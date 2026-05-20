# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        filter-space-domain.cmake

u3_add_target_dylib(
  TARGET_NAME
  vcleaner_space_vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/filter_noise/space
  OUTPUT_NAME
  vfn_space
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
