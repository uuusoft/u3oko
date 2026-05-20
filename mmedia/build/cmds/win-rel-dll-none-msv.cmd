REM win-rel-dll-none-msv.cmd
REM author      Erashov Anton erashov2026@proton.me
REM date        01.01.2026
REM copyright   Erashov A.I.

set "U3_AS_LIBS=0"
set "U3_TOOLCHAIN=./../cmake/toolchains/windows-x64-msv.cmake"
set "U3_SANITY=none"
set "U3_BUILD=Release"
set "U3_BUILD_PREFIX=rel"
set "U3_OS=Win64"

call ./u3-build.cmd
