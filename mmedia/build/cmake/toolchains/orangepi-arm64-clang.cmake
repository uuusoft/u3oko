# author      Erashov Anton erashov2026@proton.me
# date        03.04.2026
# copyright   Erashov A.I.
# file        orangepi-arm64-clang.cmake

# sudo apt install -y build-essential pkg-config binutils gcc-arm-linux-gnueabihf crossbuild-essential-armhf

set(U3_PLATFORM_NAME OrangePi)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(U3_SYSTEM_PROCESSOR_ARCH arm64)
set(ARM64 1)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_ASM_COMPILER clang)
set(U3_CXX_COMPILER_ARCH clang)
set(U3_TRIPLE aarch64-linux-gnu)
set(CMAKE_C_COMPILER_TARGET ${U3_TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${U3_TRIPLE})
set(CMAKE_ASM_COMPILER_TARGET ${U3_TRIPLE})
#set(CMAKE_ASM_COMPILER=${U3_TRIPLE})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} --target=${U3_TRIPLE})
set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -fuse-ld=lld)

#set(triple aarch64-linux-gnu)
#set(CMAKE_SYSROOT /path/to/aarch64-sysroot)

#set(CMAKE_C_COMPILER clang)
#set(CMAKE_C_COMPILER_TARGET ${triple})
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_COMPILER_TARGET ${triple})

# Use LLVM's lld linker
#set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")
#set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")

# Restrict CMake searches strictly to the target sysroot
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#et(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

#--sysroot
#--rtlib=compiler-rt, --stdlib=libc++) or GNU's equivalents (--rtlib=libgcc, --stdlib=libstdc++) provided inside your sysroot.

# Target triple for Clang
#set(TARGET_TRIPLE aarch64-linux-gnu)

# Specify Clang compilers and pass the target triple
#set(CMAKE_C_COMPILER clang)
#set(CMAKE_C_COMPILER_TARGET ${TARGET_TRIPLE})
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_CXX_COMPILER_TARGET ${TARGET_TRIPLE})

# Optional: Use LLVM's lld linker (often cleaner than GNU ld for cross-compiling)
#add_link_options(-fuse-ld=lld)

# Path to the target sysroot (contains target /usr/include and /usr/lib)
#set(CMAKE_SYSROOT /path/to/target/sysroot)
#set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})

# Restrict CMake searches for libraries/headers to the sysroot, but use host tools
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
