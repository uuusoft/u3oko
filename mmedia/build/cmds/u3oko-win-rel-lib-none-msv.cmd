REM u3oko-win-rel-lib-none-msv.cmd
REM author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
REM date        01.01.2026
REM copyright   Erashov A.I.

set "U3_APPL_NAME=u3oko"
set "U3_COMMERCIAL_PART=1"
set "U3_AS_LIBS=1"
set "U3_TOOLCHAIN=./../cmake/toolchains/windows-x64-msv.cmake"
set "U3_SANITY=none"
set "U3_BUILD=Release"
set "U3_BUILD_PREFIX=rel"
set "U3_OS=Win64"

call ./u3-build.cmd
