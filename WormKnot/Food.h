#ifndef FOOD_H
#define FOOD_H

typedef class tagFood
{
	private:
		POINT Pos;
		int iDirection;
	
	public:
		tagFood();
		int GetX();
		int GetY();
		void Generate();
		void Move(HDC);
		void Draw(HDC, bool);
} *PFOOD, FOOD;

PFOOD Food = NULL;

#include "FoodMethods.h"

#endif