# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        19.08.2024
# copyright   Erashov A.I.
# file        linux-x64-gcc.cmake

set(U3_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x64)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_ASM_COMPILER gcc)

set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -m64)
set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -m64)
