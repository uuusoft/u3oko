#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
cmake_minimum_required(VERSION 3.4.1)

project( uuu_bench )

set( project_name "uuu_bench" )
set( CMAKE_VERBOSE_MAKEFILE off )
set ( project_version_major 1)
set ( project_version_minor 0)
set( RELATIVE_PATH_TO_UUU_LIBS "." )

configure_file ( "defines/project_config.hpp.in"  "defines/project_config.hpp"  )

if( NOT CMAKE_BUILD_TYPE )
  # По умолчанию конфигурация debug
  set( CMAKE_BUILD_TYPE "Debug" )
endif()

if( ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry") OR 
    ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux") OR
    ( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows") OR
    ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android") )
    #ok
else()
  message( FATAL_ERROR "unknown OS" )
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/arc )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE} )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE} )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )

  include_directories( ./ndk_helper ${ANDROID_NDK}/sources/android/cpufeatures )
  #link_directories( "G:/projects/git_uuusoft1/boost/stage/android/clang" )

  find_library( log-lib log )
  find_library( jnigraphics-lib jnigraphics )

  set( shared_compile_def "BOOST_INTERPROCESS_SHARED_DIR_PATH=\"/sdcard\"" )
  set( shared_compile_options )
  set( shared_link_flags )

  #set( enable_hard_fpu 1 )

  if ( ${ANDROID_ABI} STREQUAL "armeabi-v7a" )

    ##set( shared_compile_options ${shared_compile_options} -mfpu=neon-fp16 -mfloat-abi=hard -mhard-float )
    #set( shared_compile_options ${shared_compile_options} -mfpu=neon-fp16 )
    ##set( shared_compile_def ${shared_compile_def} HAVE_NEON=1 _NDK_MATH_NO_SOFTFP=1 )
    #set( shared_link_flags ${shared_link_flags} -lm_hard )
    ##set( shared_link_flags ${shared_link_flags} -Wl,-lm_hard -Wl,--no-undefined )

  endif ()

elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows"  )

  set( shared_compile_def )
  set( shared_compile_options )
  set( shared_link_flags -Wl,--no-undefined )

elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )

  set( shared_compile_def )
  set( shared_compile_options )
  set( shared_link_flags -Wl,--no-undefined )

  set( shared_compile_options ${shared_compile_options} -std=c++14 -frtti -fexceptions )
  
elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry" )

  set( shared_compile_def )
  set( shared_compile_options )
  set( shared_link_flags -Wl,--no-undefined )

  # Define our host system
  #SET(CMAKE_SYSTEM_NAME Linux)
  #SET(CMAKE_SYSTEM_VERSION 1)

  # Define the cross compiler locations
  SET(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
  SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
  SET(CMAKE_ASM_COMPILER arm-linux-gnueabihf-gcc)

  # Define the sysroot path for the RaspberryPi distribution in our tools folder 
  SET( CMAKE_FIND_ROOT_PATH ${HOME}/Desktop/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/ )

  # Use our definitions for compiler tools
  SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  # Search for libraries and headers in the target directories only
  #SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  #SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

  set( shared_compile_options ${shared_compile_options} -mcpu=arm1176jzf-s -mfpu=neon-fp16 -mfloat-abi=hard -marm )

  #set( shared_compile_def ${shared_compile_def} HAVE_NEON=1 )
  #set( shared_link_flags ${shared_link_flags} -lm_hard )
  #set( shared_link_flags ${shared_link_flags} -Wl -lm_hard )
  #set( shared_link_flags ${shared_link_flags} -lm_hard )
  set( shared_compile_def ${shared_compile_def} UUU_OS_RASPBERRY )
  set( shared_compile_options ${shared_compile_options} -std=c++14 -frtti -fexceptions )

  # rdynamic means the backtrace should work
  #IF (CMAKE_BUILD_TYPE MATCHES "Debug")
  #   add_definitions(-rdynamic)
  #ENDIF()

else()
  message( FATAL_ERROR "unknown OS" )
endif()

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  set( shared_link_flags  ${shared_link_flags} -lpthread -ldl -lrt )
  set( shared_compile_options ${shared_compile_options} -pthread )  
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows"  )
  set( shared_link_flags ${shared_link_flags} user32.lib gdi32.lib )
elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
  set( shared_link_flags ${shared_link_flags} -lpthread -ldl -lrt )
  set( shared_compile_options ${shared_compile_options} -pthread )  
elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry" )
  set( shared_link_flags ${shared_link_flags} -lpthread -ldl -lrt )
  set( shared_compile_options ${shared_compile_options} -pthread )  
else()
  message( FATAL_ERROR "unknown OS" )
endif()

if ( ${CMAKE_BUILD_TYPE} STREQUAL "Release" )
    set( shared_compile_options  ${shared_compile_options} -O3 )
elseif ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
    set( shared_compile_options  ${shared_compile_options} -O0 -g )
else()
    message( FATAL_ERROR "unknown build type" )
endif()

# Опции компиляции в зависимости от версии компилятора.
if( (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC") )
  set( shared_compile_options  ${shared_compile_options} /W4 )
elseif( (${CMAKE_C_COMPILER_ID} STREQUAL "GNU") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") )
  set( shared_compile_options  ${shared_compile_options} -w -fPIC )
elseif( (${CMAKE_C_COMPILER_ID} STREQUAL "Clang") OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang") )
  set( shared_compile_options  ${shared_compile_options} -w -fPIC )
else()
  message( FATAL_ERROR "unknown compiler" )
endif()

set( BOOST_INCLUDEDIR "${RELATIVE_PATH_TO_UUU_LIBS}/../boost" )
set( Boost_NO_SYSTEM_PATHS OFF )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  set( BOOST_LIBRARYDIR "${RELATIVE_PATH_TO_UUU_LIBS}/../boost/stage/android/arm/lib" )
elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
  set( BOOST_LIBRARYDIR "${RELATIVE_PATH_TO_UUU_LIBS}/../boost/stage/windows/desktop/vs14/x32" )
elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Linux" )
  set( BOOST_LIBRARYDIR "${RELATIVE_PATH_TO_UUU_LIBS}/../boost/stage/ubuntu/x64/lib" )
elseif ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry" )
  set( BOOST_LIBRARYDIR "${RELATIVE_PATH_TO_UUU_LIBS}/../boost/stage/raspberry/lib" )
else()
  message( FATAL_ERROR "unknown OS" )
endif()

#message( STATUS "CMAKE_FIND_ROOT_PATH: " ${CMAKE_FIND_ROOT_PATH} )

find_package( Boost
 REQUIRED
 system
 program_options
 filesystem
 serialization
 wserialization
 date_time
 chrono
 thread
 log 
)

set( all-boost-libs 
  ${boost-system-lib} 
  ${boost-program_options-lib} 
  ${boost-date_time-lib} 
  ${boost-chrono-lib} 
  ${boost-filesystem-lib} 
  ${boost-serialization-lib} 
  ${boost-wserialization-lib} 
  ${boost-threads-lib}
  ${boost-log-lib} )

set( all-event-libs 
  events-lib
  ievents-lib
  ievents_events-lib
  ihttp_events-lib
  istorage_events-lib
  imdata_events-lib
  igui_events-lib
  ilog_events-lib )

set( all-generic-libs
  helpers-lib
  buffs-lib
  core-lib
  link-lib
  properties-lib)

set( all-igeneric-libs
  icore-lib
  ilink-lib
  iproperties-lib )

include_directories( ${Boost_INCLUDE_DIRS} )
link_libraries( ${Boost_LIBRARIES} )

include_directories( "${RELATIVE_PATH_TO_UUU_LIBS}/../" )

include( "${RELATIVE_PATH_TO_UUU_LIBS}/libs/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/libso/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/utils/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/modules/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/appls/CMakeLists.txt" )
