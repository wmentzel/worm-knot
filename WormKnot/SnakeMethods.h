#ifndef SNAKEMETHODS_H
#define SNAKEMETHODS_H

void tagPlayer::tagSnake::ChangeHeadPos()
{
	ptDelete.x = ptOldElementsPos[iNumElements - 1].x;
	ptDelete.y = ptOldElementsPos[iNumElements - 1].y;
	
	if(pParent->iKeys[LEFT] == pParent->GetPressedKey())
		--ptElementsPos[0].x;
	if(pParent->iKeys[RIGHT] == pParent->GetPressedKey())
		++ptElementsPos[0].x;
	if(pParent->iKeys[UP] == pParent->GetPressedKey())
		--ptElementsPos[0].y;
	if(pParent->iKeys[DOWN] == pParent->GetPressedKey())
		++ptElementsPos[0].y;
}

void tagPlayer::tagSnake::Draw(HDC hDCMem)
{
	int i;
	RECT rect;

	// delete old
	rect.left = (ptDelete.x * iColWidth) + 1; // + 1, because of the 1px grid
	rect.top = (ptDelete.y * iRowHeight) + 1 + MARGIN;
	rect.right = (ptDelete.x * iColWidth) + iColWidth;
	rect.bottom = (ptDelete.y * iRowHeight) + iRowHeight + MARGIN;

	FillRect(hDCMem, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));

	// draw the snake
	for(i = iNumElements - 1; i >= 0; i--)
	{
		rect.left = (ptElementsPos[i].x * iColWidth) + 1;
		rect.top = (ptElementsPos[i].y * iRowHeight) + 1 + MARGIN;
		rect.right = (ptElementsPos[i].x * iColWidth) + iColWidth;
		rect.bottom = (ptElementsPos[i].y * iRowHeight) + iRowHeight + MARGIN;
		
		if(i == 0) // draw head element
			FillRect(hDCMem, &rect, hHeadBrush);
		else
			FillRect(hDCMem, &rect, hBodyBrush);
	}
}

void tagPlayer::tagSnake::DetectCollision(HDC hDCMem)
{
	COLORREF crTemp;

	// eating?
	for(int i = 0; i < iNumPlayers; i++)
	{
		if((ptElementsPos[0].x == Food[i].GetX()) &&
			(ptElementsPos[0].y == Food[i].GetY()))
		{
			Food[i].Generate();
			Food[i].Draw(hDCMem, FALSE);
			
			iNumElements++;
			
			ptElementsPos.push_back(Point(ptOldElementsPos[0].x, ptOldElementsPos[0].y));
			ptOldElementsPos.push_back(Point(0, 0));
			break;
		}
	}
	
	// detect if snake touches another snake or itself
	// detect if snake touches the border
	crTemp = GetPixel (hDCMem, (ptElementsPos[0].x * iColWidth) + 1 , ((ptElementsPos[0].y * iRowHeight) + 1 + MARGIN));

	if((crTemp != RGB (255, 255, 255) && crTemp != FOOD_COLOR)	||
		((ptElementsPos[0].x) < 0) ||
		((ptElementsPos[0].x) > (GRID - 1)) ||
		((ptElementsPos[0].y) < 0) ||
		((ptElementsPos[0].y) > (GRID - 1)))
	{
		pParent->SetLost(TRUE);
		iLostCounter++;
	}	
}

void tagPlayer::tagSnake::SaveOldElementsPos()
{
	for(int i = 0; i < iNumElements; i++)
	{
		if(!pParent->isLost())
			ptOldElementsPos[i] = ptElementsPos [i];
	}
}

void tagPlayer::tagSnake::SetNewElementsPos()
{
	for(int i = 1; i < iNumElements; i++)
	{
		if(!pParent->isLost())
			ptElementsPos[i] = ptOldElementsPos [i - 1];
	}
}

#endif