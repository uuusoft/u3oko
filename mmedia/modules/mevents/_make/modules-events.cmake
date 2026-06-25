# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        modules-events.cmake

u3_add_target_dylib(
  TARGET_NAME
  module-mevents
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/modules/mevents
  OUTPUT_NAME
  mpl_mevents
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
  #u3-sqlitecpp-lib
  #u3-sqlite-lib
  DEPEND_TARGETS
  ${U3_NAME_SQLITE_UTIL}
  ${U3_NAME_SQLITECPP_UTIL}
  dbufs-dll)

#message(FATAL_ERROR "U3_INCLUDE_DIR_EXTLIB_SQLITECPP=${U3_INCLUDE_DIR_EXTLIB_SQLITECPP}")
target_include_directories(module-mevents PUBLIC "${U3_INCLUDE_DIR_EXTLIB_SQLITE}" "${U3_INCLUDE_DIR_EXTLIB_SQLITECPP}")
