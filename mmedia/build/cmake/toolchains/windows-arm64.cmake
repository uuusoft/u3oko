# author      Erashov Anton erashov2026@proton.me
# date        19.08.2024
# copyright   Erashov A.I.
# file        windows-arm64.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

set(U3_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc-11)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++-11)
set(CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc-11)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
