# author      Erashov Anton erashov2026@proton.me
# date        18.08.2024
# copyright   Erashov A.I.
# file

include("./build/cmake/libs/boost/u3-boost-lib-values.cmake")

cmake_policy(SET CMP0167 OLD)

set(Boost_DEBUG off)
set(CMAKE_FIND_DEBUG_MODE off)
#set(Boost_ROOT ${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTLIB_BOOST})
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
#set(Boost_NO_BOOST_CMAKE ON)
#set( Boost_USE_STATIC_RUNTIME OFF )
#message(FATAL_ERROR "Boost_ROOT=${Boost_ROOT}")

set(U3_NAME_EXTLIB_BOOST_UTIL ${U3_NAME_EXTLIB_BOOST}-util)

#message(FATAL_ERROR "NAME=U3_EXTLIB_BOOST${U3_VERSION_EXTLIB_BOOST_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}")
#message(FATAL_ERROR "BIN_MD5=${U3_EXTLIB_BOOST${U3_VERSION_EXTLIB_BOOST_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}")
u3_project_add(
  PROJECT_NAME
  ${U3_NAME_EXTLIB_BOOST_UTIL}
  PROJECT_VERSION
  "v${U3_VERSION_EXTLIB_BOOST}"
  URL_TO_BIN
  ${U3_URL_TO_EXTLIB_BOOST_BIN}
  NAME_BIN_MD5
  U3_EXTLIB_BOOST${U3_VERSION_EXTLIB_BOOST_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}
  BIN_MD5
  ${U3_EXTLIB_BOOST${U3_VERSION_EXTLIB_BOOST_CID}_MD5_${U3_ENV_GEN_POSTFIX_VARIABLE_NAME_TO_EXT_LIB}}
  URL_TO_SRC
  ${U3_URL_TO_EXTLIB_BOOST_SRC}
  SRC_MD5
  ${U3_EXTLIB_BOOST_MD5}
  URL_TO_SRC_EXT
  ${U3_URL_TO_EXTLIB_BOOST_SRC_EXT}
  SRC_EXT_MD5
  ${U3_EXTLIB_BOOST_MD5}
  SOURCE_PATCH_COMMAND
  ""
  USE_HTTP_FOR_EXT_SRC
  TRUE
  BUILD_IN_SOURCE
  FALSE
  IT_CMAKE_PROJECT
  FALSE
  FORCE_COMPILE
  FALSE)

ExternalProject_Get_Property(${U3_NAME_EXTLIB_BOOST_UTIL} install_dir)

