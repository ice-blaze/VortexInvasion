#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL_mixer.h"
#include <math.h>
#include <string>

#include "Classe_Enemy.h"

extern void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
extern SDL_Surface *load_image( std::string filename );
Uint32 get_pixel32( int x, int y, SDL_Surface *surface );
int collision (SDL_Rect pos1, SDL_Rect pos2);
int MyRand(int a, int b);
void ColliCible(Enemy *cible1, Enemy *cible2, SDL_Rect posiCake);
void playMusic();
void stopMusic();
void CleanUpMenu();
void CleanUpGame();
class BitmapFont
{
    private:
    //La surface du font
    SDL_Surface *bitmap;

    //Les caractères individuels dans le font
    SDL_Rect chars[ 256 ];

    public:
    //Le constructeur par defaut
    BitmapFont();

    //Le constructeur avec un argument, genere le font quand l'objet est construit
    BitmapFont( SDL_Surface *surface );

    //Genere le font
    void build_font( SDL_Surface *surface );

    //Affiche le texte
    void show_text( int x, int y, std::string text, SDL_Surface *surface );
};

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
	void Initialize();
	void RandomPosition();
	void SetAlpha();
	void ChangeTransparancy();
	int ChangeTransparancySens();
	void CleanUp();
};
