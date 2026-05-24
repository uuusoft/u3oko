# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        29.08.2024
# copyright   Erashov A.I.
# file        u3-raspberry-specific.cmake

set(U3_LIBS_SYSTEM_STATIC_LIST ${U3_LIBS_SYSTEM_STATIC_LIST} X11)
set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -std=${U3_CPP_STANDARD})
set(U3_SHARED_LINK_OPTIONS_CPP
    ${U3_SHARED_LINK_OPTIONS_CPP}
    -Wl,--no-undefined
    -Wl,-rpath='${ORIGIN}'
    -lpthread
    -ldl
    -lrt)
set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} -DHAVE_NEON=1 -DENABLE_NEON=ON -DU3_OS_RASPBERRY=1)
set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -frtti -fexceptions -pthread)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(U3_PREFIX_LIB_NAME lib)
set(U3_SUFFIX_LIB_NAME a)
set(U3_SUFFIX_DLL_NAME so)

if(U3_ENV_PTR_BITS_COUNT EQUAL 32)
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -mfpu=neon)
endif()

# Define the sysroot path for the RaspberryPi distribution in our tools folder
#SET( CMAKE_FIND_ROOT_PATH ${HOME}/Desktop/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/ )

# Search for libraries and headers in the target directories only
#SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#set( U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -mcpu=arm1176jzf-s -mfpu=neon-fp16 -mfloat-abi=hard -marm )

#set( U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -lm_hard )
#set( U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -Wl -lm_hard )
#set( U3_SHARED_LINK_OPTIONS_CPP ${U3_SHARED_LINK_OPTIONS_CPP} -lm_hard )

# rdynamic means the backtrace should work
#set( U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -rdynamic )
#Think you have to compile it with the neon c++ flag:
#cmake -DENABLE_INT8=ON -DENABLE_NEON=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-mfpu=neon"
#IF (CMAKE_BUILD_TYPE MATCHES "Debug")
#   add_definitions(-rdynamic)
#ENDIF()
