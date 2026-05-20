# author      Erashov Anton erashov2026@proton.me
# date        10.09.2024
# copyright   Erashov A.I.
# file        u3-freeimage-lib.cmake
# https://freeimage.sourceforge.io/

message(FATAL_ERROR "DEBUG-STOP")
include(ExternalProject)
include(./build/cmake/libs/freeimage/u3-freeimage-lib-values.cmake)

set(U3_NAME_EXTERNAL_LIB_FREEIMAGE_UTIL ${U3_NAME_EXTERNAL_LIB_FREEIMAGE}-util)

#message( NOTICE "${U3_MARK_WARNING} change U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_SRC_EXT from ${U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_SRC_EXT} to ${U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_SRC}. External link not working - dowload zero size zip" )
#set( U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_SRC_EXT ${U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_SRC} )

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTERNAL_LIB_FREEIMAGE_UTIL}
  PROJECT_VERSION
  "v${U3_VERSION_EXTERNAL_LIB_FREEIMAGE}"
  URL_TO_BIN
  ${U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_BIN}
  NAME_BIN_MD5
  U3_EXTERNAL_LIB_FREEIMAGE${U3_VERSION_EXTERNAL_LIB_FREEIMAGE_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  URL_TO_SRC
  ${U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_SRC}
  SRC_MD5
  ${U3_EXTERNAL_LIB_FREEIMAGE_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTERNAL_LIB_FREEIMAGE_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTERNAL_LIB_FREEIMAGE_MD5}
  # SOURCE_PATCH_COMMAND  ${GIT_EXECUTABLE} apply "${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/freeimage/u3-freeimage-lib-patch.txt"
  SOURCE_PATCH_COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/freeimage/u3-freeimage-lib-patch-Makefile.gnu.txt
  <SOURCE_DIR>/Makefile.gnu
  USE_HTTP_FOR_EXT_SRC
  TRUE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  FALSE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_FREEIMAGE_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_FREEIMAGE ${install_dir}/src/freeimage-util/include)

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
      set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/lib/FreeImaged.lib")
    else()
      set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/lib/FreeImage.lib")
    endif()
  else()
    set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/lib/libfreeimage.a")
  endif()
else()
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_FREEIMAGE ${install_dir}/src/freeimage-util/Source)

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
      if(${U3_ENV_PTR_BITS_COUNT} EQUAL 32)
        #set( U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util-build/${CMAKE_BUILD_TYPE}/FreeImaged.lib" )
        set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/Dist/x32/FreeImaged.lib")
      else()
        set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/Dist/x64/FreeImaged.lib")
      endif()
    else()
      if(${U3_ENV_PTR_BITS_COUNT} EQUAL 32)
        #set( U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util-build/${CMAKE_BUILD_TYPE}/FreeImage.lib" )
        set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/Dist/x32/FreeImage.lib")
      else()
        set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/Dist/x64/FreeImage.lib")
      endif()
    endif()
    # skip

    #add_custom_command(
    #  TARGET ${U3_NAME_EXTERNAL_LIB_FREEIMAGE_UTIL}
    #  POST_BUILD
    #  COMMAND cd ${install_dir}/src/freeimage-util/build/ && AutoBuildForWindows.bat ${U3_LOCAL_CALL_PARAM}
    #)

  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
    add_custom_command(
      TARGET ${U3_NAME_EXTERNAL_LIB_FREEIMAGE_UTIL} POST_BUILD COMMAND cd ${install_dir}/src/freeimage-util/ && make
      #COMMAND cd ${install_dir}/src/freeimage-util/ && make OS=linux ARCH=**${U3_LOCAL_CALL_PARAM}**
    )

    set(U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE "${install_dir}/src/freeimage-util/Dist/libfreeimage.a")
  else()
    message(FATAL_ERROR "unsupported OS ${U3_SYSTEM_NAME}")
  endif()
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE} CONTENT "freeimage")

add_library(freeimage-lib STATIC IMPORTED)
add_dependencies(freeimage-lib ${U3_NAME_EXTERNAL_LIB_FREEIMAGE_UTIL})
set_target_properties(freeimage-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_FREEIMAGE})

set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTERNAL_LIB_FREEIMAGE_UTIL})
