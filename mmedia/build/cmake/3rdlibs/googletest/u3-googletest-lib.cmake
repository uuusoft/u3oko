# author      Erashov Anton erashov2026@proton.me
# date        20.02.2026
# copyright   Erashov A.I.
# file        u3-googletest-lib.cmake

include("./build/cmake/3rdlibs/googletest/u3-googletest-lib-values.cmake")

set(U3_3RDLIB_NAME_GOOGLETEST_UTIL ${U3_3RDLIB_NAME_GOOGLETEST}-util)

u3_project_add(
    PROJECT_NAME ${U3_3RDLIB_NAME_GOOGLETEST_UTIL}
    PROJECT_VERSION "v${U3_3RDLIB_VER_GOOGLETEST}"
    #PROJECT_VERSION       "release-${U3_3RDLIB_VER_GOOGLETEST}"
    BIN_URL ${U3_3RDLIB_ESRC_URL_GOOGLETEST_BIN}
    NAME_BIN_MD5 U3_3RDLIB_GOOGLETEST${U3_3RDLIB_VER_GOOGLETEST_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}
    BIN_MD5 ${U3_3RDLIB_GOOGLETEST${U3_3RDLIB_VER_GOOGLETEST_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}}
    SRC_URL ${U3_3RDLIB_OSRC_URL_GOOGLETEST}
    SRC_MD5 ${U3_3RDLIB_GOOGLETEST_MD5}
    ESRC_URL ${U3_3RDLIB_ESRC_URL_GOOGLETEST_SRC}
    ESRC_MD5 ${U3_3RDLIB_GOOGLETEST_EXT_MD5}
    PATCH_CMD ""
    INSTALL_COMMAND "echo"
    USE_HTTP_FOR_ESRC FALSE
    BUILD_IN_SOURCE FALSE
    IT_CMAKE_PROJECT TRUE
    FORCE_COMPILE FALSE
    EXT_CMAKE_ARGS "")

ExternalProject_Get_Property(${U3_3RDLIB_NAME_GOOGLETEST_UTIL} install_dir)

if (U3_GVXX_PROJECT_ADD_SOURCE_TYPE STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_GOOGLETEST ${install_dir}/src/googletest-util)
  set(U3_INSTALL_DIR_EXTLIB_GOOGLETEST ${install_dir}/src/googletest-util/lib/${U3_3RDLIB_GOOGLETEST_FILE_NAME})
  set(U3_INSTALL_DIR_EXTLIB_GOOGLETEST2 ${install_dir}/src/googletest-util/lib/${U3_3RDLIB_GOOGLETEST_FILE_NAME2})
else ()
  set(U3_INCLUDE_DIR_EXTLIB_GOOGLETEST ${install_dir}/src/googletest-util/googletest/include)
  set(U3_INSTALL_DIR_EXTLIB_GOOGLETEST ${install_dir}/src/googletest-util-build/lib/${U3_3RDLIB_GOOGLETEST_FILE_NAME})
  set(U3_INSTALL_DIR_EXTLIB_GOOGLETEST2 ${install_dir}/src/googletest-util-build/lib/${U3_3RDLIB_GOOGLETEST_FILE_NAME2})

  #set(U3_INSTALL_DIR_EXTLIB_GOOGLETEST "${install_dir}/src/googletest-util-build/${U3_ADD2PATH_EXTLIB_GOOGLETEST}${U3_PREFIX_LIB_NAME}u3-googletest-lib.${U3_SUFFIX_LIB_NAME}")
  set(U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST "${install_dir}/~temp-googletest-util")

  add_custom_command(
      TARGET ${U3_3RDLIB_NAME_GOOGLETEST_UTIL}
      POST_BUILD
      COMMAND
      ${CMAKE_COMMAND} -E rm -Rf "${U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST}"
      COMMAND
      ${CMAKE_COMMAND} -E make_directory "${U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST}"
      COMMAND
      ${CMAKE_COMMAND} -E copy "${U3_INSTALL_DIR_EXTLIB_GOOGLETEST}" "${U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST}"
      COMMAND
      ${CMAKE_COMMAND} -E copy "${U3_INSTALL_DIR_EXTLIB_GOOGLETEST2}" "${U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST}"
      #COMMAND
      #${CMAKE_COMMAND} -E copy "${install_dir}/src/googletest-util/*.h" "${U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST}"
      COMMAND
      ${CMAKE_COMMAND} -E copy_directory_if_different "${install_dir}/src/googletest-util/googletest/include/" "${U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST}/include/"
      COMMAND
      ${CMAKE_COMMAND} -E chdir "${U3_BIN_TEMP_FOLDER_EXTLIB_GOOGLETEST}" tar czvf "${install_dir}/../${U3_3RDLIB_NAME_GOOGLETEST_BIN}" "./")

endif ()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_GOOGLETEST} CONTENT "googletest")

add_library(googletest-lib STATIC IMPORTED)
set_target_properties(googletest-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_GOOGLETEST})
add_dependencies(googletest-lib ${U3_3RDLIB_NAME_GOOGLETEST_UTIL})

add_library(googletest-lib2 STATIC IMPORTED)
set_target_properties(googletest-lib2 PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_GOOGLETEST2})
add_dependencies(googletest-lib2 ${U3_3RDLIB_NAME_GOOGLETEST_UTIL})

set(U3_3RDLIBS_STATIC_LIST ${U3_3RDLIBS_STATIC_LIST} googletest-lib)
set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_3RDLIB_NAME_GOOGLETEST_UTIL})
