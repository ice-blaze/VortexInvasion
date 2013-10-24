#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <math.h>
#include <string>

#include "constantes.h"
#include "Fonct_Main.h"
#include "Classe_Timer.h"
#include "Classe_Enemy.h"
#include "Classe_BitmapFont.h"
#include "Classe_Building.h"
#include "Classe_Music.h"

#include "game.h"
#include "menu.h"

bool history = true;

//menu
int main ( int argc, char** argv )
{
    SDL_Surface *screen = NULL;
    //Un seul event par JEU !!
    SDL_Event event;


	bool bContinueProg = true;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(wEcran, hEcran, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_INIT_TIMER);
    SDL_WM_SetCaption("Vortex Invasion", NULL);

    while(bContinueProg==true)
    {
        //The menu
        bContinueProg=menu(screen,event);
        if(bContinueProg==false)
            return EXIT_SUCCESS;

        //The game
        bContinueProg=game(screen,event);
        if(bContinueProg==false)
            return EXIT_SUCCESS;
    }
}
