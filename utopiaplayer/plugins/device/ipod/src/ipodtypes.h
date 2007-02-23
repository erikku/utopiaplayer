

// Database Object
typedef struct _mhbd
{
	qint32 headerID;		// 0x00 - "mhbd" - 0x6d686264
	qint32 headerSize;		// 0x04 - size of the header
	qint32 totalSize;		// 0x08 - size of the header + children (file size)
	qint32 unk1;			// 0x0c - always 1
	qint32 versionNumber;	// 0x10 - version number of the database
	qint32 childCount;		// 0x14 - number of mhsd children
	qint64 id;				// 0x18 - id value for the database
	qint32 unk2;			// 0x20 - always 2
	qint64 unk3;			// 0x24 - who knows
	// zero padded
}mhdb;

// DataSet
typedef struct _mhsd
{
	qint32 headerID;		// 0x00 - "mhsd"
	qint32 headerSize;		// 0x04 - size of the header
	qint32 totalSize;		// 0x08 - size of the header + children
	qint32 type;			// 0x0c - (1) track list (2) playlists (3) podcast list
	// zero padded
}mhsd;

// TrackList
typedef _mhlt
{
	qint32 headerID;		// 0x00 - "mhlt"
	qint32 headerSize;		// 0x04 - size of the header
	qint32 songCount;		// 0x08 - the number of songs in the list
	// zero padded
}mhlt;

