# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        utils-mem-funcs.cmake

u3_add_target_dylib(
  TARGET_NAME
  mem_funcs-dll
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/utils/mem_funcs
  OUTPUT_NAME
  mem_funcs
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  DEPEND_TARGETS
  ${U3_NAME_EXTLIB_BOOST_UTIL}
)
