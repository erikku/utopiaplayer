SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTXML TRUE)

INCLUDE_DIRECTORIES(${UTOPIADB_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libutopiaplayer/src ${CMAKE_BINARY_DIR}/libutopiaplayer/src)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libutopiaplayer/src)# ${CMAKE_BINARY_DIR}/plugins/output/xine/src)

SET(UtopiaPlayer_app_SRCS
	UtopiaPlayer.cpp
)

ADD_EXECUTABLE(utopiaplayer_app ${UtopiaPlayer_app_SRCS})

ADD_DEPENDENCIES(utopiaplayer_app utopiaplayer)

SET(utopiaplayer_app_LIBS ${QT_LIBRARIES} utopiaplayer)

IF(IPOD_PLUGIN_STATIC)
	ADD_DEPENDENCIES(utopiaplayer_app utopiaplayer_ipod_plugin)
	SET(utopiaplayer_app_LIBS ${utopiaplayer_app_LIBS} utopiaplayer_ipod_plugin)
	LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/plugins/device/ipod/src ${LINK_DIRECTORIES})
ENDIF(IPOD_PLUGIN_STATIC)

TARGET_LINK_LIBRARIES(utopiaplayer_app ${utopiaplayer_app_LIBS})

INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/utopiaplayer_app DESTINATION bin RENAME utopiaplayer)
