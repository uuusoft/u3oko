# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        19.08.2024
# copyright   Erashov A.I.
# file        raspberry-arm.cmake

# https://github.com/raspberrypi/userland
# https://hackaday.com/2016/02/03/code-craft-cross-compiling-for-the-raspberry-pi/
# sudo apt-get install build-essential
# sudo apt-get install g++-arm-linux-gnueabihf
# sudo apt-get install gdb-multiarch

set(U3_SYSTEM_NAME Raspberry)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(ARM64 0)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_ASM_COMPILER arm-linux-gnueabihf-gcc)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
