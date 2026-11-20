# author      Erashov Anton erashov2026@proton.me
# date        19.08.2024
# copyright   Erashov A.I.
# file        raspberry-arm-gcc.cmake

# https://github.com/raspberrypi/userland
# https://hackaday.com/2016/02/03/code-craft-cross-compiling-for-the-raspberry-pi/
# sudo apt-get install build-essential
# sudo apt-get install g++-arm-linux-gnueabihf
# sudo apt-get install gdb-multiarch

set(U3_PLATFORM_NAME Raspberry)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(U3_SYSTEM_PROCESSOR_ARCH arm)
set(ARM64 0)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_ASM_COMPILER arm-linux-gnueabihf-gcc)
set(U3_CXX_COMPILER_ARCH gcc)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
