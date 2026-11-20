# author      Erashov Anton erashov2026@proton.me
# date        18.08.2024
# copyright   Erashov A.I.
# file        u3-turbojpeg-lib.cmake
# https://stackoverflow.com/questions/16842218/how-do-i-use-cmake-externalproject-add-or-alternatives-in-a-cross-platform-way
# https://stackoverflow.com/questions/61893309/cmake-system-processor-value-in-toolchain-file-not-visible-in-top-level-cmakelis

include("./build/cmake/3rdlibs/turbojpeg/u3-turbojpeg-lib-values.cmake")

set(U3_3RDLIB_NAME_TURBO_JPEG_UTIL ${U3_3RDLIB_NAME_TURBO_JPEG}-util)

u3_project_add(
    PROJECT_NAME ${U3_3RDLIB_NAME_TURBO_JPEG_UTIL}
    PROJECT_VERSION ${U3_3RDLIB_VER_TURBO_JPEG}
    BIN_URL ${U3_3RDLIB_ESRC_URL_TURBO_JPEG_BIN}
    NAME_BIN_MD5 U3_3RDLIB_TURBO_JPEG${U3_3RDLIB_VER_TURBO_JPEG_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}
    BIN_MD5 ${U3_3RDLIB_TURBO_JPEG${U3_3RDLIB_VER_TURBO_JPEG_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}}
    SRC_URL ${U3_3RDLIB_OSRC_URL_TURBO_JPEG}
    SRC_MD5 ${U3_3RDLIB_TURBO_JPEG_MD5}
    ESRC_URL ${U3_3RDLIB_ESRC_URL_TURBO_JPEG_SRC}
    ESRC_MD5 ${U3_3RDLIB_TURBO_JPEG_MD5}
    PATCH_CMD ""
    INSTALL_COMMAND "echo"
    USE_HTTP_FOR_ESRC FALSE
    BUILD_IN_SOURCE TRUE
    IT_CMAKE_PROJECT TRUE
    FORCE_COMPILE FALSE
    EXT_CMAKE_ARGS "")

ExternalProject_Get_Property(${U3_3RDLIB_NAME_TURBO_JPEG_UTIL} install_dir)

if (U3_PLATFORM_NAME STREQUAL U3_PLATFORM_NAME_WINDOWS)
  set(U3_FILE_BODY_NAME_TURBO_JPEG "turbojpeg-static")
else ()
  set(U3_FILE_BODY_NAME_TURBO_JPEG "turbojpeg")
endif ()

set(U3_INCLUDE_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util")
set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/${U3_PREFIX_LIB_NAME}${U3_FILE_BODY_NAME_TURBO_JPEG}.${U3_SUFFIX_LIB_NAME}")

if (NOT U3_GVXX_PROJECT_ADD_SOURCE_TYPE STREQUAL "U3_ADD_PROJECT_RESULT_BIN")

  set(U3_INCLUDE_DIR_EXTLIB_TURBO_JPEG ${install_dir}/src/turbo_jpeg-util/src)

  if (U3_PLATFORM_NAME STREQUAL U3_PLATFORM_NAME_WINDOWS OR
      CMAKE_GENERATOR STREQUAL "Xcode")
    set(U3_ADD2PATH_EXTLIB_TURBO_JPEG "${CMAKE_BUILD_TYPE}/")
  else ()
    set(U3_ADD2PATH_EXTLIB_TURBO_JPEG "")
  endif ()

  set(U3_INSTALL_DIR_EXTLIB_TURBO_JPEG "${install_dir}/src/turbo_jpeg-util/${U3_ADD2PATH_EXTLIB_TURBO_JPEG}${U3_PREFIX_LIB_NAME}${U3_FILE_BODY_NAME_TURBO_JPEG}.${U3_SUFFIX_LIB_NAME}")
  set(U3_BIN_TEMP_FOLDER_EXTLIB_TURBO_JPEG "${install_dir}/~temp-turbo_jpeg-util")

  add_custom_command(
      TARGET ${U3_3RDLIB_NAME_TURBO_JPEG_UTIL}
      POST_BUILD
      COMMAND
      ${CMAKE_COMMAND} -E rm -Rf "${U3_BIN_TEMP_FOLDER_EXTLIB_TURBO_JPEG}"
      COMMAND
      ${CMAKE_COMMAND} -E make_directory "${U3_BIN_TEMP_FOLDER_EXTLIB_TURBO_JPEG}"
      COMMAND
      ${CMAKE_COMMAND} -E copy "${install_dir}/src/turbo_jpeg-util/*.a" "${U3_BIN_TEMP_FOLDER_EXTLIB_TURBO_JPEG}"
      COMMAND
      ${CMAKE_COMMAND} -E copy "${install_dir}/src/turbo_jpeg-util/src/*.h" "${U3_BIN_TEMP_FOLDER_EXTLIB_TURBO_JPEG}"
      COMMAND
      ${CMAKE_COMMAND} -E chdir "${U3_BIN_TEMP_FOLDER_EXTLIB_TURBO_JPEG}" tar czvf "${install_dir}/../${U3_3RDLIB_NAME_TURBO_JPEG_BIN}" "./")

endif ()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_TURBO_JPEG} CONTENT "turbo_jpeg")

add_library(turbo_jpeg-lib STATIC IMPORTED)
add_dependencies(turbo_jpeg-lib ${U3_3RDLIB_NAME_TURBO_JPEG_UTIL})
set_target_properties(turbo_jpeg-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_TURBO_JPEG})

#set( U3_3RDLIBS_STATIC_LIST ${U3_3RDLIBS_STATIC_LIST} turbo_jpeg-lib )
set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_3RDLIB_NAME_TURBO_JPEG_UTIL})
