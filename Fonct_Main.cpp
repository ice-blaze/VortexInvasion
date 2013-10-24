#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <time.h>
#include "Classe_Enemy.h"

#include "Fonct_Main.h"

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip=NULL)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

SDL_Surface *load_image( std::string filename )
{
    //L'image qui est chargée
    SDL_Surface* loadedImage = NULL;

    //L'image optimisée qu'on va utiliser
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = IMG_Load( filename.c_str() );

    //Si l'image a bien chargée
    if( loadedImage != NULL )
    {
        //Création de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Libération de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //Si la surface a bien été optimisée
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //On retourne l'image optimisée
    return optimizedImage;
}

Uint32 get_pixel32( int x, int y, SDL_Surface *surface )
{
    //Convertie les pixels en 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Recupere le pixel demande
    return pixels[ ( y * surface->w ) + x ];
}

int MyRand(int a, int b){
    return rand()%(b-a) +a;
}

int collision (SDL_Rect pos1, SDL_Rect pos2)
{
	//Nous savons que les sufraces font 45 sur 45
	//On devrait beaucoup changer la fonction si on voulait des objets avec des tailles différentes
    int result = NULL;
    if(pos1.x > pos2.x+SPRITE_WIDTH
       || pos1.x+SPRITE_WIDTH < pos2.x
       || pos1.y > pos2.y+SPRITE_WIDTH
       || pos1.y+SPRITE_WIDTH < pos2.y)

        result = 0;
    else
    {
        result = 1;
    }


    return result;
}

void SDL_Exit(std::string errorMessage)
{
	printf(errorMessage.c_str());
	//SDL_Quit(); libéré la mémoire avant
}


