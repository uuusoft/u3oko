# author      Erashov Anton erashov2026@proton.me
# date        21.03.2026
# copyright   Erashov A.I.
# file        u3-stb-lib.cmake

include("./build/cmake/libs/stb/u3-stb-lib-values.cmake")

set(U3_NAME_EXTLIB_STB_UTIL ${U3_NAME_EXTLIB_STB}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTLIB_STB_UTIL}
  #PROJECT_VERSION       "v${U3_VERSION_EXTLIB_STB}"
  URL_TO_BIN
  ${U3_URL_TO_EXTLIB_STB_BIN}
  NAME_BIN_MD5
  U3_EXTLIB_STB${U3_VERSION_EXTLIB_STB_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTLIB_STB${U3_VERSION_EXTLIB_STB_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTLIB_STB_SRC}
  SRC_MD5
  ${U3_EXTLIB_STB_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTLIB_STB_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTLIB_STB_EXT_MD5}
  SOURCE_PATCH_COMMAND
  ""
  USE_HTTP_FOR_EXTERNAL_SRC
  FALSE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  FALSE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTLIB_STB_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_STB ${install_dir}/src/stb-util)
  set(U3_INSTALL_DIR_EXTLIB_STB ${install_dir}/src/stb-util/${U3_EXTLIB_STB_FILE_NAME})
else()
  set(U3_INCLUDE_DIR_EXTLIB_STB ${install_dir}/src/stb-util)
  set(U3_INSTALL_DIR_EXTLIB_STB ${install_dir}/src/stb-util-build/${U3_EXTLIB_STB_FILE_NAME})
endif()

add_library(stb-lib INTERFACE)
add_dependencies(stb-lib ${U3_NAME_EXTLIB_STB_UTIL})
