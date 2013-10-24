#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "Classe_Enemy.h"

//ajouter load_image

Enemy::Enemy()
{
		lvl=-1;
		SDL_Rect position;
		SDL_Surface *surface;
		iSensVerti=-1; // 0= bas/gauche  1= haut/droite
		iSensHori=-1;
		iEnemyStatus=-1;
}

void Enemy::initialisation(/*enemy *enem,*/ int test, int iLvl)
{
    //variables
    if (test == 1)
    {
		iEnemyStatus=0;
        lvl=iLvl;
        iSensVerti=1;
        iSensHori=0;
    }
    //sprite
    //strcmp(chaine1,chaine2)==0
    else if (test == 2)
    {
				//On coupe la feuille de sprite
		for(int i=0;i<CLIP_ENEMY_LENGTH;i++)
		{
			clipsEnemy[ i ].x = SPRITE_WIDTH * i;
			clipsEnemy[ i ].y = 0;
			clipsEnemy[ i ].w = SPRITE_WIDTH;
			clipsEnemy[ i ].h = SPRITE_WIDTH;
		}
        if(iLvl==1)
        {
            surface = IMG_Load("Sprites/spirals1.png");
        }
        else if (iLvl==2)
        {
            surface = IMG_Load("Sprites/spirals2.png");
        }
        else if (iLvl==3)
        {
            surface = IMG_Load("Sprites/spirals3.png");
        }
    }
    //position
    else if (test == 3)
    {
        position.x = iLvl*100;
        position.y = SPRITE_WIDTH/2+hEcran;
    }
}

void Enemy::move()
{
    //Test collision avec l'écran
    if(position.x<= 0)
        iSensHori=1;
    if(position.y <= 0)
        iSensVerti=0;
    if(position.x+SPRITE_WIDTH>=wEcran)
        iSensHori=0;
    if(position.y+SPRITE_WIDTH>=hEcran)
        iSensVerti=1;

    //Bouger
    if(iSensVerti==0&&iSensHori==0)
    {
        position.y++;
        position.x--;
    }
    else if(iSensVerti==1&&iSensHori==0)
    {
        position.y--;
        position.x--;
    }
    else if(iSensVerti==0&&iSensHori==1)
    {
        position.y++;
        position.x++;
    }
    else if(iSensVerti==1&&iSensHori==1)
    {
        position.y--;
        position.x++;
    }
}

void Enemy::StatusChange()
{
	switch(iEnemyStatus)
	{
		case 0:
			iEnemyStatus=1;
			break;
		case 1:
			iEnemyStatus=2;
			break;
		case 2:
			iEnemyStatus=3;
			break;
		case 3:
			iEnemyStatus=0;
			break;
	}
}
