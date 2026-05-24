# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-storage.cmake

u3_add_target_dylib(
  TARGET_NAME
  module-uuu_storage
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/modules/uuu_storage
  OUTPUT_NAME
  mpl_uuu_storage
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
  ${U3_NAME_SQLITE_UTIL}
  dbufs-dll)

target_include_directories(module-uuu_storage PUBLIC "${U3_INCLUDE_DIR_EXTERNAL_LIB_SQLITE}")
