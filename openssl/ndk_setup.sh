#!/bin/sh
export NDK_ROOT=~/ndk
export TOOLCHAINS=$NDK_ROOT/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin
export PATH=$TOOLCHAINS:$PATH
export CC=$TOOLCHAINS/arm-linux-androideabi-gcc
export CXX=$TOOLCHAINS/arm-linux-androideabi-g++
export CPP=$TOOLCHAINS/arm-linux-androideabi-cpp
export LD=$TOOLCHAINS/arm-linux-androideabi-ld
export AS=$TOOLCHAINS/arm-linux-androideabi-as
export AR=$TOOLCHAINS/arm-linux-androideabi-ar
export STRIP=$TOOLCHAINS/arm-linux-androideabi-strip
export OBJCOPY=$TOOLCHAINS/arm-linux-androideabi-objcopy
export OBJDUMP=$TOOLCHAINS/arm-linux-androideabi-objdump
export RANLIB=$TOOLCHAINS/arm-linux-androideabi-ranlib
export NM=$TOOLCHAINS/arm-linux-androideabi-nm
export STRINGS=$TOOLCHAINS/arm-linux-androideabi-strings
export READELF=$TOOLCHAINS/arm-linux-androideabi-readelf
export SYS_ROOT=$NDK_ROOT/platforms/android-14/arch-arm/usr
export NDK_INC=$SYS_ROOT/include
export NDK_LIB=$SYS_ROOT/lib
export CFLAGS="-mandroid -march=armv7-a -fomit-frame-pointer -I$NDK_INC --sysroot=$SYS_ROOT -ffunction-sections -fdata-sections"
export CXXFLAGS=$CFLAGS
export CPPFLAGS=$CFLAGS
export LDFLAGS="-static -L$NDK_LIB -Wl,--gc-sections -Wl,--allow-shlib-undefined"
cp $NDK_LIB/crtbegin_static.o crtbegin_static.o
cp $NDK_LIB/crtend_android.o crtend_android.o
