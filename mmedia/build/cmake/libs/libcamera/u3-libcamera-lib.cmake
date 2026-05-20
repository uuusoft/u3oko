# author      Erashov Anton erashov2026@proton.me
# date        10.04.2026
# copyright   Erashov A.I.
# file        u3-libcamera-lib.cmake

# ubuntu
# sudo apt remove -y meson
# sudo pip3 install --upgrade meson
# sudo apt install python3-pip

include(ExternalProject)
include(FetchContent)

include("./build/cmake/libs/libcamera/u3-libcamera-lib-values.cmake")

set(U3_NAME_EXTERNAL_LIB_LIBCAMERA_UTIL ${U3_NAME_EXTERNAL_LIB_LIBCAMERA}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTERNAL_LIB_LIBCAMERA_UTIL}
  PROJECT_VERSION
  "v${U3_VERSION_EXTERNAL_LIB_LIBCAMERA}"
  URL_TO_BIN
  ${U3_URL_TO_EXTERNAL_LIB_LIBCAMERA_BIN}
  NAME_BIN_MD5
  U3_EXTERNAL_LIB_LIBCAMERA${U3_VERSION_EXTERNAL_LIB_LIBCAMERA_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  URL_TO_SRC
  ${U3_URL_TO_EXTERNAL_LIB_LIBCAMERA_SRC}
  SRC_MD5
  ${U3_EXTERNAL_LIB_LIBCAMERA_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTERNAL_LIB_LIBCAMERA_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTERNAL_LIB_LIBCAMERA_EXT_MD5}
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

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_LIBCAMERA_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBCAMERA ${install_dir}/src/libcamera-util/src/libcamera-util/inc)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBCAMERA ${install_dir}/src/libcamera-util/src/libcamera-util-build/${U3_EXTERNAL_LIB_LIBCAMERA_FILE_NAME})
else()
  add_custom_command(
    TARGET ${U3_NAME_EXTERNAL_LIB_LIBCAMERA_UTIL}
    POST_BUILD
    COMMAND cd ${install_dir}/src/libcamera-util/ && meson setup build --buildtype=release -Dgstreamer=enabled -Dpycamera=enabled && ninja -C build)

  set(U3_INCLUDE_DIR_EXTERNAL_LIB_LIBCAMERA ${install_dir}/src/libcamera-util/inc)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_LIBCAMERA ${install_dir}/src/libcamera-util-build/${U3_EXTERNAL_LIB_LIBCAMERA_FILE_NAME})
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBCAMERA} CONTENT "libcamera")

add_library(libcamera-lib STATIC IMPORTED)
set_target_properties(libcamera-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_LIBCAMERA})
add_dependencies(libcamera-lib ${U3_NAME_EXTERNAL_LIB_LIBCAMERA_UTIL})

#set( U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} libcamera-lib )
#set( U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTERNAL_LIB_LIBCAMERA_UTIL} )

#include_directories( ${U3_INCLUDE_DIR_EXTERNAL_LIB_LIBCAMERA} )
