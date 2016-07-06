#ifndef GLOBALS_H
#define GLOBALS_H

#define GRID 50
#define TIMER_ID 0
#define MULTIPLICATOR 100

#define MARGIN (cyChar + 4)
#define SETTINGS_MARGIN 10
#define OUTPUT TEXT("%02d")
#define TEXTMARGIN 100

#define FOOD_COLOR RGB(136, 92, 60)
#define BUFFER_SIZE 255

#define EASY 3
#define MEDIUM 2
#define HARD 1

enum 
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

#define IS_MULTIPLAYER (iNumPlayers > 1)
#define IS_SINGLEPLAYER (iNumPlayers == 1)

HWND hWndMain, hWndSettings;
WNDCLASS wndclass;
TCHAR szAppName[] = TEXT("WormKnot");
TCHAR szBuffer[BUFFER_SIZE] = TEXT(" ");
HBRUSH hFoodBrush = CreateSolidBrush(FOOD_COLOR);

int iNumPlayers = -1;
int iTime = 300;
bool bShowGrid = TRUE;
bool bStarted = FALSE;

LONG cyChar, cxChar;
int iRowHeight, iColWidth;
int iLostCounter;

COLORREF crBodyColors[] = 
{
	RGB (255, 0, 0), // red
	RGB (0, 255, 0), // green
	RGB (0, 0, 255), // blue
	RGB (255, 255, 0)
};

COLORREF crHeadColors[] =
{
	RGB (210, 0, 0),
	RGB (0, 210, 0),
	RGB (0, 0, 210),
	RGB (210, 210, 0)
};
#endif