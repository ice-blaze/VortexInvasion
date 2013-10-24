#include "menu.h"
#include <time.h>


int collisionBuilding (int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void credits(SDL_Surface *screen,SDL_Event event);

bool menu(SDL_Surface *screen,SDL_Event event)
{
    //nombres aléatoire
    srand(time(NULL));
    //menu
    bool bContinueMenu = true;
    //Mix_Music *music = NULL;
    //timer
    Timer time;

    //bouton
    bool changeTransparancy =true;//transparance des boutons
    //offset
    const int yBtnSelect=225;
    Button btnSelect1("Sprites/select.png",0,yBtnSelect);
    Button btnSelect2("Sprites/select.png",0,yBtnSelect+50);
    Button btnSelect3("Sprites/select.png",0,yBtnSelect+100);

	//Affiche le curseur
	Building buildings[3];
	//Building selects[3];
	SDL_ShowCursor(SDL_ENABLE);
	//font ini
	SDL_Surface *fontSurfaceMenu;
	fontSurfaceMenu = load_image( "Fonts/font2.png" );
	BitmapFont fontMenu( fontSurfaceMenu );
	//end font ini
	Music musicMenu("Sounds/menu.mp3");
	//transparance de l'image
	musicMenu.playMusic(false);
	//ini les building
	for(int i=0;i<NB_BUILDINGS;i++)
	{
		buildings[i].Initialize("Sprites/building.png");
	}
	//ini les select
	/*for(int i=0;i<NB_SELECTS;i++)
	{
		selects[i].Initialize("Sprites/select.png");
		selects[i].x=wEcran/2-SELECT_WIDTH;
		selects[i].y=POS_Y_SELECT+i*50;
	}*/
//bool creditContinue = true;
    while(bContinueMenu == true)
    {
        time.start();
        SDL_PollEvent(&event);//Récupération de l'évènement dans event
        switch(event.type)//Test du type d'évènement
        {
            case SDL_KEYUP :
                switch(event.key.keysym.sym)
                {
                    case SDLK_1:
                        bContinueMenu =false;
                        break;

                    case SDLK_2:
                        //problème, lorsqu'on presse, le programme fait presser souvent le bouton
                        //credits(screen,event);
                        break;

                    case SDLK_3:
                        return false;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_QUIT: //Si l'évènement est de type "quitter"
                return false;
                break;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0,0,0));
        /*SDL_Surface *test=NULL;
        test = load_image("Sprites/test.png");
        for(double i =0;i<500000;i++)
        {
            apply_surface(MyRand(0,400),MyRand(0,400),test,screen,NULL);
        }
        SDL_Flip(screen);
        fontMenu.waitInput(event);*/

         //verifie que la nouvelle position ne soit pas sur un autre building
        if(buildings[0].ChangeTransparancySens()==0)
        {
            while ((collisionBuilding(buildings[0].x,buildings[0].y,buildings[0].surface->w,buildings[0].surface->h,
                buildings[1].x,buildings[1].y,buildings[1].surface->w,buildings[1].surface->h)||

                collisionBuilding(buildings[0].x,buildings[0].y,buildings[0].surface->w,buildings[0].surface->h,
                buildings[2].x,buildings[2].y,buildings[2].surface->w,buildings[2].surface->h)||

                collisionBuilding(buildings[2].x,buildings[2].y,buildings[2].surface->w,buildings[2].surface->h,
                buildings[1].x,buildings[1].y,buildings[1].surface->w,buildings[1].surface->h))==1)
            {
                buildings[0].RandomPosition();
                buildings[1].RandomPosition();
                buildings[2].RandomPosition();
            }
        }
        //parcours chaque building et dé/incrémente la transparance puis l'affiche
        for(int i=0;i<NB_BUILDINGS;i++)
        {
            buildings[i].SetAlpha();
            apply_surface( buildings[i].x, buildings[i].y, buildings[i].surface, screen,NULL);
            buildings[i].ChangeTransparancy();
            //change la transparance des bâtiment quand ils en ont besoin +
            //s'ils réaparaissent...
            if(buildings[i].ChangeTransparancySens()==0)
            {
                //libère la mémoire sinon il y a une saturation à force de le relancer
                musicMenu.stopMusic();
                //recharge la musique
                musicMenu.playMusic(false);
                //Change la position des surface
                buildings[i].RandomPosition();

            }
        }


        //la transparance des Buttons suit les building en fond
        if(btnSelect1.getAlpha()==255)
            changeTransparancy =true;
        else if(btnSelect1.getAlpha()==0)
            changeTransparancy =false;

        unsigned char alphaTemp = btnSelect1.getAlpha();
        if(changeTransparancy == true)
        {
            alphaTemp--;
            btnSelect1.setAlpha(alphaTemp);
            btnSelect2.setAlpha(alphaTemp);
            btnSelect3.setAlpha(alphaTemp);
        }
        else
        {
            alphaTemp++;
            btnSelect1.setAlpha(alphaTemp);
            btnSelect2.setAlpha(alphaTemp);
            btnSelect3.setAlpha(alphaTemp);
        }

        //affiche les boutons si au dessus
        if(btnSelect1.mouseOver(event))
            btnSelect1.show(screen);
        if(btnSelect2.mouseOver(event))
            btnSelect2.show(screen);
        if(btnSelect3.mouseOver(event))
            btnSelect3.show(screen);

        //Action des boutons
        if(btnSelect1.click(event))
            bContinueMenu =false;

        if(btnSelect2.click(event))//&&creditContinue==true)
        {
            credits(screen,event);
        }
        if(btnSelect3.click(event))
            return false;


        //affiche le texte devant les bâtiement
        fontMenu.show_text_center(yBtnSelect+8, "1. PLAY", screen );
        fontMenu.show_text_center(yBtnSelect+58, "2. CREDIT", screen);
        fontMenu.show_text_center(yBtnSelect+108, "3. QUIT", screen);


        SDL_Flip(screen);

        while( time.get_ticks() < 180 / FRAMES_PER_SECOND )
        {
            //on attend
        }
    }
    return true;
}


int collisionBuilding (int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    if(x1 > x2+w2
       || x1+w1 < x2
       || y1 > y2+h2
       || y1+h1 < y2)

        return 0;
    else
        return 1;
}

void credits(SDL_Surface *screen,SDL_Event event)
{
    SDL_Surface *fontSurfaceCredits;
	fontSurfaceCredits = load_image( "Fonts/font2.png" );
	BitmapFont fontCredits( fontSurfaceCredits );
    //partie 1
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,0,0));
    fontCredits.show_text_center(100, "Credit !!", screen );
    fontCredits.show_text(60,150, "Graphics : Onimanta", screen);
    fontCredits.show_text(210 ,200, "Ice-Blaze", screen );
    SDL_Flip(screen);
    fontCredits.waitInput(event);

    //partie 2
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,0,0));
    fontCredits.show_text_center(100, "Credit !!", screen );
    fontCredits.show_text(30,150, "Programming : Ice-Blaze", screen );
    SDL_Flip(screen);
    fontCredits.waitInput(event);

    //partie 3
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,0,0));
    fontCredits.show_text_center(100, "Credit !!", screen );
    fontCredits.show_text(90,150, "Music : Ice-Blaze", screen );
    SDL_Flip(screen);
    fontCredits.waitInput(event);

    //partie 4
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,0,0));
    fontCredits.show_text_center(100, "Credit !!", screen );
    fontCredits.show_text(80,150, "Testing : Onimenta", screen );
    fontCredits.show_text(213,200, "Malik", screen );
    SDL_Flip(screen);
    fontCredits.waitInput(event);
}
