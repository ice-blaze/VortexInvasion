#include "game.h"

void ColliCible(Enemy *cible1, Enemy *cible2, SDL_Rect posiCake);
void quitProg(bool *prog,bool *game);
void quitGame(bool *prog,bool *game);
void intro(SDL_Surface *screen);

bool game(SDL_Surface *screen, SDL_Event event)
{
     //Game
    extern bool history;
    int iPlayerStatus=0;
    bool bContinueGame = true;
    bool bContinueProg = true;
    //Animation
    SDL_Rect clipsPlayer[ CLIP_PLAYER_LENGTH ];
    //enemies
    Enemy enemies[NB_MAX_ENEMY];
    //char Points[255];
    Timer time;
    //timer
    int iVitesse =10;
    time.start();
    //musique
    Music musicGame("Sounds/vortex.mp3");

    //Player Clips
    for(int i=0;i<CLIP_PLAYER_LENGTH;i++)
    {
        clipsPlayer[ i ].x = SPRITE_WIDTH * i;
        clipsPlayer[ i ].y = 0;
        clipsPlayer[ i ].w = SPRITE_WIDTH;
        clipsPlayer[ i ].h = SPRITE_WIDTH;
    }

    int iPastTime=0;
    int iPastTimeAnimEnemy=0;
    int iPastTimeAnimPlayer=0;
    SDL_Surface *SanDiego = NULL, *cake = NULL;
    SDL_Rect positionSanDiego, positionCake;

    SanDiego = IMG_Load("Sprites/SanDiego.png");
    SDL_SetColorKey( SanDiego, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( SanDiego->format, 0, 0xFF, 0xFF ) );
    cake = IMG_Load("Sprites/cake.png");



    positionSanDiego.x = wEcran/2-SanDiego->w/2;
    positionSanDiego.y = hEcran/2-SanDiego->h/2;
    positionCake.x = wEcran-cake->w;
    positionCake.y = hEcran-cake->h;
    //ini ennemies à améliorer
    enemies[0].initialisation(1,1);
    enemies[1].initialisation(1,2);
    enemies[2].initialisation(1,3);

    enemies[0].initialisation(3,1);
    enemies[1].initialisation(3,2);
    enemies[2].initialisation(3,3);

    enemies[0].initialisation(2,1);
    enemies[1].initialisation(2,2);
    enemies[2].initialisation(2,3);
    //fin amélioration

    //score ini
    int iPoints=0;
    string strScore;
    ostringstream strPoints;
    //end score ini

    //font
    SDL_Surface *fontSurface;
    fontSurface = load_image( "Fonts/font2.png" );
    BitmapFont font( fontSurface );
    SDL_Surface *Background=NULL;
    Background = load_image("Backgrounds/GoodSky.png");
    apply_surface(0,0,Background,screen,NULL);
    if(history==true)
    {
        font.TextBox(screen,event,"Once upon a time, where new-york was in a strange situation. A giant hole appear in the middle of the town. In there, at the deepest was born a mother vortex. Then a lot of tiny vortex flew through the city to take up people.");
        history = false;
    }
    SDL_ShowCursor(SDL_DISABLE);
    //lance la musique
    musicGame.playMusic(true);
    while(bContinueGame)
    {
        SDL_PollEvent(&event);//Récupération de l'évènement dans event
        switch(event.type)//Test du type d'évènement
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        bContinueGame = false;
                        break;
                    case SDLK_UP:
                        //positionSanDiego.y--;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)/*SDL_BUTTON_WHEELUP etc*/
                {
                    case SDL_BUTTON_RIGHT:

                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                positionSanDiego.y = event.motion.y-SPRITE_WIDTH/2.;
                positionSanDiego.x = event.motion.x-SPRITE_WIDTH/2;
                break;

            case SDL_QUIT: //Si l'évènement est de type "quitter"
                quitProg(&bContinueProg,&bContinueGame);
                break;
        }

        //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255,255,255));
        apply_surface(0,0,Background,screen,NULL);

        //score
        strPoints.str("");
        strPoints << iPoints;
        strScore = "Score : "+strPoints.str()+"/50";
        font.show_text( 10, 10, strScore , screen);
        //fin score


        //Affichage des points
        //sprintf(Points,"Points : %d", iPoints);
        //texte = TTF_RenderText_Blended(police, Points , couleurNoir);

        //Affichage des sprites
        //SDL_BlitSurface(SanDiego,NULL,screen,&positionSanDiego);
        SDL_BlitSurface(cake,NULL,screen, &positionCake);
        //SDL_BlitSurface(texte,NULL,screen,&positionTexte);

        //Si X points alors ennemyX arrive
        if(time.get_ticks()-iPastTime>iVitesse)
        {
                iPastTime=time.get_ticks();

                if(iPoints>=0)
                    enemies[0].move();
                if(iPoints>=4)
                    enemies[1].move();
                if(iPoints>=5)
                    enemies[2].move();
                if(iPoints>=6&&iVitesse==10)
                    iVitesse=8;
                if(iPoints>=7&&iVitesse==8)
                    iVitesse=6;
        }

        if(iPastTimeAnimEnemy+130<time.get_ticks())
        {
            enemies[0].StatusChange();
            enemies[1].StatusChange();
            enemies[2].StatusChange();
            iPastTimeAnimEnemy=time.get_ticks();
        }

        if(iPastTimeAnimPlayer+100<time.get_ticks())
        {
            switch(iPlayerStatus)
            {
                case 0:
                    iPlayerStatus=1;
                    break;
                case 1:
                    iPlayerStatus=2;
                    break;
                case 2:
                    iPlayerStatus=3;
                    break;
                case 3:
                    iPlayerStatus=4;
                    break;
                case 4:
                    iPlayerStatus=5;
                    break;
                case 5:
                    iPlayerStatus=6;
                    break;
                case 6:
                    iPlayerStatus=7;
                    break;
                case 7:
                    iPlayerStatus=0;
                    break;
            }
            iPastTimeAnimPlayer=time.get_ticks();
        }

        //Player
        if(iPlayerStatus<5)
            apply_surface( positionSanDiego.x, positionSanDiego.y, SanDiego, screen, &clipsPlayer[ iPlayerStatus ] );
        else if(iPlayerStatus==5)
            apply_surface( positionSanDiego.x, positionSanDiego.y, SanDiego, screen, &clipsPlayer[ 3 ] );
        else if(iPlayerStatus==6)
            apply_surface( positionSanDiego.x, positionSanDiego.y, SanDiego, screen, &clipsPlayer[ 2 ] );
        else if(iPlayerStatus==7)
            apply_surface( positionSanDiego.x, positionSanDiego.y, SanDiego, screen, &clipsPlayer[ 1 ] );
        //Enemies
        apply_surface( enemies[0].position.x, enemies[0].position.y, enemies[0].surface, screen, &enemies[0].clipsEnemy[ enemies[0].iEnemyStatus ] );
        apply_surface( enemies[1].position.x, enemies[1].position.y, enemies[1].surface, screen, &enemies[1].clipsEnemy[ enemies[1].iEnemyStatus ] );
        apply_surface( enemies[2].position.x, enemies[2].position.y, enemies[2].surface, screen, &enemies[2].clipsEnemy[ enemies[2].iEnemyStatus ] );

        SDL_Flip(screen);

        //collision cake
        if(collision(positionSanDiego,positionCake)==1)
        {
           iPoints++;
           positionCake.x = MyRand(0+cake->w, wEcran-cake->w);
           positionCake.y = MyRand(0+cake->h, hEcran-cake->h);
        }
        if(collision(enemies[0].position,positionSanDiego)==1||
           collision(enemies[1].position,positionSanDiego)==1||
           collision(enemies[2].position,positionSanDiego)==1)
        {
            bContinueGame=false;
        }

        //collision enemy & cake
        ColliCible(&enemies[0],&enemies[1],positionCake);
        ColliCible(&enemies[1],&enemies[2],positionCake);
        ColliCible(&enemies[2],&enemies[0],positionCake);

        //fin du jeu
        if(iPoints==50)
        {
            SDL_Surface *fontSurfaceCredits;
            fontSurfaceCredits = load_image( "Fonts/font2.png" );
            BitmapFont fontCredits( fontSurfaceCredits );
            //partie 1
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 230,230,0));
            fontCredits.show_text_center(100, "Winner !!", screen );
            fontCredits.show_text(60,150, "Hope you enjoyed it", screen);
            SDL_Flip(screen);
            fontCredits.waitInput(event);
            bContinueGame=false;
            iPoints=0;
        }
    }
    //CleanUpGame();
    musicGame.stopMusic();
    musicGame.freeMusic();
    return bContinueProg;
}

void ColliCible(Enemy *cible1, Enemy *cible2, SDL_Rect posiCake)
{
    //tollérence de l'éspace avec la collision, en pixel
    int iSpace =2; //tollérence doit être changer en fonctione de la vitesse !!
    //colli c1-c2
    if(collision(cible1->position,cible2->position)==1)
    {
        //hori
        if(cible2->position.x+cible2->position.w-iSpace<cible1->position.x)
        {
            cible2->iSensHori=0;
            cible1->iSensHori=1;
        }
        else if (cible2->position.x>cible1->position.x+cible1->position.w-iSpace)
        {
            cible2->iSensHori=1;
            cible1->iSensHori=0;
        }
        //verti
        if(cible2->position.y+cible2->position.h-iSpace<cible1->position.y)
        {
            cible2->iSensVerti=1;
            cible1->iSensVerti=0;
        }
        else if (cible2->position.y>cible1->position.y+cible1->position.h-iSpace)
        {
            cible2->iSensVerti=0;
            cible1->iSensVerti=1;
        }
    }
    //collision cake
    if(collision(cible1->position,posiCake)==1)
    {
        if(posiCake.x+posiCake.w-iSpace<cible1->position.x)
            cible1->iSensHori=1;
        else if (posiCake.x>cible1->position.x+cible1->position.w-iSpace)
            cible1->iSensHori=0;
        //verti
        if(posiCake.y+posiCake.h-iSpace<cible1->position.y)
            cible1->iSensVerti=0;
        else if (posiCake.y>cible1->position.y+cible1->position.h-iSpace)
            cible1->iSensVerti=1;
    }
}

void quitProg(bool *prog,bool *game)
{
    *prog=false;
    *game=false;
}

void quitGame(bool *prog,bool *game)
{
    *prog=true;
    *game=false;
}

void intro(SDL_Surface *screen)
{
    int inc = 0;
    SDL_Surface *textBox=NULL;

    //textBox->w=10;
    //textBox->h=10;
    while(inc<1000)
    {
        //apply_surface( wEcran/2-textBox->w/2, 50, textBox, screen, NULL);
        textBox = SDL_CreateRGBSurface(0,50,50,32,0,0,0,0);
        apply_surface( wEcran/2-textBox->w/2, 50, textBox, screen, NULL);
        SDL_Flip(screen);
        inc++;
    }
}
