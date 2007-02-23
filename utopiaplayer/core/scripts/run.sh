#!/bin/bash
qmake libUtopiaPlayer.pro
make
qmake UtopiaPlayer.pro
make
cd ../Build
export LD_LIBRARY_PATH=`pwd`:/home/apps/lib
cd ../Scripts
../Build/UtopiaPlayer
