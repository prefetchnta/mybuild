#!/bin/sh
chmod -R +x *
rm -f ./Modules/Setup
rm -f ./Modules/Setup.local
source ./ndk_setup.sh
./configure --prefix=/data/local --exec_prefix=/data/local --host=arm-linux-androideabi --build=x86_64-linux --disable-ipv6 ac_cv_file__dev_ptc=no ac_cv_file__dev_ptmx=no
