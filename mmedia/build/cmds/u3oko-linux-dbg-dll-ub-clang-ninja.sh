#!/bin/bash
# u3oko-linux-dbg-dll-ub-clang-ninja.sh
# author      Erashov Anton erashov2026@proton.me
# date        01.01.2026
# copyright   Erashov A.I.

export U3_AS_LIBS=0
export U3_TOOLCHAIN=./../cmake/toolchains/linux-x64-clang.cmake
export U3_SANITY=ub
export U3_BUILD=Debug
export U3_BUILD_PREFIX=dbg
export U3_OS=Linux
export U3_GENERATOR=Ninja

source ./u3-build.sh
