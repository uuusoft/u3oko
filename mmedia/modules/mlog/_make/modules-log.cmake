# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-log.cmake

u3_add_target_dylib(
  TARGET_NAME
  module-mlog
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/modules/mlog
  OUTPUT_NAME
  mpl_mlog
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  ilink-lib
  optim-lib
  icore-lib
  iproperties-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
