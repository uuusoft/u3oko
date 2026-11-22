# author      Erashov Anton erashov2026@proton.me
# date        21.03.2026
# copyright   Erashov A.I.
# file        u3-stb-lib-values.cmake

set(U3_3RDLIB_OSRC_URL_STB https://github.com/nothings/stb.git)
set(U3_3RDLIB_NAME_STB stb)
set(U3_3RDLIB_VER_STB)
set(U3_3RDLIB_VER_STB_CID 0)

set(U3_3RDLIB_NAME_STB_BIN lib-stb-bin-${U3_3RDLIB_VER_STB}-${U3_GENV_RAW_3RDLIB_POSTFIX}.zip)
set(U3_3RDLIB_ESRC_URL_STB_BIN ${U3_3RDLIBS_URL_BIN}/${U3_3RDLIB_NAME_STB_BIN})
set(U3_3RDLIB_ESRC_URL_STB_SRC ${U3_3RDLIBS_URL_SRC}/lib-stb-src.zip)
set(U3_3RDLIB_STB_FILE_NAME "${U3_PREFIX_LIB_NAME}stb-util.${U3_SUFFIX_LIB_NAME}")

set(U3_3RDLIB_STB_0_MD5 0)
set(U3_3RDLIB_STB_0_EXT_MD5 0)
set(U3_3RDLIB_STB_EXT_MD5 0)

set(U3_3RDLIB_STB_MD5 ${U3_3RDLIB_STB_${U3_3RDLIB_VER_STB_CID}_MD5})
