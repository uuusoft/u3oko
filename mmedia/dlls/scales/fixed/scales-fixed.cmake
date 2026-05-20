# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        scales-fixed.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

u3_add_target_dylib(
  TARGET_NAME
  vscaler_fixed_vsa
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/scales/fixed/source
  OUTPUT_NAME
  vsa_fixed
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  #optim-lib
  #optim_s16bit_generic-lib
  optim_scale-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
