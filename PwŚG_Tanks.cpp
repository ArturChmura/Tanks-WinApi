// PwŚG_Tanks.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "PwŚG_Tanks.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>   
#include <Windows.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


#define MAX_LOADSTRING 100
#define WINDOWHEIGHT 600
#define WINDOWWIDTH 800
#define MENUHEIGHT 600
#define MENUWIDTH 200

using namespace Gdiplus;
HWND hWndMain;

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

WCHAR szTitleStats[MAX_LOADSTRING] = _T("Stats Title");                  // The title bar text
WCHAR szWindowClassStats[MAX_LOADSTRING] = _T("Stats Class");            // the main window class name

WCHAR szTitleMenu[MAX_LOADSTRING] = _T("Menu Title");                  // The title bar text
WCHAR szWindowClassMenu[MAX_LOADSTRING] = _T("Menu Class");            // the main window class name

WCHAR szTitleTankBlue[MAX_LOADSTRING] = _T("TankBlue Title");                  // The title bar text
WCHAR szWindowClassTankBlue[MAX_LOADSTRING] = _T("TankBlue Class");

WCHAR szTitleTankGreen[MAX_LOADSTRING] = _T("TankGreen Title");                  // The title bar text
WCHAR szWindowClassTankGreen[MAX_LOADSTRING] = _T("TankGreen Class");

WCHAR szTitleScore[MAX_LOADSTRING] = _T("Score Title");                  // The title bar text
WCHAR szWindowClassScore[MAX_LOADSTRING] = _T("Score Class");

RECT rcMain;
int nCmdShowGlobal;
int tankRad = 40;
const int startingcoords[2][2] = { { tankRad,tankRad }, {WINDOWWIDTH - tankRad,WINDOWHEIGHT - tankRad} };


//=================================== TWORZENIE OKIEN ===========================================================================

void SetClientSize(HWND hwnd, int clientWidth, int clientHeight)
{
	if (IsWindow(hwnd))
	{

		DWORD dwStyle = GetWindowLongPtr(hwnd, GWL_STYLE);
		DWORD dwExStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
		HMENU menu = GetMenu(hwnd);

		RECT rc = { 0, 0, clientWidth, clientHeight };

		if (!AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle))
			MessageBox(NULL, _T("AdjustWindowRectEx Failed!"), _T("Error"), MB_OK);

		SetWindowPos(hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top,
			SWP_NOZORDER | SWP_NOMOVE);
	}
}

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcStats(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcMenu(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK	 WndProcTank1(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK	 WndProcTank2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	 WndProcScore(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	nCmdShowGlobal = nCmdShow;
	// TODO: Place code here.

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PWSGTANKS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PWSGTANKS));

	MSG msg;



	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//+
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcexMain;

	wcexMain.cbSize = sizeof(WNDCLASSEX);

	wcexMain.style = CS_HREDRAW | CS_VREDRAW;
	wcexMain.lpfnWndProc = WndProc;
	wcexMain.cbClsExtra = 0;
	wcexMain.cbWndExtra = 0;
	wcexMain.hInstance = hInstance;
	wcexMain.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcexMain.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcexMain.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(250, 236, 130)));
	wcexMain.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_PWSGTANKS);
	wcexMain.lpszClassName = szWindowClass;
	wcexMain.hIconSm = LoadIcon(wcexMain.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	WNDCLASSEX wcexStats = { 0 };
	wcexStats.cbSize = sizeof(WNDCLASSEX);

	wcexStats.style = CS_HREDRAW | CS_VREDRAW;
	wcexStats.lpfnWndProc = WndProcStats;
	wcexStats.cbClsExtra = 0;
	wcexStats.cbWndExtra = 0;
	wcexStats.hInstance = hInstance;
	wcexStats.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcexStats.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcexStats.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));
	wcexStats.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_PWSGTANKS);
	wcexStats.lpszClassName = szWindowClassStats;
	wcexStats.hIconSm = LoadIcon(wcexStats.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	//WNDCLASSEX wcexTank1 = { 0 };
	//wcexTank1.cbSize = sizeof(WNDCLASSEX);
	//wcexTank1.style = CS_HREDRAW | CS_VREDRAW;
	//wcexTank1.lpfnWndProc = WndProcTank1;
	//wcexTank1.cbClsExtra = 0;
	//wcexTank1.cbWndExtra = 0;
	//wcexTank1.hInstance = hInstance;
	//wcexTank1.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wcexTank1.hCursor = LoadCursor(nullptr, IDC_CROSS);
	//wcexTank1.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(250, 236, 130)));
	//wcexTank1.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_PWSGTANKS);
	//wcexTank1.lpszClassName = szWindowClassTankBlue;
	//wcexTank1.hIconSm = LoadIcon(wcexTank1.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	//WNDCLASSEX wcexTank2 = { 0 };
	//wcexTank2.cbSize = sizeof(WNDCLASSEX);
	//wcexTank2.style = CS_HREDRAW | CS_VREDRAW;
	//wcexTank2.lpfnWndProc = WndProcTank2;
	//wcexTank2.cbClsExtra = 0;
	//wcexTank2.cbWndExtra = 0;
	//wcexTank2.hInstance = hInstance;
	//wcexTank2.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wcexTank2.hCursor = LoadCursor(nullptr, IDC_CROSS);
	//wcexTank2.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(250, 236, 130)));
	//wcexTank2.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_PWSGTANKS);
	//wcexTank2.lpszClassName = szWindowClassTankGreen;
	//wcexTank2.hIconSm = LoadIcon(wcexTank2.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	WNDCLASSEX wcexMenu = { 0 };
	wcexMenu.cbSize = sizeof(WNDCLASSEX);
	wcexMenu.style = CS_HREDRAW | CS_VREDRAW;
	wcexMenu.lpfnWndProc = WndProcMenu;
	wcexMenu.cbClsExtra = 0;
	wcexMenu.cbWndExtra = 0;
	wcexMenu.hInstance = hInstance;
	wcexMenu.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcexMenu.hCursor = LoadCursor(nullptr, IDC_CROSS);
	wcexMenu.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 128, 91)));
	wcexMenu.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_PWSGTANKS);
	wcexMenu.lpszClassName = szWindowClassMenu;
	wcexMenu.hIconSm = LoadIcon(wcexMenu.hInstance, MAKEINTRESOURCE(IDI_ICON1));


	WNDCLASSEXW wcexScore;

	wcexScore.cbSize = sizeof(WNDCLASSEX);

	wcexScore.style = CS_HREDRAW | CS_VREDRAW;
	wcexScore.lpfnWndProc = WndProcScore;
	wcexScore.cbClsExtra = 0;
	wcexScore.cbWndExtra = 0;
	wcexScore.hInstance = hInstance;
	wcexScore.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcexScore.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcexScore.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(250, 236, 130)));
	wcexScore.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_PWSGTANKS);
	wcexScore.lpszClassName = szWindowClassScore;
	wcexScore.hIconSm = LoadIcon(wcexScore.hInstance, MAKEINTRESOURCE(IDI_ICON1));



	return RegisterClassExW(&wcexMain) && RegisterClassExW(&wcexStats)  && RegisterClassExW(&wcexMenu) && RegisterClassExW(&wcexScore);
}



