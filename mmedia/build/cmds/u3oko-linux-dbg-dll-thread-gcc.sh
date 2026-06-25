#!/bin/bash
# u3oko-linux-dbg-dll-thread-gcc.sh
# author      Erashov Anton erashov2026@proton.me
# date        01.01.2026
# copyright   Erashov A.I.

export U3_APPL_NAME=u3oko
export U3_COMMERCIAL_PART=1
export U3_AS_LIBS=0
export U3_TOOLCHAIN=./../cmake/toolchains/linux-x64-gcc.cmake
export U3_SANITY=thread
export U3_BUILD=Debug
export U3_BUILD_PREFIX=dbg
export U3_OS=Linux
#export U3_USE_GIT_HASH_FOR_MARK_BUILD=TRUE

source ./u3-build.sh
