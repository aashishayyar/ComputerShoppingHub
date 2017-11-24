#include <windows.h>
#include <CommCtrl.h>

#include "Source.h"

HWND ghwnd;
HINSTANCE ghInstance; 

#define MAX_COMBOBOX_NEST 3
HWND hwndComboBox[MAX_COMBOBOX_NEST];

HWND parent_hwndComboBox;
HWND child_hwndComboBox;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	void initialize_combo_boxes(void);

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	HDC hdc;
	BITMAP bmp;
	TCHAR szAppName[] = TEXT("Store");

	ghInstance = hInstance;

	wndclass.cbSize 	   = sizeof(WNDCLASSEX);
	wndclass.style 		   = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon 		   = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor 	   = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm 	   = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszMenuName  = NULL;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
						TEXT("Store"),
						WS_OVERLAPPEDWINDOW,
						0,
						0,
						1024,
						768,
						NULL,
						NULL,
						hInstance,
						NULL);

	ghwnd = hwnd; 

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	initialize_combo_boxes();

	MessageBox(hwnd, TEXT("HERE"), TEXT("HERE"), MB_OK);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void uninitialize(void);

	PAINTSTRUCT ps;
	HDC hdc, hMemdc;
	HBITMAP hBitmap;
	static HBITMAP hBitmapRec;
	static int state = 0;

	switch (iMsg)
	{
	case WM_CREATE:
/*			OpenClipboard(hwnd);
			EmptyClipboard();	
			hBitmap = LoadBitmap(((LPCREATESTRUCT)lParam) -> hInstance, MAKEINTRESOURCE(MY_BITMAP));
			if(SetClipboardData(CF_BITMAP, hBitmap) == NULL)
			{
				MessageBox(hwnd, TEXT("Can't set desired data"), NULL, MB_ICONERROR | MB_OK);
				CloseClipboard();
				break;
			}
			CloseClipboard();

			OpenClipboard(hwnd);
			if ((hBitmapRec = (HBITMAP)GetClipboardData(CF_BITMAP)) == NULL)
			{
				MessageBox(hwnd, TEXT("Can't access desired data"), NULL, MB_ICONERROR | MB_OK);
				CloseClipboard();
				break;
			}
			CloseClipboard();

			hBitmapRec = (HBITMAP)LoadImage(GetModuleHandle(NULL), "Smiley.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			InvalidateRect(hwnd, NULL, TRUE);	
*/		break;	

	case WM_PAINT:
/*			hdc = BeginPaint(hwnd, &ps);
			hMemdc = CreateCompatibleDC(hdc);
			SelectObject(hMemdc, hBitmap);
			StretchBlt(hdc, 0, 0, 1024, 768, hMemdc, 0, 0, 800, 600, SRCCOPY);
			DeleteDC(hMemdc);
			EndPaint(hwnd, &ps);
*/		break; 
		
	case WM_COMMAND:
        if((HIWORD(wParam) == CBN_SELCHANGE))
        { 
    //    	MessageBox(hwnd, TEXT("OUT"), TEXT("OUT"), MB_OK);
        	if ( (HWND)lParam == parent_hwndComboBox)
			{
				if (child_hwndComboBox)
					DestroyWindow(child_hwndComboBox);
	//			MessageBox(hwnd, TEXT("IN"), TEXT("IN"), MB_OK);
	            int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);

	            int gWidth  = GetSystemMetrics(SM_CXSCREEN);
				int gHeight = GetSystemMetrics(SM_CYSCREEN);
				int xpos = 0.3 * gWidth;
				int ypos = 0.1 * gHeight;

				 int nwidth  = 200 * (gWidth / gHeight);            // Width of the window
			     int nheight = 200 * (gWidth / gHeight);            // Height of the window
			 
			     HWND hwndParent =  ghwnd; // Handle to the parent window

			     child_hwndComboBox = CreateWindow(WC_COMBOBOX, TEXT("***TESTING***"), 
	         							  CBS_AUTOHSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
	         							  xpos, ypos, nwidth, nheight, hwndParent, NULL, ghInstance, NULL);

	            TCHAR Temp[255]; 
			    memset(&Temp,0,sizeof(Temp)); 
			    for (int k = 0; k <= 1; k += 1)
			    {
			        wcscpy_s((wchar_t *)Temp, sizeof(Temp)/sizeof(TCHAR),  (wchar_t *)MS_Subbulakshmi[ItemIndex].next[k].name);
			        SendMessage(child_hwndComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) Temp); 
			        memset(&Temp,0,sizeof(Temp));		     
			    }  
			    SendMessage(child_hwndComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);  
			}    
        }
    break;		

	case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					DestroyWindow(ghwnd);
				break;
			}
		break;	

	case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}



void changes (void)
{
	int gWidth  = GetSystemMetrics(SM_CXSCREEN);
	int gHeight = GetSystemMetrics(SM_CYSCREEN);
	int xpos = 0.1 * gWidth;
	int ypos = 0.1 * gHeight;

	 int nwidth  = 200 * (gWidth / gHeight);            // Width of the window
     int nheight = 200 * (gWidth / gHeight);            // Height of the window
 
     HWND hwndParent =  ghwnd; // Handle to the parent window

     parent_hwndComboBox = CreateWindow(WC_COMBOBOX, TEXT("***TESTING***"), 
         							  CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
         							  xpos, ypos, nwidth, nheight, hwndParent, NULL, ghInstance, NULL);

	TCHAR Temp[255]; 
    memset(&Temp,0,sizeof(Temp));       
    for (int k = 0; k <= 1; k += 1)
    {
        wcscpy_s((wchar_t *)Temp, sizeof(Temp)/sizeof(TCHAR),  (wchar_t *)MS_Subbulakshmi[k].name);
        SendMessage(parent_hwndComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) Temp); 
    }  
  //  SendMessage(parent_hwndComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);  
    char *str = TEXT("***RAGAM***");
    SendMessage(parent_hwndComboBox, CB_SETCUEBANNER, (WPARAM)0, (LPARAM)TEXT("***RAGAM***"));
}
