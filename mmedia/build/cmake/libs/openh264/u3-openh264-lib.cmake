# author      Erashov Anton erashov2026@proton.me
# date        08.09.2024
# copyright   Erashov A.I.
# file        u3-openh264-lib.cmake

include("./build/cmake/libs/openh264/u3-openh264-lib-values.cmake")

set(U3_NAME_EXTLIB_OPENH264_UTIL ${U3_NAME_EXTLIB_OPENH264}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTLIB_OPENH264_UTIL}
  PROJECT_VERSION
  "${U3_VERSION_EXTLIB_OPENH264}"
  URL_TO_BIN
  ${U3_URL_TO_EXTLIB_OPENH264_BIN}
  NAME_BIN_MD5
  U3_EXTLIB_OPENH264${U3_VERSION_EXTLIB_OPENH264_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTLIB_OPENH264${U3_VERSION_EXTLIB_OPENH264_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTLIB_OPENH264_SRC}
  SRC_MD5
  ${U3_EXTLIB_OPENH264_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTLIB_OPENH264_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTLIB_OPENH264_MD5}
  SOURCE_PATCH_COMMAND
  ""
  USE_HTTP_FOR_EXT_SRC
  FALSE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  FALSE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTLIB_OPENH264_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_OPENH264 ${install_dir}/src/openh264-util)
  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_OPENH264 "${install_dir}/src/openh264-util/openh264.lib")
  else()
    set(U3_INSTALL_DIR_EXTLIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a")
  endif()
else()
  set(U3_INCLUDE_DIR_EXTLIB_OPENH264 ${install_dir}/src/openh264-util)

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_OPENH264 "${install_dir}/src/openh264-util/openh264.lib")

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
      if(U3_ENV_PTR_BITS_COUNT EQUAL 32)
        set(U3_LOCAL_CALL_PARAM Win32-Debug-ASM)
      else()
        set(U3_LOCAL_CALL_PARAM Win64-Debug-ASM)
      endif()
    else()
      if(U3_ENV_PTR_BITS_COUNT EQUAL 32)
        set(U3_LOCAL_CALL_PARAM Win32-Release-ASM)
      else()
        set(U3_LOCAL_CALL_PARAM Win64-Release-ASM)
      endif()
    endif()

    add_custom_command(
      TARGET 
      ${U3_NAME_EXTLIB_OPENH264_UTIL} 
      POST_BUILD 
      COMMAND cd ${install_dir}/src/openh264-util/build/ && AutoBuildForWindows.bat ${U3_LOCAL_CALL_PARAM})
  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX})

    if(U3_ENV_PTR_BITS_COUNT EQUAL 32)
      set(U3_LOCAL_CALL_PARAM_ARCH x86)
    else()
      set(U3_LOCAL_CALL_PARAM_ARCH x86_64)
    endif()

    add_custom_command(
      TARGET 
      ${U3_NAME_EXTLIB_OPENH264_UTIL} 
      POST_BUILD 
      COMMAND cd ${install_dir}/src/openh264-util/ && make clean && make libraries OS=linux ARCH=${U3_LOCAL_CALL_PARAM})

    set(U3_INSTALL_DIR_EXTLIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a")
  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})

    if(U3_ENV_PTR_BITS_COUNT EQUAL 32)
      set(U3_LOCAL_CALL_PARAM_ARCH arm)
    else()
      set(U3_LOCAL_CALL_PARAM_ARCH arm64)
    endif()

    add_custom_command(
      TARGET ${U3_NAME_EXTLIB_OPENH264_UTIL}
      POST_BUILD
      COMMAND cd ${install_dir}/src/openh264-util/ && make clean && make libraries OS=linux CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} ARCH=${U3_LOCAL_CALL_PARAM})

    set(U3_INSTALL_DIR_EXTLIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a")

  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
    set(U3_LOCAL_CALL_PARAM_ARCH arm64)

    add_custom_command(
      TARGET ${U3_NAME_EXTLIB_OPENH264_UTIL}
      POST_BUILD
      COMMAND
      cd ${install_dir}/src/openh264-util/ && make clean && make libraries OS=android ARCH=${U3_LOCAL_CALL_PARAM_ARCH} NDKROOT=${ANDROID_NDK} TARGET=${U3_CMAKE_SYSTEM_VERSION})

    set(U3_INSTALL_DIR_EXTLIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a")

  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_DARWIN})

    if(U3_ENV_PTR_BITS_COUNT EQUAL 32)
      set(U3_LOCAL_CALL_PARAM_ARCH arm)
    else()
      set(U3_LOCAL_CALL_PARAM_ARCH arm64)
    endif()

    add_custom_command(
      TARGET ${U3_NAME_EXTLIB_OPENH264_UTIL}
      POST_BUILD
      COMMAND cd ${install_dir}/src/openh264-util/ && make clean && make libraries OS=darwin CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} ARCH=${U3_LOCAL_CALL_PARAM})

    set(U3_INSTALL_DIR_EXTLIB_OPENH264 "${install_dir}/src/openh264-util/libopenh264.a")
  else()
    message(FATAL_ERROR "unsupported OS ${U3_SYSTEM_NAME}")
  endif()
endif()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_OPENH264} CONTENT "openh264")

add_library(openh264-lib STATIC IMPORTED)
add_dependencies(openh264-lib ${U3_NAME_EXTLIB_OPENH264_UTIL})
set_target_properties(openh264-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_OPENH264})

#set( U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} openh264-lib )
set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTLIB_OPENH264_UTIL})
