# author      Erashov Anton erashov2026@proton.me
# date        29.08.2024
# copyright   Erashov A.I.
# file        u3-orangepi-specific.cmake

set(U3_SHARED_COMPILE_OPTIONS_CPP
    ${U3_SHARED_COMPILE_OPTIONS_CPP}
    -std=${U3_CPP_STANDARD}
    -frtti
    -fexceptions
    -pthread
)

set(U3_SHARED_LINK_OPTIONS_CPP
    ${U3_SHARED_LINK_OPTIONS_CPP}
    -Wl,--no-undefined
    -Wl,-rpath='${ORIGIN}'
    -lpthread
    -ldl
    -lrt
)

set(U3_SHARED_COMPILE_DEF_CPP
    ${U3_SHARED_COMPILE_DEF_CPP}
    -DHAVE_NEON=1
    -DENABLE_NEON=ON
    -DU3_OS_ORANGE_PI=1
)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(U3_PREFIX_LIB_NAME lib)
set(U3_SUFFIX_LIB_NAME a)
set(U3_SUFFIX_DLL_NAME so)

if (U3_ENV_PTR_BITS_COUNT EQUAL 32)
  set(U3_SHARED_COMPILE_OPTIONS_CPP ${U3_SHARED_COMPILE_OPTIONS_CPP} -mfpu=neon)
  set(U3_ORANGE_PI_ARCH_ID arm)
else ()
  set(U3_ORANGE_PI_ARCH_ID arm64)
endif ()
