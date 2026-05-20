# author      Erashov Anton erashov2026@proton.me
# date        02.09.2024
# file        android.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

set(U3_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_NAME Android)
set(U3_CMAKE_SYSTEM_VERSION 34)
#set( CMAKE_SYSTEM_PROCESSOR     aarch64 )
#set( CMAKE_SYSTEM_VERSION       34 )

if(NOT DEFINED CMAKE_ASM_COMPILER OR NOT ${CMAKE_ASM_COMPILER} STREQUAL "")
  set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
endif()

#set( CMAKE_C_COMPILER   aarch64-linux-gnu-gcc-11 )
#set( CMAKE_CXX_COMPILER aarch64-linux-gnu-g++-11 )
#set( CMAKE_ASM_COMPILER aarch64-linux-gnu-gcc-11 )

# https://github.com/OpenMathLib/OpenBLAS/issues/3931
#set( CMAKE_ASM_COMPILER         "$CC" )
#set( CMAKE_ASM_COMPILER_ID       "Clang" )

#set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
#set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
#set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
#set( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )
