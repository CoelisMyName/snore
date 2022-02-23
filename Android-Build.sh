#!/bin/bash
#configure here
sdk=/C/Users/Carlyle/AppData/Local/Android/Sdk
#and here
ndk_version=23.1.7779620
#and here
api_version=28
#finally here
cmake_version=3.18.1

android=android-$api_version

ndk=$sdk/ndk/$ndk_version

cmake_toolchain_file=$ndk/build/cmake/android.toolchain.cmake

cmake=$sdk/cmake/$cmake_version/bin/cmake

ninja=$sdk/cmake/$cmake_version/bin/ninja

src=$(pwd)

build=$src/build

abis=(arm64-v8a armeabi-v7a x86_64 x86)

include=$src/release/include/

mkdir -p "$include" && cp -f "$src"/snore.h "$include"/snore.h || exit

for i in $(seq 0 3)
do

compile=$build/${abis[$i]}

release=$src/release/android/

$cmake -H"$src" -B"$compile" -DANDROID_ABI="${abis[$i]}" -DANDROID_PLATFORM=$android -DANDROID_NDK=$ndk \
-DCMAKE_TOOLCHAIN_FILE=$cmake_toolchain_file -G Ninja -DCMAKE_MAKE_PROGRAM=$ninja || exit

cd "$compile" || exit

$ninja && mkdir -p "$release"/"${abis[$i]}" && mv -f "$compile"/libsnore.so "$release"/"${abis[$i]}"/libsnore.so || exit

cd "$src" || exit

done

rm -f -r "$build"