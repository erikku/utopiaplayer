
SET(UTOPIADB_OFFICIAL true)
SET(UTOPIADB_REVISION 0)
SET(UTOPIADB_VERSION 0.1.0)
SET(UTOPIADB_VERSION_MAJOR 0)
SET(UTOPIADB_VERSION_MINOR 1)
SET(UTOPIADB_VERSION_REVISION 0)
SET(UTOPIADB_SANE_VERSION ${UTOPIADB_VERSION_MAJOR}.${UTOPIADB_VERSION_MINOR}.${UTOPIADB_VERSION_REVISION})

INCLUDE(FindSubversion)
IF(Subversion_FOUND)
	FIND_PATH(IS_SVN_CHECKOUT entries ${CMAKE_SOURCE_DIR}/.svn NO_DEFAULT_PATH)
	IF(IS_SVN_CHECKOUT)
		Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Project)
		SET(UTOPIADB_OFFICIAL false)
		SET(UTOPIADB_REVISION ${Project_WC_REVISION})
		SET(UTOPIADB_VERSION ${UTOPIADB_VERSION}-SVN${UTOPIADB_REVISION})
	ENDIF(IS_SVN_CHECKOUT)
ENDIF(Subversion_FOUND)

SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTXML TRUE)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.in ${CMAKE_CURRENT_BINARY_DIR}/configure.h @ONLY IMMEDIATE)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../scripts/utopiadb.pc.in ${CMAKE_CURRENT_BINARY_DIR}/utopiadb.pc @ONLY IMMEDIATE)

SET(utopiadb_SRCS
	album.cpp
	albumset.cpp
	artist.cpp
	blockparser.cpp
	composer.cpp
	cover.cpp
	credit.cpp
	genre.cpp
	individual.cpp
	metabase.cpp
	mood.cpp
	publisher.cpp
	qgzipfile.cpp
	sha1.c
	song.cpp
	songedition.cpp
	songfile.cpp
	songset.cpp
	sqlmetabase.cpp
	staff.cpp
	tagid.cpp
	utopiablock.cpp
	xmlmetabase.cpp
)

SET(utopiadb_HDRS
	metabase.h
	qgzipfile.h
	sqlmetabase.h
	xmlmetabase.h
)

SET(utopiadb_HDRS_NOMOC
	album.h
	albumset.h
	artist.h
	blockparser.h
	common.h
	composer.h
	cover.h
	credit.h
	genre.h
	individual.h
	mood.h
	publisher.h
	song.h
	songedition.h
	songfile.h
	songset.h
	staff.h
	tagid.h
	utopiablock.h
	utopiadb.h
)

FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include/utopiadb)

FOREACH(current_header ${utopiadb_HDRS} ${utopiadb_HDRS_NOMOC})
	CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/${current_header} ${CMAKE_BINARY_DIR}/include/utopiadb/${current_header} COPYONLY)
ENDFOREACH(current_header)

QT4_WRAP_CPP(utopiadb_SRCS ${utopiadb_HDRS})

ADD_LIBRARY(utopiadb SHARED ${utopiadb_SRCS})

SET_TARGET_PROPERTIES(utopiadb PROPERTIES VERSION ${UTOPIADB_SANE_VERSION} SOVERSION ${UTOPIADB_VERSION_MAJOR})

TARGET_LINK_LIBRARIES(utopiadb ${QT_LIBRARIES})

# Doxygen Docs
SET(DOXYGEN_LANG English)
OPTION(BUILD_DOCS "Build the documentation" OFF)

IF(BUILD_DOCS)
	INCLUDE(FindDoxygen)
	MAKE_DIRECTORY(${CMAKE_BINARY_DIR}/doc)
	MAKE_DIRECTORY(${CMAKE_BINARY_DIR}/doc/api)
	MAKE_DIRECTORY(${CMAKE_BINARY_DIR}/doc/api/html)

	SET(Doxyfile_in ${CMAKE_SOURCE_DIR}/scripts/Doxyfile.in)
	SET(Doxyfile ${CMAKE_BINARY_DIR}/Doxyfile)
	SET(Doxydepends ${Doxyfile_in} ${utopiadb_SRCS} ${utopiadb_HDRS} ${utopiadb_HDRS_NOMOC} ${CMAKE_SOURCE_DIR}/doc/common/Mainpage.dox)

	CONFIGURE_FILE(${Doxyfile_in} ${Doxyfile} @ONLY)

	ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_BINARY_DIR}/doc/api/utopiadb.tag COMMAND ${DOXYGEN} ${CMAKE_BINARY_DIR}/Doxyfile > ${CMAKE_BINARY_DIR}/doxygen.log DEPENDS ${Doxydepends} COMMENT "Generating API Documentation" VERBATIM)
	ADD_CUSTOM_TARGET(docs ALL DEPENDS ${Doxydepends} ${CMAKE_BINARY_DIR}/doc/api/utopiadb.tag)

	INSTALL(FILES ${CMAKE_BINARY_DIR}/doc/api/utopiadb.tag DESTINATION share/utopiadb/doc/api)
	INSTALL(DIRECTORY ${CMAKE_BINARY_DIR}/doc/api/html DESTINATION share/utopiadb/doc/api)

	ADD_DEPENDENCIES(utopiadb docs)
ENDIF(BUILD_DOCS)

INSTALL(TARGETS utopiadb DESTINATION lib)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/utopiadb.pc DESTINATION lib/pkgconfig)
INSTALL(FILES ${utopiadb_HDRS} ${utopiadb_HDRS_NOMOC} ${CMAKE_CURRENT_BINARY_DIR}/configure.h DESTINATION include/utopiadb)
