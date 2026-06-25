# author      Erashov Anton erashov2026@proton.me
# date        21.03.2026
# copyright   Erashov A.I.
# file        u3-sqlitecpp-lib.cmake

include("./build/cmake/libs/sqlitecpp/u3-sqlitecpp-lib-values.cmake")

set(U3_NAME_EXTLIB_SQLITECPP_UTIL ${U3_NAME_EXTLIB_SQLITECPP}-util)

#message(FATAL_ERROR "NAME=U3_EXTLIB_SQLITECPP${U3_VERSION_EXTLIB_SQLITECPP_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}")
u3_project_add(
    PROJECT_NAME
    ${U3_NAME_EXTLIB_SQLITECPP_UTIL}
    PROJECT_VERSION
    ${U3_VERSION_EXTLIB_SQLITECPP}
    URL_TO_BIN
    ${U3_URL_TO_EXTLIB_SQLITECPP_BIN}
    NAME_BIN_MD5
    U3_EXTLIB_SQLITECPP${U3_VERSION_EXTLIB_SQLITECPP_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
    BIN_MD5
    ${U3_EXTLIB_SQLITECPP${U3_VERSION_EXTLIB_SQLITECPP_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
    URL_TO_SRC
    ${U3_URL_TO_EXTLIB_SQLITECPP_SRC}
    SRC_MD5
    ${U3_EXTLIB_SQLITECPP_MD5}
    URL_TO_SRC_EXT
    ${U3_URL_TO_EXTLIB_SQLITECPP_SRC_EXT}
    URL_TO_SRC_EXT
    ${U3_URL_TO_EXTLIB_SQLITECPP_SRC_EXT}
    SRC_EXT_MD5
    ${U3_EXTLIB_SQLITECPP_MD5}
    SOURCE_PATCH_COMMAND
    #${CMAKE_COMMAND}
    #-E
    #copy_if_different
    #${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/sqlitecpp/u3-sqlitecpp-lib-patch.cmake
    #<SOURCE_DIR>/CMakeLists.txt
    USE_HTTP_FOR_EXT_SRC
    TRUE
    BUILD_IN_SOURCE
    FALSE
    IT_CMAKE_PROJECT
    TRUE
    FORCE_COMPILE
    FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTLIB_SQLITECPP_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_SQLITECPP ${install_dir}/src/sqlitecpp-util/include)

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_SQLITECPP "${install_dir}/src/sqlitecpp-util/SQLiteCpp.lib")
  else()
    set(U3_INSTALL_DIR_EXTLIB_SQLITECPP ${install_dir}/src/sqlitecpp-util/libSQLiteCpp.a)
  endif()
else()
  set(U3_INCLUDE_DIR_EXTLIB_SQLITECPP ${install_dir}/src/sqlitecpp-util/include)

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_SQLITECPP "${install_dir}/src/sqlitecpp-util-build/${CMAKE_BUILD_TYPE}/SQLiteCpp.lib")
  else()
    set(U3_INSTALL_DIR_EXTLIB_SQLITECPP "${install_dir}/src/sqlitecpp-util-build/libSQLiteCpp.a")
  endif()
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_SQLITECPP} CONTENT "sqlitecpp")

add_library(u3-sqlitecpp-lib STATIC IMPORTED)
set_target_properties(u3-sqlitecpp-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_SQLITECPP})
add_dependencies(u3-sqlitecpp-lib ${U3_NAME_EXTLIB_SQLITECPP_UTIL})

set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTLIB_SQLITECPP_UTIL})
set(U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} u3-sqlitecpp-lib)
