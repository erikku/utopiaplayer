PROJECT(iPodPlugin)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/interfaces)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/core/src)

ADD_DEFINITIONS(-DQT_PLUGIN -DQT_SHARED)

SET(iPodPlugin_SRCS
	ipod.cpp
	iPodNotes.cpp
    ipodplugin.cpp
	mhdb.cpp
)

SET(iPodPlugin_HDRS
	ipod.h
	ipodnode.h
	iPodNotes.h
	ipodplugin.h
	mhdb.h
)

SET(iPodPlugin_UIS
    ../ui/mhdb.ui
)

QT4_WRAP_UI(iPodPlugin_SRCS ${iPodPlugin_UIS})

QT4_WRAP_CPP(iPodPlugin_SRCS ${iPodPlugin_HDRS})

ADD_LIBRARY(utopiaplayer_ipod_plugin SHARED ${iPodPlugin_SRCS})

TARGET_LINK_LIBRARIES(utopiaplayer_ipod_plugin ${QT_LIBRARIES} utopiaplayer)

INSTALL(TARGETS utopiaplayer_ipod_plugin DESTINATION share/utopiaplayer/plugins/device)