//FUNCTION: InitInstance(HINSTANCE, int)

//PURPOSE: Saves instance handle and creates main window

//COMMENTS:

//     In this function, we save the instance handle in a global variable and
//     create and display the main program window.

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	//Główna plansza
	hWndMain = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
		GetSystemMetrics(SM_CXSCREEN) / 2 - WINDOWWIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - WINDOWHEIGHT / 2, CW_DEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWndMain)
	{
		return FALSE;
	}
	SetClientSize(hWndMain, WINDOWWIDTH, WINDOWHEIGHT);
	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);

	//Staty nad planszą
	RECT rc;
	GetWindowRect(hWndMain, &rc);
	HWND hWndStats = CreateWindowW(szWindowClassStats, szTitleStats, WS_POPUP,
		rc.left, rc.top - 100, CW_DEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if (!hWndStats)
	{
		return FALSE;
	}
	SetClientSize(hWndStats, WINDOWWIDTH, 50);
	ShowWindow(hWndStats, nCmdShow);
	UpdateWindow(hWndStats);



	////Czołgi
	//hWndTankBlue = CreateWindowW(szWindowClassTankBlue, szTitleTankBlue, WS_POPUP | WS_EX_TOPMOST,
	//	CW_DEFAULT, 0, CW_DEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	//if (!hWndTankBlue)
	//{
	//	return FALSE;
	//}
	//SetWindowPos(hWndTankBlue, HWND_TOPMOST, rc.left, rc.top, tankRad * 2, tankRad * 2, SWP_NOACTIVATE);
	//ShowWindow(hWndTankBlue, nCmdShow);
	//UpdateWindow(hWndTankBlue);

	//hWndTankGreen = CreateWindowW(szWindowClassTankGreen, szTitleTankGreen, WS_POPUP | WS_EX_TOPMOST,
	//	CW_DEFAULT, 0, CW_DEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	//if (!hWndTankGreen)
	//{
	//	return FALSE;
	//}
	//SetWindowPos(hWndTankGreen, HWND_TOPMOST, rc.right - tankRad * 2, rc.bottom - tankRad * 2, tankRad * 2, tankRad * 2, SWP_NOACTIVATE);
	//ShowWindow(hWndTankGreen, nCmdShow);
	//UpdateWindow(hWndTankGreen);

	//Menu
	/*HWND hWndMenu = CreateWindowW(szWindowClassMenu, szTitleMenu, WS_CHILD  ,
		rc.left - 250, rc.top, CW_DEFAULT, 0, hWndMain, nullptr, hInstance, nullptr);*/
	HWND hWndMenu = CreateWindowW(szWindowClassMenu, szTitleMenu, WS_POPUP | WS_BORDER,
		rcMain.left - MENUWIDTH - 20, rc.top, CW_DEFAULT, 0, hWndMain, nullptr, hInstance, nullptr);
	if (!hWndMenu)
	{
		return FALSE;
	}

	SetClientSize(hWndMenu, MENUWIDTH, MENUHEIGHT);
	ShowWindow(hWndMenu, nCmdShow);
	UpdateWindow(hWndMenu);

	return TRUE;
}




//==========================================================================  GRA    ===========================================================================

//------------------------------------------------------------------------  ENUM    ----------------------------------------------------------------------
enum class direction
{
	up = 0, left = 1, down = 2, right = 3
};
enum class items
{
	coin = 0,
	ammo = 1,
	healthkit = 2,

};
//--------------------------------------------------------  DEKLARACJE KLAS   ----------------------------------------------------------------------

class player;
class missile;

//--------------------------------------------------------  DEKLARACJE FUNKCJI   ----------------------------------------------------------------------
template<typename T>
void swap(T& a, T& b);
int didPlayersCollide(direction dir);
void MovePressedToFront(direction dir, int player);
void setTankDir(int player);
void MoveUnpressedDown(int player);
void paintItem(HDC hdc);
bool didMissleHit(missile mis);
void paintMissiles(HDC hdc);
void createItem();
void fireMissile(int player);
void died(int player);
void paintHit(int x, int y);
void moveMissiles();
void SetWasd();
bool isOnRectangle(POINT* pt, RECT* rec);
void paintPause();
void startNewGame();
void paintBck(HDC hdc);
void gameOver();
void printWinner(int winner);
void paintHello();
void saveResoultTop10(int resoult, int resoult2);
void ShowTop10();
void drawTanks(HDC hdc);
//bool loadBitMap(PCWSTR szFileName, HDC hWinDC);

//--------------------------------------------------------  GLOBLANE    ------------------------------------------------------------------------------------

const int no_Players = 2;
int winner = -1;
char top10filename[10] = "top10.txt";
std::vector<int> wyniki;
int FPS = 160;
bool PAUSE = false;
int timePassed = 0, mp_roundtime = 60;
bool isGameOn = false;

items item = items::coin;
int itemRad = 15;
int itemcoords[2] = { 200,200 };

int baseSpeed = 10;
int baseDamage = 20;

std::list<missile> missilesList;
int missilesRad = 5;
int missileSpeed = 20;
int ammo[2] = { 20,20 };



TCHAR StatsStringBlue[100];
TCHAR StatsStringGreen[100];
TCHAR TimeString[30];

RECT resumeRec = { 10 ,10,MENUWIDTH - 10,90 };
RECT newGameRec = { 10, 100, MENUWIDTH - 10, 190 };
RECT top10Rec = { 10, 200, MENUWIDTH - 10, 290 };
RECT quitRec = { 10, 300, MENUWIDTH - 10, 390 };
RECT returnRec = { 10,WINDOWHEIGHT - 100,190,WINDOWHEIGHT - 10 };

