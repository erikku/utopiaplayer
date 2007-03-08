IF(IPOD_PLUGIN)

PROJECT(iPodPlugin)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/interfaces)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/core/src)

IF(IPOD_PLUGIN_STATIC)
	ADD_DEFINITIONS(-DQT_PLUGIN -DQT_STATICPLUGIN)
ELSE(IPOD_PLUGIN_STATIC)
	ADD_DEFINITIONS(-DQT_PLUGIN -DQT_SHARED)
ENDIF(IPOD_PLUGIN_STATIC)

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
	
	# We need to moc and link in all classes derived from QObject that sit outside
	# of the plugin (like from libutopiaplayer), otherwise the application will
	# crash under Windows.
	${CMAKE_SOURCE_DIR}/core/src/Device.h
)

SET(iPodPlugin_UIS
    ../ui/mhdb.ui
)

QT4_WRAP_UI(iPodPlugin_SRCS ${iPodPlugin_UIS})

QT4_WRAP_CPP(iPodPlugin_SRCS ${iPodPlugin_HDRS})

IF(IPOD_PLUGIN_STATIC)
	ADD_LIBRARY(utopiaplayer_ipod_plugin STATIC ${iPodPlugin_SRCS})
ELSE(IPOD_PLUGIN_STATIC)
	ADD_LIBRARY(utopiaplayer_ipod_plugin SHARED ${iPodPlugin_SRCS})
ENDIF(IPOD_PLUGIN_STATIC)

TARGET_LINK_LIBRARIES(utopiaplayer_ipod_plugin ${QT_LIBRARIES} utopiaplayer)

INSTALL(TARGETS utopiaplayer_ipod_plugin DESTINATION share/utopiaplayer/plugins/device)

ENDIF(IPOD_PLUGIN)
