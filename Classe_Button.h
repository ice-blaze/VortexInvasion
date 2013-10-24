#include "Fonct_Main.h"
#include "Classe_Timer.h"

#ifndef CLASSE_BUTTON_H
#define CLASSE_BUTTON_H

class Button
{
    private:
    int x,y,w,h;
    bool bClick;
    unsigned char alpha;
    SDL_Surface *imageButton;
    //SDL_Event event;

    public:
    //Le constructeur par defaut
    Button(std::string linkImage ,int X,int Y);
    void show(SDL_Surface *screen);
    void setAlpha(int al);
    int getAlpha();

    //Le constructeur avec un argument, genere le font quand l'objet est construit
    //initialization( SDL_Surface *screen,std::string text );

    //Genere le font
    bool click(SDL_Event event);
    bool mouseOver(SDL_Event event);

    //Affiche le texte
    /*void show_text( int x, int y, std::string text, SDL_Surface *screen);
    void show_text_left( int x, int y, std::string text, SDL_Surface *screen);
    void show_text_center( int x, int y, std::string text, SDL_Surface *screen);
    void show_text_right( int x, int y, std::string text, SDL_Surface *screen);

    void TextBox(SDL_Surface *screen,SDL_Event event,std::string text);

    void waitInput(SDL_Event event);

    void fontDelete();*/
};
#endif

