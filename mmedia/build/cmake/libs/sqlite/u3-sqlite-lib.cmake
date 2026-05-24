# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        21.08.2024
# copyright   Erashov A.I.
# file        u3-sqlite-lib.cmake

include(ExternalProject)
include(FetchContent)
include("./build/cmake/libs/sqlite/u3-sqlite-lib-values.cmake")

set(U3_NAME_EXTERNAL_LIB_SQLITE_UTIL ${U3_NAME_EXTERNAL_LIB_SQLITE}-util)

#message(FATAL_ERROR "NAME=U3_EXTERNAL_LIB_SQLITE${U3_VERSION_EXTERNAL_LIB_SQLITE_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}")
u3_project_add(
    PROJECT_NAME
    ${U3_NAME_EXTERNAL_LIB_SQLITE_UTIL}
    PROJECT_VERSION
    ${U3_VERSION_EXTERNAL_LIB_SQLITE}
    URL_TO_BIN
    ${U3_URL_TO_EXTERNAL_LIB_SQLITE_BIN}
    NAME_BIN_MD5
    U3_EXTERNAL_LIB_SQLITE${U3_VERSION_EXTERNAL_LIB_SQLITE_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
    BIN_MD5
    ${U3_EXTERNAL_LIB_SQLITE${U3_VERSION_EXTERNAL_LIB_SQLITE_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
    URL_TO_SRC
    ${U3_URL_TO_EXTERNAL_LIB_SQLITE_SRC}
    SRC_MD5
    ${U3_EXTERNAL_LIB_SQLITE_MD5}
    URL_TO_SRC_EXT
    ${U3_URL_TO_EXTERNAL_LIB_SQLITE_SRC_EXT}
    URL_TO_SRC_EXT
    ${U3_URL_TO_EXTERNAL_LIB_SQLITE_SRC_EXT}
    SRC_EXT_MD5
    ${U3_EXTERNAL_LIB_SQLITE_MD5}
    SOURCE_PATCH_COMMAND
    ${CMAKE_COMMAND}
    -E
    copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/sqlite/u3-sqlite-lib-patch.cmake
    <SOURCE_DIR>/CMakeLists.txt
    USE_HTTP_FOR_EXT_SRC
    TRUE
    BUILD_IN_SOURCE
    FALSE
    IT_CMAKE_PROJECT
    TRUE
    FORCE_COMPILE
    FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_SQLITE_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_SQLITE ${install_dir}/src/sqlite-util)
  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTERNAL_LIB_SQLITE "${install_dir}/src/sqlite-util/u3-sqlite-lib.lib")
  else()
    set(U3_INSTALL_DIR_EXTERNAL_LIB_SQLITE ${install_dir}/src/sqlite-util/libu3-sqlite-lib.a)
  endif()
else()
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_SQLITE ${install_dir}/src/sqlite-util ${install_dir}/src/sqlite-util-build/sqlite)

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTERNAL_LIB_SQLITE "${install_dir}/src/sqlite-util-build/${CMAKE_BUILD_TYPE}/u3-sqlite-lib.lib")
  else()
    if(${CMAKE_GENERATOR} STREQUAL "Xcode")
      set(U3_INSTALL_DIR_EXTERNAL_LIB_SQLITE "${install_dir}/src/sqlite-util-build/${CMAKE_BUILD_TYPE}/libu3-sqlite-lib.a")
    else()
      set(U3_INSTALL_DIR_EXTERNAL_LIB_SQLITE "${install_dir}/src/sqlite-util-build/libu3-sqlite-lib.a")
    endif()
  endif()
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTERNAL_LIB_SQLITE} CONTENT "sqlite")

add_library(u3-sqlite-lib STATIC IMPORTED)
set_target_properties(u3-sqlite-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_SQLITE})
add_dependencies(u3-sqlite-lib ${U3_NAME_EXTERNAL_LIB_SQLITE_UTIL})

set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTERNAL_LIB_SQLITE_UTIL})
set(U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} u3-sqlite-lib)
