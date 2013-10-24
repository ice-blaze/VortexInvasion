#include "Fonct_Main.h"
#include "Classe_Timer.h"

#ifndef CLASSE_BITMAPFONT_H
#define CLASSE_BITMAPFONT_H

class BitmapFont
{
    private:
    //La surface du font
    SDL_Surface *bitmap;

    //Les caract�res individuels dans le font
    SDL_Rect chars[ 256 ];

    public:
    //Le constructeur par defaut
    BitmapFont();

    //Le constructeur avec un argument, genere le font quand l'objet est construit
    BitmapFont( SDL_Surface *surface );

    //Genere le font
    void build_font( SDL_Surface *surface );

    //Affiche le texte
    void show_text( int x, int y, std::string text, SDL_Surface *surface);
    void show_text_left( int y, std::string text, SDL_Surface *surface);
    void show_text_center(int y, std::string text, SDL_Surface *surface);
    void show_text_right( int y, std::string text, SDL_Surface *surface);

    void TextBox(SDL_Surface *screen,SDL_Event event,std::string text);

    void waitInput(SDL_Event event);

    void fontDelete();
};
#endif
