INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/src)

SET(UtopiaLyrics_SRCS
	mainwindow.cpp
	qrubylabel.cpp
	utopialyrics.cpp
	verseedit.cpp
	xmlrubyhandler.cpp
)

SET(UtopiaLyrics_UIS
)

KDE4_ADD_UI_FILES(UtopiaLyrics_SRCS ${UtopiaLyrics_UIS})

KDE4_AUTOMOC(${UtopiaLyrics_SRCS})

KDE4_ADD_KCFG_FILES(UtopiaLyrics_SRCS utopialyricssettings.kcfgc)

KDE4_ADD_EXECUTABLE(utopialyrics ${UtopiaLyrics_SRCS})

TARGET_LINK_LIBRARIES(utopialyrics ${KDE4_KDEUI_LIBS} kutils)

INSTALL(TARGETS utopialyrics DESTINATION ${BIN_INSTALL_DIR})
INSTALL(FILES utopialyrics.desktop DESTINATION ${XDG_APPS_DIR})
INSTALL(FILES utopialyrics.kcfg DESTINATION ${KCFG_INSTALL_DIR})
INSTALL(FILES utopialyricsui.rc DESTINATION ${DATA_INSTALL_DIR}/utopialyrics)

KDE4_INSTALL_ICONS(${ICON_INSTALL_DIR})
