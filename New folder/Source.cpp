#include <windows.h>
#include <CommCtrl.h>

#include "Source.h"

HWND ghwnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	HDC hdc;
	BITMAP bmp;

	TCHAR szAppName[] = TEXT("Computer Shop");

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
						TEXT("Computer Shop"),
						WS_OVERLAPPEDWINDOW,
						100,
						100,
						800,
						600,
						NULL,
						NULL,
						hInstance,
						NULL);

	ghwnd = hwnd; 

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	HGDIOBJ hGdiObj;
	hGdiObj = (HGDIOBJ)LoadImage(GetModuleHandle(NULL), "Smiley.bmp", 
			  IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(hGdiObj, sizeof(bmp), &bmp);

	HDC hdcDest = GetDC(hwnd);
	if (hdcDest == NULL)
	{
		MessageBox(hwnd, TEXT("GetDC : FAILED"), TEXT("FAILED"), MB_ICONERROR);
	}

	HDC hdcSrc = NULL;

/*	if( SelectObject(
	 			hdcDest,          // handle to device context
				hGdiObj   		  // handle to object
		)== NULL)
	
		MessageBox(hwnd, TEXT("SelectObject : FAILED"), TEXT("FAILED"), MB_ICONERROR);
*/


	if (StretchBlt( hdcDest,
				100, 100, 
				800, 600, 
				hdcDest,
				0, 0, 
				bmp.bmWidth, bmp.bmHeight,
				SRCCOPY) == 0)
	{
		MessageBox(hwnd, TEXT("FAILED"), TEXT("FAILED"), MB_ICONERROR);
	}	

  // Create the Combobox
    //
    // Uses the CreateWindow function to create a child window of 
    // the application window. The WC_COMBOBOX window style specifies  
    // that it is a combobox.

	int gWidth  = GetSystemMetrics(SM_CXSCREEN);
	int gHeight = GetSystemMetrics(SM_CYSCREEN);
	int xpos = 0.1 * gWidth;
	int ypos = 0.1 * gHeight;
	
 /*    int xpos 	 = 100;            // Horizontal position of the window.
     int ypos 	 = 100;            // Vertical position of the window.
 */  int nwidth  = 200 * (gWidth / gHeight);            // Width of the window
     int nheight = 200 * (gWidth / gHeight);            // Height of the window
 
     HWND hwndParent =  hwnd; // Handle to the parent window

     HWND hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT("***PLANETS***"), 
         							  CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
         							  xpos, ypos, nwidth, nheight, hwndParent, NULL, hInstance,
        							  NULL);

    // load the combobox with item list.  
    // Send a CB_ADDSTRING message to load each item

    TCHAR Planets[9][10] =  
    {
        TEXT("Planets"), TEXT("Venus"),  TEXT("Terra"),  TEXT("Mars"), 
        TEXT("Jupiter"), TEXT("Saturn"), TEXT("Uranus"), TEXT("Neptune"), 
        TEXT("Pluto??") 
    };         
    TCHAR A[16]; 
    int  k = 0; 

    memset(&A,0,sizeof(A));       
    for (k = 0; k <= 8; k += 1)
    {
        wcscpy_s((wchar_t *)A, sizeof(A)/sizeof(TCHAR),  (wchar_t *)(TCHAR*)Planets[k]);

        // Add string to combobox.
        SendMessage(hWndComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
    }    
    // Send the CB_SETCURSEL message to display an initial item 
    //  in the selection field  
    SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

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

	switch (iMsg)
	{

	case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					DestroyWindow(ghwnd);
				break;
			}
		break;	

	case WM_COMMAND:
        if(HIWORD(wParam) == CBN_SELCHANGE)
        // If the user makes a selection from the list:
        //   Send CB_GETCURSEL message to get the index of the selected list item.
        //   Send CB_GETLBTEXT message to get the item.
        //   Display the item in a messagebox.
        { 
            int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL, 
                (WPARAM) 0, (LPARAM) 0);
            TCHAR  ListItem[256];
            (TCHAR) SendMessage((HWND) lParam, (UINT) CB_GETLBTEXT, 
                (WPARAM) ItemIndex, (LPARAM) ListItem);
            MessageBox(hwnd, (LPCSTR) ListItem, TEXT("Item Selected"), MB_OK);                        
        }
    break;

	case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
