INCLUDE_DIRECTORIES(${UTOPIADB_INCLUDE_DIR} ${VORBIS_INCLUDE_DIR} ${VORBISFILE_INCLUDE_DIR} ${OGG_INCLUDE_DIR} ${WAVPACK_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/libutopiaplayer/interfaces)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libutopiaplayer/adapters)

LINK_DIRECTORIES(${QT_LIBRARY_DIR} ${UTOPIADB_LINK_DIR} ${VORBIS_LINK_DIR} ${VORBISFILE_LINK_DIR} ${OGG_LINK_DIR} ${WAVPACK_LINK_DIR})

SET(UTOPIAPLAYER_OFFICIAL true)
SET(UTOPIAPLAYER_REVISION 0)

SET(UTOPIAPLAYER_VERSION 0.1.0)
SET(UTOPIAPLAYER_VERSION_MAJOR 0)
SET(UTOPIAPLAYER_VERSION_MINOR 1)
SET(UTOPIAPLAYER_VERSION_PATCH 0)
SET(UTOPIAPLAYER_SANE_VERSION ${UTOPIAPLAYER_VERSION_MAJOR}.${UTOPIAPLAYER_VERSION_MINOR}.${UTOPIAPLAYER_VERSION_PATCH})

#FIND_PACKAGE(Subversion)
#IF(Subversion_FOUND)
#	FIND_PATH(IS_SVN_CHECKOUT entries ${CMAKE_SOURCE_DIR}/.svn NO_DEFAULT_PATH)
#	IF(IS_SVN_CHECKOUT)
#		Subversion_WC_INFO(${PROJECT_SOURCE_DIR} Project)
#		SET(UTOPIAPLAYER_OFFICIAL false)
#		SET(UTOPIAPLAYER_REVISION ${Project_WC_REVISION})
#		SET(UTOPIAPLAYER_VERSION ${UTOPIAPLAYER_VERSION}-SVN${UTOPIAPLAYER_REVISION})
#	ENDIF(IS_SVN_CHECKOUT)
#ENDIF(Subversion_FOUND)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/UtopiaPlayer.h.in ${CMAKE_CURRENT_BINARY_DIR}/UtopiaPlayer.h @ONLY IMMEDIATE)

SET(UtopiaPlayer_SRCS
	AddRemoveTestDialog.cpp
	AdvancedTag.cpp
    AlbumList.cpp
	APEv2.cpp
    Application.cpp
	ArtLabel.cpp
	AudioFile.cpp
	AudioThread.cpp
	ComponentList.cpp
	ContextTabBar.cpp
	Cuesheet.cpp
    DatabaseList.cpp
	DeviceManager.cpp
	FileProperties.cpp
	FileTypeFactory.cpp
	GUIManager.cpp
	ID3v1.cpp
    InsertAlbum.cpp
    InsertArtist.cpp
    InsertGenre.cpp
	iTunesImportOptions.cpp
	iTunesLibraryImportExport.cpp
	iTunesLibraryPreParser.cpp
	Logger.cpp
    Login.cpp
	MainTabWidget.cpp
    MainWindow.cpp
	Node.cpp
	OGGFile.cpp
    OptionsDialog.cpp
	PaletteEditor.cpp
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
	Tag.cpp
	TagEditBasic.cpp
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
	AdvancedTag.h
    AlbumList.h
    Application.h
	APEv2.h
	ArtLabel.h
	AudioThread.h
	ComponentList.h
	ContextTabBar.h
	Cuesheet.h
    DatabaseList.h
	Device.h
	DeviceManager.h
    #DatabasePlugin.h
	FileProperties.h
    GUIManager.h
	ID3v1.h
	ID3v2.h
    InsertAlbum.h
    InsertArtist.h
    InsertGenre.h
	iTunesImportOptions.h
	iTunesLibraryImportExport.h
    #Library.h
	Logger.h
    Login.h
	MainTabWidget.h
    MainWindow.h
    NullOutput.h
    OptionsDialog.h
	PaletteEditor.h
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
	TagEditBasic.h
	Tag.h
    #SplashScreen.h
	UtopiaDBImportOptions.h
    #UtopiaExport.h
    #UtopiaPlayer.h
	VolumeDevice.h
	VolumeEdit.h
	VolumeList.h
	VolumePlugin.h
	VolumeSlider.h
	#../adapters/CurrentSongAdapter.h
	../interfaces/OutputInterface.h
)

SET(UtopiaPlayer_RCC
    ../res/UtopiaPlayer.qrc
)

QT4_ADD_RESOURCES(UtopiaPlayer_RCC_SRCS ${UtopiaPlayer_RCC})

SET(UtopiaPlayer_UIS
    ../ui/CurrentlyPlaying.ui
    ../ui/EditBox.ui
	../ui/FileProperties.ui
    ../ui/InsertAlbum.ui
    ../ui/InsertArtist.ui
    ../ui/InsertGenre.ui
    ../ui/Login.ui
    ../ui/LyricsEditor.ui
    ../ui/OptionsDialog.ui
	../ui/PaletteEditor.ui
    ../ui/ProgressWindow.ui
    ../ui/SongEdit.ui
	../ui/TagEditBasic.ui
	../ui/UtopiaDBImportOptions.ui
	../ui/iTunesImportOptions.ui
	../ui/VolumeEdit.ui
	../ui/VolumeList.ui
)

QT4_WRAP_UI(UtopiaPlayer_SRCS ${UtopiaPlayer_UIS})

QT4_WRAP_CPP(UtopiaPlayer_SRCS ${UtopiaPlayer_HDRS})

ADD_LIBRARY(utopiaplayer SHARED ${UtopiaPlayer_SRCS} ${UtopiaPlayer_RCC_SRCS})

SET_TARGET_PROPERTIES(utopiaplayer PROPERTIES VERSION ${UTOPIAPLAYER_SANE_VERSION} SOVERSION ${UTOPIAPLAYER_VERSION_MAJOR})

SET(utopiaplayer_LIBS ${QT_LIBRARIES} ${UTOPIADB_LINK_FLAGS} ${VORBIS_LINK_FLAGS} ${VORBISFILE_LINK_FLAGS} ${OGG_LINK_FLAGS} ${WAVPACK_LINK_FLAGS})

IF(WIN32)
	SET(utopiaplayer_LIBS ${utopiaplayer_LIBS} iconv)#QtDBus4)
ELSE(WIN32)
	SET(utopiaplayer_LIBS ${utopiaplayer_LIBS})#QtDBus)
ENDIF(WIN32)

TARGET_LINK_LIBRARIES(utopiaplayer ${utopiaplayer_LIBS})

INSTALL(TARGETS utopiaplayer DESTINATION lib)
