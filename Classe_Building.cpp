#include "Classe_Building.h"

Building::Building()
{
	surface = NULL;
	x=NULL;
	y=NULL;
	alphaSens=NULL; 
	alpha=NULL;
}

void Building::Initialize(std::string filename)
{
	surface = load_image(filename.c_str());
	RandomPosition();
	alphaSens=0; 
	alpha=SDL_ALPHA_TRANSPARENT ;
}

void Building::RandomPosition()
{
	x= MyRand(0,wEcran-surface->w);
	y= MyRand(0,hEcran-surface->h);
}

void Building::SetAlpha()
{
	SDL_SetAlpha( surface, SDL_SRCALPHA | SDL_RLEACCEL, alpha );
}

void Building::ChangeTransparancy()
{
	//change la transparance
	if(alphaSens==1)
			alpha--;
		else
			alpha++;
}

int Building::ChangeTransparancySens()
{
	//Change le sense de transparance
	if(alpha==SDL_ALPHA_OPAQUE)
		alphaSens=1;
	else if(alpha==SDL_ALPHA_TRANSPARENT)
	{
		alphaSens=0;
		return 0;//pour que la boucle main sache qu'elle doive lancer la musique 
	}
	return 1;
}

void Building::CleanUp()
{
	alpha=NULL;
	alphaSens=NULL;
	x=NULL;
	y=NULL;
	SDL_FreeSurface(surface);
}