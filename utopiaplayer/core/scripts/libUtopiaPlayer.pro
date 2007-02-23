TEMPLATE = lib
VERSION = 0.1.0
TARGET = UtopiaPlayer
DEFINES = UPLAYER_BUILD _LARGEFILE_SOURCE _FILE_OFFSET_BITS=64

INCPATH     += ../Include /usr/include/taglib /usr/include/gstreamer-0.8 /usr/include/glib-2.0 /usr/lib/glib-2.0/include /usr/include/libxml2
LIBPATH     += /usr/lib/gstreamer-0.8
LIBS        += -ltag -lgstreamer-0.8 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lglib-2.0

DESTDIR              = ../Build
OBJECTS_DIR          = ../Build/.objs
MOC_DIR              = ../Build/.moc
RCC_DIR              = ../Build/.rcc
UI_DIR               = ../Build/.ui

Release:DESTDIR      = ../Release
Release:OBJECTS_DIR  = ../Release/.objs
Release:MOC_DIR      = ../Release/.moc
Release:RCC_DIR      = ../Release/.rcc
Release:UI_DIR       = ../Release/.ui

Debug:DESTDIR        = ../Debug
Debug:OBJECTS_DIR    = ../Debug/.objs
Debug:MOC_DIR        = ../Debug/.moc
Debug:RCC_DIR        = ../Debug/.rcc
Debug:UI_DIR         = ../Debug/.ui

QT += sql

TRANSLATIONS = UtopiaPlayer_ja.ts
RESOURCES    = UtopiaPlayer.qrc

FORMS += Login.ui OptionsDialog.ui InsertAlbum.ui InsertArtist.ui InsertGenre.ui

HEADERS += ../Include/Application.h \
           ../Include/AlbumList.h \
           ../Include/DatabaseList.h \
#           ../Include/DatabasePlugin.h \
           ../Include/GStreamerPlugin.h \
           ../Include/InsertAlbum.h \
           ../Include/InsertArtist.h \
           ../Include/InsertGenre.h \
           ../Include/Login.h \
           ../Include/OptionsDialog.h \
           ../Include/OutputPlugin.h \
           ../Include/SaveTagsThread.h \
           ../Include/SongList.h \
           ../Include/SongListWindow.h \
           ../Include/SplashScreen.h

SOURCES += ../Source/Application.cpp \
           ../Source/AlbumList.cpp \
           ../Source/DatabaseList.cpp \
           ../Source/GStreamerPlugin.cpp \
           ../Source/InsertAlbum.cpp \
           ../Source/InsertArtist.cpp \
           ../Source/InsertGenre.cpp \
           ../Source/Login.cpp \
           ../Source/SaveTagsThread.cpp \
           ../Source/SongList.cpp \
           ../Source/SongListWindow.cpp \
           ../Source/SplashScreen.cpp \
           ../Source/OptionsDialog.cpp
