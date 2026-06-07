# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-http.cmake
# U3_COMMERCIAL_PART

u3_add_target_dylib(
  TARGET_NAME
  module-mhttp
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/modules/mhttp
  OUTPUT_NAME
  mpl_mhttp
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
  openssl-lib
  crypto-lib
  DEPEND_TARGETS
  openssl-util
  dbufs-dll)

#message( FATAL_ERROR "U3_INCLUDE_DIR_EXTERNAL_LIB_OPENSSL=${U3_INCLUDE_DIR_EXTERNAL_LIB_OPENSSL}")
target_include_directories(module-mhttp PUBLIC "${U3_INCLUDE_DIR_EXTERNAL_LIB_OPENSSL}")
