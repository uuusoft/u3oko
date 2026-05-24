# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        20.02.2026
# copyright   Erashov A.I.
# file        u3-libscreencapture-wayland-lib.cmake
# https://github.com/DafabHoid/libscreencapture-wayland

include(ExternalProject)
include(FetchContent)

include("./build/cmake/libs/libscreencapture-wayland/u3-libscreencapture-wayland-lib-values.cmake")

set(U3_NAME_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_UTIL ${U3_NAME_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE}-util)

#message(AUTHOR_WARNING "bin name=${U3_URL_TO_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_BIN}")
#message(AUTHOR_WARNING "bin md5=U3_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE${U3_VERSION_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}")
#message(FATAL_ERROR "${U3_MARK_DEV}U3_DBG_STOP_BEFORE_COMPILE_EXT_LIBS=${U3_DBG_STOP_BEFORE_COMPILE_EXT_LIBS}")

u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_UTIL}
  #PROJECT_VERSION       "v${U3_VERSION_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE}"
  URL_TO_BIN
  ${U3_URL_TO_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_BIN}
  NAME_BIN_MD5
  U3_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE${U3_VERSION_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  URL_TO_SRC
  ${U3_URL_TO_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_SRC}
  SRC_MD5
  ${U3_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_EXT_MD5}
  SOURCE_PATCH_COMMAND
  ""
  USE_HTTP_FOR_EXT_SRC
  FALSE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  TRUE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE ${install_dir}/src/wlscreencapture-util/include ${install_dir}/src/wlscreencapture-util)
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE ${install_dir}/src/wlscreencapture-util/src/wlscreencapture-util/include
                                                         ${install_dir}/src/wlscreencapture-util/src/wlscreencapture-util)
  #set( U3_INSTALL_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE ${install_dir}/src/wlscreencapture-util/build/${U3_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_FILE_NAME} )
  set(U3_INSTALL_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE ${install_dir}/src/wlscreencapture-util/src/wlscreencapture-util-build/${U3_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_FILE_NAME})
else()
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE ${install_dir}/src/wlscreencapture-util/include ${install_dir}/src/wlscreencapture-util)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE ${install_dir}/src/wlscreencapture-util/src/wlscreencapture-util-build/${U3_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_FILE_NAME})
  #/home/erashov/Documents/u3media/u3temp-OrangePi-GNU-GNU--aarch64-Release-ub/wlscreencapture-util/src/wlscreencapture-util/build/libscreencapture-wayland.a
endif()

#u3_make_fake_file(
#  FILE_NAME ${U3_INSTALL_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE}
#  CONTENT "wlscreencapture"
#)

add_library(wlscreencapture-lib STATIC IMPORTED)
set_target_properties(wlscreencapture-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE})
add_dependencies(wlscreencapture-lib ${U3_NAME_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_UTIL})

#set( U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} wlscreencapture-lib )
#set( U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_NAME_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_UTIL} )

#include_directories( ${U3_INCLUDE_DIR_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE} )

#/home/erashov/Documents/u3media/u3temp-OrangePi-GNU-GNU--aarch64-Release-ub/wlscreencapture-util/src/wlscreencapture-util/build/PortalModule/sdbus-cpp/libsdbus-c++.a
#set( U3_INSTALL_DIR_EXTERNAL_LIB_SDBUS_CPP ${install_dir}/src/wlscreencapture-util/build/PortalModule/sdbus-cpp/${U3_EXTERNAL_LIB_SDBUS_CPP_FILE_NAME} )
set(U3_INSTALL_DIR_EXTERNAL_LIB_SDBUS_CPP ${install_dir}/src/wlscreencapture-util/src/wlscreencapture-util-build/PortalModule/sdbus-cpp/${U3_EXTERNAL_LIB_SDBUS_CPP_FILE_NAME})
add_library(sdbus-cpp-lib STATIC IMPORTED)
set_target_properties(sdbus-cpp-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTERNAL_LIB_SDBUS_CPP})
#add_dependencies( sdbus-lib ${U3_NAME_EXTERNAL_LIB_WAYLAND_SCREEN_CAPTURE_UTIL} )

#sudo apt-get install pkg-config
#sudo apt install libsystemd-dev

#sudo add-apt-repository ppa:pipewire-debian/pipewire-upstream
#sudo apt update
#sudo apt install pipewire-media-session-wireplumber
#sudo apt install libpipewire-0.3-{0,dev,modules}
#sudo apt install pipewire-audio-client-libraries
#sudo apt install libavutil-dev
#sudo apt install libavcodec-dev
#sudo apt install libavformat-dev
#sudo apt install libavfilter-dev

# cmake -DCMAKE_BUILD_TYPE=Release ..
