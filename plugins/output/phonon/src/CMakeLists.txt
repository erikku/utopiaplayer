PROJECT(PhononPlugin)

INCLUDE(UsePkgConfig)

LINK_DIRECTORIES(${KDE4_LIB_DIR})

INCLUDE_DIRECTORIES(${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/interfaces)

#ADD_DEFINITIONS()

SET(PhononPlugin_SRCS
    phononplugin.cpp
)

SET(PhononPlugin_HDRS
	${CMAKE_SOURCE_DIR}/core/interfaces/plugin.h
    ${CMAKE_SOURCE_DIR}/core/interfaces/outputinterface.h
)

QT4_WRAP_CPP(PhononPlugin_SRCS ${PhononPlugin_HDRS})

KDE4_AUTOMOC(${PhononPlugin_SRCS})

KDE4_ADD_PLUGIN(utopiaplayer_phonon_plugin ${PhononPlugin_SRCS})

KDE4_INSTALL_LIBTOOL_FILE(${PLUGIN_INSTALL_DIR} utopiaplayer_phonon_plugin)

TARGET_LINK_LIBRARIES(utopiaplayer_phonon_plugin ${KDE4_KDEUI_LIBS} phononcore)

INSTALL(TARGETS utopiaplayer_phonon_plugin DESTINATION ${PLUGIN_INSTALL_DIR})
INSTALL(FILES utopiaplayer_phonon_plugin.desktop DESTINATION ${SERVICES_INSTALL_DIR})
