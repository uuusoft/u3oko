# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        27.02.2026
# copyright   Erashov A.I.
# file        u3-libva-lib.cmake
# U3_LIB_PREPARE sudo apt-get install git cmake pkg-config meson libdrm-dev automake libtool
# U3_COMMERCIAL_PART

if(1)
  return()
endif()

include(ExternalProject)
include(FetchContent)

find_program(U3_LIB_LIBVA_STATUS_MESON meson)
if(NOT U3_LIB_LIBVA_STATUS_MESON)
  message(FATAL_ERROR "${U3_MARK_FATAL}Meson not found")
endif()

find_program(U3_LIB_LIBVA_AUTORECONF_PATH autoreconf)
if(NOT U3_LIB_LIBVA_AUTORECONF_PATH)
  message(FATAL_ERROR "${U3_MARK_FATAL}autoreconf not found. Please install autoconf/automake.")
endif()

include("./build/cmake/libs/libva/u3-libva-lib-values.cmake")

set(U3_NAME_EXTERNAL_LIB_LIBVA_UTIL ${U3_NAME_EXTERNAL_LIB_LIBVA}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTERNAL_LIB_LIBVA_UTIL}
  #PROJECT_VERSION       "v${U3_VERSION_EXTERNAL_LIB_LIBVA}"
  URL_TO_BIN
  ${U3_URL_TO_EXTERNAL_LIB_LIBVA_BIN}
  NAME_BIN_MD5
  U3_EXTERNAL_LIB_LIBVA${U3_VERSION_EXTERNAL_LIB_LIBVA_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTERNAL_LIB_LIBVA${U3_VERSION_EXTERNAL_LIB_LIBVA_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTERNAL_LIB_LIBVA_SRC}
  SRC_MD5
  ${U3_EXTERNAL_LIB_LIBVA_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTERNAL_LIB_LIBVA_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTERNAL_LIB_LIBVA_EXT_MD5}
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

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_LIBVA_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBVA ${install_dir}/src/libva-util)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA ${install_dir}/src/libva-util/va/drm/.libs/${U3_EXTERNAL_LIB_LIBVA_FILE_NAME})
else()
  #add_custom_command(TARGET ${U3_NAME_EXTERNAL_LIB_LIBVA_UTIL} POST_BUILD COMMAND cd ${install_dir}/src/libva-util/src/libva-util/ && ./autogen.sh && make && sudo make install)
  add_custom_command(TARGET ${U3_NAME_EXTERNAL_LIB_LIBVA_UTIL} POST_BUILD COMMAND cd ${install_dir}/src/libva-util/ && ./autogen.sh && make && sudo make install)

  #COMMAND cd ${install_dir}/src/libva-util/ && make clean && make libraries OS=linux ARCH=${U3_LOCAL_CALL_PARAM}
  #set( U3_INSTALL_DIR_EXTERNAL_LIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a" )

  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBVA ${install_dir}/src/libva-util/src/libva-util/)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA ${install_dir}/src/libva-util/src/libva-util/va/drm/.libs/${U3_EXTERNAL_LIB_LIBVA_FILE_NAME})
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA} CONTENT "libva")

add_library(libva-lib STATIC IMPORTED)
set_target_properties(libva-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA})
add_dependencies(libva-lib ${U3_NAME_EXTERNAL_LIB_LIBVA_UTIL})