// Track Item
typedef _mhit
{
	qint32 headerID;		// 0x00 - "mhit"
	qint32 headerSize;		// 0x04 - size of the header
	qint32 totalSize;		// 0x08 - size of the header + children
	qint32 stringCount;		// 0x0c - number of strings (mhods) that are children
	qint32 uniqueID;		// 0x10 - unique ID for this track (referenced in playlists)
	qint32 visible;			// 0x14 - (1) visible (not 1) not visible
	qint32 filetype;		// 0x18 - 1 on 1-4g, ANSI string with space padding on 5g+ and shuffle
	qint8  type1;			// 0x1c - CBR MP3s == 0x00 | VBR MP3s == 0x01 | AAC == 0x00
	qint8  type2;			// 0x1d - CBR MP3s == 0x01 | VBR MP3s == 0x01 | AAC == 0x00
	qint8  compilation;		// 0x1e - (1) compilation (2) not a compilation
	qint8  rating;			// 0x1f - rating (0 to 5) * 20
	qint32 modifiedTime;	// 0x20 - last mofified time of the track (don't ask me how it's formated)
	qint32 size;			// 0x24 - size of the track in bytes
	qint32 length;			// 0x28 - length of the track in milliseconds
	qint32 trackNumber;		// 0x2c - number of this track
	qint32 totalTracks;		// 0x30 - number of tracks in the album
	qint32 year;			// 0x34 - year of the track (or album)
	qint32 bitrate;			// 0x38 - bitrate of the track
	qint32 sampleRate;		// 0x3c - sample rate of track * 0x10000
	qint32 volume;			// 0x40 - volume to apply to the track (-255 to 255)
	qint32 startTime;		// 0x44 - time, in millisecons, that the song will start at
	qint32 stopTime;		// 0x48 - time, in millisecons, that the song will stop at
	qint32 soundcheckl		// 0x4c - SoundCheck / ReplayGain value
	qint32 playCount;		// 0x50 - times the song has been played
	qint32 playCount2;		// 0x54 - same as above
	qint32 lastPlayTime;	// 0x58 - another date time stamp (don't ask me how they work)
	qint32 discNumber;		// 0x5c - disc number for this track
	qint32 totalDiscs;		// 0x60 - total number of discs for the album
	qint32 userID;			// 0x64 - Apple DRM User ID (0 for non-drm files)
	qint32 dateAdded;		// 0x68 - Date added to the iPod (or maybe iTunes)
	qint32 bookmarkTime;	// 0x6c - The point, in milliseconds, that the track will start playing at
	qint64 dbid;			// 0x70 - Unique value that identifies the song across databases
	qint8  checked;			// 0x78 - If the track is checked in iTunes
	qint8  appRating;		// 0x79 - What the rating is in iTunes during the last sync
	qint16 BPM;				// 0x7a - The beats per minute of the song
	qint16 artworkCount;	// 0x7c - The number of artwork items put into the tags of this song (must be AT LEAST 1 to display artwork in ithmb files)
	qint16 unk9;			// 0x7e - 0xffff for MP3/AAC | 0x0000 for uncompressed (WAV) | 0x0001 for Audible
	qint32 artworkSize;		// 0x80 - Total size of artwork (in bytes) attached to this song (i.e. put into the song tags)
	qint32 unk11;			// 0x84 - We have no clue
	qint32 sampleRate2;		// 0x88 - The sample rate of the song expressed as a 32-bit float
	qint32 releaseDate;		// 0x8c - Date the song was released (mainly for podcasts)
	qint16 unk14_1;			// 0x90 - MP3 - 0x000c | AAC - 0x0033 | Audible - 0x0029 | WAV - 0x0000
	qint16 unk14_2;			// 0x92 - (1) MP3/AAC/Audible (0) WAV
	qint32 unk15;			// 0x94 - for Apple DRM, always 0 for no DRM
	qint32 unk16;			// 0x98 - Who knows
	qint32 unk17;			// 0x9c - unknown (added in dbversion 0x0c)
	qint32 unk18;			// 0xa0 - unknown (added in dbversion 0x0c)
	qint8  hasArtwork;		// 0xa4 - 0x02 for no artwork, 0x01 for artwork
	qint8  skipShuffling;	// 0xa5 - sets "Skip When Shuffling" when set to 0x01
	qint8  rememberPlayPos;	// 0xa6 - sets "Remember Playback Position" - 0x0 for .m4b and .aa | 0x1 for everything else
	qint8  podcast;			// 0xa7 - 0x1 or 0x2 for podcast, 0x0 otherwise
	qint64 dbid2;			// 0xa8 - Prior to dbversion 0x12 it was the same as dbid, Since 0x12 it differs
	qint8  lyricsFlag;		// 0xb0 - 0x1 if lyrics are stored in the MP3 tags ("USLT")
	qint8  movieFlag;		// 0xb1 - 0x1 video file, 0x0 audio file
	qint8  played;			// 0xb2 - 0x01 for non-podcasts | 0x02 marks this track with a bullet as "not played", 0x01 removes the bullet
	qint8  unk37;			// 0xb3 - So far, always 0
	qint32 unk21;			// 0xb4 - unknown (added in dbversion 0x0c)
	qint32 pregap;			// 0xb8 - number of samples of silence at start of the song (for gapless playback)
	qint64 sampleCount;		// 0xbc - number of samples in the song (for gapless playback)
	qint32 unk25;			// 0xc4 - unknown (added in dbversion 0x0c)
	qint32 postgap;			// 0xc8 - number of samples of silence at the end of the song (for gapless playback)
	qint32 unk27;			// 0xcc - unknown - added in 0x0c - 0x1 for files encoded with the MP3 encoder, 0x0 otherwise
	qint32 mediaType;		// 0xd0 - What type of media we have and what lists it shows up in
							//        * 0x00000000 - Audio/Video
							//        * 0x00000001 - Audio
							//        * 0x00000002 - Video
							//        * 0x00000004 - Podcast
							//        * 0x00000006 - Video Podcast
							//        * 0x00000008 - Audiobook
							//        * 0x00000020 - Music Video
							//        * 0x00000040 - TV Show (shows up ONLY in TV Shows
							//        * 0x00000060 - TV Show (shows up in the Music lists as well)
	qint32 seasonNumber;	// 0xd4 - Season number of the TV show, oherwise 0x0
	qint32 episodeNumber;	// 0xd8 - Episode number of the TV show
	qint32 unk31;			// 0xdc - unknown (added in dbversion 0x0c) Protected files? 0x0 for non-protected files
	qint32 unk32;			// 0xe0 - unknown (added in dbversion 0x0c)
	qint32 unk33;			// 0xe4 - unknown (added in dbversion 0x0c)
	qint32 unk34;			// 0xe8 - unknown (added in dbversion 0x0c)
	qint32 unk35;			// 0xec - unknown (added in dbversion 0x0c)
	qint32 unk36;			// 0xf0 - unknown (added in dbversion 0x0c)
	// zero padded
}mhit;
