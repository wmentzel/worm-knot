#ifndef FOODMETHODS_H
#define FOODMETHODS_H

int tagFood::GetX() { return Pos.x; }
int tagFood::GetY() { return Pos.y; }

tagFood::tagFood()
{
	Generate(); // initialize pos
	iDirection = -1;
}

void tagFood::Generate() // generate new food / food pos
{
	Pos.x = rand () % (GRID - 1);
	Pos.y = rand () % (GRID - 1);
}

void tagFood::Draw(HDC hDCMem, bool fErase)
{
	// draw food
	RECT rect;
	rect.left = (Pos.x * iColWidth) + 1;
	rect.top = (Pos.y * iRowHeight) + 1 + MARGIN;
	rect.right = (Pos.x * iColWidth) + iColWidth;
	rect.bottom = (Pos.y * iRowHeight) + iRowHeight + MARGIN;
	
	if(fErase)
		FillRect(hDCMem, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));
	else
		FillRect(hDCMem, &rect, hFoodBrush);
}

void tagFood::Move(HDC hDCMem)
{
	Draw(hDCMem, TRUE); // delete old

	if(iDirection == -1)
		iDirection = rand() % 4;
	
	switch(iDirection)
	{
		case DOWN:
		if((Pos.y + 1) < GRID)
			Pos.y++;
		else
			iDirection = -1;
		break;

		case UP:
		if((Pos.y - 1) >= 0)
			Pos.y--;
		else
			iDirection = -1;
		break;

		case RIGHT:
		if((Pos.x + 1) < GRID)
			Pos.x++;
		else
			iDirection = -1;
		break;

		case LEFT:
		if((Pos.x - 1) >= 0)
			Pos.x--;
		else
			iDirection = -1;
		break;
	}

	Draw(hDCMem, FALSE);
}

#endif