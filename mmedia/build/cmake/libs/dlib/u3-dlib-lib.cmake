# author      Erashov Anton erashov2026@proton.me
# date        18.08.2024
# copyright   Erashov A.I.
# file        u3-dlib-lib.cmake

include("./build/cmake/libs/dlib/u3-dlib-lib-values.cmake")

set(U3_NAME_EXTLIB_DLIB_UTIL ${U3_NAME_EXTLIB_DLIB}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTLIB_DLIB_UTIL}
  PROJECT_VERSION
  ${U3_VERSION_EXTLIB_DLIB}
  URL_TO_BIN
  ${U3_URL_TO_EXTLIB_DLIB_BIN}
  NAME_BIN_MD5
  U3_EXTLIB_DLIB${U3_VERSION_EXTLIB_DLIB_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTLIB_DLIB${U3_VERSION_EXTLIB_DLIB_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTLIB_DLIB_SRC}
  SRC_MD5
  ${U3_EXTLIB_DLIB_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTLIB_DLIB_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTLIB_DLIB_MD5}
  SOURCE_PATCH_COMMAND
  USE_HTTP_FOR_EXTERNAL_SRC
  TRUE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  TRUE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTLIB_DLIB_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util)
  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util/${U3_EXTLIB_DLIB_FILE_NAME})
  else()
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util/${U3_EXTLIB_DLIB_FILE_NAME})
  endif()
else()
  set(U3_INCLUDE_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util)

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util-build/dlib/${CMAKE_BUILD_TYPE}/${U3_EXTLIB_DLIB_FILE_NAME})
  else()
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util-build/dlib/${U3_EXTLIB_DLIB_FILE_NAME})
  endif()

  # fix error: unresolved external symbol _USER_ERROR__inconsistent_build_configuration__see_dlib_faq_2
  add_custom_command(
    TARGET ${U3_NAME_EXTLIB_DLIB_UTIL}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/src/dlib-util-build/dlib/config.h ${U3_INCLUDE_DIR_EXTLIB_DLIB}/dlib/config.h)
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_DLIB} CONTENT "dlib")

add_library(dlib-lib STATIC IMPORTED)
set_target_properties(dlib-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_DLIB})
#add_dependencies( dlib-lib ${U3_NAME_EXTLIB_DLIB_UTIL} )

set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTLIB_DLIB_UTIL})
