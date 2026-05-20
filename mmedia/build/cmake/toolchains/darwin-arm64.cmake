# author      Erashov Anton erashov2026@proton.me
# date        19.08.2024
# copyright   Erashov A.I.
# file        darwin-arm64.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

set(U3_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

if(NOT DEFINED CMAKE_ASM_COMPILER OR NOT ${CMAKE_ASM_COMPILER} STREQUAL "")
  set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
endif()

#message( FATAL_ERROR "CMAKE_ASM_COMPILER=${CMAKE_ASM_COMPILER}" )

#set( CMAKE_C_COMPILER   aarch64-linux-gnu-gcc-11 )
#set( CMAKE_CXX_COMPILER aarch64-linux-gnu-g++-11 )
#set( CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc-11 )

# https://github.com/OpenMathLib/OpenBLAS/issues/3931
#set( CMAKE_ASM_COMPILER         "$CC" )
#set( CMAKE_ASM_COMPILER_ID       "Clang" )
