# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        29.08.2024
# copyright   Erashov A.I.
# file        u3-windows-specific.cmake

set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -std:${U3_CPP_STANDARD})
set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DUNICODE=1 -D_UNICODE=1 -DU3_OS_WIN32_DESKTOP=1)
set(U3_LIBS_SYSTEM_STATIC_LIST ${U3_LIBS_SYSTEM_STATIC_LIST} Shcore.lib Shell32.lib user32.lib gdi32.lib)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(U3_PREFIX_LIB_NAME "")
set(U3_SUFFIX_LIB_NAME lib)
set(U3_SUFFIX_DLL_NAME dll)

#set( U3_TARGET_PROPERTY_MSVC_RUNTIME_LIBRARY      "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL" CACHE FORCE )
#set( U3_SHARED_LINK_OPTIONS_CPP                   ${U3_SHARED_LINK_OPTIONS_CPP}       -Wl, --no-undefined  )
