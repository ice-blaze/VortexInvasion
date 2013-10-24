#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "constantes.h"

#ifndef FONCT_MAIN_H
#define FONCT_MAIN_H

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
SDL_Surface *load_image( std::string filename );
Uint32 get_pixel32( int x, int y, SDL_Surface *surface );
int MyRand(int a, int b);
int collision (SDL_Rect pos1, SDL_Rect pos2);
void SDL_Exit(std::string errorMessage);

#endif
