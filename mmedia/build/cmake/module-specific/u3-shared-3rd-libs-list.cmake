# author      Erashov Anton erashov2026@proton.me
# date        12.09.2024
# copyright   Erashov A.I.
# file        u3-shared-3rd-libs-list.cmake

include("./build/cmake/libs/sqlite/u3-sqlite-lib.cmake")
set(U3_NAME_SQLITE_LIB u3-sqlite-lib)
set(U3_NAME_SQLITE_UTIL sqlite-util)
include("./build/cmake/libs/sqlitecpp/u3-sqlitecpp-lib.cmake")

# shared external libs
include("./build/cmake/libs/boost/u3-boost-lib.cmake")
include("./build/cmake/libs/turbojpeg/u3-turbojpeg-lib.cmake")
include("./build/cmake/libs/pugixml/u3-pugixml-lib.cmake")
include("./build/cmake/libs/openssl/u3-openssl-lib.cmake")

if(U3_BUILD_TESTING)
  include("./build/cmake/libs/googletest/u3-googletest-lib.cmake")
endif()

if(U3_DBG_COMPILE_AT_BEGIN_EXTLIBS)
  # debug - force first compile
  include("./build/cmake/libs/stb/u3-stb-lib.cmake")
  include("./build/cmake/libs/openh264/u3-openh264-lib.cmake")
  include("./build/cmake/libs/dlib/u3-dlib-lib.cmake")

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
    include("./build/cmake/libs/libv4l2cpp/u3-libv4l2cpp-lib.cmake")

    if(U3_COMMERCIAL_PART EQUAL 1)
      include("./build/cmake/libs/libva/u3-libva-lib.cmake")
      include("./build/cmake/libs/libva-utils/u3-libva-utils-lib.cmake")
      #include( "./build/cmake/libs/libscreencapture-wayland/u3-libscreencapture-wayland-lib.cmake" )
      #include( "./build/cmake/libs/libdatachannel/u3-libdatachannel-lib.cmake" )
      #include( "./build/cmake/libs/libcamera/u3-libcamera-lib.cmake" )
    endif()
  endif()
endif()
