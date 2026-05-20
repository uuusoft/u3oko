# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        filter-freq-domain.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

u3_add_target_dylib(
  TARGET_NAME
  vcleaner_freq_vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/filter_noise/freq_domain/source
  OUTPUT_NAME
  vfn_freq_domain
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  devents-dll
  doptim-dll
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
