# author      Erashov Anton erashov2026@proton.me
# date        21.03.2026
# copyright   Erashov A.I.
# file        u3-stb-lib.cmake

include("./build/cmake/3rdlibs/stb/u3-stb-lib-values.cmake")

set(U3_3RDLIB_NAME_STB_UTIL ${U3_3RDLIB_NAME_STB}-util)

u3_project_add(
    PROJECT_NAME ${U3_3RDLIB_NAME_STB_UTIL}
    #PROJECT_VERSION       "v${U3_3RDLIB_VER_STB}"
    BIN_URL ${U3_3RDLIB_ESRC_URL_STB_BIN}
    NAME_BIN_MD5 U3_3RDLIB_STB${U3_3RDLIB_VER_STB_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}
    BIN_MD5 ${U3_3RDLIB_STB${U3_3RDLIB_VER_STB_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}}
    SRC_URL ${U3_3RDLIB_OSRC_URL_STB}
    SRC_MD5 ${U3_3RDLIB_STB_MD5}
    ESRC_URL ${U3_3RDLIB_ESRC_URL_STB_SRC}
    ESRC_MD5 ${U3_3RDLIB_STB_EXT_MD5}
    PATCH_CMD ""
    USE_HTTP_FOR_ESRC FALSE
    BUILD_IN_SOURCE FALSE
    IT_CMAKE_PROJECT FALSE
    FORCE_COMPILE FALSE
    EXT_CMAKE_ARGS "")

ExternalProject_Get_Property(${U3_3RDLIB_NAME_STB_UTIL} install_dir)

if (${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_STB ${install_dir}/src/stb-util)
  set(U3_INSTALL_DIR_EXTLIB_STB ${install_dir}/src/stb-util/${U3_3RDLIB_STB_FILE_NAME})
else ()
  set(U3_INCLUDE_DIR_EXTLIB_STB ${install_dir}/src/stb-util)
  set(U3_INSTALL_DIR_EXTLIB_STB ${install_dir}/src/stb-util-build/${U3_3RDLIB_STB_FILE_NAME})
endif ()

add_library(stb-lib INTERFACE)
add_dependencies(stb-lib ${U3_3RDLIB_NAME_STB_UTIL})
