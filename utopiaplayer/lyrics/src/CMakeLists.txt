SET(QT_USE_QTXML TRUE)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/src ${CMAKE_BINARY_DIR}/core/src)

SET(UtopiaLyrics_SRCS
	mainwindow.cpp
	qrubylabel.cpp
	utopialyrics.cpp
	verseedit.cpp
	xmlrubyhandler.cpp
)

SET(UtopiaLyrics_HDRS
	mainwindow.h
	qrubylabel.h
	verseedit.h
)

SET(UtopiaLyrics_UIS
)

QT4_WRAP_UI(UtopiaLyrics_SRCS ${UtopiaLyrics_UIS})

QT4_WRAP_CPP(UtopiaLyrics_SRCS ${UtopiaLyrics_HDRS})

ADD_EXECUTABLE(utopialyrics ${UtopiaLyrics_SRCS})

ADD_DEPENDENCIES(utopialyrics utopiaplayer)

TARGET_LINK_LIBRARIES(utopialyrics ${QT_LIBRARIES})

INSTALL(TARGETS utopialyrics DESTINATION bin)
