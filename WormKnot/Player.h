#ifndef PLAYER_H
#define PLAYER_H

class Point
{
	public:
		int x;
		int y;
	
	Point(int cx, int cy)
	{
		x = cx;
		y = cy;
	}
};
typedef class tagPlayer
{
	private:
		int iPressedKey;
		bool bLost;
		int iKeys[4];

	public:
		tagPlayer();
		void SetPressedKey(int);
		void SetDefinedKeys(int, int, int, int);
		void SetLost(bool);
		bool isLost();
		bool isPlayerKey(int);
		int	 GetPressedKey();

	#include "Snake.h"
} *PPLAYER, PLAYER;

PPLAYER Player = NULL;

#include "SnakeMethods.h"
#include "PlayerMethods.h"

#endif