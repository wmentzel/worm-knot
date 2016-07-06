#ifndef SETTINGSPROC_H
#define SETTINGSPROC_H

LRESULT CALLBACK SettingsProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	static RECT rect;
	HDC hDC;
	
	enum
	{
		CHECK1 = 1, CHECK2, CHECK3,
		STATIC_TEXT1,
		STATIC_TEXT2,
		EDIT,
		BUTTON,
		BUTTON_INFO
	};
	
	static const int iIDCheckboxes[] = { CHECK1, CHECK2, CHECK3 };
	static const TCHAR szLabel[3][7] = { TEXT("easy"), TEXT("medium"), TEXT("hard") };
	static HWND hwndSText1, hwndSText2;
	static HWND hwndEdit;
	static HWND hwndCheckboxes[3];
	static HWND hwndButton, hwndButtonInfo;
	
	switch(message)
	{
		case WM_CREATE:
		{
			EnableWindow(hWndMain, FALSE);

			GetClientRect(hwnd, &rect);

			hwndSText1 = CreateWindow(TEXT("static"), TEXT("Players"),
			WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP,
			SETTINGS_MARGIN, 10, 100, 30, hwnd, (HMENU) STATIC_TEXT1, 
			((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			
			hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
			TEXT("edit"), TEXT("4"), WS_CHILD | WS_VISIBLE,
			SETTINGS_MARGIN + 60, 10, 30, 22,
			hwnd, (HMENU) EDIT,
			((LPCREATESTRUCT) lParam) -> hInstance, NULL);

			hwndSText2 = CreateWindow(TEXT("static"), TEXT("Difficulty: easy"),
			WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP,
			SETTINGS_MARGIN, 50, 120, 20, hwnd, (HMENU) STATIC_TEXT1, 
			((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			
			// checkboxes to set the difficulty
			for(int i = 0; i < 3; i++)
			{
				hwndCheckboxes[i] = CreateWindow(TEXT("button"), 
				TEXT("Difficulty"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
				(20 * i) + 10, 80, 20, 20, hwnd, (HMENU) iIDCheckboxes[i],
				((LPCREATESTRUCT) lParam)->hInstance, NULL);
			}

			hwndButton = CreateWindow(TEXT("button"), 
			TEXT("Start"), WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE,
			SETTINGS_MARGIN, 110, 70, 20,
			hwnd, (HMENU) BUTTON,
			((LPCREATESTRUCT) lParam)->hInstance, NULL);

			hwndButtonInfo = CreateWindow(TEXT("button"),
			TEXT("Controls"), WS_CHILD | BS_DEFPUSHBUTTON | WS_VISIBLE,
			85, 110, 70, 20,
			hwnd, (HMENU) BUTTON_INFO,
			((LPCREATESTRUCT) lParam)->hInstance, NULL);

			SendMessage(hwndCheckboxes[0], BM_SETCHECK, BST_CHECKED, 0);

			return 0;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case BUTTON:
					GetWindowText(hwndEdit, szBuffer, BUFFER_SIZE);
					_stscanf(szBuffer, TEXT("%d"), &iNumPlayers);

					if(iNumPlayers > 0 && iNumPlayers <= 4)
					{
						EnableWindow(hWndMain, TRUE);
						ShowWindow(hwnd, SW_HIDE);
						
						InitializeGame();
						bStarted = TRUE;

						SetTimer(hWndMain, TIMER_ID, iTime, NULL);
					}
					else
						SetWindowText(hwndEdit, TEXT("4"));
				break;

				case BUTTON_INFO:
				{
					MessageBox(hwnd, TEXT("Order: left, right, up, down\n\nPlayer 1: arrow keys\nPlayer 2: a, d, w, s\n")
						TEXT("Player 3: j, l, i, k\nPlayer 4: 1, 3, 5, 2 (NUM BLOCK)\n\np: pause\ng: grid on/off"), TEXT("Controls"), MB_OK);
				}
				break;
				
				case CHECK1:
				case CHECK2:
				case CHECK3:
				{
					iTime = 400 - (LOWORD(wParam) * MULTIPLICATOR);
					
					// uncheck the other checkboxes
					for(int i = 0; i < 3; i++)
					{
						if(iIDCheckboxes[i] != LOWORD(wParam))
							SendMessage(hwndCheckboxes[i], BM_SETCHECK, BST_UNCHECKED, 0);
						else
						{
							wsprintf(szBuffer, TEXT("Difficulty: "));
							_tcscat_s(szBuffer, BUFFER_SIZE, szLabel[i]);
							SetWindowText(hwndSText2, szBuffer);
						}
					}
				}
				break;
			}
		}
		return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

#endif
