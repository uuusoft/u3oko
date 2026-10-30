# author      Erashov Anton erashov2026@proton.me
# date        17.09.2024
# copyright   Erashov A.I.
# file        u3-openssl-lib.cmake

include("./build/cmake/3rdlibs/openssl/u3-openssl-lib-values.cmake")

set(U3_3RDLIB_NAME_OPENSSL_UTIL ${U3_3RDLIB_NAME_OPENSSL}-util)

u3_project_add(
    PROJECT_NAME ${U3_3RDLIB_NAME_OPENSSL_UTIL}
    PROJECT_VERSION "v${U3_3RDLIB_VER_OPENSSL}"
    BIN_URL ${U3_3RDLIB_ESRC_URL_OPENSSL_BIN}
    NAME_BIN_MD5 U3_3RDLIB_OPENSSL${U3_3RDLIB_VER_OPENSSL_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}
    BIN_MD5 ${U3_3RDLIB_OPENSSL${U3_3RDLIB_VER_OPENSSL_CID}_MD5_${U3_ENV_GEN_3RDLIB_POSTFIX}}
    SRC_URL ${U3_3RDLIB_OSRC_URL_OPENSSL}
    SRC_MD5 ${U3_3RDLIB_OPENSSL_MD5}
    ESRC_URL ${U3_3RDLIB_ESRC_URL_OPENSSL_SRC}
    ESRC_MD5 ${U3_3RDLIB_OPENSSL_MD5}
    PATCH_CMD ""
    USE_HTTP_FOR_ESRC TRUE
    BUILD_IN_SOURCE FALSE
    IT_CMAKE_PROJECT FALSE
    FORCE_COMPILE FALSE
    EXT_CMAKE_ARGS "")

ExternalProject_Get_Property(${U3_3RDLIB_NAME_OPENSSL_UTIL} install_dir)

if (${U3_GVXX_PROJECT_ADD_SOURCE_TYPE} STREQUAL "U3_ADD_PROJECT_RESULT_BIN")
  set(U3_INCLUDE_DIR_EXTLIB_OPENSSL ${install_dir}/src/openssl-util/include)
  if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    set(U3_INSTALL_DIR_EXTLIB_OPENSSL "${install_dir}/src/openssl-util/openssl.lib")
    set(U3_INSTALL_DIR_EXTLIB_CRYPTO "${install_dir}/src/openssl-util/crypto.lib")
  else ()
    set(U3_INSTALL_DIR_EXTLIB_OPENSSL "${install_dir}/src/openssl-util/libssl.a")
    set(U3_INSTALL_DIR_EXTLIB_CRYPTO "${install_dir}/src/openssl-util/libcrypto.a")
  endif ()
