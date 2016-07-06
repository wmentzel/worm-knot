/**********************************
WormKnot
started 30.12.2007
Copyright 2007, 2008 Willi Mentzel
willi.mentzel@gmail.com
**********************************/

#include <windows.h>
#include <TCHAR.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#include <time.h>
#include <string.h>

void GenerateNewFood();

#include "Globals.h"
#include "PlayerKeys.h"

#include "Food.h"
#include "Player.h"

#include "Main.h"

#include "WndProc.h"
#include "SettingsProc.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	srand(time(0));

	MSG msg;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL; 
	wndclass.lpszClassName = szAppName;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Programm arheitet mit Unicode und setzt Windows NT voraus!"),
		szAppName, MB_ICONERROR);
		return 0;
	}

	hWndMain = CreateWindow(szAppName,
							TEXT("WormKnot v.0.1 BETA"),
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							NULL,
							NULL,
							hInstance,
							NULL
							);

	// create settings window
	
	wndclass.lpfnWndProc = SettingsProc;
	wndclass.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(240, 240, 240));
	wndclass.lpszClassName = TEXT("Settings");
	RegisterClass(&wndclass);
	
	hWndSettings = CreateWindow(TEXT("Settings"),
	TEXT("Optionen"),
	WS_BORDER | WS_CAPTION,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	175,
	165,
	NULL, // parent handle
	NULL,
	hInstance,
	NULL
	);

	ShowWindow(hWndMain, iCmdShow);
	UpdateWindow(hWndMain);
	
	ShowWindow(hWndSettings, iCmdShow);
    UpdateWindow(hWndSettings);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}