PROJECT(XinePlugin)

INCLUDE(${QT_USE_FILE})
INCLUDE(UsePkgConfig)

PKGCONFIG(libxine XINE_INCLUDE_DIR XINE_LIB_DIR XINE_LD_FLAGS XINE_CPP_FLAGS)
IF(DEFINED XINE_INCLUDE_DIR)
	MESSAGE("-- Found xine")
ELSE(DEFINED XINE_INCLUDE_DIR)
	MESSAGE(FATAL_ERROR "xine Not found! You need to fix this!")
ENDIF(DEFINED XINE_INCLUDE_DIR)

INCLUDE_DIRECTORIES(${XINE_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/interfaces)
ADD_DEFINITIONS(-DQT_PLUGIN ${XINE_CPP_FLAGS})
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/core/src)

SET(XinePlugin_SRCS
    xineplugin.cpp
)

SET(XinePlugin_HDRS
	xineplugin.h
)

QT4_WRAP_CPP(XinePlugin_SRCS ${XinePlugin_HDRS})

ADD_LIBRARY(utopiaplayer_xine_plugin SHARED ${XinePlugin_SRCS})

ADD_DEPENDENCIES(utopiaplayer_xine_plugin utopiaplayer)

TARGET_LINK_LIBRARIES(utopiaplayer_xine_plugin ${QT_LIBRARIES} ${XINE_LD_FLAGS} utopiaplayer)

INSTALL(TARGETS utopiaplayer_xine_plugin DESTINATION share/utopiaplayer/plugins/output)
