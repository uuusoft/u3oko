#!/bin/bash
# u3-build.sh
# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2026
# copyright   Erashov A.I.

clear

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

if [[ ! -v U3_BUILD_TESTING ]]; then
    U3_BUILD_TESTING=0
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

if [[ ! -v U3_COMMERCIAL_PART ]]; then
    U3_COMMERCIAL_PART=0
fi

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
echo U3_USE_GIT_HASH_FOR_MARK_BUILD=${U3_USE_GIT_HASH_FOR_MARK_BUILD}

cd ./../../

#echo "start clang-tidy, results at ${U3_BIN}/clang-tidy-fixes.log"
#run-clang-tidy -p ${U3_BIN} -config-file ./../.clang-tidy > ${U3_BIN}/clang-tidy-fixes.log 2>&1

# config
cmake -G "${U3_GENERATOR}" -S . -B ${U3_BIN} -DCMAKE_TOOLCHAIN_FILE:FILEPATH=${U3_ABSOULT_TOOLCHAIN} -DCMAKE_BUILD_TYPE=${U3_BUILD} -DU3_APPL_NAME=${U3_APPL_NAME} -DU3_USE_GIT_HASH_FOR_MARK_BUILD=${U3_USE_GIT_HASH_FOR_MARK_BUILD} -DU3_COMMERCIAL_PART=${U3_COMMERCIAL_PART} -DU3_BUILD_MODULES_AS_LIBS=${U3_AS_LIBS} -DU3_SANITY_BUILD_TYPE=${U3_SANITY} -DU3_BUILD_TESTING=${U3_BUILD_TESTING} ${U3_EXT_PARAMS}

if [[ ${U3_BUILD_TESTING} == "1" ]]; then
    cmake --build ${U3_BIN} -j 1 --config ${U3_BUILD} --target ${U3_APPL_NAME}-tests
    ./${U3_BIN}/Linux/Release/${U3_APPL_NAME}-tests
    exit 1
fi

# build
cmake --build ${U3_BIN} -j 1 --config ${U3_BUILD}

# copy resource
echo cp -r ./assets/xmls/templates   ${U3_BIN}/${U3_OS}/${U3_BUILD}
cp -r ./assets/xmls/templates  ${U3_BIN}/${U3_OS}/${U3_BUILD}

# strip debug symbols from release
if [[ ${U3_BUILD} != "Debug" ]]; then
    #du -ch ${U3_BIN}/${U3_OS}/${U3_BUILD}/*.so | tail -n 1
    du -chx ${U3_BIN}/${U3_OS}/${U3_BUILD}/*.so
    #strip --strip-all ${U3_BIN}/${U3_OS}/${U3_BUILD}/mpl_mappl
    #strip -g -S -d --strip-debug ${U3_BIN}/${U3_OS}/${U3_BUILD}/mpl_mappl
    
    if [[ ${U3_AS_LIBS} == "0" ]]; then
        for file in ${U3_BIN}/${U3_OS}/${U3_BUILD}/*.so; do
            #[ -f "$file" ] &&  strip --strip-all "$file"
            #[ -f "$file" ] &&  strip -g -S -d --strip-debug "$file"            
        done
    fi
fi

#du -ch ${U3_BIN}/${U3_OS}/${U3_BUILD}/*.so | tail -n 1
du -chx ${U3_BIN}/${U3_OS}/${U3_BUILD}/*.so

# run
#ps -a | grep mpl_mappl | grep -v grep | awk '{print $2}' | xargs kill
#ps -a | grep mpl_mappl | awk '{print $1}' | xargs kill -9
#gnome-terminal -- bash -c "#cd ${U3_BIN}/${U3_OS}/${U3_BUILD} && ./mpl_mappl; exec bash"
#gnome-terminal -- bash -c "echo Hello World; exec bash"
#perf record -g ./mpl_mappl
#pert report
