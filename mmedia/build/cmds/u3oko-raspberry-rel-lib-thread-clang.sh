#!/bin/bash
# u3oko-raspberry-rel-lib-thread-clang.sh
# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2026
# copyright   Erashov A.I.

export U3_APPL_NAME=u3oko
#export U3_COMMERCIAL_PART=1
export U3_AS_LIBS=1
export U3_TOOLCHAIN=./../cmake/toolchains/raspberry-arm64-clang.cmake
export U3_SANITY=thread
export U3_BUILD=Release
export U3_BUILD_PREFIX=rel
export U3_OS=Raspberry

source ./u3-build.sh