POINT mouseCoords; 


//-------------------------------------------------------- IMPLEMENTACJA  KLASY      ----------------------------------------------------------------------

class player
{
public:
	int lp;
	int x;
	int y;
	int health;
	int ammo;
	int points;
	int speed;
	int damage;
	direction dir;
	bool wasdPressed[4] = { false,false,false,false };
	direction dirTab[4] = { direction::up,direction::left, direction::down, direction::right };

	player(int lp, int x, int y, int health, int ammo, int points, int speed,int damage, direction dir) :
		lp(lp), x(x), y(y), health(health), ammo(ammo), points(points), speed(speed), dir(dir) , damage(damage){	}

	void move()
	{
		if (wasdPressed[0] || wasdPressed[1] || wasdPressed[2] || wasdPressed[3])
		{
			switch (dirTab[0])
			{
			case direction::up:
			{
				y -= speed;
				if (y < tankRad) y = tankRad;
				//if (didPlayersCollide()) y += (2 * tankRad - (y - players[!lp].y));
				break;
			}
			case direction::left:
			{
				x -= speed;
				if (x < tankRad) x = tankRad;
				//if (didPlayersCollide()) x += (2 * tankRad - (x - players[!lp].x));
				break;
			}
			case direction::down:
			{
				y += speed;
				if (y > WINDOWHEIGHT - tankRad) y = WINDOWHEIGHT - tankRad;
				//if (didPlayersCollide()) y -= (2 * tankRad - (players[!lp].y - y));
				break;
			}
			case direction::right:
			{
				x += speed;
				if (x > WINDOWWIDTH - tankRad) x = WINDOWWIDTH - tankRad;
				//if (didPlayersCollide()) x -= (2 * tankRad - (players[!lp].x - x));
				break;
			}
			default:
				break;
			}

			int colision = didPlayersCollide(dir);
			switch (dir)
			{
			case direction::up:
				y += colision;
				break;
			case direction::left:
				x += colision;
				break;
			case direction::down:
				y -= colision;
				break;
			case direction::right:
				x -= colision;
				break;
			default:
				break;
			}
		}
		

		if (isOnItem())
		{
			switch (item)
			{
			case items::coin:
				points += 5;
				break;
			case items::ammo:
				ammo += 20;
				break;
			case items::healthkit:
				health = min(health + 50, 100);
				break;
			default:
				break;
			}
			createItem();
			InvalidateRect(hWndMain, 0, TRUE);
		}
	}
	bool isOnItem()
	{
		int xDis = abs(x - itemcoords[0]);
		int yDis = abs(y - itemcoords[1]);
		if (xDis < itemRad + tankRad && yDis < itemRad + tankRad)
		{
			return true;
		}

		return false;
	}
};
player players[2] = { player(0,tankRad,tankRad,100,20,0,baseSpeed + 10,baseDamage-10,direction::right),player(1,WINDOWWIDTH - tankRad,WINDOWHEIGHT - tankRad,100,20,0,baseSpeed,baseDamage+10,direction::right) };

class missile
{
public:
	int x;
	int y;
	direction dir;
	int player;
	missile(int x, int y, direction dir, int player) : x(x), y(y), dir(dir), player(player) {}
};



