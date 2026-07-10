# author      Erashov Anton erashov2026@proton.me
# date        18.08.2024
# copyright   Erashov A.I.
# file        u3-turbojpeg-lib.cmake
# https://stackoverflow.com/questions/16842218/how-do-i-use-cmake-externalproject-add-or-alternatives-in-a-cross-platform-way
# https://stackoverflow.com/questions/61893309/cmake-system-processor-value-in-toolchain-file-not-visible-in-top-level-cmakelis

include("./build/cmake/libs/turbojpeg/u3-turbojpeg-lib-values.cmake")

set(U3_NAME_EXTLIB_TURBO_JPEG_UTIL ${U3_NAME_EXTLIB_TURBO_JPEG}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTLIB_TURBO_JPEG_UTIL}
  PROJECT_VERSION
  ${U3_VERSION_EXTLIB_TURBO_JPEG}
  URL_TO_BIN
  ${U3_URL_TO_EXTLIB_TURBO_JPEG_BIN}
  NAME_BIN_MD5
  U3_EXTLIB_TURBO_JPEG${U3_VERSION_EXTLIB_TURBO_JPEG_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTLIB_TURBO_JPEG${U3_VERSION_EXTLIB_TURBO_JPEG_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTLIB_TURBO_JPEG_SRC}
  SRC_MD5
  ${U3_EXTLIB_TURBO_JPEG_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTLIB_TURBO_JPEG_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTLIB_TURBO_JPEG_MD5}
  SOURCE_PATCH_COMMAND
  ""
  USE_HTTP_FOR_EXTERNAL_SRC
  FALSE
  BUILD_IN_SOURCE
  TRUE
  IT_CMAKE_PROJECT
  TRUE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTLIB_TURBO_JPEG_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_TURBO_JPEG ${install_dir}/src/turbo_jpeg-util)
  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/turbojpeg-static.lib")
  else()
    set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/libturbojpeg.a")
  endif()
else()
  set(U3_INCLUDE_DIR_EXTLIB_TURBO_JPEG ${install_dir}/src/turbo_jpeg-util/src)
  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/${CMAKE_BUILD_TYPE}/turbojpeg-static.lib")
  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_DARWIN})
    if(${CMAKE_GENERATOR} STREQUAL "Xcode")
      set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/${CMAKE_BUILD_TYPE}/libturbojpeg.a")
    else()
      set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/libturbojpeg.a")
    endif()
  else()
    set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/libturbojpeg.a")
  endif()
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_TURBO_JPEG} CONTENT "turbo_jpeg")

add_library(turbo_jpeg-lib STATIC IMPORTED)
add_dependencies(turbo_jpeg-lib ${U3_NAME_EXTLIB_TURBO_JPEG_UTIL})
set_target_properties(turbo_jpeg-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_TURBO_JPEG})

#set( U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} turbo_jpeg-lib )
set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTLIB_TURBO_JPEG_UTIL})
