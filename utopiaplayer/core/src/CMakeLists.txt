SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTXML TRUE)

INCLUDE(${QT_USE_FILE})
INCLUDE(FindTagLib)
INCLUDE(UsePkgConfig)

PKGCONFIG(utopiadb UTOPIADB_INCLUDE_DIR UTOPIADB_LINK_DIR UTOPIADB_LINK_FLAGS UTOPIADB_CFLAGS)
IF(DEFINED UTOPIADB_INCLUDE_DIR)
	MESSAGE("-- Found utopiadb")
ELSE(DEFINED UTOPIADB_INCLUDE_DIR)
	MESSAGE(FATAL_ERROR "utopiadb Not found! You need to fix this!")
ENDIF(DEFINED UTOPIADB_INCLUDE_DIR)

PKGCONFIG(vorbis VORBIS_INCLUDE_DIR VORBIS_LINK_DIR VORBIS_LINK_FLAGS VORBIS_CFLAGS)
IF(DEFINED VORBIS_INCLUDE_DIR)
	MESSAGE("-- Found vorbis")
ELSE(DEFINED VORBIS_INCLUDE_DIR)
	MESSAGE(FATAL_ERROR "vorbis Not found! You need to fix this!")
ENDIF(DEFINED VORBIS_INCLUDE_DIR)

PKGCONFIG(vorbisfile VORBISFILE_INCLUDE_DIR VORBISFILE_LINK_DIR VORBISFILE_LINK_FLAGS VORBISFILE_CFLAGS)
IF(DEFINED VORBISFILE_INCLUDE_DIR)
	MESSAGE("-- Found vorbisfile")
ELSE(DEFINED VORBISFILE_INCLUDE_DIR)
	MESSAGE(FATAL_ERROR "vorbisfile Not found! You need to fix this!")
ENDIF(DEFINED VORBISFILE_INCLUDE_DIR)

PKGCONFIG(ogg OGG_INCLUDE_DIR OGG_LINK_DIR OGG_LINK_FLAGS OGG_CFLAGS)
IF(DEFINED OGG_INCLUDE_DIR)
	MESSAGE("-- Found ogg")
ELSE(DEFINED OGG_INCLUDE_DIR)
	MESSAGE(FATAL_ERROR "ogg Not found! You need to fix this!")
ENDIF(DEFINED OGG_INCLUDE_DIR)

PKGCONFIG(wavpack WAVPACK_INCLUDE_DIR WAVPACK_LINK_DIR WAVPACK_LINK_FLAGS WAVPACK_CFLAGS)
IF(DEFINED WAVPACK_INCLUDE_DIR)
	MESSAGE("-- Found wavpack")
ELSE(DEFINED WAVPACK_INCLUDE_DIR)
	MESSAGE(FATAL_ERROR "wavpack Not found! You need to fix this!")
ENDIF(DEFINED WAVPACK_INCLUDE_DIR)

INCLUDE_DIRECTORIES(${UTOPIADB_INCLUDE_DIR} ${VORBIS_INCLUDE_DIR} ${VORBISFILE_INCLUDE_DIR} ${OGG_INCLUDE_DIR} ${WAVPACK_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${TAGLIB_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/interfaces ${CMAKE_SOURCE_DIR}/core/adapters ${INCLUDE_DIRECTORIES})

LINK_DIRECTORIES(${QT_LIBRARY_DIR} ${UTOPIADB_LINK_DIR} ${VORBIS_LINK_DIR} ${VORBISFILE_LINK_DIR} ${OGG_LINK_DIR} ${WAVPACK_LINK_DIR})

SET(UTOPIAPLAYER_OFFICIAL true)
SET(UTOPIAPLAYER_REVISION 0)

SET(UTOPIAPLAYER_VERSION 0.1.0)
SET(UTOPIAPLAYER_VERSION_MAJOR 0)
SET(UTOPIAPLAYER_VERSION_MINOR 1)
SET(UTOPIAPLAYER_VERSION_PATCH 0)
SET(UTOPIAPLAYER_SANE_VERSION ${UTOPIAPLAYER_VERSION_MAJOR}.${UTOPIAPLAYER_VERSION_MINOR}.${UTOPIAPLAYER_VERSION_PATCH})

FIND_PACKAGE(Subversion)
IF(Subversion_FOUND)
	Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Project)
	SET(UTOPIAPLAYER_OFFICIAL false)
	SET(UTOPIAPLAYER_REVISION ${Project_WC_REVISION})
	SET(UTOPIAPLAYER_VERSION ${UTOPIAPLAYER_VERSION}-SVN${UTOPIAPLAYER_REVISION})
ENDIF(Subversion_FOUND)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/UtopiaPlayer.h.in ${CMAKE_CURRENT_BINARY_DIR}/UtopiaPlayer.h @ONLY IMMEDIATE)

