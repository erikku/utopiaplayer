INCLUDE_DIRECTORIES(${UTOPIADB_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libutopiaplayer/src ${CMAKE_BINARY_DIR}/libutopiaplayer/src)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libutopiaplayer/src)

SET(UtopiaBrowser_app_SRCS
	Browser.cpp
	UtopiaBrowser.cpp
)

SET(UtopiaBrowser_app_HDRS
	Browser.h
)

QT4_WRAP_CPP(UtopiaBrowser_app_SRCS ${UtopiaBrowser_app_HDRS})

ADD_EXECUTABLE(utopiabrowser ${UtopiaBrowser_app_SRCS})

ADD_DEPENDENCIES(utopiabrowser utopiabrowser)

TARGET_LINK_LIBRARIES(utopiabrowser ${QT_LIBRARIES} utopiaplayer)

INSTALL(TARGETS utopiabrowser DESTINATION bin)
