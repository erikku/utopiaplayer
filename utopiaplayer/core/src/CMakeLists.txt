SET(QT_USE_QTSQL TRUE)
SET(QT_USE_QTXML TRUE)

INCLUDE(${QT_USE_FILE})
INCLUDE(FindTagLib)
INCLUDE(UsePkgConfig)

PKGCONFIG(utopiadb UTOPIADB_INCLUDE_DIR UTOPIADB_LINK_DIR UTOPIADB_LINK_FLAGS UTOPIADB_CFLAGS)
PKGCONFIG(vorbis VORBIS_INCLUDE_DIR VORBIS_LINK_DIR VORBIS_LINK_FLAGS VORBIS_CFLAGS)
PKGCONFIG(vorbisfile VORBISFILE_INCLUDE_DIR VORBISFILE_LINK_DIR VORBISFILE_LINK_FLAGS VORBISFILE_CFLAGS)
PKGCONFIG(wavpack WAVPACK_INCLUDE_DIR WAVPACK_LINK_DIR WAVPACK_LINK_FLAGS WAVPACK_CFLAGS)

INCLUDE_DIRECTORIES(${TAGLIB_INCLUDE_DIR} ${UTOPIADB_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/interfaces)
INCLUDE_DIRECTORIES(${UTOPIADB_INCLUDE_DIR} ${WAVPACK_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/core/interfaces ${CMAKE_SOURCE_DIR}/core/adapters)

LINK_DIRECTORIES(${QT_LIBRARY_DIR} ${UTOPIADB_LINK_DIR} ${WAVPACK_LINK_DIR})

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
    AlbumList.cpp
    Application.cpp
	ArtLabel.cpp
	AudioFile.cpp
	AudioThread.cpp
    DatabaseList.cpp
	DeviceManager.cpp
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
	sha1.c
	Slider.cpp
    #SongEdit.cpp
    SongList.cpp
    SongListWindow.cpp
    SongManager.cpp
    SplashScreen.cpp
	UtopiaDBImportOptions.cpp
    #UtopiaExport.cpp
    UtopiaPlayer.cpp
	VolumeDevice.cpp
	VolumeEdit.cpp
	VolumeList.cpp
	VolumePlugin.cpp
	VolumeSlider.cpp
	WavPackFile.cpp
)

SET(UtopiaPlayer_HDRS
    AlbumList.h
    Application.h
	ArtLabel.h
	AudioThread.h
    DatabaseList.h
	Device.h
	DeviceManager.h
    #DatabasePlugin.h
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
	../interfaces/DeviceInterface.h
    ../interfaces/OutputInterface.h
	../interfaces/PluginInterface.h
	../interfaces/ImportExportInterface.h
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

ADD_EXECUTABLE(utopiaplayer ${UtopiaPlayer_SRCS} ${UtopiaPlayer_RCC_SRCS})

TARGET_LINK_LIBRARIES(utopiaplayer ${QT_LIBRARIES} QtDBus ${UTOPIADB_LINK_FLAGS} ${TAGLIB_LIBRARIES} ${WAVPACK_LINK_FLAGS} ${VORBIS_LINK_FLAGS} ${VORBISFILE_LINK_FLAGS})

INSTALL(TARGETS utopiaplayer DESTINATION bin)
