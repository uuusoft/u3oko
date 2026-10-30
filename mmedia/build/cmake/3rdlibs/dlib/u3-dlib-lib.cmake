# author      Erashov Anton erashov2026@proton.me
# date        18.08.2024
# copyright   Erashov A.I.
# file        u3-dlib-lib.cmake

include("./build/cmake/3rdlibs/dlib/u3-dlib-lib-values.cmake")

set(U3_3RDLIB_NAME_DLIB_UTIL ${U3_3RDLIB_NAME_DLIB}-util)

#DLIB_NO_GUI_SUPPORT_STR
u3_project_add(
    PROJECT_NAME ${U3_3RDLIB_NAME_DLIB_UTIL}
    PROJECT_VERSION ${U3_3RDLIB_VER_DLIB}
    BIN_URL ${U3_3RDLIB_ESRC_URL_DLIB_BIN}
    NAME_BIN_MD5 U3_3RDLIB_DLIB${U3_3RDLIB_VER_DLIB_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}
    BIN_MD5 ${U3_3RDLIB_DLIB${U3_3RDLIB_VER_DLIB_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}}
    SRC_URL ${U3_3RDLIB_OSRC_URL_DLIB}
    SRC_MD5 ${U3_3RDLIB_DLIB_MD5}
    ESRC_URL ${U3_3RDLIB_ESRC_URL_DLIB_SRC}
    ESRC_MD5 ${U3_3RDLIB_DLIB_MD5}
    PATCH_CMD ""
    USE_HTTP_FOR_ESRC TRUE
    BUILD_IN_SOURCE FALSE
    IT_CMAKE_PROJECT TRUE
    FORCE_COMPILE FALSE
    EXT_CMAKE_ARGS -DDLIB_NO_GUI_SUPPORT=ON)

ExternalProject_Get_Property(${U3_3RDLIB_NAME_DLIB_UTIL} install_dir)

if (${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util)

  if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util/${U3_3RDLIB_DLIB_FILE_NAME})
  else ()
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util/${U3_3RDLIB_DLIB_FILE_NAME})
  endif ()

else ()
  set(U3_INCLUDE_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util)

  if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util-build/dlib/${CMAKE_BUILD_TYPE}/${U3_3RDLIB_DLIB_FILE_NAME})
  else ()
    set(U3_INSTALL_DIR_EXTLIB_DLIB ${install_dir}/src/dlib-util-build/dlib/${U3_3RDLIB_DLIB_FILE_NAME})
  endif ()

  # fix error: unresolved external symbol _USER_ERROR__inconsistent_build_configuration__see_dlib_faq_2
  add_custom_command(
      TARGET ${U3_3RDLIB_NAME_DLIB_UTIL}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/src/dlib-util-build/dlib/config.h ${U3_INCLUDE_DIR_EXTLIB_DLIB}/dlib/config.h)
endif ()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_DLIB} CONTENT "dlib")

add_library(dlib-lib STATIC IMPORTED)
set_target_properties(dlib-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_DLIB})
#add_dependencies( dlib-lib ${U3_3RDLIB_NAME_DLIB_UTIL} )

set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_3RDLIB_NAME_DLIB_UTIL})
