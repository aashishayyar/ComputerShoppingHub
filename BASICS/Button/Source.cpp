#include <windows.h>
#include "Source.h"

HINSTANCE ghInstance;

// Macros for Error Checking 
#define ERRORBOX1(lpText, lpCaption) {																		 \
										MessageBox((HWND)NULL, TEXT(lpText), TEXT(lpCaption), MB_ICONERROR); \
										ExitProcess(EXIT_FAILURE);											 \
									}

#define ERRORBOX2(hwnd, lpText, lpCaption) {																		 \
										MessageBox((HWND)NULL, TEXT(lpText), TEXT(lpCaption), MB_ICONERROR)	 \
									 	DestroyWindow(hwnd);												 \
									 }

// Declaring Window Procedure Call
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdShow, int nCmdShow)
{
	HWND 		hwnd;
	MSG 		msg;
	WNDCLASSEX 	wndclass;
	HICON 		hIcon;
	HICON 		hIconSm;
	HBRUSH		hBrush;
	HCURSOR 	hCursor;	
	TCHAR 		szAppName[] = TEXT("Template Application");

	// Acquire brush to paint the window background 
	hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	if (hBrush == NULL)
		ERRORBOX1("Failed to acquire brush to paint window background", "Error");
	
	// Set an Icon 
	hIcon = (HICON)LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
	if (hIcon == NULL)
		ERRORBOX1("Failed to load Icon", "Error");

	// Set a Small Icon
	hIconSm = (HICON)LoadIcon((HINSTANCE)NULL,IDI_APPLICATION);
	if (hIconSm == NULL)
		ERRORBOX1("Failed to load Small Icon", "Error");

	// Set a Cursor
	hCursor = (HCURSOR)LoadCursor((HINSTANCE)NULL,IDC_ARROW);
	if (hCursor == NULL)
		ERRORBOX1("Failed to load Cursor", "Error");		

	wndclass.cbSize 		= sizeof(WNDCLASSEX);
	wndclass.style  		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpszMenuName 	= NULL;
	wndclass.lpszClassName  = szAppName;
	wndclass.cbClsExtra 	= 0;
	wndclass.cbWndExtra 	= 0;
	wndclass.hInstance 		= hInstance;
	wndclass.lpfnWndProc 	= WndProc;
	wndclass.hIcon 			= hIcon;
	wndclass.hIconSm 		= hIconSm;
	wndclass.hCursor		= hCursor;
	wndclass.hbrBackground	= hBrush;	

	// Registering the above filled structure
	if (RegisterClassEx(&wndclass) == 0)
		ERRORBOX1("Failed to Register Class", "Error");

	// Creating Window in memory
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						szAppName,
						TEXT("TemplateApplication : Aashish Ayyar"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
					 	CW_USEDEFAULT,
						NULL, NULL,
						hInstance,
						NULL);
	if (hwnd == NULL)
		ERRORBOX1("Failed to Create Window", "Error");


	ghInstance = hInstance;				
	
	HWND hwndButton = CreateWindowEx(WS_EX_WINDOWEDGE, TEXT("BUTTON"), TEXT("OK"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
					100, 100, 100, 30, 
				  hwnd, NULL, hInstance, NULL);

	// Displaying the window on Screen
	ShowWindow  (hwnd, nCmdShow);

	// To send an WM_PAINT message
	UpdateWindow(hwnd);

	// Message Loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage (&msg);	
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HBITMAP hBitmap;
	HDC hdcMain ;
	HDC hdcImage;
	BITMAP Bitmap;

	switch(iMsg)
	{
		case WM_CREATE:
			break;
		case WM_PAINT:
			break;
		case WM_COMMAND:
				if (HIWORD(wParam) == BN_CLICKED)
					MessageBox(NULL, TEXT("Button Clicked"), TEXT("Button CLicked"), MB_OK);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);	
			break;	 
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}