if(${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_BOOST ${install_dir}/src/boost-util)
  set(BOOST_LIBRARYDIR "${U3_INCLUDE_DIR_EXTLIB_BOOST}/lib")

  #set(U3_WORK_DIR_EXTLIB_BOOST "${install_dir}/src/u3-boost-build")
  #set(U3_INCLUDE_DIR_EXTLIB_BOOST "${U3_WORK_DIR_EXTLIB_BOOST}/include")
  #set(BOOST_LIBRARYDIR "${U3_WORK_DIR_EXTLIB_BOOST}/lib")
  #set(U3_BOOST_SELECTED_LIBS --with-program_options --with-serialization --with-filesystem --with-json --with-thread)
  #set(Boost_ROOT ${U3_WORK_DIR_EXTLIB_BOOST})
  set(Boost_ROOT ${U3_INCLUDE_DIR_EXTLIB_BOOST})
  #message(FATAL_ERROR "Boost_ROOT=${Boost_ROOT}")

else()

  if(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
    set(U3_WORK_DIR_EXTLIB_BOOST "${install_dir}/src/u3-boost-build")
    set(U3_INCLUDE_DIR_EXTLIB_BOOST "${U3_WORK_DIR_EXTLIB_BOOST}/include")
    set(BOOST_LIBRARYDIR "${U3_WORK_DIR_EXTLIB_BOOST}/lib")
    set(U3_BOOST_SELECTED_LIBS --with-program_options --with-serialization --with-filesystem --with-json --with-thread)
    set(Boost_ROOT ${U3_WORK_DIR_EXTLIB_BOOST})

    add_custom_command(
      TARGET ${U3_NAME_EXTLIB_BOOST_UTIL}
      POST_BUILD
      COMMAND cd ${install_dir}/src/boost-util && ./bootstrap.sh --prefix=${U3_WORK_DIR_EXTLIB_BOOST} && ./b2 ${U3_BOOST_SELECTED_LIBS} cxxflags=-fPIC cflags=-fPIC && ./b2 install
      VERBATIM
    )

  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
    include("./build/cmake/libs/boost-for-android/u3-boost-for-android-lib.cmake")

    add_dependencies(${U3_NAME_EXTLIB_BOOST_UTIL} ${U3_NAME_EXTLIB_BOOST_FOR_ANDROID_UTIL})
    
    #set(U3_WORK_DIR_EXTLIB_BOOST ${install_dir}/src/boost-util)
    #set(U3_INCLUDE_DIR_EXTLIB_BOOST ${install_dir}/src/boost-util/u3-boost-build/include)
    #set(BOOST_LIBRARYDIR "${U3_WORK_DIR_EXTLIB_BOOST}/lib")
    set(U3_WORK_DIR_EXTLIB_BOOST "${install_dir}/src/u3-boost-build")
    set(U3_INCLUDE_DIR_EXTLIB_BOOST "${U3_WORK_DIR_EXTLIB_BOOST}/include")
    set(BOOST_LIBRARYDIR "${U3_WORK_DIR_EXTLIB_BOOST}/lib")

    #message(FATAL_ERROR "BOOST_LIBRARYDIR=${BOOST_LIBRARYDIR}")
    #set(Boost_ROOT "~/Documents/uuusoft/u3media2/u3media2/boost-${U3_VERSION_EXTLIB_BOOST}")

    if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
      #set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTLIB_BOOST}/stage/android/clang/arm/lib")
    elseif(${ANDROID_ABI} STREQUAL "arm64-v8a")
      #set(BOOST_LIBRARYDIR "~/Documents/uuusoft/u3media2/u3media2/boost-1.86.0/stage/android/clang/arm64/lib")
    elseif(${ANDROID_ABI} STREQUAL "x86_64")
      #set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTLIB_BOOST}/stage/android/clang/x64/lib")
    else()
      #set(BOOST_LIB_DIR ${BOOST_DIR_TEST}/ERROR_NOT_FOUND/)
      message(FATAL_ERROR "unknown ANDROID_ABI=" ${ANDROID_ABI})
    endif()


    #message(FATAL_ERROR "${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin")
    #/home/erashov/Android/Sdk/ndk/30.0.14904198/toolchains/llvm/prebuilt/linux-x86_64/bin
    add_custom_command(
      TARGET ${U3_NAME_EXTLIB_BOOST_UTIL}
      POST_BUILD
      COMMAND cd ${U3_INCLUDE_DIR_EXTLIB_BOOST_FOR_ANDROID} && ./build-android.sh ${ANDROID_NDK}
      COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/build/out/arm64-v8a/lib ${BOOST_LIBRARYDIR}
      COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/build/out/arm64-v8a/include/boost-1_91 ${U3_INCLUDE_DIR_EXTLIB_BOOST}
      VERBATIM
    )

#  add_custom_command(
#    TARGET ${U3_NAME_EXTLIB_BOOST_FOR_ANDROID_UTIL} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    <SOURCE_DIR>/build/out/arm64-v8a/lib
#  )

#  add_custom_command(
#    TARGET ${U3_NAME_EXTLIB_BOOST_FOR_ANDROID_UTIL} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    <SOURCE_DIR>/build/out/arm64-v8a/include/boost-1_91
#  )



    #COMMAND cd ${U3_INCLUDE_DIR_EXTLIB_BOOST_FOR_ANDROID} && ./build-android.sh --prefix=${U3_WORK_DIR_EXTLIB_BOOST}
    #COMMAND cd ${install_dir}/src/boost-util && ./bootstrap.sh --prefix=${U3_WORK_DIR_EXTLIB_BOOST} && ./b2 ${U3_BOOST_SELECTED_LIBS} cxxflags=-fPIC cflags=-fPIC && ./b2 install
    #export TOOLCHAIN=${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64
    #export CXXFLAGS="-fPIC -Os"
    #export CPPFLAGS="-DANDROID -fPIC -Os"
    #export PATH=${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin:${ANDROID_NDK}/toolchains/:$ENV{PATH}

    #set(Boost_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../boost-${U3_VERSION_EXTLIB_BOOST})
    #[[
    u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/libboost_atomic.a" CONTENT "libboost_atomic") 
    u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/libboost_program_options.a" CONTENT "libboost_program_options") 
    u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/libboost_serialization.a" CONTENT "libboost_serialization") 
    u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/libboost_wserialization.a" CONTENT "libboost_wserialization") 
    u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/libboost_filesystem.a" CONTENT "libboost_filesystem") 
    u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/libboost_json.a" CONTENT "libboost_json") 
    u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/libboost_thread.a" CONTENT "libboost_thread") 

    add_library(boost-program_options-lib STATIC IMPORTED)
    add_dependencies(boost-program_options-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    set_target_properties(boost-program_options-lib PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/libboost_program_options.a)

    add_library(boost-filesystem-lib STATIC IMPORTED)
    add_dependencies(boost-filesystem-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    set_target_properties(boost-filesystem-lib PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/libboost_filesystem.a)

    add_library(boost-serialization-lib STATIC IMPORTED)
    add_dependencies(boost-serialization-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    set_target_properties(boost-serialization-lib PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/libboost_serialization.a)

    add_library(boost-wserialization-lib STATIC IMPORTED)
    add_dependencies(boost-wserialization-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    set_target_properties(boost-wserialization-lib PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/libboost_wserialization.a)

    #add_library(boost-threads-lib STATIC IMPORTED)
    #add_dependencies(boost-threads-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    #set_target_properties(boost-threads-lib PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/libboost_thread.a)

    add_library(boost-json-lib STATIC IMPORTED)
    add_dependencies(boost-json-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    set_target_properties(boost-json-lib PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/libboost_json.a)

    #add_library(boost-log-lib STATIC IMPORTED)
    #add_dependencies(boost-log-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    #set_target_properties(boost-log-lib PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/)

    #add_library( STATIC IMPORTED)
    #add_dependencies( ${U3_NAME_EXTLIB_BOOST_UTIL})
    #set_target_properties( PROPERTIES IMPORTED_LOCATION ${BOOST_LIBRARYDIR}/)
    ]]

    #[[
    find_library(boost-program_options-lib NAMES libboost_program_options.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
    find_library(boost-filesystem-lib NAMES libboost_filesystem.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
    find_library(boost-serialization-lib NAMES libboost_serialization.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
    find_library(boost-wserialization-lib NAMES libboost_wserialization.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
    find_library(boost-threads-lib NAMES libboost_thread.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
    find_library(boost-json-lib NAMES libboost_json.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)
    find_library(boost-log-lib NAMES libboost_log.a HINTS ${BOOST_LIBRARYDIR} REQUIRED)

    add_dependencies(boost-program_options-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    add_dependencies(boost-filesystem-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    add_dependencies(boost-serialization-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    add_dependencies(boost-wserialization-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    add_dependencies(boost-threads-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    add_dependencies(boost-json-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
    add_dependencies(boost-log-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
  
    set(Boost_LIBRARIES
        ${boost-program_options-lib}
        ${boost-filesystem-lib}
        ${boost-serialization-lib}
        ${boost-wserialization-lib}
        ${boost-threads-lib}
        ${boost-json-lib}
        ${boost-log-lib})
    ]]

    #[[
  link_libraries(
    ${boost-program_options-lib}
    ${boost-filesystem-lib}
    ${boost-serialization-lib}
    ${boost-wserialization-lib}
    ${boost-threads-lib}
    ${boost-json-lib}
    ${boost-log-lib}
  )
    ]]

  elseif(${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_DARWIN})
    set(BOOST_LIBRARYDIR "${U3_BUILD_PATH_TO_LIBS}/../boost-${U3_VERSION_EXTLIB_BOOST}/stage/mac/arm/lib")
  else()
    message(FATAL_ERROR "Build boost lib, unknown OS=" ${U3_SYSTEM_NAME})
  endif()
endif()

if(1)
#if(NOT ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})

  set(U3_NAME_LIB_BOOST_ATOMIC "libboost_atomic.a")
  set(U3_NAME_LIB_BOOST_PROGRAM_OPTIONS "libboost_program_options.a")
  set(U3_NAME_LIB_BOOST_SER "libboost_serialization.a")
  set(U3_NAME_LIB_BOOST_WSER "libboost_wserialization.a")
  set(U3_NAME_LIB_BOOST_FILESYSTEM "libboost_filesystem.a")
  set(U3_NAME_LIB_BOOST_JSON "libboost_json.a")

  u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_ATOMIC}" CONTENT "libboost_atomic") 
  u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_PROGRAM_OPTIONS}" CONTENT "libboost_program_options") 
  u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_SER}" CONTENT "libboost_serialization") 
  u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_WSER}" CONTENT "libboost_wserialization") 
  u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_FILESYSTEM}" CONTENT "libboost_filesystem") 
  u3_make_fake_file(FILE_NAME "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_JSON}" CONTENT "libboost_json") 

  add_library(boost-atomic-lib STATIC IMPORTED)
  add_dependencies(boost-atomic-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
  set_target_properties(boost-atomic-lib PROPERTIES IMPORTED_LOCATION "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_ATOMIC}")

  add_library(boost-program-options-lib STATIC IMPORTED)
  add_dependencies(boost-program-options-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
  set_target_properties(boost-program-options-lib PROPERTIES IMPORTED_LOCATION "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_PROGRAM_OPTIONS}")

  add_library(boost-ser-lib STATIC IMPORTED)
  add_dependencies(boost-ser-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
  set_target_properties(boost-ser-lib PROPERTIES IMPORTED_LOCATION "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_SER}")

  add_library(boost-wser-lib STATIC IMPORTED)
  add_dependencies(boost-wser-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
  set_target_properties(boost-wser-lib PROPERTIES IMPORTED_LOCATION "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_WSER}")

  add_library(boost-filesystem-lib STATIC IMPORTED)
  add_dependencies(boost-filesystem-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
  set_target_properties(boost-filesystem-lib PROPERTIES IMPORTED_LOCATION "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_FILESYSTEM}")

  add_library(boost-json-lib STATIC IMPORTED)
  add_dependencies(boost-json-lib ${U3_NAME_EXTLIB_BOOST_UTIL})
  set_target_properties(boost-json-lib PROPERTIES IMPORTED_LOCATION "${BOOST_LIBRARYDIR}/${U3_NAME_LIB_BOOST_JSON}")

  link_libraries(
    boost-atomic-lib
    boost-program-options-lib
    boost-ser-lib
    boost-wser-lib
    boost-filesystem-lib
    boost-json-lib
  )

  #[[
  find_package(
    Boost ${U3_VERSION_EXTLIB_BOOST} EXACT REQUIRED
    COMPONENTS 
    program_options
    filesystem
    serialization
    wserialization
    json
    #thread
    #log
    #locale
    #date_time
    #chrono
    PATHS ${Boost_ROOT}
    PATHS ${BOOST_LIBRARYDIR}
    #HINTS ${Boost_ROOT}
    #HINTS ${BOOST_LIBRARYDIR}
  )

  link_libraries(
    Boost::program_options
    Boost::filesystem
    Boost::serialization
    Boost::wserialization
    Boost::json
  )
  ]]

endif()

include_directories(${U3_INCLUDE_DIR_EXTLIB_BOOST})
#include_directories(${Boost_INCLUDE_DIRS})

#message(NOTICE "${U3_MARK_WARN}Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
#message(NOTICE "${U3_MARK_WARN}BOOST_LIBRARYDIR=${BOOST_LIBRARYDIR}")
#message(NOTICE "${U3_MARK_WARN}Boost_LIBRARIES=${Boost_LIBRARIES}")
