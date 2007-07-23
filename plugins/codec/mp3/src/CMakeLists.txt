PROJECT(MP3FilePlugin)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/libutopiaplayer/src ${CMAKE_SOURCE_DIR}/libutopiaplayer/interfaces)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libutopiaplayer/src)

ADD_DEFINITIONS(-DQT_PLUGIN -DQT_SHARED -DQT_NO_DEBUG -DQT_DLL)

SET(MP3FilePlugin_SRCS
	MP3File.cpp
    MP3FilePlugin.cpp
)

SET(MP3FilePlugin_HDRS
	MP3FilePlugin.h
)

QT4_WRAP_CPP(MP3FilePlugin_SRCS ${MP3FilePlugin_HDRS})

ADD_LIBRARY(utopiaplayer_mp3file_plugin SHARED ${MP3FilePlugin_SRCS})

TARGET_LINK_LIBRARIES(utopiaplayer_mp3file_plugin ${QT_LIBRARIES} utopiaplayer)

INSTALL(TARGETS utopiaplayer_mp3file_plugin DESTINATION share/utopiaplayer/plugins/codec)