// ========================================================================================= WndProc ==========================================================================


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		 // Create an off-screen DC for double-buffering
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmMem = CreateCompatibleBitmap(hdc, WINDOWWIDTH, WINDOWHEIGHT);

		HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);

		// Draw into hdcMem here

		// Transfer the off-screen DC to the screen
		
		if (!isGameOn)
		{
			paintBck(hdcMem);
			printWinner(winner);
		}
		else
		{
			paintBck(hdcMem);
			paintItem(hdcMem);
			paintMissiles(hdcMem);
			drawTanks(hdcMem);
		}
		BitBlt(hdc, 0, 0, WINDOWWIDTH, WINDOWHEIGHT, hdcMem, 0, 0, SRCCOPY);

		// Free-up the off-screen DC
		SelectObject(hdcMem, hOld);

		DeleteObject(hbmMem);
		DeleteDC(hdcMem);
		EndPaint(hWnd, &ps);


	}
	break;
	case WM_EXITSIZEMOVE:
	{
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
		UpdateWindow(hWnd);
		GetClientRect(hWnd, &rcMain); // get client coords
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rcMain.left)); // convert top-left
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rcMain.right)); // convert bottom-right
		break;
	}
	case WM_CREATE:
	{
		SetTimer(hWnd, 7, 1000, NULL);
		SetTimer(hWnd, 8, 1000/FPS	, NULL);
		break;
	}
	case WM_TIMER:
	{
		if (!isGameOn)
		{
			break;
		}
		if (PAUSE)
		{
			paintPause();
			break;
		}
		if (wParam == 7) // 1/sec
		{
			timePassed++;
			if (timePassed == mp_roundtime)
			{
				gameOver();
			}
		}

		if (wParam == 8) // FPS/sec
		{
			moveMissiles();
			players[0].move();
			players[1].move();
			InvalidateRect(hWnd, 0, TRUE);
		}
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{

		case 'W':
		{
			players[0].wasdPressed[0] = true;
			players[0].dir = direction::up;
			MovePressedToFront(direction::up, 0);
			break;
		}
		case 'A':
		{
			players[0].wasdPressed[1] = true;
			players[0].dir = direction::left;
			MovePressedToFront(direction::left, 0);
			break;
		}
		case 'S':
		{
			players[0].wasdPressed[2] = true;
			players[0].dir = direction::down;
			MovePressedToFront(direction::down, 0);
			break;
		}
		case 'D':
		{
			players[0].wasdPressed[3] = true;
			players[0].dir = direction::right;
			MovePressedToFront(direction::right, 0);
			break;
		}
		case VK_SPACE:
		{
			fireMissile(0);
			break;
		}
		case VK_NUMPAD8:
		{
			players[1].wasdPressed[0] = true;
			players[1].dir = direction::up;
			MovePressedToFront(direction::up, 1);
			break;
		}
		case VK_NUMPAD4:
		{
			players[1].wasdPressed[1] = true;
			players[1].dir = direction::left;
			MovePressedToFront(direction::left, 1);
			break;
		}
		case VK_NUMPAD5:
		{
			players[1].wasdPressed[2] = true;
			players[1].dir = direction::down;
			MovePressedToFront(direction::down, 1);
			break;
		}
		case VK_NUMPAD6:
		{
			players[1].wasdPressed[3] = true;
			players[1].dir = direction::right;
			MovePressedToFront(direction::right, 1);
			break;
		}
		case VK_NUMPAD0:
		{
			fireMissile(1);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case 'W':
			players[0].wasdPressed[0] = false;
			MoveUnpressedDown(0);
			break;
		case 'A':
			players[0].wasdPressed[1] = false;
			MoveUnpressedDown(0);
			break;
		case 'S':
			players[0].wasdPressed[2] = false;
			MoveUnpressedDown(0);
			break;
		case 'D':
			players[0].wasdPressed[3] = false;
			MoveUnpressedDown(0);
			break;
		case VK_NUMPAD8:
			players[1].wasdPressed[0] = false;
			MoveUnpressedDown(1);
			break;
		case VK_NUMPAD4:
			players[1].wasdPressed[1] = false;
			MoveUnpressedDown(1);
			break;
		case VK_NUMPAD5:
			players[1].wasdPressed[2] = false;
			MoveUnpressedDown(1);
			break;
		case VK_NUMPAD6:
			players[1].wasdPressed[3] = false;
			MoveUnpressedDown(1);
			break;
		default:
			break;
		}
	}
	break;

	case WM_MOVING:
	{
		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd, 0, (255 * 50) / 100, LWA_ALPHA);
		UpdateWindow(hWnd);
		GetClientRect(hWnd, &rcMain); // get client coords
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rcMain.left)); // convert top-left
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rcMain.right)); // convert bottom-right
		break;
	}
	case WM_SIZE:
		if (wParam == SIZE_MAXIMIZED) {
			SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
			return 0;
		}
		GetClientRect(hWnd, &rcMain); // get client coords
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rcMain.left)); // convert top-left
		ClientToScreen(hWnd, reinterpret_cast<POINT*>(&rcMain.right)); // convert bottom-right
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	
	case WM_ACTIVATE:
	{
		if (wParam == WA_INACTIVE)
		{
			HDC dc1 = ::GetDC(hWnd);
			RECT rc;
			GetWindowRect(hWnd, &rc);
			::DrawText(dc1, _T("PAUSE"), 5, &rc, DT_CENTER | DT_EXTERNALLEADING | DT_WORDBREAK);
			::ReleaseDC(hWnd, dc1);
		}
		else
		{
			PAUSE = false;
			SetWasd();
		}
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcStats(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 7, 1000 / 60, NULL);
		break;
	}
	case WM_TIMER:
	{
		if (wParam == 7)
		{
			InvalidateRect(hWnd, 0, TRUE);
		}
	}
	case WM_ACTIVATE:
	{
		if (wParam == 1 || wParam == 2)
			SetActiveWindow(hWndMain);
	}

	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...

		HBRUSH bluebrush = CreateSolidBrush(RGB(10, 242, 250));
		HBRUSH greenbrush = CreateSolidBrush(RGB(142, 250, 10));
		HBRUSH greybrush = CreateSolidBrush(RGB(150, 150, 150));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, bluebrush);

		RECT rc;
		GetWindowRect(hWnd, &rc);
		int rcWidth2 = (rc.right - rc.left) / 2, rcHeight = rc.bottom - rc.top;
		rc = { 0,0,rcWidth2,rcHeight };

		FillRect(hdc, &rc, bluebrush);
		SetBkMode(hdc, TRANSPARENT);
		SetBkColor(hdc, RGB(0, 0, 0));
		wsprintf(StatsStringBlue, _T("BLUE \nPoints: %4d  \nLife %4d Ammo %3d"), players[0].points, players[0].health, players[0].ammo);
		DrawText(hdc, StatsStringBlue, -1, &rc, DT_LEFT);


		OffsetRect(&rc, rcWidth2, 0);
		FillRect(hdc, &rc, greenbrush);
		wsprintf(StatsStringBlue, _T("GREEN \nPoints: %4d  \nLife %4d Ammo %3d"), players[1].points, players[1].health, players[1].ammo);
		DrawText(hdc, StatsStringBlue, -1, &rc, DT_RIGHT);

		rc.left = rcWidth2 - 70;
		rc.right = rcWidth2 + 70;
		FillRect(hdc, &rc, greybrush);
		wsprintf(TimeString, _T("TIME:\n%4d\nRound Time: %d"), timePassed, mp_roundtime);
		DrawText(hdc, TimeString, -1, &rc, DT_CENTER);


		SelectObject(hdc, oldBrush);
		DeleteObject(bluebrush);
		DeleteObject(greenbrush);
		DeleteObject(greybrush);

		EndPaint(hWnd, &ps);

	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);


	}

	return(Result);
}

