#include "Playlist.h"
using std::shuffle;

void Playlist::addSongToPlaylist(const Song& s) {
	this->playlistSongs.push_back(s);
	notify();
}
void Playlist::emptyPlaylist() {
	this->playlistSongs.clear();
	notify();
}

void Playlist::addRandomSongs(vector<Song> originalSongs, int howMany) {
	shuffle(originalSongs.begin(), originalSongs.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (playlistSongs.size() < howMany && originalSongs.size() > 0) {
		playlistSongs.push_back(originalSongs.back());
		originalSongs.pop_back();
	}
	notify();
}
const vector<Song>& Playlist::getAllPlaylistSongs() {
	return this->playlistSongs;
}