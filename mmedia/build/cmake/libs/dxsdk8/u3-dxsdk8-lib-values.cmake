# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        10.09.2024
# copyright   Erashov A.I.
# file        u3-dxsdk8-lib-values.cmake

# Windows
# cd C:\Users\anton\Documents\uuusoft\3rdlibs\dxsdk8
# tar -zcvf lib-dxsdk8-src-8.0.zip dxsdk8-src
# tar -zcvf lib-dxsdk8-bin-8.0-Windows-MSVC-MSVC--Win32-Release-none.zip dxsdk8-src

set(U3_URL_TO_EXTERNAL_LIB_DXSDK8_SRC_EXT http://uuusoft.com/libs/examples/lib-dxsdk8-src-8.0.zip)
set(U3_ARCHIVE_NAME_EXTERNAL_LIB_DXSDK8 dxsdk8.xxx)
set(U3_NAME_EXTERNAL_LIB_DXSDK8 dxsdk8)
set(U3_VERSION_EXTERNAL_LIB_DXSDK8 8.0)

string(MAKE_C_IDENTIFIER ${U3_VERSION_EXTERNAL_LIB_DXSDK8} U3_VERSION_EXTERNAL_LIB_DXSDK8_CID)

#set( U3_URL_TO_EXTERNAL_LIB_DXSDK8_BIN        ${U3_URL_TO_EXTERNAL_LIBS_BIN}/lib-dxsdk8-bin-${U3_VERSION_EXTERNAL_LIB_DXSDK8}-${U3_ENV_GEN_POSTFIX_NAME_TO_EXT_LIB}.zip )
set(U3_URL_TO_EXTERNAL_LIB_DXSDK8_BIN ${U3_URL_TO_EXTERNAL_LIBS_SRC}/lib-dxsdk8-src-${U3_VERSION_EXTERNAL_LIB_DXSDK8}.zip)
set(U3_URL_TO_EXTERNAL_LIB_DXSDK8_SRC ${U3_URL_TO_EXTERNAL_LIBS_SRC}/lib-dxsdk8-src-${U3_VERSION_EXTERNAL_LIB_DXSDK8}.zip)

set(U3_EXTERNAL_LIB_DXSDK8_8_0_MD5 dc14af80cb2df2071f7cfd1773292e49)
set(U3_EXTERNAL_LIB_DXSDK8_8_0_MD5_Windows_MSVC_MSVC__AMD64_Release_none dc14af80cb2df2071f7cfd1773292e49)
set(U3_EXTERNAL_LIB_DXSDK8_8_0_MD5_Windows_MSVC_MSVC__AMD64_Debug_none dc14af80cb2df2071f7cfd1773292e49)
set(U3_EXTERNAL_LIB_DXSDK8_8_0_MD5_Windows_MSVC_MSVC__Win32_Release_none dc14af80cb2df2071f7cfd1773292e49)
set(U3_EXTERNAL_LIB_DXSDK8_8_0_MD5_Windows_MSVC_MSVC__Win32_Debug_none dc14af80cb2df2071f7cfd1773292e49)

set(U3_EXTERNAL_LIB_DXSDK8_MD5 ${U3_EXTERNAL_LIB_DXSDK8${U3_VERSION_EXTERNAL_LIB_DXSDK8_CID}_MD5})
