#include <SDL.h>

#include "constantes.h"

#ifndef CLASSE_ENEMY_H
#define CLASSE_ENEMY_H

class Enemy
{
	private:
		int lvl;

	public:
		int iEnemyStatus;
		int iSensVerti; // 0= bas/gauche  1= haut/droite
		int iSensHori;
		SDL_Rect position;
		SDL_Surface *surface;
		SDL_Rect clipsEnemy[ CLIP_ENEMY_LENGTH ];
		Enemy();
		void initialisation(int test, int iLvl);
		void move();
		void StatusChange();
};
#endif
