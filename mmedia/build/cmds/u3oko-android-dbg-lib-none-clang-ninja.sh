#!/bin/bash
# u3oko-android-dbg-lib-none-clang-ninja.sh
# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2026
# copyright   Erashov A.I.

#EAI-REFACT
#set in gradle.build
#export U3_APPL_NAME=u3oko
#export U3_COMMERCIAL_PART=1
#export U3_AS_LIBS=1
#export U3_TOOLCHAIN=./../cmake/toolchains/linux-x64-clang.cmake
#export U3_SANITY=none
#export U3_BUILD=Debug
#export U3_BUILD_PREFIX=dbg
#export U3_OS=Linux
#export U3_GENERATOR=Ninja
export JAVA_HOME=/home/erashov/Documents/android-studio/jbr
#export JAVA_HOME=${GRADLE_LOCAL_JAVA_HOME}

cd ./../../appls/u3oko/android
chmod +x ./gradlew
#./gradlew clean build
./gradlew assembleDebug
./gradlew tasks
./gradlew installDebug
