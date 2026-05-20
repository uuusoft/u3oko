# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-http.cmake

u3_add_target_dylib(
  TARGET_NAME
  module-uuu_http
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/modules/uuu_http
  OUTPUT_NAME
  mpl_uuu_http
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
target_include_directories(module-uuu_http PUBLIC "${U3_INCLUDE_DIR_EXTERNAL_LIB_OPENSSL}")