SET(UtopiaPlayer_SRCS
	AddRemoveTestDialog.cpp
    AlbumList.cpp
    Application.cpp
	ArtLabel.cpp
	AudioFile.cpp
	AudioThread.cpp
	ComponentList.cpp
    DatabaseList.cpp
	DeviceManager.cpp
	GUIManager.cpp
	ID3v1.cpp
    InsertAlbum.cpp
    InsertArtist.cpp
    InsertGenre.cpp
	iTunesImportOptions.cpp
	iTunesLibraryImportExport.cpp
	iTunesLibraryPreParser.cpp
    Login.cpp
    MainWindow.cpp
	Node.cpp
	OGGFile.cpp
    OptionsDialog.cpp
	PieChart.cpp
    PluginManager.cpp
	ProgressSlider.cpp
    SaveTagsThread.cpp
    SearchEdit.cpp
    SearchTree.cpp
    SettingsManager.cpp
	sha1.c
	Slider.cpp
    #SongEdit.cpp
    SongList.cpp
    SongListWindow.cpp
    SongManager.cpp
    SplashScreen.cpp
	UtopiaDBImportOptions.cpp
    #UtopiaExport.cpp
	VolumeDevice.cpp
	VolumeEdit.cpp
	VolumeList.cpp
	VolumePlugin.cpp
	VolumeSlider.cpp
	WavPackFile.cpp
)

SET(UtopiaPlayer_HDRS
	AddRemoveTestDialog.h
    AlbumList.h
    Application.h
	ArtLabel.h
	AudioThread.h
	ComponentList.h
    DatabaseList.h
	Device.h
	DeviceManager.h
    #DatabasePlugin.h
    GUIManager.h
    InsertAlbum.h
    InsertArtist.h
    InsertGenre.h
	iTunesImportOptions.h
	iTunesLibraryImportExport.h
    #Library.h
    Login.h
    MainWindow.h
    NullOutput.h
    OptionsDialog.h
	PieChart.h
    PluginManager.h
	ProgressSlider.h
    #Ruby.h
    SaveTagsThread.h
    #Scrobbler.h
    SearchEdit.h
    SearchTree.h
	Slider.h
    #SongEdit.h
    SongList.h
    SongListWindow.h
    SongManager.h
    #SplashScreen.h
	UtopiaDBImportOptions.h
    #UtopiaExport.h
    #UtopiaPlayer.h
	VolumeDevice.h
	VolumeEdit.h
	VolumeList.h
	VolumePlugin.h
	VolumeSlider.h
	../adapters/CurrentSongAdapter.h
)

SET(UtopiaPlayer_RCC
    ../res/UtopiaPlayer.qrc
)

QT4_ADD_RESOURCES(UtopiaPlayer_RCC_SRCS ${UtopiaPlayer_RCC})

SET(UtopiaPlayer_UIS
    ../ui/CurrentlyPlaying.ui
    ../ui/EditBox.ui
    ../ui/InsertAlbum.ui
    ../ui/InsertArtist.ui
    ../ui/InsertGenre.ui
    ../ui/Login.ui
    ../ui/LyricsEditor.ui
    ../ui/OptionsDialog.ui
    ../ui/ProgressWindow.ui
    ../ui/SongEdit.ui
	../ui/UtopiaDBImportOptions.ui
	../ui/iTunesImportOptions.ui
	../ui/VolumeEdit.ui
	../ui/VolumeList.ui
)

QT4_WRAP_UI(UtopiaPlayer_SRCS ${UtopiaPlayer_UIS})

QT4_WRAP_CPP(UtopiaPlayer_SRCS ${UtopiaPlayer_HDRS})

ADD_LIBRARY(utopiaplayer SHARED ${UtopiaPlayer_SRCS} ${UtopiaPlayer_RCC_SRCS})

SET_TARGET_PROPERTIES(utopiaplayer PROPERTIES VERSION ${UTOPIAPLAYER_SANE_VERSION} SOVERSION ${UTOPIAPLAYER_VERSION_MAJOR})

SET(utopiaplayer_LIBS ${QT_LIBRARIES} ${TAGLIB_LIBRARIES} ${UTOPIADB_LINK_FLAGS} ${VORBIS_LINK_FLAGS} ${VORBISFILE_LINK_FLAGS} ${OGG_LINK_FLAGS} ${WAVPACK_LINK_FLAGS})

IF(WIN32)
	SET(utopiaplayer_LIBS ${utopiaplayer_LIBS} QtDBus4)
ELSE(WIN32)
	SET(utopiaplayer_LIBS ${utopiaplayer_LIBS} QtDBus)
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(utopiaplayer ${utopiaplayer_LIBS})

INSTALL(TARGETS utopiaplayer DESTINATION lib)
