# author      Erashov Anton erashov2026@proton.me
# date        21.08.2024
# copyright   Erashov A.I.
# file        u3-sqlite-lib.cmake

include("./build/cmake/3rdlibs/sqlite/u3-sqlite-lib-values.cmake")

set(U3_3RDLIB_NAME_SQLITE_UTIL ${U3_3RDLIB_NAME_SQLITE}-util)

u3_project_add(
    PROJECT_NAME ${U3_3RDLIB_NAME_SQLITE_UTIL}
    PROJECT_VERSION ${U3_3RDLIB_VER_SQLITE}
    BIN_URL ${U3_3RDLIB_ESRC_URL_SQLITE_BIN}
    NAME_BIN_MD5 U3_3RDLIB_SQLITE${U3_3RDLIB_VER_SQLITE_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}
    BIN_MD5 ${U3_3RDLIB_SQLITE${U3_3RDLIB_VER_SQLITE_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}}
    SRC_URL ${U3_3RDLIB_OSRC_URL_SQLITE}
    SRC_MD5 ${U3_3RDLIB_SQLITE_MD5}
    ESRC_URL ${U3_3RDLIB_ESRC_URL_SQLITE_SRC}
    ESRC_MD5 ${U3_3RDLIB_SQLITE_MD5}
    PATCH_CMD
    ${CMAKE_COMMAND}
    -E
    copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/3rdlibs/sqlite/patchs/u3-sqlite-lib-patch.cmake
    <SOURCE_DIR>/CMakeLists.txt
    USE_HTTP_FOR_ESRC TRUE
    BUILD_IN_SOURCE FALSE
    IT_CMAKE_PROJECT TRUE
    FORCE_COMPILE FALSE
    EXT_CMAKE_ARGS "")

ExternalProject_Get_Property(${U3_3RDLIB_NAME_SQLITE_UTIL} install_dir)

if (${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_SQLITE ${install_dir}/src/sqlite-util)

  if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_SQLITE "${install_dir}/src/sqlite-util/u3-sqlite-lib.lib")
  else ()
    set(U3_INSTALL_DIR_EXTLIB_SQLITE ${install_dir}/src/sqlite-util/libu3-sqlite-lib.a)
  endif ()
else ()
  set(U3_INCLUDE_DIR_EXTLIB_SQLITE ${install_dir}/src/sqlite-util)

  if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_SQLITE "${install_dir}/src/sqlite-util-build/${CMAKE_BUILD_TYPE}/u3-sqlite-lib.lib")
  else ()
    if (${CMAKE_GENERATOR} STREQUAL "Xcode")
      set(U3_INSTALL_DIR_EXTLIB_SQLITE "${install_dir}/src/sqlite-util-build/${CMAKE_BUILD_TYPE}/libu3-sqlite-lib.a")
    else ()
      set(U3_INSTALL_DIR_EXTLIB_SQLITE "${install_dir}/src/sqlite-util-build/libu3-sqlite-lib.a")
    endif ()
  endif ()
endif ()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_SQLITE} CONTENT "sqlite")

add_library(u3-sqlite-lib STATIC IMPORTED)
set_target_properties(u3-sqlite-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_SQLITE})
add_dependencies(u3-sqlite-lib ${U3_3RDLIB_NAME_SQLITE_UTIL})

set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_3RDLIB_NAME_SQLITE_UTIL})
set(U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} u3-sqlite-lib)
