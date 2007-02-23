#!/bin/bash

#QTDIR="/home/eric/qt4"
#PATH="/home/eric/qt4/bin:$PATH"

qmake libUtopiaPlayer.pro
make clean
uic -o ../Build/.ui/ui_Login.h Login.ui
uic -o ../Build/.ui/ui_OptionsDialog.h OptionsDialog.ui
uic -o ../Build/.ui/ui_InsertAlbum.h InsertAlbum.ui
uic -o ../Build/.ui/ui_InsertArtist.h InsertArtist.ui
uic -o ../Build/.ui/ui_InsertGenre.h InsertGenre.ui
make
qmake UtopiaPlayer.pro
make clean
make
