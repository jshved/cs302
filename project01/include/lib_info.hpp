#pragma once

#include <map>
#include <string>

struct Song { 
	std::string title;
    int time;  // could also be a string
    int track;
};

struct Album {
	std::map <int, Song > songs;
	std::string name;
    int time;
    int nsongs;  // optional variable but makes it easier
};

struct Artist {
	std::map <std::string, Album > albums;
	std::string name;
    int time;
    int nsongs;
};

class Lib_Info
{
	public:
		void PrintArtist(const Artist &artist) const;
		void PrintAlbum(const Album &album) const;
		void PrintSong(const Song &song) const;
};
