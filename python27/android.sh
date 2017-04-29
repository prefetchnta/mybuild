#!/bin/sh
chmod +x ./cleanup.sh
chmod +x ./configure
chmod +x ./ndk_setup.sh
chmod +x ./setup.py
chmod +x ./Modules/*.py
chmod +x ./Modules/makesetup
chmod +x ./Parser/*.py
chmod +x ./Parser/pgen
chmod +x ./Python/*.py
rm -f ./Modules/Setup
rm -f ./Modules/Setup.local
source ./ndk_setup.sh
./configure --prefix=/data/local --exec_prefix=/data/local --host=arm-linux-androideabi --build=x86_64-linux --disable-ipv6 ac_cv_file__dev_ptc=no ac_cv_file__dev_ptmx=no
