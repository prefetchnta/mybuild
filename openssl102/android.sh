#!/bin/sh
chmod -R +x *
source ./ndk_setup.sh
MACHINE=armv7 SYSTEM=android ./config -fPIC
