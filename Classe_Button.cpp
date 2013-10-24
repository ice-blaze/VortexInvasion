#include "Classe_Button.h"
#include "SDL.h"

int colliClick (int x1, int y1, int w1, int h1, int xS, int yS);

Button::Button(std::string linkImage,int X,int Y)
{
    y=Y;
    x=X;
    bClick = false;
    alpha = 0;
    imageButton = load_image(linkImage.c_str());
    if( imageButton == NULL )
    {
		SDL_Exit("chargement de l'image du Button \"X\" echouer");
        return;
    }
    w = imageButton->w;
    h = imageButton->h;
}

void Button::show(SDL_Surface *screen)
{
    apply_surface(x,y,imageButton,screen,NULL);
}

bool Button::click(SDL_Event event)
{
    SDL_PollEvent(&event);//Récupération de l'évènement dans event
    switch(event.type)//Test du type d'évènement
    {
         case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                //When left mouse click on the button
                if(colliClick(x, y, w, h,event.motion.x,  event.motion.y))
                bClick = true;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                //When left mouse click on the button
                if(colliClick(x, y, w, h,event.motion.x,  event.motion.y)&&bClick==true)
                {
                    bClick = false;
                    return true;
                }
            }
            break;
    }
    return false;
}

bool Button::mouseOver(SDL_Event event)
{
    if(colliClick(x, y, w, h,event.motion.x,  event.motion.y))
        return true;

    return false;
}

//al 0(transparant)->255(opaque)
void Button::setAlpha(int al)
{
    alpha=al;
    SDL_SetAlpha( imageButton, SDL_SRCALPHA | SDL_RLEACCEL, al );
}

int Button::getAlpha()
{
    return alpha;
}

int colliClick (int x1, int y1, int w1, int h1, int xS, int yS)
{
    if(xS > x1+w1
       || xS < x1
       || yS > y1+h1
       || yS< y1)

        return 0;
    else
        return 1;
}

