#!/bin/bash
# u3oko-orangepi-rel-lib-ub-clang-ninja.sh
# author      Erashov Anton erashov2026@proton.me
# date        01.01.2026
# copyright   Erashov A.I.

export U3_APPL_NAME=u3oko
export U3_COMMERCIAL_PART=1
export U3_AS_LIBS=1
export U3_TOOLCHAIN=./../cmake/toolchains/orangepi-arm64-clang.cmake
export U3_SANITY=none
export U3_BUILD=Release
export U3_BUILD_PREFIX=rel
export U3_OS=OrangePi
export U3_GENERATOR=Ninja

source ./u3-build.sh
