# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        terminals-video-sender.cmake

u3_add_target_dylib(
  TARGET_NAME
  msg_video-vdd
  SOURCE_PATH
  ${U3_BUILD_PATH_TO_LIBS}/dlls/terminals/video_sender
  OUTPUT_NAME
  vts_video_sender
  FORCE_TO_DYLIB
  FALSE
  USE_EXACTLY_SOURCE_FILES
  FALSE
  SOURCE_FILES
  ""
  EXTENDED_LIBS
  #optim-lib
  dbufs-dll
  DEPEND_TARGETS
  dbufs-dll)
