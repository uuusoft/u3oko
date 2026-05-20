#!/bin/bash
# u3oko-orangepi-rel-dll-ub-gcc.sh
# author      Erashov Anton erashov2026@proton.me
# date        01.01.2026
# copyright   Erashov A.I.

export U3_AS_LIBS=0
export U3_TOOLCHAIN=./../cmake/toolchains/orangepi-arm64-gcc.cmake
export U3_SANITY=ub
export U3_BUILD=Release
export U3_BUILD_PREFIX=rel
export U3_OS=OrangePi

source ./u3-build.sh
