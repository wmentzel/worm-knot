#ifndef MAIN_H
#define MAIN_H

void InitializeGame()
{	
	if((Player == NULL) && (Food == NULL))
	{
		if(!(Player = new PLAYER[iNumPlayers]) ||
			!(Food = new FOOD[iNumPlayers]))
		{
			MessageBox(hWndMain, TEXT("No memory could be allocated!"), TEXT("Error"), MB_ICONERROR | MB_APPLMODAL);
			PostQuitMessage (0);
		}
	}

	for(int i = 0; i < iNumPlayers; i++)
	{
		Player[i].SetPressedKey(PlayerKeys[i].iRight);
		Player[i].SetLost(FALSE);
		Player[i].SetDefinedKeys(PlayerKeys[i].iLeft, PlayerKeys[i].iRight, PlayerKeys[i].iUp, PlayerKeys[i].iDown);
		
		Player[i].Snake.iNumElements = 1;

		Player[i].Snake.hBodyBrush = CreateSolidBrush(crBodyColors[i]);
		Player[i].Snake.hHeadBrush = CreateSolidBrush(crHeadColors[i]);
		
		Player[i].Snake.crBodyColor = crHeadColors[i];
		Player[i].Snake.crHeadColor = crBodyColors[i];
		
		Player[i].Snake.ptElementsPos.push_back(Point(rand() % (GRID - 1), rand() % (GRID - 1)));
		Player[i].Snake.ptOldElementsPos.push_back(Point(Player[i].Snake.ptElementsPos[0].x, Player[i].Snake.ptElementsPos[0].y));
	}

	iLostCounter = 0;
}

void DrawGrid(HDC hDCMem, RECT *rect)
{
	HPEN hPen;
	HGDIOBJ hOldPen;
	POINT pt;
	RECT rectTemp;
	
	if(bShowGrid)
		hPen = (HPEN) GetStockObject(BLACK_PEN);
	else
		hPen = (HPEN) GetStockObject(WHITE_PEN);
	
	hOldPen = SelectObject(hDCMem, hPen);

	for(int i = 0; i <= GRID; i++)
	{
		MoveToEx(hDCMem, 0, (i * iRowHeight) + MARGIN, &pt); // horizontal
		LineTo(hDCMem, (iColWidth * GRID), (i * iRowHeight) + MARGIN);
		
		MoveToEx(hDCMem, (i * iColWidth), MARGIN, &pt); // vertical
		LineTo(hDCMem, (i * iColWidth), (iRowHeight * GRID) + MARGIN);
	}

	SelectObject(hDCMem, hOldPen);
	DeleteObject(hOldPen);

	if(bShowGrid == FALSE)
	{
		SetRect(&rectTemp, 0, MARGIN, (GRID * iColWidth) + 1, (GRID * iRowHeight) + MARGIN + 1);
		FrameRect(hDCMem, &rectTemp, (HBRUSH) GetStockObject(BLACK_BRUSH));
	}
}

void UpdateHUD(HDC hDCMem, RECT * rect)
{
	RECT rectTemp;
	
	SetRect(&rectTemp, 0, 0, rect->right, MARGIN);
	FillRect(hDCMem, &rectTemp, (HBRUSH) GetStockObject(WHITE_BRUSH));
		
	SetBkMode(hDCMem, TRANSPARENT);
	
	// updating HUD
	for(int i = 0; i < iNumPlayers; i++)
	{
		if(Player[i].isLost())
			wsprintf(szBuffer, TEXT("Lost!"));
		else
			wsprintf(szBuffer, TEXT("%d"), (Player[i].Snake.iNumElements - 1));

		SetTextColor(hDCMem, crHeadColors[i]);
		TextOut(hDCMem, TEXTMARGIN * i + 10, 2, szBuffer, lstrlen (szBuffer));
	}
}

void BltIt(HDC hDCMem, RECT * rect)
{
	HDC hDCMain = GetDC(hWndMain);
	BitBlt(hDCMain, 0, 0, rect->right, rect->bottom, hDCMem, 0, 0, SRCCOPY);
	ReleaseDC(hWndMain, hDCMain);
	ValidateRect(hWndMain, rect);
}

#endif