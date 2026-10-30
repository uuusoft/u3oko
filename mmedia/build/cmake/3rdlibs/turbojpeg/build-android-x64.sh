NDK_PATH=~/Android/Sdk/ndk/27.0.12077973
TOOLCHAIN=clang
ANDROID_VERSION=34
BUILD_DIRECTORY=./turbo_jpeg-util

cd ${BUILD_DIRECTORY}

cmake -G"Unix Makefiles" \
 -DANDROID_ABI=x86_64 \
 -DANDROID_ARM_MODE=x86 \
 -DANDROID_PLATFORM=android-${ANDROID_VERSION} \
 -DANDROID_TOOLCHAIN=${TOOLCHAIN} \
 -DCMAKE_ASM_FLAGS="--target=x86_64-linux-android${ANDROID_VERSION}" \
 -DCMAKE_TOOLCHAIN_FILE=${NDK_PATH}/build/cmake/android.toolchain.cmake

make
