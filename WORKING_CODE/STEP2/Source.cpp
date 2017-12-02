#include <windows.h>
#include <CommCtrl.h>

#include "Source.h"

#define WINDOWWIDTH  800
#define WINDOWHEIGHT 600

#define COMBOBOXWIDTH  0.2
#define COMBOBOXHEIGHT 0.2

int windowWidth, windowHeight; 

HWND ghwnd;
HINSTANCE ghInstance; 

#define MAX_COMBOBOX_NEST 3
HWND hwndComboBox[MAX_COMBOBOX_NEST];

HWND parent_hwndComboBox;
HWND child_hwndComboBox;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	void InitializeComboBoxes(void);

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
						30,
						30,
						WINDOWWIDTH,
						WINDOWHEIGHT,
						NULL,
						NULL,
						hInstance,
						NULL);

	ghwnd = hwnd; 

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	InitializeComboBoxes();

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
	void CreateComboBox(int, int, node_t *, HWND *);
	void GetIndexInComboBox(LPARAM, int *, int *);
	void GetNodeForString(int, int, node_t **);

	PAINTSTRUCT ps;
	HDC hdc, hMemdc;
	HBITMAP hBitmap;
	static HBITMAP hBitmapRec;
	static int state = 0;
	int iIndexComboBox = -1, iIndexOfElement;
	static int currIndexComboBox;
	node_t *nodeForString;

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
		
	case WM_SIZE:
		windowWidth  = LOWORD(lParam);
		windowHeight = HIWORD(lParam);
		break;	
	case WM_COMMAND:
        if((HIWORD(wParam) == CBN_SELCHANGE))
        { 
        	GetIndexInComboBox(lParam, &iIndexComboBox, &iIndexOfElement);	

        	GetNodeForString(iIndexComboBox, iIndexOfElement, &nodeForString);

        	for (int i = 0; i < 2; i++)
        	{
	        	if ((HWND)lParam == hwndComboBox[i])
		    	{   
		    		int x = i*25 + 35;
		    		CreateComboBox(x, 10, nodeForString, &hwndComboBox[i+1]);
		    		break;
		    	}
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

void InitializeComboBoxes(void)
{
	void CreateComboBox(int, int, node_t *, HWND *);

	CreateComboBox(10, 10, MS_Subbulakshmi, &hwndComboBox[0]);
}

void CreateComboBox (int xpos, int ypos, node_t *node, HWND *hwndComboBox)
{
	xpos = ((float)xpos / 100.0f) * windowWidth;
	ypos = ((float)ypos / 100.0f) * windowHeight;

	int comboBoxWidth  = 0.20 * windowWidth; 	
	int comboBoxHeight = 0.20 * windowHeight;	

    HWND hwndParent =  ghwnd; // Handle to the parent window

    HWND hwndCWComboBox = CreateWindow(WC_COMBOBOX, TEXT("***TESTING***"), 
         							  CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
         							  xpos, ypos, comboBoxWidth, comboBoxHeight, hwndParent, NULL, ghInstance, NULL);

	TCHAR Temp[255]; 
    memset(&Temp,0,sizeof(Temp));       
    for (int k = 0; k < (sizeof(*node) / sizeof(node_t)); k += 1)
    {
        wcscpy_s((wchar_t *)Temp, sizeof(Temp)/sizeof(TCHAR),  (wchar_t *)node[k].name);
        SendMessage(hwndCWComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) Temp); 
    }  
    SendMessage(hwndCWComboBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);

    *hwndComboBox = hwndCWComboBox;
  //  char *str = TEXT("COMBOBOX");
  //  SendMessage(parent_hwndComboBox, CB_SETCUEBANNER, (WPARAM)0, (LPARAM)TEXT("***RAGAM***"));
}

void GetIndexInComboBox(LPARAM lParam, int *indexComboBox, int *indexElement)
{
	int temp = 0;
	for (int i = 0; i < MAX_COMBOBOX_NEST; i++)
		if ((HWND)lParam == hwndComboBox[i])
			*indexComboBox = i;

	temp = *indexComboBox;

	while (temp + 1 < MAX_COMBOBOX_NEST)
	{
		if (hwndComboBox[temp + 1])
			DestroyWindow(hwndComboBox[temp + 1]);
		temp += 1;		
	}

    *indexElement = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
}

void GetNodeForString(int indexComboBox,int indexOfElement, node_t **node)
{
	static int maintain_indexElement[3];
	switch(indexComboBox)
	{
		case 0:
			maintain_indexElement[0] = indexOfElement; 
			*node =  MS_Subbulakshmi[indexOfElement].next;
			break;
		case 1:
			maintain_indexElement[1] = indexOfElement;
			*node =  MS_Subbulakshmi[maintain_indexElement[0]].next[indexOfElement].next;
			if((**node).next == NULL)
			{
				cost_per_row[0] = atof((**node).name);
			}
			break;
		case 2:
			maintain_indexElement[2] = indexOfElement;	
			*node =  MS_Subbulakshmi[maintain_indexElement[0]].next[maintain_indexElement[1]].next[indexOfElement].next;
			if((**node).next == NULL)
			{
				cost_per_row[0] = atof((**node).name);
			}
			break;
	}
}
