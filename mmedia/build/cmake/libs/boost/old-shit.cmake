# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        18.08.2024
# copyright   Erashov A.I.
# file

include("./build/cmake/libs/boost/u3-boost-lib-values.cmake")

cmake_policy(SET CMP0167 OLD)

set(Boost_DEBUG off)
set(CMAKE_FIND_DEBUG_MODE off)
set(Boost_ROOT ${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST})
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
#set(Boost_NO_BOOST_CMAKE ON)
#set( Boost_USE_STATIC_RUNTIME OFF )
#message(FATAL_ERROR "Boost_ROOT=${Boost_ROOT}")


if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTERNAL_LIB_GOOGLETEST ${install_dir}/src/googletest-util)
  set(U3_INSTALL_DIR_EXTERNAL_LIB_GOOGLETEST ${install_dir}/src/googletest-util/lib/${U3_EXTERNAL_LIB_GOOGLETEST_FILE_NAME})
  set(U3_INSTALL_DIR_EXTERNAL_LIB_GOOGLETEST2 ${install_dir}/src/googletest-util/lib/${U3_EXTERNAL_LIB_GOOGLETEST_FILE_NAME2})
else()

if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
  # copy boost libs to ~/Android/Sdk/ndk/27.0.12077973/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/x86_64-linux-android
  # /home/ytkoduff/Android/Sdk/ndk/28.0.12433566/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android
  #BOOST_INTERPROCESS_SHARED_DIR_FUNC and BOOST_INTERPROCESS_SHARED_DIR_PATH
  set(Boost_ROOT "~/Documents/uuusoft/u3media2/u3media2/boost-${U3_VERSION_EXTERNAL_LIB_BOOST}")

  #if( ${U3_ENV_PTR_BITS_COUNT} EQUAL 32 )
  #set( BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/android/clang/arm/lib" )
  #else()
  #set( BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/android/clang/arm64/lib" )
  # set( BOOST_LIBRARYDIR "~/Documents/uuusoft/u3media2/u3media2/boost-1.86.0/stage/android/clang/arm64/lib" )
  #endif()

  #message( FATAL_ERROR "ANDROID_ABI=${ANDROID_ABI}" )

  if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
    #set( BOOST_LIB_DIR ${BOOST_DIR_TEST}/stage/android/clang/arm/lib )
    set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/android/clang/arm/lib")
    #set( BOOST_LIBS_POSTFIX a32-1_78 )
  elseif(${ANDROID_ABI} STREQUAL "arm64-v8a")
    #set( BOOST_LIB_DIR ${BOOST_DIR_TEST}/stage/android/clang/arm64/lib/ )
    #set( BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/android/clang/arm64/lib" )
    set(BOOST_LIBRARYDIR "~/Documents/uuusoft/u3media2/u3media2/boost-1.86.0/stage/android/clang/arm64/lib")
    #set( BOOST_LIBS_POSTFIX a64-1_78 )
  elseif(${ANDROID_ABI} STREQUAL "x86_64")
    #set( BOOST_LIB_DIR ${BOOST_DIR_TEST}/stage/android/clang/x64/lib/ )
    set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/android/clang/x64/lib")
    #set( BOOST_LIBS_POSTFIX x64-1_78 )
  else()
    set(BOOST_LIB_DIR ${BOOST_DIR_TEST}/ERROR_NOT_FOUND/)
    message(FATAL_ERROR "unknown ANDROID_ABI=" ${ANDROID_ABI})
  endif()

  set(Boost_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST})

  #message( FATAL_ERROR "Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}" )
  #message( FATAL_ERROR "BOOST_LIBRARYDIR=${BOOST_LIBRARYDIR}" )
  #find_library(boost-system-lib NAMES libboost_system.a REQUIRED)
  find_library(boost-program_options-lib NAMES libboost_program_options.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
  find_library(boost-filesystem-lib NAMES libboost_filesystem.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
  find_library(boost-serialization-lib NAMES libboost_serialization.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
  find_library(boost-wserialization-lib NAMES libboost_wserialization.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
  find_library(boost-threads-lib NAMES libboost_thread.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
  find_library(boost-json-lib NAMES libboost_json.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
  find_library(boost-log-lib NAMES libboost_log.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)

  #find_library( boost-system-lib NAMES libboost_system.a PATHS ${BOOST_LIBRARYDIR} PATHS ${BOOST_LIBRARYDIR} REQUIRED )
  #find_library( boost-system-lib NAMES libboost_system.a PATHS ${BOOST_LIBRARYDIR} PATHS ${BOOST_LIBRARYDIR} PATH_SUFFIXES "lib" REQUIRED )
  #find_library( boost-system-lib NAMES libboost_system-clang-mt-${BOOST_LIBS_POSTFIX}.a HINTS ${BOOST_LIBRARYDIR} REQUIRED )
  #find_library( boost-program_options-lib NAMES libboost_program_options-clang-mt-${BOOST_LIBS_POSTFIX}.a  HINTS ${BOOST_LIBRARYDIR} REQUIRED )
  #find_library( boost-filesystem-lib NAMES libboost_filesystem-clang-mt-${BOOST_LIBS_POSTFIX}.a HINTS ${BOOST_LIBRARYDIR} REQUIRED )
  #find_library( boost-serialization-lib NAMES libboost_serialization-clang-mt-${BOOST_LIBS_POSTFIX}.a HINTS ${BOOST_LIBRARYDIR} REQUIRED )
  #find_library( boost-wserialization-lib NAMES libboost_wserialization-clang-mt-${BOOST_LIBS_POSTFIX}.a HINTS ${BOOST_LIBRARYDIR} REQUIRED )
  #find_library( boost-threads-lib NAMES libboost_thread-clang-mt-${BOOST_LIBS_POSTFIX}.a HINTS ${BOOST_LIBRARYDIR} REQUIRED )
  #find_library( boost-json-lib NAMES libboost_json-clang-mt-${BOOST_LIBS_POSTFIX}.a HINTS ${BOOST_LIBRARYDIR} REQUIRED )
  #message( FATAL_ERROR "boost-system-lib=%{boost-system-lib}" )

  set(Boost_LIBRARIES
      ${boost-program_options-lib}
      ${boost-filesystem-lib}
      ${boost-serialization-lib}
      ${boost-wserialization-lib}
      ${boost-threads-lib}
      ${boost-json-lib}
      ${boost-log-lib})

elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
  if(${U3_ENV_PTR_BITS_COUNT} EQUAL 32)
    set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/windows/desktop/x32/lib")
  else()
    set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/windows/desktop/x64/lib")
  endif()
elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX})



  if(${U3_ENV_PTR_BITS_COUNT} EQUAL 32)
    set(BOOST_LIBRARYDIR ${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/ubuntu/x32/lib)
  else()
    set(BOOST_LIBRARYDIR ${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/ubuntu/x64/lib)
  endif()




elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_DARWIN})
  set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/mac/arm/lib")
elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
  if(${U3_ENV_PTR_BITS_COUNT} EQUAL 32)
    set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/raspberry/arm/lib")
  else()
    set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTERNAL_LIB_BOOST}/stage/raspberry/arm64/lib")
  endif()
else()
  message(FATAL_ERROR "Build boost lib, unknown OS=" ${U3_SYSTEM_NAME})
endif()

if(NOT ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
  find_package(
    Boost ${U3_VERSION_EXTERNAL_LIB_BOOST} EXACT REQUIRED
    COMPONENTS program_options
               filesystem
               serialization
               wserialization
               json
               #thread
               #log
               #locale
               #date_time
               #chrono
    #PATHS ${Boost_ROOT}
    #PATHS ${BOOST_LIBRARYDIR}
    #HINTS ${Boost_ROOT}
    #HINTS ${BOOST_LIBRARYDIR}
  )
endif()
endif()

include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

message(NOTICE "${U3_MARK_WARN}Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
message(NOTICE "${U3_MARK_WARN}BOOST_LIBRARYDIR=${BOOST_LIBRARYDIR}")
message(NOTICE "${U3_MARK_WARN}Boost_LIBRARIES=${Boost_LIBRARIES}")
