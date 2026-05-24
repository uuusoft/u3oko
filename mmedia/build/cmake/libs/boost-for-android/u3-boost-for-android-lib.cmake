# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        21.03.2026
# copyright   Erashov A.I.
# file        u3-boost-for-android-lib.cmake

include(ExternalProject)
include(FetchContent)

include("./build/cmake/libs/boost-for-android/u3-boost-for-android-lib-values.cmake")

set(U3_NAME_EXTERNAL_LIB_BOOST_FOR_ANDROID_UTIL ${U3_NAME_EXTERNAL_LIB_BOOST_FOR_ANDROID}-util)

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTERNAL_LIB_BOOST_FOR_ANDROID_UTIL}
  #PROJECT_VERSION       "v${U3_VERSION_EXTERNAL_LIB_BOOST_FOR_ANDROID}"
  URL_TO_BIN
  ${U3_URL_TO_EXTERNAL_LIB_BOOST_FOR_ANDROID_BIN}
  NAME_BIN_MD5
  U3_EXTERNAL_LIB_BOOST_FOR_ANDROID${U3_VERSION_EXTERNAL_LIB_BOOST_FOR_ANDROID_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTERNAL_LIB_BOOST_FOR_ANDROID${U3_VERSION_EXTERNAL_LIB_BOOST_FOR_ANDROID_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTERNAL_LIB_BOOST_FOR_ANDROID_SRC}
  SRC_MD5
  ${U3_EXTERNAL_LIB_BOOST_FOR_ANDROID_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTERNAL_LIB_BOOST_FOR_ANDROID_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTERNAL_LIB_BOOST_FOR_ANDROID_EXT_MD5}
  SOURCE_PATCH_COMMAND
  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/build-android.sh
  <SOURCE_DIR>/build-android.sh

  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-arm64-v8a.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-arm64-v8a.jam

  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-armeabi-v7a.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-armeabi-v7a.jam

  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-common.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-common.jam

  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-common.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-common.jam

  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-x86_64.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-x86_64.jam

  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-x86.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-x86.jam
  
  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0.jam

  COMMAND
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/boost-1_91_0.patch
  <SOURCE_DIR>/patches/boost-1_91_0/boost-1_91_0.patch

  USE_HTTP_FOR_EXT_SRC
  FALSE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  FALSE
  FORCE_COMPILE
  FALSE)


#[[
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-armeabi-v7a.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-armeabi-v7a.jam

  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-common.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-common.jam

  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-common.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-common.jam

  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-x86_64.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-x86_64.jam

  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-x86.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0-x86.jam
  
  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0.jam
  <SOURCE_DIR>/configs/user-config-ndk23-1_91_0.jam

  ${CMAKE_COMMAND}
  -E
  copy_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/build/cmake/libs/boost-for-android/boost-1_91_0.patch
  <SOURCE_DIR>/patches/boost-1_91_0/boost-1_91_0.patch


 FAILED: /home/erashov/Documents/u3-android-build/RelWithDebInfo/u3temp-Android-Clang-21-Clang-21--aarch64-RelWithDebInfo-none/boost-for-android-util/src/boost-for-android-util-stamp/boost-for-android-util-patch 
  cd /home/erashov/Documents/u3-android-build/RelWithDebInfo/u3temp-Android-Clang-21-Clang-21--aarch64-RelWithDebInfo-none/boost-for-android-util/src/boost-for-android-util && /home/erashov/Android/Sdk/cmake/4.1.2/bin/cmake -E copy_if_different /home/erashov/Documents/u3media/mmedia/build/cmake/libs/boost-for-android/build-android.sh /home/erashov/Documents/u3-android-build/RelWithDebInfo/u3temp-Android-Clang-21-Clang-21--aarch64-RelWithDebInfo-none/boost-for-android-util/src/boost-for-android-util/build-android.sh /home/erashov/Android/Sdk/cmake/4.1.2/bin/cmake -E copy_if_different /home/erashov/Documents/u3media/mmedia/build/cmake/libs/boost-for-android/user-config-ndk23-1_91_0-arm64-v8a.jam /home/erashov/Documents/u3-android-build/RelWithDebInfo/u3temp-Android-Clang-21-Clang-21--aarch64-RelWithDebInfo-none/boost-for-android-util/src/boost-for-android-util/configs/user-config-ndk23-1_91_0-arm64-v8a.jam && /home/erashov/Android/Sdk/cmake/4.1.2/bin/cmake -E touch /home/erashov/Documents/u3-android-build/RelWithDebInfo/u3temp-Android-Clang-21-Clang-21--aarch64-RelWithDebInfo-none/boost-for-android-util/src/boost-for-android-util-stamp/boost-for-android-util-patch
  Error: Target (for copy_if_different command) "/home/erashov/Documents/u3-android-build/RelWithDebInfo/u3temp-Android-Clang-21-Clang-21--aarch64-RelWithDebInfo-none/boost-for-android-util/src/boost-for-android-util/configs/user-config-ndk23-1_91_0-arm64-v8a.jam" is not a directory.
  [32/947] Perfor  
]]


#  add_custom_command(
#    TARGET ${U3_NAME_EXTERNAL_LIB_BOOST_FOR_ANDROID_UTIL} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    <SOURCE_DIR>/build/out/arm64-v8a/lib
#  )

#  add_custom_command(
#    TARGET ${U3_NAME_EXTERNAL_LIB_BOOST_FOR_ANDROID_UTIL} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    <SOURCE_DIR>/build/out/arm64-v8a/include/boost-1_91
#  )

  #user-config-ndk23-1_91_0-arm64-v8a.jam
  #user-config-ndk23-1_91_0-armeabi-v7a.jam
  #user-config-ndk23-1_91_0-common.jam
  #user-config-ndk23-1_91_0-x86_64.jam
  #user-config-ndk23-1_91_0-x86.jam
  #user-config-ndk23-1_91_0.jam

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_BOOST_FOR_ANDROID_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_BOOST_FOR_ANDROID ${install_dir}/src/boost-for-android-util)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_BOOST_FOR_ANDROID ${install_dir}/src/boost-for-android-util/${U3_EXTERNAL_LIB_BOOST_FOR_ANDROID_FILE_NAME})
else()
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_BOOST_FOR_ANDROID ${install_dir}/src/boost-for-android-util)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_BOOST_FOR_ANDROID ${install_dir}/src/boost-for-android-util-build/${U3_EXTERNAL_LIB_BOOST_FOR_ANDROID_FILE_NAME})
endif()

add_library(boost-for-android-lib INTERFACE)
