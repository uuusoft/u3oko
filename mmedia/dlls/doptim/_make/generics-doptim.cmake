# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        generics-doptim.cmake

u3_add_target_dylib(
  TARGET_NAME
  doptim-dll
  SOURCE_PATH
  ${U3_PATH_ROOT}/dlls/doptim
  OUTPUT_NAME
  vdd_doptim
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  optim-lib
  optim_gen_convert-lib
  optim_convert-lib
  optim_bits-lib
  optim_block-lib
  optim_conv-lib
  optim_filter-lib
  optim_freq-lib
  optim_gen-lib
  optim_statistics-lib
  optim_motion-lib
  optim_ops-lib
  optim_scale-lib
  optim_s16bit_generic-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
