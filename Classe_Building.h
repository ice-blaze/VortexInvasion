#include "constantes.h"
#include "Fonct_Main.h"

#ifndef CLASSE_BUILDING_H
#define CLASSE_BUILDING_H

class Building
{
    private:
	int alphaSens; //0 -> transparance  1 -> opaque
	int alpha;

    public:
	SDL_Surface *surface;
	int x,y;
    //Initialise les variables
    Building();
	void Initialize(std::string filename);
	void RandomPosition();
	void SetAlpha();
	void ChangeTransparancy();
	int ChangeTransparancySens();
	void CleanUp();
};
#endif
