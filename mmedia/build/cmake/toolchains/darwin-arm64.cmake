# author      Erashov Anton erashov2026@proton.me
# date        19.08.2024
# copyright   Erashov A.I.
# file        darwin-arm64.cmake

set(U3_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

if(NOT DEFINED CMAKE_ASM_COMPILER OR NOT ${CMAKE_ASM_COMPILER} STREQUAL "")
  set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
endif()
