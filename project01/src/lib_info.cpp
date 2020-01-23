// Author: Grant Anderson
// Author: Logan Tillman
// Date: January 22, 2020
/*
	This program parses through a text file containing information about various artists
	and their works. It keeps track of every song for an album, and it keeps a running total
	of the time for each song, album, and artist.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <map>
#include <set>
#include <string>
#include "lib_info.hpp"

using namespace std;

// Converts MM:SS into an integer value
int TimeToInt(string mss);

// Converts an integer into MM:SS format
string IntToTime(int inttime);

void PrintArtist(const Artist &artist);

void PrintAlbum(const Album &album);

void PrintSong(const Song &song);

int main (int argc, char **argv)
{
	map <string, Artist> armap;
	map <string, Artist>::iterator arit;
	map <string, Album>::iterator alit;
	map <int, Song>::iterator soit;
	stringstream ss;
    string title, mss, artist, album, genre;
    string st;
    int track;
    ifstream ifs;
    Artist newArtist;
    Album newAlbum;
    Song newSong;

    ifs.open(argv[1]);

    while(getline(ifs,st))
	{
		ss.clear();
		ss.str(st);
		ss >> title >> mss >> artist >> album >> genre >> track;

		// Turning the underscores in the file into spaces
		for(int i = 0; i < (int) title.size(); i++)
			if(title[i] == '_')
				title[i] = ' ';

		for(int i = 0; i < (int) artist.size(); i++)
			if(artist[i] == '_')
				artist[i] = ' ';

		for(int i = 0; i < (int) album.size(); i++)
			if(album[i] == '_')
				album[i] = ' ';

		for(int i = 0; i < (int) genre.size(); i++)
			if(genre[i] == '_')
				genre[i] = ' ';


		arit = armap.find(artist);
	
		// If the artist doesn't exist
		if (arit == armap.end())
		{
			// Insert the artist into the map
			newArtist.name = artist;
			newArtist.time = 0;
			newArtist.nsongs = 0;
			armap.insert(make_pair(artist, newArtist));
		}

		alit = armap.find(artist)->second.albums.find(album);

		// If the album doesn't exist
		if (alit == armap.find(artist)->second.albums.end())
		{
			// Insert the album into its map
			newAlbum.name = album;
			newAlbum.time = 0;
			newAlbum.nsongs = 0;
			armap.find(artist)->second.albums.insert(make_pair(album, newAlbum));
		}

		// Update the info for the new song
		newSong.title = title;
		newSong.time = TimeToInt(mss);
		newSong.track = track;

		// Find which artist & album the song belongs to and insert it
		arit = armap.find(artist);
		alit = arit->second.albums.find(album);
		alit->second.songs.insert(make_pair(track, newSong));

		// Increase the time and number of songs for the album
		alit->second.time += newSong.time;
		alit->second.nsongs++;

		// Increase the time and number of songs for the artist
		arit->second.time += newSong.time;
		arit->second.nsongs++;
	}

		// Printing out the information for each artist
		for (arit = armap.begin(); arit != armap.end(); arit++)
			PrintArtist(arit->second);
return 0;
}

// Converts MM:SS into integer form
int TimeToInt(string mss)
{
	string minutes;
	string seconds;
	int min;
	int sec;
	int total;
	int colon;

	// Find's the index where the colon is
	colon = mss.find(':');

	// Separate the minutes into its own string
	for(int i = 0; i < colon; i++)
		minutes += mss[i];

	// Separate the seconds into it's own string
	for(int i = colon+1; i < (int) mss.size(); i++)
		seconds += mss[i];

	// Converting the strings into integers
	istringstream(minutes) >> min;
	istringstream(seconds) >> sec;

	// Adding the integers to get the total number of seconds
	min *= 60;
	total = min + sec;

return total;
}

// Converts an integer into MM:SS format
string IntToTime(int inttime)
{
	stringstream ss;
	string rv, temp;
	int minutes;
	int seconds;

	rv = "";

	// Figuring out how many minutes and seconds there are
	minutes = inttime / 60;
	seconds = inttime - (minutes * 60);

	// Inserting the minutes into the string
	ss.clear();
	ss << minutes;
	ss >> rv;

	// Adding the colon
	rv += ':';

	// Convering the seconds into a string
	ss.clear();
	ss << seconds;
	ss >> temp;

	// If the seconds are a single digit, we add a 0 to the beginning so it's ":SS"
	if (temp.size() == 1)
		temp = '0' + temp;

	return rv += temp;
}

// Printing out the information in the correct format
void PrintArtist(const Artist &artist)
{
	map <string, Album>::const_iterator ait;

	printf("%s: %d, %s\n", artist.name.c_str(), artist.nsongs, IntToTime(artist.time).c_str());

	// Printing out each album for the artist
	for (ait = artist.albums.begin(); ait != artist.albums.end(); ait++)
		PrintAlbum(ait->second);
}

void PrintAlbum(const Album &album)
{
	map <int, Song>::const_iterator sit;

	printf("%8s%s: %d, %s\n", "", album.name.c_str(), album.nsongs, IntToTime(album.time).c_str());

	// Printing out each song for the album
	for (sit = album.songs.begin(); sit != album.songs.end(); sit++)
		PrintSong(sit->second);
}

void PrintSong(const Song &song)
{
	printf("%16s%d. %s: %s\n", "", song.track, song.title.c_str(), IntToTime(song.time).c_str());
}
