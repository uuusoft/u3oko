# author      Erashov Anton erashov2026@proton.me
# date        18.08.2024
# copyright   Erashov A.I.
# file        u3-userland-lib.cmake
# U3_THIS_COMMERCIAL_PART_SOURCE_CODE

include(ExternalProject)

set(U3_URL_TO_EXTERNAL_LIB_USERLAND https://github.com/raspberrypi/userland)

#set( U3_TOOLCHAIN ${U3_ENV_GEN_FOLDER_EXT_LIBS}/../../userland/src/userland-util/makefiles/cmake/toolchains/arm-linux-gnueabihf.cmake )
#set( U3_TOOLCHAIN ${U3_ENV_GEN_FOLDER_EXT_LIBS}/../../userland/src/userland-util/makefiles/cmake/toolchains/aarch64-linux-gnu.cmake )

ExternalProject_Add(
  userland-util
  GIT_REPOSITORY "${U3_URL_TO_EXTERNAL_LIB_USERLAND}"
  GIT_PROGRESS FALSE
  PREFIX "${U3_ENV_GEN_FOLDER_EXT_LIBS}/userland"
  #TMP_DIR         "${U3_PATH_TO_TEMP_EXTERNAL_LIB_TURBO_JPEG}"
  #LOG_DIR         "${U3_PATH_TO_LOG_EXTERNAL_LIB_TURBO_JPEG}"
  #DOWNLOAD_DIR    "${U3_PATH_TO_DOWNLOAD_EXTERNAL_LIB_TURBO_JPEG}"
  #SOURCE_DIR      "${U3_PATH_TO_BUILD_EXTERNAL_LIB_TURBO_JPEG}"
  #INSTALL_DIR     "${U3_PATH_TO_INSTALL_EXTERNAL_LIB_TURBO_JPEG}"
  #URL_HASH MD5=00000
  #DOWNLOAD_NAME ${U3_ARCHIVE_NAME_EXTERNAL_LIB_TURBO_JPEG}
  DOWNLOAD_EXTRACT_TIMESTAMP FALSE
  TIMEOUT 1200
  #PATCH_COMMAND
  #CONFIGURE_COMMAND
  #CMAKE_GENERATOR_PLATFORM
  #CMAKE_GENERATOR_TOOLSET
  #CMAKE_ARGS -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE=${U3_TOOLCHAIN}
  CMAKE_ARGS -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
  #BUILD_COMMAND ""
  BUILD_COMMAND ${CMAKE_COMMAND} --build . --config ${CMAKE_BUILD_TYPE}
  BUILD_IN_SOURCE TRUE
  BUILD_ALWAYS FALSE
  INSTALL_COMMAND cmake -E echo "Skipping install step."
  #INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config ${CMAKE_BUILD_TYPE}
  #DEPENDS <targets>...
  STEP_TARGETS build install)

ExternalProject_Get_Property(userland-util install_dir)
#message( FATAL_ERROR "install_dir=" ${install_dir} )

set(U3_INCLUDE_DIR_EXTERNAL_LIB_USERLAND ${install_dir}/src/userland-util)

add_library(bcm_host-lib SHARED IMPORTED)
set(U3_INSTALL_DIR_EXTERNAL_LIB_BCM_HOST ${U3_INCLUDE_DIR_EXTERNAL_LIB_USERLAND}/build/lib/libbcm_host.so)
set_target_properties(bcm_host-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_BCM_HOST})

add_library(vcos-lib SHARED IMPORTED)
set(U3_INSTALL_DIR_EXTERNAL_LIB_VCOS ${U3_INCLUDE_DIR_EXTERNAL_LIB_USERLAND}/build/lib/libvcos.so)
set_target_properties(vcos-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_VCOS})

add_library(mmal_util-lib SHARED IMPORTED)
set(U3_INSTALL_DIR_EXTERNAL_LIB_MMAL_UTIL ${U3_INCLUDE_DIR_EXTERNAL_LIB_USERLAND}/build/lib/libmmal_util.so)
set_target_properties(mmal_util-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_MMAL_UTIL})

add_library(mmal_core-lib SHARED IMPORTED)
set(U3_INSTALL_DIR_EXTERNAL_LIB_MMAL_CORE ${U3_INCLUDE_DIR_EXTERNAL_LIB_USERLAND}/build/lib/libmmal_core.so)
set_target_properties(mmal_core-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_MMAL_CORE})

add_library(mmal_vc_client SHARED IMPORTED)
set(U3_INSTALL_DIR_EXTERNAL_LIB_MMAL_VCLIENT ${U3_INCLUDE_DIR_EXTERNAL_LIB_USERLAND}/build/lib/libmmal_vc_client.so)
set_target_properties(mmal_vc_client PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_MMAL_VCLIENT})

#add_library( SHARED IMPORTED )
#set( U3_INSTALL_DIR_EXTERNAL_LIB_ ${U3_INCLUDE_DIR_EXTERNAL_LIB_USERLAND}/build/lib/lib.so )
#set_target_properties(  PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_} )

#vchiq_arm-lib
#

#set_target_properties( turbo_jpeg-lib PROPERTIES IMPORTED_LOCATION c:/libjpeg-turbo/lib/turbojpeg-static.lib )
#set_target_properties( turbo_jpeg-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_TURBO_JPEG}/lib/turbojpeg-static.lib )
