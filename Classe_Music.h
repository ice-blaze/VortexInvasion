#include "SDL_mixer.h"
#include "Fonct_Main.h"

#ifndef CLASSE_MUSIC_H
#define CLASSE_MUSIC_H

class Music
{
	private:
	Mix_Music *music;
	std::string filename;

	public:
	Music(std::string file);
	void playMusic(bool nbFois);
	void stopMusic();
	void freeMusic();
};

#endif
