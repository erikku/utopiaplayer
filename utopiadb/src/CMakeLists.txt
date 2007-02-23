PROJECT(utopiadb)

SET(DOXYGEN_LANG English)
SET(UTOPIADB_VERSION 0.1.0-pre1)
SET(UTOPIADB_VERSION_MAJOR 0)
SET(UTOPIADB_VERSION_MINOR 1)
SET(UTOPIADB_VERSION_REVISION 0)
SET(UTOPIADB_SANE_VERSION ${UTOPIADB_VERSION_MAJOR}.${UTOPIADB_VERSION_MINOR}.${UTOPIADB_VERSION_REVISION})

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/src/configure.h.in ${CMAKE_CURRENT_BINARY_DIR}/configure.h @ONLY IMMEDIATE)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/scripts/utopiadb.pc.in ${CMAKE_CURRENT_BINARY_DIR}/utopiadb.pc @ONLY IMMEDIATE)

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
	song.cpp
	songedition.cpp
	songfile.cpp
	songset.cpp
	sqlmetabase.cpp
	sqlparsers.cpp
	staff.cpp
	tagid.cpp
	utopiablock.cpp
	xmlmetabase.cpp
	#utopiafactory.cpp
	#mangaseries.cpp
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
	#mangapublisher.h
	#mangaseries.h
	mood.h
	publisher.h
	#series.h
	song.h
	songedition.h
	songfile.h
	songset.h
	staff.h
	tagid.h
	utopiablock.h
	utopiadb.h
	#utopiafactory.h
)

QT4_WRAP_CPP(utopiadb_SRCS ${utopiadb_HDRS})

ADD_LIBRARY(utopiadb SHARED ${utopiadb_SRCS})

SET_TARGET_PROPERTIES(utopiadb PROPERTIES VERSION ${UTOPIADB_SANE_VERSION} SOVERSION ${UTOPIADB_VERSION_MAJOR})

TARGET_LINK_LIBRARIES(utopiadb ${QT_LIBRARIES})

# Doxygen Docs
#IF(BUILD_DOCS)
	INCLUDE(FindDoxygen)
	MAKE_DIRECTORY(${CMAKE_BINARY_DIR}/doc)
	MAKE_DIRECTORY(${CMAKE_BINARY_DIR}/doc/api)

	SET(Doxyfile_in ${CMAKE_SOURCE_DIR}/scripts/Doxyfile.in)
	SET(Doxyfile ${CMAKE_BINARY_DIR}/Doxyfile)

	CONFIGURE_FILE(${Doxyfile_in} ${Doxyfile} @ONLY)

	# I may want to add some other stuff like Mainpage.dox to the DEPENDS for this command
	#ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_BINARY_DIR}/doc/api/html/index.html COMMAND echo "Building API Documentation..." COMMAND ${DOXYGEN} ${CMAKE_BINARY_DIR}/Doxyfile &> ${CMAKE_BINARY_DIR}/doxygen.log DEPENDS ${Doxyfile} ${utopiadb_SRCS} ${utopiadb_HDRS})
	#ADD_CUSTOM_TARGET(api-docs DEPENDS ${CMAKE_BINARY_DIR}/doc/api/html/index.html)
	# I need to fix the install for the docs, it scans the folder BEFORE building instead of after

	#FILE(GLOB utopidb_DOCS ${CMAKE_CURRENT_BINARY_DIR}/doc/api/html *)
	#INSTALL(FILES ${utopiadb_DOCS} DESTINATION share/doc/utopiadb-${UTOPIADB_SANE_VERSION}/api)
	#INSTALL(CODE "FILE(GLOB utopidb_DOCS ${CMAKE_BINARY_DIR}/doc/api/html *)")
	#INSTALL(CODE "INSTALL(FILES ${utopiadb_DOCS} DESTINATION share/doc/utopiadb-${UTOPIADB_SANE_VERSION}/api)")
	#INSTALL(FILES ${CMAKE_BINARY_DIR}/doc/api/utopiadb.tag DESTINATION share/doc/utopiadb-${UTOPIADB_SANE_VERSION})

	#ADD_DEPENDENCIES(utopiadb api-docs)
#ENDIF(BUILD_DOCS)

INSTALL(TARGETS utopiadb DESTINATION lib)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/utopiadb.pc DESTINATION lib/pkgconfig)
INSTALL(FILES ${utopiadb_HDRS} ${utopiadb_HDRS_NOMOC} ${CMAKE_CURRENT_BINARY_DIR}/configure.h DESTINATION include/utopiadb)
