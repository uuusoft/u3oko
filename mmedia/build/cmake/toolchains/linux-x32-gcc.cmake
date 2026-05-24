# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        20.08.2024
# copyright   Erashov A.I.
# file        linux-x32-gcc.cmake

# https://stackoverflow.com/questions/7412548/error-gnu-stubs-32-h-no-such-file-or-directory-while-compiling-nachos-source
# opensuse sudo zypper install glibc-devel-32bit

set(U3_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x32)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_ASM_COMPILER gcc)

# -mllvm --x86-asm-syntax=intel
set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -m32)
set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -m32)
