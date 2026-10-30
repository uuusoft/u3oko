# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        desk-vgen-source-dlls.cmake

if (NOT U3_COMMERCIAL_PART EQUAL 1)
  message(FATAL_ERROR "U3_COMMERCIAL_PART not 1 " ${U3_COMMERCIAL_PART})
  return()
endif ()

#set(U3_USE_WAYLAND_SCREENCAPTURE_LIB FALSE)
set(U3_DESK_VGEN_VSS_EXT_DEPEND_TARGETS "")
set(U3_DESK_VGEN_VSS_3RDLIBS "")

#if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} OR
#    ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR
#    ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
#  set(U3_USE_WAYLAND_SCREENCAPTURE_LIB TRUE)
if (U3_USE_WAYLAND_SCREENCAPTURE_LIB)
  find_package(PkgConfig REQUIRED)
  #find_package(PipeWire REQUIRED)
  #pkg_check_modules(PipeWire REQUIRED IMPORTED_TARGET libpipewire-0.3)
  pkg_check_modules(PIPEWIRE REQUIRED libpipewire-0.3)
  #usr/include/pipewire-0.3/pipewire
endif ()

if (NOT U3_DBG_COMPILE_AT_BEGIN_EXTLIBS)
  if (U3_USE_WAYLAND_SCREENCAPTURE_LIB)
    include("./build/cmake/3rdlibs/libscreencapture-wayland/u3-libscreencapture-wayland-lib.cmake")
    pkg_check_modules(SYSTEMD REQUIRED libsystemd)
    # 4. Link the systemd library and include directories
    #target_link_libraries(my_app PRIVATE ${SYSTEMD_LIBRARIES})
    #target_include_directories(my_app PRIVATE ${SYSTEMD_INCLUDE_DIRS})
  endif ()
endif ()

if (U3_USE_WAYLAND_SCREENCAPTURE_LIB)
  pkg_check_modules(PIPEWIRE REQUIRED libpipewire-0.3)
  set(U3_DESK_VGEN_VSS_EXT_DEPEND_TARGETS ${U3_DESK_VGEN_VSS_EXT_DEPEND_TARGETS} wlscreencapture-util)
  set(U3_DESK_VGEN_VSS_3RDLIBS ${U3_DESK_VGEN_VSS_3RDLIBS} wlscreencapture-lib sdbus-cpp-lib systemd pipewire-0.3)
endif ()

u3_add_target_dylib(
    TARGET_NAME
    desk_vgen-vss
    SOURCE_PATH
    ${U3_PATH_ROOT}/dlls/sources/desk_vgen/source
    OUTPUT_NAME
    vss_desk_vgen
    FORCE_TO_DYLIB
    FALSE
    USE_EXACTLY_SOURCE_FILES
    FALSE
    SOURCE_FILES
    ""
    EXTENDED_LIBS
    gen_lib-lib
    dbufs-dll
    ${U3_DESK_VGEN_VSS_3RDLIBS}
    #wlscreencapture-lib
    #sdbus-cpp-lib
    #systemd
    #pipewire-0.3
    ${SYSTEMD_LIBRARIES}
    DEPEND_TARGETS
    ${U3_DESK_VGEN_VSS_EXT_DEPEND_TARGETS}
    dbufs-dll)


#if ( ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
#    wlscreencapture-lib
#endif()
if (U3_USE_WAYLAND_SCREENCAPTURE_LIB)
  #message( FATAL_ERROR "U3_INCLUDE_DIR_EXTLIB_WAYLAND_SCREEN_CAPTURE=${U3_INCLUDE_DIR_EXTLIB_WAYLAND_SCREEN_CAPTURE}" )
  #message( FATAL_ERROR "U3_INSTALL_DIR_EXTLIB_WAYLAND_SCREEN_CAPTURE=${U3_INSTALL_DIR_EXTLIB_WAYLAND_SCREEN_CAPTURE}")
  #U3_INCLUDE_DIR_EXTLIB_WAYLAND_SCREEN_CAPTURE
  target_include_directories(desk_vgen-vss SYSTEM PRIVATE "${U3_INCLUDE_DIR_EXTLIB_WAYLAND_SCREEN_CAPTURE}" ${SYSTEMD_INCLUDE_DIRS} ${PIPEWIRE_INCLUDE_DIRS})
  #target_link_libraries(desk_vgen-vss PRIVATE PkgConfig::PipeWire)
  #PkgConfig::PipeWire
  #target_include_directories(my_app PRIVATE ${SYSTEMD_INCLUDE_DIRS})
  #/home/erashov/Documents/u3media/u3temp-Raspberry-Clang-Clang--aarch64-Release-ub/wlscreencapture-util/wlscreencapture-util/src/wlscreencapture-util/include
  #/home/erashov/Documents/u3media/u3temp-Raspberry-Clang-Clang--aarch64-Release-ub/wlscreencapture-util/src/wlscreencapture-util/wlscreencapture-util/include
  #u3_make_fake_file(
  #  FILE_NAME ${U3_INCLUDE_DIR_EXTLIB_WAYLAND_SCREEN_CAPTURE}/c_common.h2
  #  CONTENT "c_common.h2"
  #)

  #target_include_directories( vcodec_mjpg_vvd   SYSTEM PRIVATE  "${U3_INCLUDE_DIR_EXTLIB_TURBO_JPEG}" )

  # for Ubuntu
  # sudo apt update
  # sudo apt install libx11-dev
  # temporarily disabled for raspberry
  #find_package( X11 REQUIRED )
  #link_directories( /usr/lib/X11 )
  #target_link_libraries( desk_vgen-vss X11 )
endif ()
