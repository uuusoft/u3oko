# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        utils-mems.cmake

u3_add_target_dylib(
  TARGET_NAME
  mems-dll
  SOURCE_PATH
  ${U3_PATH_ROOT}/utils/mems
  OUTPUT_NAME
  mems
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  DEPEND_TARGETS
  ${U3_NAME_EXTLIB_BOOST_UTIL})
