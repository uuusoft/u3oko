# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        appls-u3oko.cmake

u3_add_target_dylib(
  TARGET_NAME
  appl-u3oko
  SOURCE_PATH
  ""
  OUTPUT_NAME
  appl_u3oko
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  TRUE
  SOURCE_FILES
  ${U3_BUILD_PATH_TO_LIBS}/appls/u3oko/appl/u3oko-appl.cpp
  ${U3_BUILD_PATH_TO_LIBS}/appls/u3oko/appls-u3oko-main.cpp
  EXTENDED_LIBS
  ilink-lib
  optim-lib
  icore-lib
  iproperties-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
