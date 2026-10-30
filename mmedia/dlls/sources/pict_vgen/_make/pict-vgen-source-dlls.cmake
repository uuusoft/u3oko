# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017-01.01.2024
# copyright   Erashov A.I.
# file        pict-vgen-source-dlls.cmake

#if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
#  return()
#endif()

if (NOT U3_DBG_COMPILE_AT_BEGIN_EXTLIBS)
  include("./build/cmake/3rdlibs/stb/u3-stb-lib.cmake")
endif ()

u3_add_target_dylib(
    TARGET_NAME
    pict_vgen-vss
    SOURCE_PATH
    ${U3_PATH_ROOT}/dlls/sources/pict_vgen/source
    OUTPUT_NAME
    vss_pict_vgen
    FORCE_TO_DYLIB
    FALSE
    USE_EXACTLY_SOURCE_FILES
    FALSE
    SOURCE_FILES
    ""
    EXTENDED_LIBS
    gen_lib-lib
    dbufs-dll
    DEPEND_TARGETS
    dbufs-dll
    stb-lib)
#add_dependencies(std-lib ${U3_3RDLIB_NAME_STB_UTIL})

#message(FATAL_ERROR "U3_INCLUDE_DIR_EXTLIB_STB=${U3_INCLUDE_DIR_EXTLIB_STB}")
target_include_directories(pict_vgen-vss PUBLIC "${U3_INCLUDE_DIR_EXTLIB_STB}")
