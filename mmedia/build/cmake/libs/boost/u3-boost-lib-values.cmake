# author      Erashov Anton erashov2026@proton.me
# date        30.08.2024
# copyright   Erashov A.I.
# file        u3-boost-lib-values.cmake

set(U3_VERSION_EXTLIB_BOOST 1.91.0)

string(MAKE_C_IDENTIFIER ${U3_VERSION_EXTLIB_BOOST} U3_VERSION_EXTLIB_BOOST_CID)
string(REPLACE "." "_" U3_VERSION_EXTLIB_BOOST_CID_SOURCE ${U3_VERSION_EXTLIB_BOOST})

set(U3_URL_TO_EXTLIB_BOOST_SRC_EXT https://archives.boost.io/release/${U3_VERSION_EXTLIB_BOOST}/source/boost_${U3_VERSION_EXTLIB_BOOST_CID_SOURCE}.tar.gz)
set(U3_ARCHIVE_NAME_EXTLIB_BOOST boost.xxx)
set(U3_NAME_EXTLIB_BOOST boost)

set(U3_URL_TO_EXTLIB_BOOST_BIN ${U3_URL_TO_EXTLIBS_BIN}/lib-BOOST-bin-${U3_VERSION_EXTLIB_BOOST}-${U3_ENV_GEN_POSTFIX_NAME_TO_EXT_LIB}.zip)
set(U3_URL_TO_EXTLIB_BOOST_SRC ${U3_URL_TO_EXTLIBS_SRC}/lib-BOOST-src-${U3_VERSION_EXTLIB_BOOST}.zip)

set(U3_EXTLIB_BOOST_1_91_0_MD5 e799ed3e5af9708739fb2e088c670ae1)
set(U3_EXTLIB_BOOST_1_91_0_MD5_Linux_Clang_21_Clang_21__x64_Release_none 523b64c2de0053755f766bde03c82bfe)
set(U3_EXTLIB_BOOST_1_91_0_MD5_Linux_Clang_21_Clang_21__x64_Debug_none a44c69b317a15de564f59951182b5e8a)
set(U3_EXTLIB_BOOST_1_91_0_MD5_Linux_Clang_21_Clang_21__x64_Debug_address 7073385c5041adbdfb8ba6e5d57b8c0d)
set(U3_EXTLIB_BOOST_1_91_0_MD5_Linux_Clang_21_Clang_21__x64_Release_address 7acb949d488406ca413c806842522839)

set(U3_EXTLIB_BOOST_1_91_0_MD5_Android_Clang_21_Clang_21__aarch64_RelWithDebInfo_none aebfb1e1ddbb3e2cc7e1ff8f325608f6)
set(U3_EXTLIB_BOOST_1_91_0_MD5_Android_Clang_21_Clang_21__aarch64_Debug_none aebfb1e1ddbb3e2cc7e1ff8f325608f6)
set(U3_EXTLIB_BOOST_1_91_0_MD5_Android_Clang_21_Clang_21__aarch64_Debug_hwaddress aebfb1e1ddbb3e2cc7e1ff8f325608f6)

set(U3_EXTLIB_BOOST_MD5 ${U3_EXTLIB_BOOST${U3_VERSION_EXTLIB_BOOST_CID}_MD5})
