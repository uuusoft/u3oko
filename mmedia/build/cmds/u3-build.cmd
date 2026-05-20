REM u3-build.cmd
REM author      Erashov Anton erashov2026@proton.me
REM date        01.01.2026
REM copyright   Erashov A.I.

IF NOT DEFINED ASAN_OPTIONS (
    set "ASAN_OPTIONS=detect_odr_violation=0"
)

IF NOT DEFINED U3_TOOLCHAIN (
    set "U3_TOOLCHAIN=./mmedia/build/cmake/toolchains/windows-x64-msv.cmake"
)

IF NOT DEFINED U3_BUILD (
    set "U3_BUILD=Debug"
)

IF NOT DEFINED U3_BUILD_PREFIX (
    set "U3_BUILD_PREFIX=dbg"
)

IF NOT DEFINED U3_SANITY (
    set "U3_SANITY=ub"
)

IF NOT DEFINED U3_OS (
    set "U3_OS=Windows"
)

IF NOT DEFINED U3_AS_LIBS (
    set "U3_AS_LIBS=0"
)

IF "%U3_AS_LIBS%"=="1" (
    set "U3_LIBS_PREFIX=lib"
)
ELSE (
    set "U3_LIBS_PREFIX=dll"
)

IF "%U3_GENERATOR%"=="Ninja" (
    set "U3_GENERATOR="-G %U3_GENERATOR%"
)

REM set "U3_FILE_TOOLCHAIN=%basename %U3_TOOLCHAIN% .cmake%"
REM set "U3_FILE_TOOLCHAIN=(Get-Item "%U3_TOOLCHAIN%").BaseName"
set "U3_FILE_TOOLCHAIN=%U3_TOOLCHAIN%"
set "U3_FILE_TOOLCHAIN=windows-x64-msv"
set "U3_BIN=./../builds-%U3_LIBS_PREFIX%-%U3_BUILD_PREFIX%-%U3_SANITY%-%U3_FILE_TOOLCHAIN%-%U3_GENERATOR%"
set "U3_EXT_PARAMS=-DU3_FORCE_COMPILE_ALL_EXT_LIBS=0"
REM set "U3_ABSOULT_TOOLCHAIN=%realpath %U3_TOOLCHAIN%%"
REM set "U3_ABSOULT_TOOLCHAIN=%U3_TOOLCHAIN%"
REM set "U3_ABSOULT_TOOLCHAIN=C:/Users/ARleap/Documents/u3media/mmedia/build/cmake/toolchains/windows-x64-msv.cmake"
set "U3_ABSOULT_TOOLCHAIN=c:/Users/ARleap/Documents/u3media/mmedia/build/cmake/toolchains/windows-x64-msv.cmake"

echo U3_TOOLCHAIN=%U3_TOOLCHAIN%
echo U3_ABSOULT_TOOLCHAIN=%U3_ABSOULT_TOOLCHAIN%
echo U3_BIN=%U3_BIN%
echo U3_BUILD=%U3_BUILD%
echo U3_SANITY=%U3_SANITY%
echo U3_BUILD_PREFIX=%U3_BUILD_PREFIX%
echo U3_OS=%U3_OS%
echo U3_AS_LIBS=%U3_AS_LIBS%
echo U3_EXT_PARAMS=%U3_EXT_PARAMS%
echo U3_LIBS_PREFIX=%U3_LIBS_PREFIX%
echo U3_GENERATOR=%U3_GENERATOR%

cd ./../../
cmake %U3_GENERATOR% -S . -B %U3_BIN% -DCMAKE_TOOLCHAIN_FILE:FILEPATH=%U3_ABSOULT_TOOLCHAIN% -DCMAKE_BUILD_TYPE=%U3_BUILD% -DU3_BUILD_MODULES_AS_LIBS=%U3_AS_LIBS% -DU3_SANITY_BUILD_TYPE=%U3_SANITY% %U3_EXT_PARAMS%
cmake --build %U3_BIN% -j 1 --config %U3_BUILD%
REM #cmake --build %U3_BIN%
REM echo xcopy ./assets/xmls/templates  "%U3_BIN%/%U3_OS%/%U3_BUILD%" /s /e
xcopy .\assets\xmls\templates  "%U3_BIN%\%U3_OS%\%U3_BUILD%\templates" /s /e
