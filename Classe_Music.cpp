#include "Classe_Music.h"

Music::Music(std::string file)
{
	filename=file;
	music = NULL;
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
		//charge la musique
	music = Mix_LoadMUS( filename.c_str() );
	if(music==NULL)
	{
		SDL_Exit("chargement de la musique �chou�");
	}
}

void Music::playMusic(bool nbFois)
{

	//joue la musique 0=1X, -1= en boucle
	if(nbFois == true)
	{
	    if(Mix_PlayMusic( music, -1 )==-1)
        {
            printf("echec du lancement de la musique");
        }
	}
	else
	{
	    if(Mix_PlayMusic( music, 0 )==-1)
        {
            printf("echec du lancement de la musique");
        }
	}
}

void Music::stopMusic()
{
	//arr�te la musique
	Mix_HaltMusic();
}

void Music::freeMusic()
{
	//arr�te la musique
	Mix_HaltMusic();
	//lib�re la m�moire
	Mix_FreeMusic(music);
}