LRESULT CALLBACK WndProcMenu(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 7, 1000 / 60, NULL);
		break;
	}
	case WM_TIMER:
	{
		if (wParam == 7)
		{
			InvalidateRect(hWnd, 0, true);
		}

		break;
	}
	case WM_MOUSEMOVE:
	{
		GetCursorPos(&mouseCoords);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		POINT mouseMenuCoords = mouseCoords;
		ScreenToClient(hWnd, &mouseMenuCoords);
		if (isOnRectangle(&mouseMenuCoords, &resumeRec))
		{
			if (PAUSE)
			{
				PAUSE = false;
				SetActiveWindow(hWndMain);
			}
			else
			{
				PAUSE = true;
			}


		}
		else if (isOnRectangle(&mouseMenuCoords, &newGameRec))
		{
			startNewGame();
			SetActiveWindow(hWndMain);
		}
		else if (isOnRectangle(&mouseMenuCoords, &top10Rec))
		{
			ShowTop10();
		}
		else if (isOnRectangle(&mouseMenuCoords, &quitRec))
		{
			PostQuitMessage(WM_QUIT);
		}
		else SetActiveWindow(hWndMain);
	}



	case WM_PAINT:
	{

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...

		HBRUSH brush = CreateSolidBrush(RGB(103, 113, 128));
		HBRUSH greybrush = CreateSolidBrush(RGB(103, 113, 128));
		HBRUSH greenbrush = CreateSolidBrush(RGB(169, 252, 3));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		POINT mouseMenuCoords = mouseCoords;
		ScreenToClient(hWnd, &mouseMenuCoords);
		SetBkMode(hdc, TRANSPARENT);
		SetBkColor(hdc, RGB(0, 0, 0));
		if (isGameOn)
		{
			if (isOnRectangle(&mouseMenuCoords, &resumeRec))
			{
				FillRect(hdc, &resumeRec, greenbrush);
			}
			else  FillRect(hdc, &resumeRec, greybrush);
			if (PAUSE)
			{
				DrawText(hdc, TEXT("RESUME"), -1, &resumeRec, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			}
			else
			{
				DrawText(hdc, TEXT("PAUSE"), -1, &resumeRec, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			}

		}


		if (isOnRectangle(&mouseMenuCoords, &newGameRec))
		{
			FillRect(hdc, &newGameRec, greenbrush);
		}
		else FillRect(hdc, &newGameRec, greybrush);
		DrawText(hdc, TEXT("NEW GAME"), -1, &newGameRec, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		if (isOnRectangle(&mouseMenuCoords, &top10Rec))
		{
			FillRect(hdc, &top10Rec, greenbrush);
		}
		else FillRect(hdc, &top10Rec, greybrush);
		DrawText(hdc, TEXT("TOP10"), -1, &top10Rec, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		if (isOnRectangle(&mouseMenuCoords, &quitRec))
		{
			FillRect(hdc, &quitRec, greenbrush);
		}
		else FillRect(hdc, &quitRec, greybrush);
		DrawText(hdc, TEXT("QUIT"), -1, &quitRec, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		SelectObject(hdc, oldBrush);

		DeleteObject(brush);
		DeleteObject(greybrush);
		DeleteObject(greenbrush);

		EndPaint(hWnd, &ps);



	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);


	}

	return(Result);
}
LRESULT CALLBACK WndProcScore(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd, 7, 1000 / 60, NULL);
		break;
	}
	case WM_TIMER:
	{
		if (wParam == 7)
		{
			InvalidateRect(hWnd, 0, true);
		}

		break;
	}
	case WM_MOUSEMOVE:
	{
		GetCursorPos(&mouseCoords);
		break;
	}
	case WM_PAINT:
	{
		POINT mouseMenuCoords = mouseCoords;
		ScreenToClient(hWnd, &mouseMenuCoords);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		HBRUSH greybrush = CreateSolidBrush(RGB(103, 113, 128));
		HBRUSH greenbrush = CreateSolidBrush(RGB(169, 252, 3));
		HBRUSH goldbrush = CreateSolidBrush(RGB(252, 190, 3));

		
		SetBkMode(hdc, TRANSPARENT);
		SetBkColor(hdc, RGB(0, 0, 0));

		WCHAR str[10];
		RECT rc = { 10,10,190,50 };
		std::vector<int>::iterator iter = wyniki.begin();
		for (int i = 0; i < 10 && iter != wyniki.end(); i++)
		{
			FillRect(hdc, &rc, goldbrush);
			wsprintf(str, _T("%d  "), *iter);
			DrawText(hdc, str, -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			OffsetRect(&rc, 0, 49);
			iter++;
		}



		if (isOnRectangle(&mouseMenuCoords, &returnRec))
		{
			FillRect(hdc, &returnRec, greenbrush);
		}
		else FillRect(hdc, &returnRec, greybrush);

		DrawText(hdc, _T("RETURN"), -1, &returnRec, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		EndPaint(hWnd, &ps);
		DeleteObject(greybrush);
		DeleteObject(goldbrush);
		DeleteObject(greenbrush);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINT mouseScoreCoords = mouseCoords;
		ScreenToClient(hWnd, &mouseScoreCoords);
		
		if (isOnRectangle(&mouseScoreCoords, &returnRec))
		{
			DestroyWindow(hWnd);
		}
	}
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);


	}

	return(Result);
}

//LRESULT CALLBACK WndProcTank1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//
//	switch (message)
//	{
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//	}
//	break;
//
//	case WM_CREATE:
//	{
//		SetBkMode(GetDC(hWnd), TRANSPARENT);
//		SetTimer(hWnd, 7, 1000 / FPS, NULL);
//		break;
//	}
//	case WM_TIMER:
//	{
//		if (wParam == 7)
//		{
//			//MessageBox(hWndTankBlue, _T("simea"), _T("simea"), MB_OK);
//
//			MoveWindow(hWndTankBlue, rcMain.left + players[0].x - tankRad, rcMain.top + players[0].y - tankRad, tankRad * 2, tankRad * 2, TRUE);
//			InvalidateRect(hWndTankBlue, 0, false);
//		}
//
//		break;
//	}
//
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code that uses hdc here...
//
//		//HBRUSH brush = CreateSolidBrush(RGB(18, 107, 37));
//		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//
//		
//		
//
//		
//		Gdiplus::Graphics gr(hdc);
//		Rect rc = { 0,0, 2 * tankRad, 2 * tankRad };
//
//		Image img(L"tank_blue.png");
//
//		switch (players[0].dir)
//		{
//		case direction::left:
//			img.RotateFlip(Rotate180FlipNone);
//			break;
//		case direction::right:
//			break;
//		case direction::up:
//			img.RotateFlip(Rotate270FlipNone);
//			break;
//		case direction::down:
//			img.RotateFlip(Rotate90FlipNone);
//			break;
//		default:
//			break;
//		}
//
//
//
//		gr.DrawImage(&img, rc);
//
//	
//		
//
//		//SelectObject(hdc, oldBrush);
//		//DeleteObject(brush);
//
//		EndPaint(hWnd, &ps);
//
//	}
//	break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
////}
//LRESULT CALLBACK WndProcTank2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//
//	switch (message)
//	{
//
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//	}
//	break;
//
//	case WM_CREATE:
//	{
//		SetTimer(hWnd, 7, 1000 / FPS, NULL);
//		break;
//	}
//	case WM_TIMER:
//	{
//		if (wParam == 7)
//		{
//			//MessageBox(hWndTankBlue, _T("simea"), _T("simea"), MB_OK);
//
//			MoveWindow(hWndTankGreen, rcMain.left + players[1].x - tankRad, rcMain.top + players[1].y - tankRad, tankRad * 2, tankRad * 2, TRUE);
//			InvalidateRect(hWndTankGreen, 0, FALSE);
//		}
//
//		break;
//	}
//
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code that uses hdc here...
//
//		//HBRUSH brush = CreateSolidBrush(RGB(18, 107, 37));
//		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//
//		
//		
//
//
//
//		Gdiplus::Graphics gr(hdc);
//		Rect rc = { 0,0, 2 * tankRad, 2 * tankRad };
//
//		Image img(L"tank_green.png");
//
//		switch (players[1].dir)
//		{
//		case direction::left:
//			
//			img.RotateFlip(Rotate180FlipNone);
//			break;
//		case direction::right:
//			
//			break;
//		case direction::up:
//			
//			img.RotateFlip(Rotate270FlipNone);
//			break;
//		case direction::down:
//			
//			img.RotateFlip(Rotate90FlipNone);
//			break;
//		default:
//			break;
//		}
//
//
//
//		gr.DrawImage(&img, rc);
//
//		//SelectObject(hdc, oldBrush);
//		//DeleteObject(brush);
//
//		EndPaint(hWnd, &ps);
//
//	}
//	break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}




// ================================================================== FUNKCJE DO GRY ==============================================================================================

void MovePressedToFront(direction dir, int player)
{
	for (int i = 0; i < 4; i++)
	{
		if (players[player].dirTab[i] == dir)
		{
			for (int j = i; j > 0; j--)
			{
				swap(players[player].dirTab[j], players[player].dirTab[j - 1]);
			}
			break;
		}
	}
	players[player].dir = dir;
}

void setTankDir(int player)
{
	for (int i = 0; i < 4; i++)
	{
		if (players[player].wasdPressed[(int)players[player].dirTab[i]])
		{
			players[player].dir = players[player].dirTab[i];
			break;
		}
	}
}

void MoveUnpressedDown(int player)
{
	for (int i = 0; i < 4; i++)
	{
		if (players[player].wasdPressed[(int)players[player].dirTab[i]] == false)
		{
			for (int j = i; j < 3; j++)
			{
				swap(players[player].dirTab[j], players[player].dirTab[j + 1]);
			}
		}
	}
	setTankDir(player);
}

//void paintTank(HDC hdc);
//{
//	HBRUSH brush = CreateSolidBrush(RGB(18, 107, 37));
//	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//	Rectangle(hdc, tankX - tankRad, tankY - tankRad, tankX + tankRad, tankY + tankRad);
//	switch (tankDir) //lufa 
//	{
//	case direction::left:
//		Rectangle(hdc, tankX - tankRad, tankY - tankRad / 5, tankX, tankY + tankRad / 5);
//		break;
//	case direction::right:
//		Rectangle(hdc, tankX, tankY - tankRad / 5, tankX + tankRad, tankY + tankRad / 5);
//		break;
//	case direction::up:
//		Rectangle(hdc, tankX - tankRad / 5, tankY - tankRad, tankX + tankRad / 5, tankY);
//		break;
//	case direction::down:
//		Rectangle(hdc, tankX - tankRad / 5, tankY, tankX + tankRad / 5, tankY + tankRad);
//		break;
//	default:
//		break;
//	}
//
//	SelectObject(hdc, oldBrush);
//	DeleteObject(brush);
//}

void paintItem(HDC hdc)
{
	

	Gdiplus::Graphics gr(hdc);
	
	Rect rc(itemcoords[0] - itemRad, itemcoords[1] - itemRad,2* itemRad,2* itemRad);
	Image img(L"coin.png");
	Image img2(L"ammo.png");
	Image img3(L"medkit.png");

	switch (item)
	{
	case items::coin:
		
		gr.DrawImage(&img, rc);
		break;
	case items::ammo:
		gr.DrawImage(&img2, rc);
		break;
	case items::healthkit:
		
		gr.DrawImage(&img3, rc);
		break;
	default:
		break;
	}
	
}

bool didMissleHit(missile mis)
{
	int xDis = abs(players[!mis.player].x - mis.x);
	int yDis = abs(players[!mis.player].y - mis.y);
	if (xDis < missilesRad + tankRad && yDis < missilesRad + tankRad)
	{
		return true;
	}

	return false;
}

void paintMissiles(HDC hdc)
{

	if (!missilesList.empty())
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		std::list<missile>::iterator it;
		for (it = missilesList.begin(); it != missilesList.end(); it++)
		{
			Ellipse(hdc, (*it).x - missilesRad, (*it).y - missilesRad, (*it).x + missilesRad, (*it).y + missilesRad);
		}


		SelectObject(hdc, oldBrush);
		DeleteObject(brush);
	}

}

