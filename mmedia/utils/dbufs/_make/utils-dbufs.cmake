# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        utils-dbufs.cmake

u3_add_target_dylib(
  TARGET_NAME
  dbufs-dll
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/utils/dbufs
  OUTPUT_NAME
  dbufs
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  DEPEND_TARGETS
  ${U3_NAME_EXTERNAL_LIB_BOOST_UTIL}
)
