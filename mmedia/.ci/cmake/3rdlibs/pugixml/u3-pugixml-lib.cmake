# author      Erashov Anton erashov2026@proton.me
# date        10.08.2024
# copyright   Erashov A.I.
# file        u3-pugixml-lib.cmake

include("./.ci/cmake/3rdlibs/pugixml/u3-pugixml-lib-values.cmake")

set(U3_3RDLIB_NAME_PUGIXML_UTIL ${U3_3RDLIB_NAME_PUGIXML}-util)

u3_project_add(
    PROJECT_NAME ${U3_3RDLIB_NAME_PUGIXML_UTIL}
    PROJECT_VERSION "v${U3_3RDLIB_VER_PUGIXML}"
    BIN_URL ${U3_3RDLIB_ESRC_URL_PUGIXML_BIN}
    NAME_BIN_MD5 U3_3RDLIB_PUGIXML${U3_3RDLIB_VER_PUGIXML_CID}_MD5_${U3_GENV_3RDLIB_POSTFIX}
    BIN_MD5 ${U3_3RDLIB_PUGIXML${U3_3RDLIB_VER_PUGIXML_CID}_MD5_${U3_GENV_3RDLIB_POSTFIX}}
    SRC_URL ${U3_3RDLIB_OSRC_URL_PUGIXML}
    SRC_MD5 ${U3_3RDLIB_PUGIXML_MD5}
    ESRC_URL ${U3_3RDLIB_ESRC_URL_PUGIXML_SRC}
    ESRC_MD5 ${U3_3RDLIB_PUGIXML_EXT_MD5}
    PATCH_CMD ""
    INSTALL_COMMAND "echo"
    USE_HTTP_FOR_ESRC FALSE
    BUILD_IN_SOURCE FALSE
    IT_CMAKE_PROJECT TRUE
    FORCE_COMPILE FALSE
    EXT_CMAKE_ARGS "")

ExternalProject_Get_Property(${U3_3RDLIB_NAME_PUGIXML_UTIL} install_dir)

set(U3_INCLUDE_DIR_EXTLIB_PUGIXML ${install_dir}/src/pugixml-util)
set(U3_INSTALL_DIR_EXTLIB_PUGIXML ${install_dir}/src/pugixml-util/${U3_3RDLIB_PUGIXML_FILE_NAME})

if (NOT U3_GVXX_SOURCE_TYPE STREQUAL "U3_ADD_PROJECT_RESULT_BIN")

  set(U3_INCLUDE_DIR_EXTLIB_PUGIXML ${install_dir}/src/pugixml-util/src)

  if (U3_PLATFORM_NAME STREQUAL U3_PLATFORM_NAME_WINDOWS OR
      CMAKE_GENERATOR STREQUAL "Xcode")
    set(U3_ADD2PATH_EXTLIB_PUGIXML "${CMAKE_BUILD_TYPE}/")
  else ()
    set(U3_ADD2PATH_EXTLIB_PUGIXML "")
  endif ()

  set(U3_INSTALL_DIR_EXTLIB_PUGIXML "${install_dir}/src/pugixml-util-build/${U3_ADD2PATH_EXTLIB_PUGIXML}${U3_PREFIX_LIB_NAME}pugixml.${U3_SUFFIX_LIB_NAME}")
  set(U3_BIN_TEMP_FOLDER_EXTLIB_PUGIXML "${install_dir}/~temp-pugixml-util")

  add_custom_command(
      TARGET ${U3_3RDLIB_NAME_PUGIXML_UTIL}
      POST_BUILD
      COMMAND
      ${CMAKE_COMMAND} -E rm -Rf "${U3_BIN_TEMP_FOLDER_EXTLIB_PUGIXML}"
      COMMAND
      ${CMAKE_COMMAND} -E make_directory "${U3_BIN_TEMP_FOLDER_EXTLIB_PUGIXML}"
      COMMAND
      ${CMAKE_COMMAND} -E copy "${install_dir}/src/pugixml-util-build/*.a" "${U3_BIN_TEMP_FOLDER_EXTLIB_PUGIXML}"
      COMMAND
      ${CMAKE_COMMAND} -E copy "${install_dir}/src/pugixml-util/src/*.hpp" "${U3_BIN_TEMP_FOLDER_EXTLIB_PUGIXML}"
      COMMAND
      ${CMAKE_COMMAND} -E chdir "${U3_BIN_TEMP_FOLDER_EXTLIB_PUGIXML}" tar czvf "${install_dir}/../${U3_3RDLIB_NAME_PUGIXML_BIN}" "./")

endif ()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_PUGIXML} CONTENT "pugixml")

add_library(pugixml-lib STATIC IMPORTED)
set_target_properties(pugixml-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_PUGIXML})
add_dependencies(pugixml-lib ${U3_3RDLIB_NAME_PUGIXML_UTIL})

set(U3_SELECTED_3RDLIBS_LIST ${U3_SELECTED_3RDLIBS_LIST} pugixml-lib)
set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_3RDLIB_NAME_PUGIXML_UTIL})

include_directories(${U3_INCLUDE_DIR_EXTLIB_PUGIXML})
