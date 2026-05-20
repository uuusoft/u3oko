#!/bin/bash
# u3-build.sh
# author      Erashov Anton erashov2026@proton.me
# date        01.01.2026
# copyright   Erashov A.I.

if [[ ! -v ASAN_OPTIONS ]]; then
    ASAN_OPTIONS=detect_odr_violation=0 
fi

if [[ ! -v U3_APPL_NAME ]]; then
    U3_APPL_NAME=u3oko
fi

if [[ ! -v U3_TOOLCHAIN ]]; then
    U3_TOOLCHAIN=./../../mmedia/build/cmake/toolchains/linux-arm64-gcc.cmake
fi

if [[ ! -v U3_BUILD ]]; then
    U3_BUILD=Debug
fi

if [[ ! -v U3_BUILD_PREFIX ]]; then
    U3_BUILD_PREFIX=dbg
fi

if [[ ! -v U3_SANITY ]]; then
    U3_SANITY=ub
fi

if [[ ! -v U3_OS ]]; then
    U3_OS=OrangePi
fi

if [[ ! -v U3_AS_LIBS ]]; then
    U3_AS_LIBS=0
fi

if [[ ${U3_AS_LIBS} == "1" ]]; then
    U3_LIBS_PREFIX=lib
else
    U3_LIBS_PREFIX=dll
fi

if [[ ! -v U3_GENERATOR ]]; then
    U3_GENERATOR=Unix Makefiles
fi

#if [[ ${U3_GENERATOR} == "Ninja" ]]; then
#    U3_GENERATOR="-G ${U3_GENERATOR}"
#fi

U3_FILE_TOOLCHAIN=$(basename ${U3_TOOLCHAIN} .cmake)
U3_BIN=./../builds-${U3_LIBS_PREFIX}-${U3_BUILD_PREFIX}-${U3_SANITY}-${U3_FILE_TOOLCHAIN}-${U3_GENERATOR}
#U3_EXT_PARAMS="-DU3_FORCE_COMPILE_ALL_EXT_LIBS=0"
U3_ABSOULT_TOOLCHAIN=$(realpath ${U3_TOOLCHAIN})

echo U3_APPL_NAME=${U3_APPL_NAME}
echo U3_TOOLCHAIN=${U3_TOOLCHAIN}
echo U3_ABSOULT_TOOLCHAIN=${U3_ABSOULT_TOOLCHAIN}
echo U3_BIN=${U3_BIN}
echo U3_BUILD=${U3_BUILD}
echo U3_SANITY=${U3_SANITY}
echo U3_BUILD_PREFIX=${U3_BUILD_PREFIX}
echo U3_OS=${U3_OS}
echo U3_AS_LIBS=${U3_AS_LIBS}
echo U3_EXT_PARAMS=${U3_EXT_PARAMS}
echo U3_LIBS_PREFIX=${U3_LIBS_PREFIX}
echo U3_GENERATOR=${U3_GENERATOR}

cd ./../../
cmake -G "${U3_GENERATOR}" -S . -B ${U3_BIN} -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${U3_ABSOULT_TOOLCHAIN} -DCMAKE_BUILD_TYPE=${U3_BUILD} -DU3_APPL_NAME=${U3_APPL_NAME} -DU3_BUILD_MODULES_AS_LIBS=${U3_AS_LIBS} -DU3_SANITY_BUILD_TYPE=${U3_SANITY} ${U3_EXT_PARAMS}
cmake --build ${U3_BIN} -j 1 --config ${U3_BUILD}
#cmake --build ${U3_BIN}
echo cp -r ./assets/xmls/templates   ${U3_BIN}/${U3_OS}/${U3_BUILD}
cp -r ./assets/xmls/templates  ${U3_BIN}/${U3_OS}/${U3_BUILD}

#ps -a | grep mpl_uuu_appl | grep -v grep | awk '{print $2}' | xargs kill
ps -a | grep mpl_uuu_appl | awk '{print $1}' | xargs kill -9
#gnome-terminal -- bash -c "#cd ${U3_BIN}/${U3_OS}/${U3_BUILD} && ./mpl_uuu_appl; exec bash"
#gnome-terminal -- bash -c "echo Hello World; exec bash"