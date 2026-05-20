# author      Erashov Anton erashov2026@proton.me
# date        08.03.2026
# copyright   Erashov A.I.
# file        linux-x64-clang.cmake

set(U3_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x64)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_ASM_COMPILER clang)

set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -m64)
set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -m64)
