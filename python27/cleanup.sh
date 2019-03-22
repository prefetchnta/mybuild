#!/bin/sh
source ./ndk_setup.sh
arm-linux-androideabi-strip --strip-unneeded python
arm-linux-androideabi-strip --strip-unneeded libpython2.7.so.1.0
