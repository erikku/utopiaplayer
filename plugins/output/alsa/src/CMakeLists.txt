PROJECT(ALSAPlugin)

INCLUDE_DIRECTORIES(${ALSA_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/libutopiaplayer/src ${CMAKE_SOURCE_DIR}/libutopiaplayer/interfaces)

ADD_DEFINITIONS(-DQT_PLUGIN -DQT_SHARED)
ADD_DEFINITIONS(${ALSA_CPP_FLAGS})

SET(ALSAPlugin_SRCS
    ALSAPlugin.cpp
)

SET(ALSAPlugin_HDRS
	ALSAPlugin.h
)

QT4_WRAP_UI(ALSAPlugin_SRCS ${ALSAPlugin_UIS})

QT4_WRAP_CPP(ALSAPlugin_SRCS ${ALSAPlugin_HDRS})

ADD_LIBRARY(utopiaplayer_alsa_plugin SHARED ${ALSAPlugin_SRCS})

TARGET_LINK_LIBRARIES(utopiaplayer_alsa_plugin ${QT_LIBRARIES} ${ALSA_LD_FLAGS})

INSTALL(TARGETS utopiaplayer_alsa_plugin DESTINATION share/utopiaplayer/plugins/output)
