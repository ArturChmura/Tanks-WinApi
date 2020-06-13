//// PwŒG_Tanks.cpp : Defines the entry point for the application.
////
//
#include "pch.h"
//#include "framework.h"
//#include "PwŒG_Tanks.h"
//#include <list>
//
//#define MAX_LOADSTRING 100
//#define WINDOWHEIGHT 600
//#define WINDOWWIDTH 800
//// Global Variables:
//HINSTANCE hInst;                                // current instance
//WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
//WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//
//enum class direction
//{
//	left = 1, right = 2, up = 3, down = 4
//};
//
//class missile
//{
//public:
//	int x;
//	int y;
//	direction dir;
//	missile(int x, int y, direction dir) : x(x), y(y), dir(dir) {}
//};
//
//int points = 0, time = 0;
//
//int tankRad = 30;
//int tankX = tankRad, tankY = tankRad;
//int tankSpeed = 10;
//
//int coinRad = 15;
//int coinX = 200, coinY = 200;
//direction tankDir = direction::left;
//
//std::list<missile> missilesList;
//int missilesRad = 5;
//int missileSpeed;
//
//
//// Forward declarations of functions included in this code module:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
//	// TODO: Place code here.
//
//	// Initialize global strings
//	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadStringW(hInstance, IDC_PWSGTANKS, szWindowClass, MAX_LOADSTRING);
//	MyRegisterClass(hInstance);
//
//	// Perform application initialization:
//	if (!InitInstance(hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//
//	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PWSGTANKS));
//
//	MSG msg;
//
//	// Main message loop:
//	while (GetMessage(&msg, nullptr, 0, 0))
//	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//
//	return (int)msg.wParam;
//}
//
//
//
////
////  FUNCTION: MyRegisterClass()
////
////  PURPOSE: Registers the window class.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEXW wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = NULL;// MAKEINTRESOURCEW(IDC_PWSGTANKS);
//	wcex.lpszClassName = szWindowClass;
//	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
//
//	return RegisterClassExW(&wcex);
//}
//
//
////FUNCTION: InitInstance(HINSTANCE, int)
//
////PURPOSE: Saves instance handle and creates main window
//
////COMMENTS:
//
////     In this function, we save the instance handle in a global variable and
////     create and display the main program window.
//
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//	hInst = hInstance; // Store instance handle in our global variable
//
//	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
//		GetSystemMetrics(SM_CXSCREEN) / 2 - WINDOWWIDTH / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - WINDOWHEIGHT / 2, WINDOWWIDTH, WINDOWHEIGHT, nullptr, nullptr, hInstance, nullptr);
//
//	if (!hWnd)
//	{
//		return FALSE;
//	}
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	return TRUE;
//}
//
////
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  PURPOSE: Processes messages for the main window.
////
////  WM_COMMAND  - process the application menu
////  WM_PAINT    - Paint the main window
////  WM_DESTROY  - post a quit message and return
////
////
//void paintTank(HDC hdc)
//{
//	HBRUSH brush = CreateSolidBrush(RGB(18, 107, 37));
//	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//	Rectangle(hdc, tankX - tankRad, tankY - tankRad, tankX + tankRad, tankY + tankRad);
//
//	SelectObject(hdc, oldBrush);
//	DeleteObject(brush);
//}
//
//void paintCoin(HDC hdc)
//{
//	HBRUSH brush = CreateSolidBrush(RGB(230, 209, 28));
//	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//	Ellipse(hdc, coinX - coinRad, coinY - coinRad, coinX + coinRad, coinY + coinRad);
//
//	SelectObject(hdc, oldBrush);
//	DeleteObject(brush);
//}
//
//void paintMissiles(HDC hdc)
//{
//
//	if (!missilesList.empty())
//	{
//		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
//		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//
//		std::list<missile>::iterator it;
//		for (it = missilesList.begin(); it != missilesList.end(); it++)
//		{
//			Ellipse(hdc, (*it).x - missilesRad, (*it).y - missilesRad, (*it).x + missilesRad, (*it).y + missilesRad);
//		}
//
//
//		SelectObject(hdc, oldBrush);
//		DeleteObject(brush);
//	}
//
//}
//
//bool isOnCoin()
//{
//	int xDis = abs(tankX - coinX);
//	int yDis = abs(tankY - coinY);
//	if (xDis < coinRad + tankRad && yDis < coinRad + tankRad) return true;
//	return false;
//}
//
//void createCoin()
//{
//	coinX = rand() % (WINDOWWIDTH - coinRad * 2) + coinRad;
//	coinY = rand() % (WINDOWHEIGHT - coinRad * 2) + coinRad;
//}
//
//void fireMissile()
//{
//	switch (tankDir)
//	{
//	case direction::left:
//		missilesList.push_back(missile(tankX - tankRad, tankY, direction::left));
//		break;
//	case direction::right:
//		missilesList.push_back(missile(tankX + tankRad, tankY, direction::right));
//		break;
//	case direction::up:
//		missilesList.push_back(missile(tankX, tankY - tankRad, direction::up));
//		break;
//	case direction::down:
//		missilesList.push_back(missile(tankX, tankY + tankRad, direction::down));
//		break;
//	default:
//		break;
//	}
//
//}
//
//void moveMissiles()
//{
//	if (!missilesList.empty())
//	{
//
//		std::list<missile>::iterator it = missilesList.begin();
//		while (it != missilesList.end())
//		{
//
//			switch ((*it).dir)
//			{
//			case direction::left:
//			{
//				MessageBox(NULL, _T("mis"), NULL, MB_OK);
//				(*it).x -= missileSpeed;
//				if ((*it).x < 0)
//				{
//					missilesList.erase(it);
//				}
//				else it++;
//			}
//			break;
//			case direction::right:
//			{
//				(*it).x += missileSpeed;
//				if ((*it).x > WINDOWWIDTH)
//				{
//					missilesList.erase(it);
//				}
//				else it++;
//			}
//			break;
//			case direction::up:
//			{
//				(*it).y -= missileSpeed;
//				if ((*it).y < 0)
//				{
//					missilesList.erase(it);
//				}
//				else it++;
//			}
//			break;
//			case direction::down:
//			{
//				(*it).y += missileSpeed;
//				if ((*it).x > WINDOWHEIGHT)
//				{
//					missilesList.erase(it);
//				}
//				else it++;
//			}
//			break;
//			default:
//				break;
//			}
//		}
//
//
//	}
//}
//
//void moveTank(direction dir)
//{
//	tankDir = dir;
//	switch (dir)
//	{
//	case direction::up:
//	{
//		tankY -= tankSpeed;
//		if (tankY < tankRad) tankY = tankRad;
//		break;
//	}
//	case direction::left:
//	{
//		tankX -= tankSpeed;
//		if (tankX < tankRad) tankX = tankRad;
//		break;
//	}
//	case direction::down:
//	{
//		tankY += tankSpeed;
//		if (tankY > WINDOWHEIGHT - 2 * tankRad) tankY = WINDOWHEIGHT - 2 * tankRad;
//		break;
//	}
//	case direction::right:
//	{
//		tankX += tankSpeed;
//		if (tankX > WINDOWWIDTH - tankRad) tankX = WINDOWWIDTH - tankRad;
//		break;
//	}
//	default:
//		break;
//	}
//	if (isOnCoin())
//	{
//		createCoin();
//	}
//
//}
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//
//	switch (message)
//	{
//	case WM_EXITSIZEMOVE:
//	{
//		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
//		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
//		UpdateWindow(hWnd);
//		break;
//	}
//	case WM_CREATE:
//	{
//		SetTimer(hWnd, 7, 1000 / 60, NULL);
//		break;
//	}
//	case WM_TIMER:
//	{
//		if (wParam == 7) // check timer id
//		{
//			time++;
//			moveMissiles();
//			InvalidateRect(hWnd, 0, TRUE);
//			//missilesList.push_back({ rand() % (800 - missilesRad * 2) + missilesRad, rand() % (600 - missilesRad * 2) + missilesRad });
//		}
//		break;
//	}
//	case WM_KEYDOWN:
//	{
//		switch (wParam)
//		{
//
//		case 'W':
//		{
//			moveTank(direction::up);
//			break;
//		}
//		case 'A':
//		{
//			moveTank(direction::left);
//			break;
//		}
//		case 'S':
//		{
//			moveTank(direction::down);
//			break;
//		}
//		case 'D':
//		{
//			moveTank(direction::right);
//			break;
//		}
//		case VK_SPACE:
//		{
//			fireMissile();
//			break;
//		}
//		default:
//			break;
//		}
//
//		InvalidateRect(hWnd, 0, TRUE);
//		break;
//	}
//
//	case WM_MOVING:
//	{
//		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
//		SetLayeredWindowAttributes(hWnd, 0, (255 * 50) / 100, LWA_ALPHA);
//		UpdateWindow(hWnd);
//		break;
//	}
//	case WM_SIZE:
//		if (wParam == SIZE_MAXIMIZED) {
//			SendMessage(hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
//			return 0;
//		}
//		break;
//	case WM_COMMAND:
//	{
//		int wmId = LOWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
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
//	case WM_PAINT:
//	{
//		PAINTSTRUCT ps;
//		HDC hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code that uses hdc here...
//
//		paintTank(hdc);
//		paintCoin(hdc);
//		paintMissiles(hdc);
//
//		EndPaint(hWnd, &ps);
//		WCHAR windowTitle[30];
//		wsprintf(windowTitle, _T("Points: %d, Time: %d"), points, time / 60);
//		SetWindowText(hWnd, windowTitle);
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
//
//// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}
