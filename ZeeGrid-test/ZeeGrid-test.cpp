// ZeeGrid-test.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ZeeGrid-test.h"
#include "zeegrid.h"

#define MAX_LOADSTRING 100

HMODULE hgridmod;    //for result of LoadLibrary() function
HWND hgrid;          //window handle for the grid.

int field1 = 897324;
char field3[]="hello there";


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ZEEGRIDTEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ZEEGRIDTEST));

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

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ZEEGRIDTEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ZEEGRIDTEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void FormatGrid(HWND hg)
{
	SendMessage(hg, ZGM_SHOWROWNUMBERS, TRUE, 0);
	SendMessage(hg, ZGM_SETDEFAULTFCOLOR,FOREGROUND_RED,0);
	//SendMessage(hg, ZGM_SETDEFAULTBCOLOR, 10, 0);
	//create 5 rows of empty cells
	int j;
	for (j = 1; j <= 5; j++)
	{
		SendMessage(hg, ZGM_APPENDROW, 0, 0);
	}
	//set column header titles
	SendMessage(hg, ZGM_SETCELLTEXT, 1, (LPARAM)"First\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 2, (LPARAM)"Second\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 3, (LPARAM)"Third\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 4, (LPARAM)"Fourth\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 5, (LPARAM)"Fifth\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 6, (LPARAM)"Sixth\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 7, (LPARAM)"Seventh Column is wide");
	SendMessage(hg, ZGM_SETCELLTEXT, 8, (LPARAM)"Eighth\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 9, (LPARAM)"Ninth\nColumn");
	SendMessage(hg, ZGM_SETCELLTEXT, 10, (LPARAM)"Tenth\nand\nlast\nColumn");

	//make column 3 editable by the user
	SendMessage(hg, ZGM_SETCOLEDIT, 3, 1);

	//auto size all columns
	SendMessage(hg, ZGM_AUTOSIZE_ALL_COLUMNS, 0, 0);
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int result;
    switch (message)
    {
	case WM_CREATE:
		hgridmod = LoadLibrary(L"zeegrid.dll");
		if (!hgridmod)
		{
			MessageBox(hWnd, L"Unable to load ZeeGrid.DLL", L"Error", MB_OK);
			PostQuitMessage(0);
		}
		hgrid = CreateWindow(L"ZeeGrid", L"My First ZeeGrid", WS_CHILD | WS_VISIBLE | WS_BORDER, 0, 0, 0, 0, hWnd, (HMENU)700, hInst, NULL);
		SendMessage(hgrid, ZGM_DIMGRID, 10, 0);  //set the grid to have 10 columns instead of the default 5
		SendMessage(hgrid, ZGM_ALLOCATEROWS, 5000, 0);  //allocate memory for 5000 rows of data (50,000 cells)
		FormatGrid(hgrid);

		SendMessage(hgrid, ZGM_SHOWTITLE, TRUE, 0);
		
		SendMessage(hgrid, ZGM_SETCELLTEXT, 11, (LPARAM)"11");
		SendMessage(hgrid, ZGM_SETCELLTEXT, 21, (LPARAM)"21");
		SendMessage(hgrid, ZGM_SETCELLTEXT, 31, (LPARAM)"31");
		SendMessage(hgrid, ZGM_SETCELLTEXT, 41, (LPARAM)"41");
		SendMessage(hgrid, ZGM_SETCELLTEXT, 51, (LPARAM)"51");
		result=SendMessage(hgrid, ZGM_GETCELLINDEX, 3, 10);		
		SendMessage(hgrid, ZGM_SETCELLINT, 40, (LPARAM)&result);
		SendMessage(hgrid, ZGM_SETROWFCOLOR, 3, FOREGROUND_BLUE);
		SendMessage(hgrid, ZGM_SETROWBCOLOR, 3, FOREGROUND_GREEN);

		//SendMessage(hgrid, ZGM_INSERTROW, 3, 0);
		//SendMessage(hgrid, ZGM_SETCELLTEXT, 31, (LPARAM)"Another one");
		//SendMessage(hgrid, ZGM_SETCELLFCOLOR, 11, FOREGROUND_RED);
		SendMessage(hgrid, ZGM_DELETEROW, 0, 0);

		SendMessage(hgrid, ZGM_AUTOSIZE_ALL_COLUMNS, 0, 0);		// auto resize
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_SIZE:
		{
		RECT rect;
		GetClientRect(hWnd, &rect);
		MoveWindow(hgrid, 0, 0, rect.right, rect.bottom , TRUE);
		}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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