else ()
  set(U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL ${install_dir}/src/openssl-util/u3-install)
  set(U3_INCLUDE_DIR_EXTLIB_OPENSSL ${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL}/include)

  if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_WINDOWS})
    #set( U3_INSTALL_DIR_EXTLIB_OPENSSL "${install_dir}/src/openssl-util-build/${CMAKE_BUILD_TYPE}/openssl.lib" )
    set(U3_INSTALL_DIR_EXTLIB_OPENSSL "${install_dir}/src/openssl-util/openssl.lib")
    set(U3_INSTALL_DIR_EXTLIB_CRYPTO "${install_dir}/src/openssl-util/crypto.lib")

    #- `perl Configure VC-WIN32`     if you want 32-bit OpenSSL or
    #- `perl Configure VC-WIN64A`    if you want 64-bit OpenSSL or
    #- `perl Configure VC-WIN64-ARM` if you want Windows on Arm (win-arm64)
    #   OpenSSL or

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
      if (U3_ENV_PTR_BITS_COUNT EQUAL 32)
        set(U3_LOCAL_CALL_PARAM Win32-Debug-ASM)
      else ()
        set(U3_LOCAL_CALL_PARAM Win64-Debug-ASM)
      endif ()
    else ()
      if (U3_ENV_PTR_BITS_COUNT EQUAL 32)
        set(U3_LOCAL_CALL_PARAM Win32-Release-ASM)
      else ()
        set(U3_LOCAL_CALL_PARAM Win64-Release-ASM)
      endif ()
    endif ()

    #C:/uuusoft/u3media3/u3externals-Windows-MSVC-MSVC--Win32-Release-none/openssl-util/src/openssl-util/src/openssl-util/
    #add_custom_command(
    #  TARGET ${U3_3RDLIB_NAME_OPENSSL_UTIL}
    #  POST_BUILD
    #  #COMMAND cd ${install_dir}/src/openssl-util && "c:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat"  x86_amd64 && perl Configure VC-WIN32
    #  #COMMAND "c:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat"  x86_amd64 && cd ${install_dir}/src/openssl-util && perl Configure VC-WIN32
    #  #&& nmake
    #)

  elseif (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} OR
      ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_RASPBERRY} OR
      ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI} OR
      ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_DARWIN})

    add_custom_command(
        TARGET ${U3_3RDLIB_NAME_OPENSSL_UTIL}
        POST_BUILD
        COMMAND
        cd ${install_dir}/src/openssl-util/ && ./Configure --prefix=${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL} --openssldir=${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL} && make && make
        install)

    if (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_LINUX} OR
        ${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ORANGE_PI})
      set(U3_INSTALL_DIR_EXTLIB_OPENSSL "${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL}/lib64/libssl.a")
      set(U3_INSTALL_DIR_EXTLIB_CRYPTO "${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL}/lib64/libcrypto.a")
    else ()
      set(U3_INSTALL_DIR_EXTLIB_OPENSSL "${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL}/lib/libssl.a")
      set(U3_INSTALL_DIR_EXTLIB_CRYPTO "${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL}/lib/libcrypto.a")
    endif ()

  elseif (${U3_SYSTEM_NAME} STREQUAL ${U3_SYSTEM_NAME_ANDROID})
    set(U3_ANDROID_OPENSSL_OPTIONS
        no-apps
        no-asm
        no-docs
        no-engine
        no-gost
        no-legacy
        no-shared
        no-ssl
        no-tests
        no-zlib
        no-external-tests)

    file(
        CONFIGURE
        OUTPUT
        u3-openssl-android-build.sh
        CONTENT
        [=[cd ${install_dir}/src/openssl-util/
      export ANDROID_NDK_ROOT=${ANDROID_NDK}
      export HOST_TAG=linux-x86_64
      export TOOLCHAIN=${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64
      export CXXFLAGS="-fPIC -Os"
      export CPPFLAGS="-DANDROID -fPIC -Os"
      export PATH=${ANDROID_NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin:${ANDROID_NDK}/toolchains/:$ENV{PATH}
      ./Configure android-arm64 --prefix=${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL} --openssldir=${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL} -static ${U3_ANDROID_OPENSSL_OPTIONS}
      make
      make install
      ]=]
        ESCAPE_QUOTES
        #@ONLY
        NEWLINE_STYLE
        UNIX)

    file(CHMOD
        ${CMAKE_CURRENT_BINARY_DIR}/u3-openssl-android-build.sh
        FILE_PERMISSIONS
        OWNER_EXECUTE
        GROUP_EXECUTE
        WORLD_EXECUTE
        OWNER_READ
        GROUP_READ
        WORLD_READ)

    add_custom_command(
        TARGET
        ${U3_3RDLIB_NAME_OPENSSL_UTIL}
        POST_BUILD COMMAND /bin/bash -c ${CMAKE_CURRENT_BINARY_DIR}/u3-openssl-android-build.sh VERBATIM)

    set(U3_INSTALL_DIR_EXTLIB_OPENSSL "${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL}/lib/libssl.a")
    set(U3_INSTALL_DIR_EXTLIB_CRYPTO "${U3_INSTALL_DIR_EXTLIB_OPENSSL_UTIL}/lib/libcrypto.a")
  else ()
    message(FATAL_ERROR "unsupported OS ${U3_SYSTEM_NAME}")
  endif ()
endif ()

u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_OPENSSL} CONTENT "openssl")
u3_make_fake_file(FILE_NAME ${U3_INSTALL_DIR_EXTLIB_CRYPTO} CONTENT "crypto")

add_library(openssl-lib STATIC IMPORTED)
add_dependencies(openssl-lib ${U3_3RDLIB_NAME_OPENSSL_UTIL})
set_target_properties(openssl-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_OPENSSL})

add_library(crypto-lib STATIC IMPORTED)
add_dependencies(crypto-lib ${U3_3RDLIB_NAME_OPENSSL_UTIL})
set_target_properties(crypto-lib PROPERTIES IMPORTED_LOCATION ${U3_INSTALL_DIR_EXTLIB_CRYPTO})

set(U3_LIBS_3RD_STATIC_LIST ${U3_LIBS_3RD_STATIC_LIST} openssl-lib crypto-lib)
set(U3_DEPENDENCY_TARGETS_LIST ${U3_DEPENDENCY_TARGETS_LIST} ${U3_3RDLIB_NAME_OPENSSL_UTIL})
