# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        02.09.2024
# file        android.cmake
# U3_COMMERCIAL_PART

set(U3_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_NAME Android)
set(U3_CMAKE_SYSTEM_VERSION 34)
#set( CMAKE_SYSTEM_PROCESSOR     aarch64 )
#set( CMAKE_SYSTEM_VERSION       34 )

if(NOT DEFINED CMAKE_ASM_COMPILER OR NOT ${CMAKE_ASM_COMPILER} STREQUAL "")
  set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
endif()
