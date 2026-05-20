# author      Erashov Anton erashov2026@proton.me
# date        30.08.2024
# copyright   Erashov A.I.
# file        u3-check-preconditions.cmake

# depends: openssl
find_package(Perl)
if(NOT PERL_FOUND)
  message(FATAL_ERROR "${U3_MARK_FATAL}Perl not found, PERL_EXECUTABLE=${PERL_EXECUTABLE}, install https://strawberryperl.com/")
endif()

find_package(Git)
# depends: many
if(NOT Git_FOUND)
  message(FATAL_ERROR "${U3_MARK_FATAL}Git not found, install???")
endif()

# depends: many
find_package(Wget)
if(NOT WGET_FOUND)
  message(FATAL_ERROR "${U3_MARK_FATAL}Wget not found, WGET_EXECUTABLE=${WGET_EXECUTABLE}, install https://www.msys2.org/ or apt-get install wget")
endif()

# depends: develop
find_package(Python)
if(NOT Python_FOUND)
  message(FATAL_ERROR "${U3_MARK_FATAL}Python not found, Python_EXECUTABLE=${Python_EXECUTABLE}, install https://www.python.org/downloads/windows/")
endif()

# depends: many
if(NOT CMAKE_ASM_NASM_COMPILER_LOADED)
  message(FATAL_ERROR "${U3_MARK_FATAL}Nasm not found, install https://www.nasm.us/")
endif()

# depends: develop
# https://github.com/cheshirekow/cmake_format

message(NOTICE "${U3_MARK_SYSTEM_ENV}PERL_EXECUTABLE=${PERL_EXECUTABLE} v.${PERL_VERSION_STRING}")
message(NOTICE "${U3_MARK_SYSTEM_ENV}GITL_EXECUTABLE=${GIT_EXECUTABLE} v.${GIT_VERSION_STRING}")
message(NOTICE "${U3_MARK_SYSTEM_ENV}WGET_EXECUTABLE=${WGET_EXECUTABLE}")

set(U3_INTERNAL_BUILD_LIST "Release" "MinSizeRel" "RelWithDebInfo" "Debug")
if(NOT ${CMAKE_BUILD_TYPE} IN_LIST U3_INTERNAL_BUILD_LIST)
  message(FATAL_ERROR "${U3_MARK_FATAL}Unknown build type ${U3_MARK_FATAL}CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} not in list U3_INTERNAL_BUILD_LIST=${U3_INTERNAL_BUILD_LIST}")
endif()

# "ANDROID_SANITIZE"
set(U3_INTERNAL_SANITY_LIST
    "none"
    "ub"
    "address"
    "hwaddress"
    "memory"
    "thread")
if(NOT ${U3_SANITY_BUILD_TYPE} IN_LIST U3_INTERNAL_SANITY_LIST)
  message(
    FATAL_ERROR "${U3_MARK_FATAL}Unknown sanity type ${U3_MARK_FATAL}U3_SANITY_BUILD_TYPE=${U3_SANITY_BUILD_TYPE} not in list U3_INTERNAL_SANITY_LIST=${U3_INTERNAL_SANITY_LIST}")
endif()

if(NOT ${U3_SANITY_BUILD_TYPE} STREQUAL "none")
  if(NOT (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
    message(FATAL_ERROR "${U3_MARK_FATAL}${U3_MARK_FATAL}U3_SANITY_BUILD_TYPE=${U3_SANITY_BUILD_TYPE} not supported for CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
  endif()
endif()

set(U3_INTERNAL_OS_LIST
    ${U3_SYSTEM_NAME_WINDOWS}
    ${U3_SYSTEM_NAME_LINUX}
    ${U3_SYSTEM_NAME_ANDROID}
    ${U3_SYSTEM_NAME_RASPBERRY}
    ${U3_SYSTEM_NAME_DARWIN}
    ${U3_SYSTEM_NAME_ORANGE_PI})
if(NOT ${U3_SYSTEM_NAME} IN_LIST U3_INTERNAL_OS_LIST)
  message(FATAL_ERROR "${U3_MARK_FATAL}Unknown os type ${U3_MARK_FATAL}U3_SYSTEM_NAME=${U3_SYSTEM_NAME} not in list U3_INTERNAL_OS_LIST=${U3_INTERNAL_OS_LIST}")
endif()
