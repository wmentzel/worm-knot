#ifndef SNAKE_H
#define SNAKE_H
	
class tagSnake
{
	public:
		tagPlayer *pParent;
		POINT ptDelete;

		vector<Point> ptElementsPos;
		vector<Point> ptOldElementsPos;

		int iNumElements;
	
		HBRUSH hHeadBrush;
		COLORREF crHeadColor;
	
		HBRUSH hBodyBrush;
		COLORREF crBodyColor;
	
		void ChangeHeadPos();
		void Draw(HDC); 
		void DetectCollision(HDC);
		void SaveOldElementsPos();
		void SetNewElementsPos();
} Snake;

#endif