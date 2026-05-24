# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        27.02.2026
# copyright   Erashov A.I.
# file        u3-libdrm-lib.cmake

include(ExternalProject)
include(FetchContent)

find_program(U3_LIB_LIBDRM_STATUS_MESON meson)
if(NOT U3_LIB_LIBDRM_STATUS_MESON)
  message(FATAL_ERROR "${U3_MARK_FATAL}Meson not found")
endif()

find_program(U3_LIB_LIBDRM_AUTORECONF_PATH autoreconf)
if(NOT U3_LIB_LIBDRM_AUTORECONF_PATH)
  message(FATAL_ERROR "${U3_MARK_FATAL}autoreconf not found. Please install autoconf/automake.")
endif()

include("./build/cmake/libs/libdrm/u3-libdrm-lib-values.cmake")

set(U3_NAME_EXTERNAL_LIB_LIBDRM_UTIL ${U3_NAME_EXTERNAL_LIB_LIBDRM}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTERNAL_LIB_LIBDRM_UTIL}
  #PROJECT_VERSION       "v${U3_VERSION_EXTERNAL_LIB_LIBDRM}"
  URL_TO_BIN
  ${U3_URL_TO_EXTERNAL_LIB_LIBDRM_BIN}
  NAME_BIN_MD5
  U3_EXTERNAL_LIB_LIBDRM${U3_VERSION_EXTERNAL_LIB_LIBDRM_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  URL_TO_SRC
  ${U3_URL_TO_EXTERNAL_LIB_LIBDRM_SRC}
  SRC_MD5
  ${U3_EXTERNAL_LIB_LIBDRM_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTERNAL_LIB_LIBDRM_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTERNAL_LIB_LIBDRM_EXT_MD5}
  SOURCE_PATCH_COMMAND
  ""
  USE_HTTP_FOR_EXT_SRC
  FALSE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  FALSE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_LIBDRM_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBDRM ${install_dir}/src/libdrm-util//src/libdrm-util)
  #set( U3_INSTALL_DIR_EXTERNAL_LIB_LIBDRM ${install_dir}/src/libdrm-util/lib/${U3_EXTERNAL_LIB_LIBDRM_FILE_NAME} )
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBDRM ${install_dir}/src/libdrm-util/src/libdrm-util/va/drm/.libs/${U3_EXTERNAL_LIB_LIBDRM_FILE_NAME})
else()
  #add_custom_command(TARGET ${U3_NAME_EXTERNAL_LIB_LIBDRM_UTIL} POST_BUILD COMMAND cd ${install_dir}/src/libdrm-util/src/libdrm-util/ && ./autogen.sh && make && sudo make install)
  add_custom_command(TARGET ${U3_NAME_EXTERNAL_LIB_LIBDRM_UTIL} POST_BUILD COMMAND cd ${install_dir}/src/libdrm-util/ && ./autogen.sh && make && sudo make install)

  #COMMAND cd ${install_dir}/src/libdrm-util/ && make clean && make libraries OS=linux ARCH=${U3_LOCAL_CALL_PARAM}
  #set( U3_INSTALL_DIR_EXTERNAL_LIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a" )

  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBDRM ${install_dir}/src/libdrm-util/src/libdrm-util/)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBDRM ${install_dir}/src/libdrm-util/src/libdrm-util/va/drm/.libs/${U3_EXTERNAL_LIB_LIBDRM_FILE_NAME})
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBDRM} CONTENT "libdrm")

add_library(libdrm-lib STATIC IMPORTED)
set_target_properties(libdrm-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBDRM})
add_dependencies(libdrm-lib ${U3_NAME_EXTERNAL_LIB_LIBDRM_UTIL})
