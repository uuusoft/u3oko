# author      Erashov Anton erashov2026@proton.me
# date        19.08.2024
# copyright   Erashov A.I.
# file        windows-x32-msv.cmake
# https://stackoverflow.com/questions/31148943/option-to-force-either-32-bit-or-64-bit-build-with-cmake

set(U3_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_GENERATOR_PLATFORM Win32 CACHE INTERNAL "Force 32-bit compilation")
set(CMAKE_SYSTEM_PROCESSOR Win32)
