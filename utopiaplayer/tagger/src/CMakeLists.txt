INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/src ${CMAKE_BINARY_DIR}/core/src)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/core/src)

SET(UtopiaTagger_app_SRCS
	FileList.cpp
	UtopiaTagger.cpp
)

SET(UtopiaTagger_app_HDRS
	FileList.h
)

QT4_WRAP_CPP(UtopiaTagger_app_SRCS ${UtopiaTagger_app_HDRS})

ADD_EXECUTABLE(utopiatagger ${UtopiaTagger_app_SRCS})

ADD_DEPENDENCIES(utopiatagger utopiatagger)

TARGET_LINK_LIBRARIES(utopiatagger ${QT_LIBRARIES} utopiaplayer)

INSTALL(TARGETS utopiatagger DESTINATION bin)
