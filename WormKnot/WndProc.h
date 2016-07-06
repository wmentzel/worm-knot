#ifndef WNDPROC_H
#define WNDPROC_H

#define KEY_G 0x47
#define KEY_P 0x50

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	TEXTMETRIC tm;
	
	int i, iPlayer;
	static bool bPause = FALSE;
	static HDC hDCMem; 
	static HBITMAP hBitmap = NULL;
	static HGDIOBJ hOldBitmap = NULL;
	static RECT rect;

	HBRUSH crNew = CreateSolidBrush(RGB(255, 255, 0));;

	switch(message)
	{
		case WM_CREATE:
		{	
			hDC = GetDC(hwnd);
			hDCMem = CreateCompatibleDC(hDC);
			GetTextMetrics(hDC, &tm);
			cyChar = tm.tmHeight;
			cxChar = tm.tmAveCharWidth;
			ReleaseDC(hwnd, hDC);

			return 0;
		}
		
		case WM_ERASEBKGND: return 1;

		case WM_SIZE:
		{
			GetClientRect(hwnd, &rect);

			if(hBitmap != NULL)
			{
				SelectObject(hDCMem, hOldBitmap);
				DeleteObject(hBitmap);
			}
			
			hDC = GetDC(hwnd);
			hBitmap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
			ReleaseDC(hwnd, hDC);
			
			if(hOldBitmap == NULL)
				hOldBitmap = SelectObject(hDCMem, hBitmap);
			else
				SelectObject(hDCMem, hBitmap);

			iColWidth = float(rect.right) / float(GRID);				// width of a col
			iRowHeight = float(rect.bottom - MARGIN) / float(GRID);	// height of a row
			
			FillRect(hDCMem, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));
			
			for(iPlayer = 0; iPlayer < iNumPlayers && bStarted; iPlayer++)
			{
				Player[iPlayer].Snake.Draw(hDCMem);
				Food[iPlayer].Draw(hDCMem, FALSE);
			}
			
			DrawGrid(hDCMem, &rect);
			
			if(bStarted)
				UpdateHUD(hDCMem, &rect);

			BltIt(hDCMem, &rect);
			return 0;

		}// WM_SIZE

		case WM_KEYDOWN:
		{
			if(wParam == KEY_G)
			{
				bShowGrid = !bShowGrid;
				
				DrawGrid(hDCMem, &rect);
				BltIt(hDCMem, &rect);
				return 0;
			}
			else if(wParam == KEY_P)
			{
				bPause = !bPause;
				
				if(bPause == TRUE)
					KillTimer(hwnd, TIMER_ID);
				else 
					SetTimer(hwnd, TIMER_ID, iTime, NULL);
				
				return 0;
			}
			else
			{
				// retrieve which player belongs to the pressed key
				for(iPlayer = 0; iPlayer < iNumPlayers; iPlayer++)
				{
					if(Player[iPlayer].isPlayerKey (wParam))
						break;
				} // for
			} // else
			return 0;
		} // case WM_KEYDOWN

		case WM_TIMER:
		
		if((iNumPlayers - 1) <= iLostCounter && IS_MULTIPLAYER ||
			iLostCounter == 1 && IS_SINGLEPLAYER)
		{
			KillTimer(hwnd, TIMER_ID);

			if(iLostCounter == (iNumPlayers - 1) && IS_MULTIPLAYER) // only for multiplayer
			{
				// detect which player has won
				for(i = 0; i < iNumPlayers; i++)
				{
					if(!Player[i].isLost())
					{
						wsprintf(szBuffer, TEXT("Player %d wins!\n\nGo on?"), (i + 1));
						break;
					}
				}
			}
			
			if(iLostCounter == iNumPlayers)
			{
				if(IS_SINGLEPLAYER)
					wsprintf(szBuffer, TEXT("Lost!\n\nGo on?"));
				else // IS_MUTLIPLAYER == TRUE
					wsprintf(szBuffer, TEXT("Draw!\n\nGo on?"));
			}

			// restart the game
			if(MessageBox(hwnd, szBuffer, TEXT("GAME OVER"), MB_YESNO | MB_APPLMODAL) == IDYES)
			{
				// resetting the bitmap
				SelectObject(hDCMem, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hDCMem);

				hBitmap = NULL;
				
				// creating new Memory Device Context
				hDC = GetDC(hwnd);
				hDCMem = CreateCompatibleDC(hDC);
				ReleaseDC(hwnd, hDC);
				
				for(iPlayer = 0; iPlayer < iNumPlayers; iPlayer++)
				{
					Player[iPlayer].Snake.ptElementsPos.clear();
					Player[iPlayer].Snake.ptOldElementsPos.clear();
					Food[iPlayer].Generate();
				}

				InitializeGame();
				
				SendMessage(hwnd, WM_SIZE, 0, 0);

				SetTimer(hwnd, TIMER_ID, iTime, NULL);
			}
			else	// end the game
			{
				PostQuitMessage(0);
				return 0; 
			}
		}

		for(iPlayer = 0; iPlayer < iNumPlayers; iPlayer++)
		{
			if(!Player[iPlayer].isLost())
			{
				Player[iPlayer].Snake.SaveOldElementsPos();
				Player[iPlayer].Snake.ChangeHeadPos();
				Player[iPlayer].Snake.SetNewElementsPos();
				Player[iPlayer].Snake.DetectCollision(hDCMem);
				Player[iPlayer].Snake.Draw(hDCMem);
				Food[iPlayer].Draw(hDCMem, FALSE);
			}
			else
				Food[iPlayer].Draw(hDCMem, TRUE);
		}

		UpdateHUD(hDCMem, &rect);
		BltIt(hDCMem, &rect);

		return 0;

		case WM_PAINT:
			BltIt(hDCMem, &rect);
		return 0;

		case WM_DESTROY:
		{
			KillTimer(hwnd, TIMER_ID);
				
			// cleaning up...
			delete Player;
			delete Food;

			SelectObject(hDCMem, hOldBitmap);
			DeleteObject(hBitmap);
			DeleteDC(hDCMem);

			MessageBox(hwnd, TEXT("Developed by Willi Mentzel\nwilli.mentzel@gmail.com\nCopyright 2008 Willi Mentzel\n\nThis program was released under the terms of GNU GPL v3. Visit http://www.gnu.org/ for further information.\n\nThis is a BETA! Please report all bugs! Have fun!"), TEXT("WormKnot"), MB_OK | MB_APPLMODAL);

			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif