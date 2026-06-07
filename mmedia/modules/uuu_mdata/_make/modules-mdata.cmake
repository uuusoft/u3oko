# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-mdata.cmake
# U3_COMMERCIAL_PART

u3_add_target_dylib(
  TARGET_NAME
  module-uuu_mdata
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/modules/uuu_mdata
  OUTPUT_NAME
  mpl_uuu_mdata
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
