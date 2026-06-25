# author      Erashov Anton erashov2026@proton.me
# date        29.08.2024
# copyright   Erashov A.I.
# file        u3-linux-specific.cmake

set(U3_LIBS_SYSTEM_STATIC_LIST ${U3_LIBS_SYSTEM_STATIC_LIST} X11)
set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -std=${U3_CPP_STANDARD} -frtti -fexceptions -pthread)
set(U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -Wl,--no-undefined -Wl,-rpath='${ORIGIN}' -lpthread -ldl -lrt)
set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DU3_OS_LINUX=1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(U3_PREFIX_LIB_NAME lib)
set(U3_SUFFIX_LIB_NAME a)
set(U3_SUFFIX_DLL_NAME so)

# mmedia/dlls/sources/desk_vgen/source/impls/linux/capture-desk-impl-linux.hpp
# for Ubuntu
# sudo apt update
# sudo apt install libx11-dev
find_package(X11 REQUIRED)
