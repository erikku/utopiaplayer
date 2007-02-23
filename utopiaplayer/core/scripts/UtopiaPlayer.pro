INCPATH += ../Include

LIBS                += -lUtopiaPlayer -L../Build
DESTDIR              = ../Build
OBJECTS_DIR          = ../Build/.objs
MOC_DIR              = ../Build/.moc
RCC_DIR              = ../Build/.rcc
UI_DIR               = ../Build/.ui

Release:LIBS        += -lUtopiaPlayer -L../Release
Release:DESTDIR      = ../Release
Release:OBJECTS_DIR  = ../Release/.objs
Release:MOC_DIR      = ../Release/.moc
Release:RCC_DIR      = ../Release/.rcc
Release:UI_DIR       = ../Release/.ui

Debug:LIBS          += -lUtopiaPlayer -L../Debug
Debug:DESTDIR        = ../Debug
Debug:OBJECTS_DIR    = ../Debug/.objs
Debug:MOC_DIR        = ../Debug/.moc
Debug:RCC_DIR        = ../Debug/.rcc
Debug:UI_DIR         = ../Debug/.ui

win32-x-g++:RC_FILE = UtopiaPlayer_res.rc
win32::RC_FILE = UtopiaPlayer_res.rc

SOURCES += ../Source/UtopiaPlayer.cpp