void createItem()
{
	item = (items)(rand() % 3);
	itemcoords[0] = rand() % (WINDOWWIDTH - itemRad * 2) + itemRad;
	itemcoords[1] = rand() % (WINDOWHEIGHT - itemRad * 2) + itemRad;
}

void fireMissile(int player)
{
	if (players[player].ammo == 0) return;
	players[player].ammo--;
	switch (players[player].dir)
	{
	case direction::left:
		missilesList.push_back(missile(players[player].x - tankRad, players[player].y, direction::left, player));
		break;
	case direction::right:
		missilesList.push_back(missile(players[player].x + tankRad, players[player].y, direction::right, player));
		break;
	case direction::up:
		missilesList.push_back(missile(players[player].x, players[player].y - tankRad, direction::up, player));
		break;
	case direction::down:
		missilesList.push_back(missile(players[player].x, players[player].y + tankRad, direction::down, player));
		break;
	default:
		break;
	}


}

void died(int player)
{
	players[!player].points += 10;
	players[player].points -= 10;
	players[player].health = 100;
	players[player].x = startingcoords[player][0];
	players[player].y = startingcoords[player][1];
}

void paintHit(int x, int y)
{
	HDC hdc = ::GetDC(hWndMain);
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	for (short i = 5; i > 0; i -= 2)
	{
		Ellipse(hdc, x - i, y - i, x + i, y + i);
	}

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void moveMissiles()
{

	if (!missilesList.empty())
	{

		std::list<missile>::iterator it = missilesList.begin();
		auto hit = [&]()
		{
			players[(*it).player].points++;
			players[!(*it).player].health -= players[(*it).player].damage;
			if (players[!(*it).player].health <= 0) died(!(*it).player);
			//paintHit((*it).x, (*it).y);
			it = missilesList.erase(it);
		};
		while (it != missilesList.end())
		{

			switch ((*it).dir)
			{
			case direction::left:
			{
				(*it).x -= missileSpeed;
				if (didMissleHit(*it))
				{
					hit();
				}
				else if ((*it).x < 0)
				{
					it = missilesList.erase(it);
				}
				else it++;
			}
			break;
			case direction::right:
			{
				(*it).x += missileSpeed;
				if (didMissleHit(*it))
				{
					hit();
				}
				else if ((*it).x > WINDOWWIDTH)
				{
					it = missilesList.erase(it);
				}
				else it++;
			}
			break;
			case direction::up:
			{
				(*it).y -= missileSpeed;
				if (didMissleHit(*it))
				{
					hit();
				}
				else if ((*it).y < 0)
				{
					it = missilesList.erase(it);
				}
				else it++;
			}
			break;
			case direction::down:
			{
				(*it).y += missileSpeed;
				if (didMissleHit(*it))
				{
					hit();
				}
				else if ((*it).y > WINDOWHEIGHT)
				{
					it = missilesList.erase(it);
				}
				else it++;
			}
			break;
			default:
				break;
			}
		}


	}
}

int didPlayersCollide(direction dir)
{
	if (abs(players[0].x - players[1].x) < 2 * tankRad && abs(players[0].y - players[1].y) < 2 * tankRad)
	{
		switch (dir)
		{
		case direction::up:
		case direction::down:
			return 2 * tankRad - abs(players[0].y - players[1].y);
		case direction::left:
		case direction::right:
			return  2 * tankRad - abs(players[0].x - players[1].x);
		default:
			break;
		}
		return true;
	}
	return 0;
}

void SetWasd()
{

	if (GetKeyState('W') < 0) {
		players[0].wasdPressed[0] = true;
	}
	else {
		players[0].wasdPressed[0] = false;
	}
	if (GetKeyState('A') < 0) {
		players[0].wasdPressed[1] = true;
	}
	else {
		players[0].wasdPressed[1] = false;
	}
	if (GetKeyState('S') < 0) {
		players[0].wasdPressed[2] = true;
	}
	else {
		players[0].wasdPressed[2] = false;
	}
	if (GetKeyState('D') < 0) {
		players[0].wasdPressed[3] = true;
	}
	else {
		players[0].wasdPressed[3] = false;
	}
	if (GetKeyState(VK_NUMPAD8) < 0) {
		players[1].wasdPressed[0] = true;
	}
	else {
		players[1].wasdPressed[0] = false;
	}
	if (GetKeyState(VK_NUMPAD4) < 0) {
		players[1].wasdPressed[1] = true;
	}
	else {
		players[1].wasdPressed[1] = false;
	}
	if (GetKeyState(VK_NUMPAD5) < 0) {
		players[1].wasdPressed[2] = true;
	}
	else {
		players[1].wasdPressed[2] = false;
	}
	if (GetKeyState(VK_NUMPAD6) < 0) {
		players[1].wasdPressed[3] = true;
	}
	else {
		players[1].wasdPressed[3] = false;
	}

}

//void moveTank(int player)
//{
//	if (!players[player].wasdPressed[0] && !players[player].wasdPressed[1] && !players[player].wasdPressed[2] && !players[player].wasdPressed[3]) return;
//	switch (players[player].dirTab[0])
//	{
//	case direction::up:
//	{
//		players[player].y -= players[player].speed;
//		if (players[player].y < tankRad) players[player].y = tankRad;
//		if (didPlayersCollide()) players[player].y += (2 * tankRad - (players[player].y - players[!player].y));
//		break;
//	}
//	case direction::left:
//	{
//		players[player].x -= players[player].speed;
//		if (players[player].x < tankRad) players[player].x = tankRad;
//		if (didPlayersCollide()) players[player].x += (2 * tankRad - (players[player].x - players[!player].x));
//		break;
//	}
//	case direction::down:
//	{
//		players[player].y += players[player].speed;
//		if (players[player].y > WINDOWHEIGHT - tankRad) players[player].y = WINDOWHEIGHT - tankRad;
//		if (didPlayersCollide()) players[player].y -= (2 * tankRad - (players[!player].y - players[player].y));
//		break;
//	}
//	case direction::right:
//	{
//		players[player].x += players[player].speed;
//		if (players[player].x > WINDOWWIDTH - tankRad) players[player].x = WINDOWWIDTH - tankRad;
//		if (didPlayersCollide()) players[player].x -= (2 * tankRad - (players[!player].x - players[player].x));
//		break;
//	}
//	default:
//		break;
//	}
//	if (isOnItem(player))
//	{
//		switch (item)
//		{
//		case items::coin:
//			players[player].points += 5;
//			break;
//		case items::ammo:
//			players[player].ammo += 20;
//			break;
//		case items::healthkit:
//			players[player].health = min(players[player].health + 50, 100);
//			break;
//		default:
//			break;
//		}
//		createItem();
//	}
//
//
//}

bool isOnRectangle(POINT* pt, RECT* rec)
{
	if (pt->x >= rec->left && pt->x <= rec->right && pt->y >= rec->top && pt->y <= rec->bottom) return true;
	return false;
}

void paintPause()
{
	HDC hdc = GetDC(hWndMain);
	RECT pausedRc = { WINDOWWIDTH / 2 - 200, WINDOWHEIGHT / 2 - 100,WINDOWWIDTH / 2 + 200 ,WINDOWHEIGHT / 2 + 100 };
	HBRUSH brush = CreateSolidBrush(RGB(252, 3, 248));
	FillRect(hdc, &pausedRc, brush);
	SetBkMode(hdc, TRANSPARENT);
	SetBkColor(hdc, RGB(0, 0, 0));
	DrawText(hdc, TEXT("PAUSED"), -1, &pausedRc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DeleteObject(brush);
	ReleaseDC(hWndMain, hdc);
}

void startNewGame()
{
	PAUSE = false;
	isGameOn = true;
	timePassed = 0;
	players[0] = player(0, tankRad, tankRad, 100, 20, 0, baseSpeed + 10, baseDamage - 10, direction::right);
	players[1] = player(1, WINDOWWIDTH - tankRad, WINDOWHEIGHT - tankRad, 100, 20, 0, baseSpeed, baseDamage + 10, direction::right);
	InvalidateRect(hWndMain, 0, true);
}

void printWinner(int winner)
{
	if (winner == -1)
	{
		paintHello();
		return;
	}
	HDC hdc = GetDC(hWndMain);
	RECT pausedRc = { WINDOWWIDTH / 2 - 200, WINDOWHEIGHT / 2 - 100,WINDOWWIDTH / 2 + 200 ,WINDOWHEIGHT / 2 + 100 };
	HBRUSH brush = CreateSolidBrush(RGB(252, 3, 248));
	FillRect(hdc, &pausedRc, brush);
	SetBkMode(hdc, TRANSPARENT);
	SetBkColor(hdc, RGB(0, 0, 0));
	WCHAR winnerStr[MAX_LOADSTRING];
	if (winner == 0)
	{
		wsprintf(winnerStr, _T("DROW"));
	}
	else
	{
		wsprintf(winnerStr, _T("PLAYER %d WON"), winner);
	}

	DrawText(hdc, winnerStr, (int)_tcslen(winnerStr), &pausedRc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DeleteObject(brush);
	ReleaseDC(hWndMain, hdc);
}

void gameOver()
{
	isGameOn = false;
	timePassed = 0;
	if (players[0].points > players[1].points) winner = 1;
	else if (players[0].points < players[1].points) winner = 2;
	else winner = 0;
	missilesList.clear();
	printWinner(winner);
	saveResoultTop10(players[0].points, players[1].points);
}

void paintHello()
{
	HDC hdc = GetDC(hWndMain);
	RECT pausedRc = { WINDOWWIDTH / 2 - 200, WINDOWHEIGHT / 2 - 100,WINDOWWIDTH / 2 + 200 ,WINDOWHEIGHT / 2 + 100 };
	HBRUSH brush = CreateSolidBrush(RGB(252, 3, 248));
	FillRect(hdc, &pausedRc, brush);
	SetBkMode(hdc, TRANSPARENT);
	SetBkColor(hdc, RGB(0, 0, 0));
	DrawText(hdc, _T("Witaj w super-duper grze"), -1, &pausedRc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	DeleteObject(brush);
	ReleaseDC(hWndMain, hdc);
}

void saveResoultTop10(int resoult,int resoult2 )
{
	std::vector<int> wyniki;
	std::ifstream file;
	file.open(top10filename);
	if (!file.is_open())
	{
		OutputDebugString(_T("nie otworzono pliku"));
	}
	std::string wynik;
	while (std::getline(file, wynik))
	{
		wyniki.push_back(stoi(wynik));
	}
	wyniki.push_back(resoult);
	wyniki.push_back(resoult2);

	std::sort(wyniki.begin(), wyniki.end(), std::greater<int>());

	int it = 0;
	std::vector<int>::iterator iter = wyniki.begin();
	file.close();
	std::ofstream file2;
	file2.open(top10filename);
	while (it++ < 10 && iter != wyniki.end())
	{
		file2 << std::to_string(*iter) << std::endl;
     		iter++;
	}

	file2.close();

}

void ShowTop10()
{
	wyniki.clear();
	std::ifstream file;
	file.open(top10filename);
	if (!file.is_open()) OutputDebugString(_T("nie otworzono pliku"));
	std::string wynik;
	while (std::getline(file, wynik))
	{
		wyniki.push_back(stoi(wynik));
	}
	
	HWND hWndScore = CreateWindowW(szWindowClassScore, szTitleScore, WS_POPUP ,
		rcMain.right + 10, rcMain.top,CW_DEFAULT,0, nullptr,nullptr, hInst, nullptr);
	if (!hWndScore)
	{
		return;
	}
	SetClientSize(hWndScore, 200,WINDOWHEIGHT);
	ShowWindow(hWndScore, nCmdShowGlobal);
	UpdateWindow(hWndScore);

	
}

//
//bool loadBitMap(PCWSTR szFileName, HDC hWinDC)
//{
//	bmBlueTank = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 2*tankRad,2 * tankRad, LR_LOADFROMFILE);
//	if (bmBlueTank == NULL) {
//		::MessageBox(NULL, __T("LoadImage Failed"), __T("Error"), MB_OK);
//		return false;
//	}
//	HDC hLocalDC;
//	hLocalDC = ::CreateCompatibleDC(hWinDC);
//	// Verify that the device context was created
//	if (hLocalDC == NULL) {
//		::MessageBox(NULL, __T("CreateCompatibleDC Failed"), __T("Error"), MB_OK);
//		return false;
//	}
//
//	// Get the bitmap's parameters and verify the get
//	
//	int iReturn = GetObject(reinterpret_cast<HGDIOBJ>(bmBlueTank), sizeof(BITMAP),
//		reinterpret_cast<LPVOID>(&qBitmap));
//	if (!iReturn) {
//		::MessageBox(NULL, __T("GetObject Failed"), __T("Error"), MB_OK);
//		return false;
//	}
//
//	// Select the loaded bitmap into the device context
//	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hLocalDC, bmBlueTank);
//	if (hOldBmp == NULL) {
//		::MessageBox(NULL, __T("SelectObject Failed"), __T("Error"), MB_OK);
//		return false;
//	}
//
//	// Blit the dc which holds the bitmap onto the window's dc
//	
//
//	// Unitialize and deallocate resources
//	::SelectObject(hLocalDC, hOldBmp);
//	::DeleteDC(hLocalDC);
//	::DeleteObject(bmBlueTank);
//	return true;
//}

void drawTanks(HDC hdc)
{
	Gdiplus::Graphics gr(hdc);
	Rect rc1 = { players[0].x-tankRad, players[0].y - tankRad, 2 * tankRad, 2 * tankRad };
	Rect rc2 = { players[1].x - tankRad, players[1].y - tankRad, 2 * tankRad, 2 * tankRad };

	Image img1(L"tank_blue.png");
	Image img2(L"tank_green.png");

	switch (players[0].dir)
	{
	case direction::left:
		img1.RotateFlip(Rotate180FlipNone);
		break;
	case direction::right:
		break;
	case direction::up:
		img1.RotateFlip(Rotate270FlipNone);
		break;
	case direction::down:
		img1.RotateFlip(Rotate90FlipNone);
		break;
	default:
		break;
	}
	switch (players[1].dir)
	{
	case direction::left:
		img2.RotateFlip(Rotate180FlipNone);
		break;
	case direction::right:
		break;
	case direction::up:
		img2.RotateFlip(Rotate270FlipNone);
		break;
	case direction::down:
		img2.RotateFlip(Rotate90FlipNone);
		break;
	default:
		break;
	}
	gr.DrawImage(&img1, rc1);
	gr.DrawImage(&img2, rc2);
}

void paintBck(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(250, 236, 130));
	RECT rc = { 0,0,WINDOWWIDTH,WINDOWHEIGHT };
	FillRect(hdc, &rc, brush);
	DeleteObject(brush);
}

template <class T> 
void swap(T& a, T& b)
{
	T c(std::move(a)); a = std::move(b); b = std::move(c);
}