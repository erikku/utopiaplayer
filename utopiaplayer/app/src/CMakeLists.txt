SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTXML TRUE)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/src ${CMAKE_BINARY_DIR}/core/src)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/core/src)

SET(UtopiaPlayer_SRCS
    UtopiaPlayer.cpp
)

ADD_EXECUTABLE(utopiaplayer_app ${UtopiaPlayer_SRCS})

ADD_DEPENDENCIES(utopiaplayer_app utopiaplayer)

TARGET_LINK_LIBRARIES(utopiaplayer_app ${QT_LIBRARIES} utopiaplayer)

INSTALL(TARGETS utopiaplayer_app DESTINATION bin)
