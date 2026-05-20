# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        utils-vec2image.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

u3_add_target_dylib(
  TARGET_NAME
  vgen_vec2image-vgd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/utils/vec2image/source
  OUTPUT_NAME
  vut_vec2image
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  #optim-lib
  dbufs-dll
  DEPEND_TARGETS)
