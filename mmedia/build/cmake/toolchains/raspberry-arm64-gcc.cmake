# author      Erashov Anton erashov2026@proton.me
# date        19.08.2024
# copyright   Erashov A.I.
# file        raspberry-arm64-gcc.cmake

# raspberrypi 64 bit
# https://stackoverflow.com/questions/61771494/how-do-i-cross-compile-llvm-clang-for-aarch64-on-x64-host
# apt install g++-10-aarch64-linux-gnu libstdc++-10-dev-arm64-cross gcc-10 g++-10
# apt install cmake ninja-build python3
# sudo apt install gcc-13 gcc-13-aarch64-linux-gnu
# !!! последние две строчки
# sudo apt-get install gcc-aarch64-linux-gnu
# sudo apt-get install g++-aarch64-linux-gnu

# apt install g++-11-aarch64-linux-gnu libstdc++-11-dev-arm64-cross gcc-11 g++-11
# CC=aarch64-linux-gnu-gcc-11 CXX=aarch64-linux-gnu-g++-11 cmake ../llvm \
#    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
#    -DLLVM_ENABLE_ASSERTIONS=On \
#    -DCMAKE_CROSSCOMPILING=True \
#    -DCMAKE_INSTALL_PREFIX=install \
#    -DLLVM_DEFAULT_TARGET_TRIPLE=aarch64-linux-gnueabihf \
#    -DLLVM_TARGET_ARCH=AArch64 \
#    -DLLVM_TARGETS_TO_BUILD=AArch64 \
#    -DCMAKE_CXX_FLAGS='-march=armv8-a -mtune=cortex-a72' \
#    -GNinja \
#    -DLLVM_ENABLE_PROJECTS='clang;compiler-rt;lld;clang-tools-extra' \
#    -DLLVM_TABLEGEN=/mnt/repos/llvm-project/build-host/bin/llvm-tblgen \
#    -DCLANG_TABLEGEN=/mnt/repos/llvm-project/build-host/bin/clang-tblgen \
#    -DLLVM_BUILD_LLVM_DYLIB=On \
#    -DLLVM_LINK_LLVM_DYLIB=On \
#    -DLLVM_INSTALL_TOOLCHAIN_ONLY=On

#add_definitions("-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -marm")

#SET(CMAKE_SYSTEM_NAME Linux)
#SET(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
#SET(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
#SET(CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc)
#SET(CMAKE_SYSTEM_PROCESSOR arm)

##ADD_DEFINITIONS("-march=armv6")
##add_definitions("-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -marm")

## rdynamic means the backtrace should work
#IF (CMAKE_BUILD_TYPE MATCHES "Debug")
#   add_definitions(-rdynamic)
#ENDIF()

# avoids annoying and pointless warnings from gcc
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -U_FORTIFY_SOURCE")
#SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -c")

set(U3_SYSTEM_NAME Raspberry)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(ARM64 1)

set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
