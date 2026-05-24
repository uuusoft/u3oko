# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        27.02.2026
# copyright   Erashov A.I.
# file        u3-libva-utils-lib.cmake
# U3_COMMERCIAL_PART

include(ExternalProject)
include(FetchContent)
include("./build/cmake/libs/libva-utils/u3-libva-utils-lib-values.cmake")

set(U3_NAME_EXTERNAL_LIB_LIBVA_UTILS_UTIL ${U3_NAME_EXTERNAL_LIB_LIBVA_UTILS}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTERNAL_LIB_LIBVA_UTILS_UTIL}
  #PROJECT_VERSION       "v${U3_VERSION_EXTERNAL_LIB_LIBVA_UTILS}"
  URL_TO_BIN
  ${U3_URL_TO_EXTERNAL_LIB_LIBVA_UTILS_BIN}
  NAME_BIN_MD5
  U3_EXTERNAL_LIB_LIBVA_UTILS${U3_VERSION_EXTERNAL_LIB_LIBVA_UTILS_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTERNAL_LIB_LIBVA_UTILS${U3_VERSION_EXTERNAL_LIB_LIBVA_UTILS_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTERNAL_LIB_LIBVA_UTILS_SRC}
  SRC_MD5
  ${U3_EXTERNAL_LIB_LIBVA_UTILS_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTERNAL_LIB_LIBVA_UTILS_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTERNAL_LIB_LIBVA_UTILS_EXT_MD5}
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

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_LIBVA_UTILS_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBVA_UTILS ${install_dir}/src/libva_utils-util)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA_UTILS ${install_dir}/src/libva_utils-util/${U3_EXTERNAL_LIB_LIBVA_UTILS_FILE_NAME})
else()
  #Alternatively, you may set the environment variables LIBVA_CFLAGS
  #and LIBVA_LIBS to avoid the need to call pkg-config.
  #message(AUTHOR_WARNING  "${install_dir}/src/libva_utils-util")
  #U3_INCLUDE_DIR_EXTERNAL_LIB_LIBVA
  #${U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA}
  #COMMAND cd ${install_dir}/src/libva-utils-util/ && export LIBVA_LIBS=${U3_INCLUDE_DIR_EXTERNAL_LIB_LIBVA} && ./autogen.sh && make
  add_custom_command(TARGET ${U3_NAME_EXTERNAL_LIB_LIBVA_UTILS_UTIL} POST_BUILD COMMAND cd ${install_dir}/src/libva-utils-util/ && ./autogen.sh && make)

  #COMMAND cd ${install_dir}/src/libva_utils-util/ && make clean && make libraries OS=linux ARCH=${U3_LOCAL_CALL_PARAM}
  #set( U3_INSTALL_DIR_EXTERNAL_LIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a" )

  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBVA_UTILS ${install_dir}/src/libva_utils-util/)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA_UTILS ${install_dir}/src/libva_utils-util-build/${U3_EXTERNAL_LIB_LIBVA_UTILS_FILE_NAME})
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA_UTILS} CONTENT "libva-utils")

add_library(libva-utils-lib STATIC IMPORTED)
set_target_properties(libva-utils-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBVA_UTILS})
add_dependencies(libva-utils-lib ${U3_NAME_EXTERNAL_LIB_LIBVA_UTILS_UTIL})

#set( U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} libva-lib )
#set( U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTERNAL_LIB_LIBVA_UTILS_UTIL} )

#include_directories( ${U3_INCLUDE_DIR_EXTERNAL_LIB_LIBVA_UTILS} )
