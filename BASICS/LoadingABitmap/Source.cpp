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
				hBitmap     = LoadBitmap(ghInstance, MAKEINTRESOURCE(IDBITMAP_TEST));
				if (hBitmap == NULL)
					MessageBox(NULL, TEXT("HERE1"), TEXT("HERE1"), NULL);	
				hdcMain     = GetDC(hwnd);
				if (hdcMain == NULL)
					MessageBox(NULL, TEXT("HERE2"), TEXT("HERE2"), NULL);						
				hdcImage    = CreateCompatibleDC(hdcMain);
				

				GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);

				SelectObject(hdcImage , hBitmap);

				SetStretchBltMode(hdcMain, COLORONCOLOR);

				StretchBlt(hdcMain, 0, 0, 100, 100, hdcImage, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
				
				DeleteDC(hdcImage);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);	
			break;	 
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}