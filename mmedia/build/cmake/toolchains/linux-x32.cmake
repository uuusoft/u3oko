# author      Erashov Anton erashov2026@proton.me
# date        19.08.2024
# copyright   Erashov A.I.
# file        linux-x32.cmake

set(U3_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x32)

set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -m32)
set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -m32)
