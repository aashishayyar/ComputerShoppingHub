#include <windows.h>
#include <CommCtrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Source.h"

#define WINDOWWIDTH  800
#define WINDOWHEIGHT 600

#define COMBOBOXWIDTH  0.2
#define COMBOBOXHEIGHT 0.2

#define XK_S 0x53
#define XK_s 0x73

int windowWidth, windowHeight; 

HWND ghwnd;
HINSTANCE ghInstance; 

HWND parent_hwndComboBox;
HWND child_hwndComboBox;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
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

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

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
	void CreateComboBox(int, int, int, node_t *, HWND *);
	void GetIndexInComboBox(LPARAM, int *, int *);
	bool GetNodeForString(int, int, int *, node_t **);
	void InitializeComboBoxes(void);
	void SetMainThreadIndex(LPARAM);
	void printFile(void);


	PAINTSTRUCT ps;
	HDC hdc, hMemdc;
	static HBITMAP hBitmapRec;
	static int state = 0;
	int iIndexComboBox = -1, iIndexOfElement;
	static int currIndexComboBox;
	node_t *nodeForString;
	int number_of_elements;

	HBITMAP hBitmap;
	HDC hdcMain ;
	HDC hdcImage;
	BITMAP Bitmap;

	switch (iMsg)
	{
	case WM_CREATE:
		break;	

	case WM_PAINT:
			if (screen == 0)
			{
				HBITMAP hBitmap = LoadBitmap(ghInstance, MAKEINTRESOURCE(VIOLIN2));
				HDC hdcMain     = GetDC(hwnd);
				HDC hdcImage    = CreateCompatibleDC(hdcMain);
				
				GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);

				SelectObject(hdcImage , hBitmap);

				SetStretchBltMode(hdcMain, COLORONCOLOR);
				StretchBlt(hdcMain, 0, 0, 1360, 768, hdcImage, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);

				DeleteDC(hdcImage);
				DeleteDC(hdcMain);

			}
			else if (screen == 1)	
			{				
				hBitmap 	= LoadBitmap(ghInstance, MAKEINTRESOURCE(TABLA));
				hdcMain     = GetDC(hwnd);
				hdcImage    = CreateCompatibleDC(hdcMain);
				
				GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);

				SelectObject(hdcImage , hBitmap);

				SetStretchBltMode(hdcMain, COLORONCOLOR);
				StretchBlt(hdcMain, 0, 0, 1360 , 768, hdcImage, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);

				DeleteDC(hdcImage);
				DeleteDC(hdcMain);
				screen = 2;	
			}	
		break; 
		
	case WM_SIZE:
		windowWidth  = LOWORD(lParam);
		windowHeight = HIWORD(lParam);
		break;	
	case WM_LBUTTONDOWN:
//		SetFocus(hwnd);	
		break;	
	case WM_COMMAND:
        if(HIWORD(wParam) == CBN_SELCHANGE)
        { 	

        	SetMainThreadIndex(lParam);

        	GetIndexInComboBox(lParam, &iIndexComboBox, &iIndexOfElement);	

        	if (GetNodeForString(iIndexComboBox, iIndexOfElement, &number_of_elements, &nodeForString) == true)
        	{	
	        	int x = iIndexComboBox    * 25 + 35;
	        	int y = main_thread_index * 10 + 10;

	        	CreateComboBox(x, y, number_of_elements, nodeForString, &hwndComboBox[main_thread_index][iIndexComboBox + 1]);
        	}

/*
        	for (int i = 0; i < 2; i++)
        	{
	        	if ((HWND)lParam == hwndComboBox[][])
		    	{   
		    		int x = i*25 + 35;
		    		CreateComboBox(x, 10, nodeForString, &hwndComboBox[][i+1]);
		    		break;
		    	}
		    }	
  
*/      }
        else if (HIWORD(wParam) == CBN_CLOSEUP)
        {
        		SetFocus(hwnd);	
        }	
        break;		

	case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
						DestroyWindow(ghwnd);
				break;
				case VK_SPACE:
				if (screen == 0)
				{
					screen = 1;
					InvalidateRect( hwnd, NULL, TRUE );
					InitializeComboBoxes();
				}
				break;		
				case XK_S:
				case XK_s:
						printFile();
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
	void CreateComboBox(int, int, int, node_t *, HWND *);
// ( sizeof(main_node) / sizeof(main_node[0])


	int x = 10, y = 10;
#define X_OFFSET 10
#define Y_OFFSET 10	

	CreateComboBox(x, y + (0 * Y_OFFSET),  sizeof( Chordophones )   / sizeof ( Chordophones[0]   ), Chordophones, 	&hwndComboBox[0][0]);
	CreateComboBox(x, y + (1 * Y_OFFSET),  sizeof( Aerophones )     / sizeof ( Aerophones[0]     ), Aerophones, 	&hwndComboBox[1][0]);
	CreateComboBox(x, y + (2 * Y_OFFSET),  sizeof( Membranophones ) / sizeof ( Membranophones[0] ), Membranophones, &hwndComboBox[2][0]);
	CreateComboBox(x, y + (3 * Y_OFFSET),  sizeof( Idiophones )     / sizeof ( Idiophones[0]     ), Idiophones, 	&hwndComboBox[3][0]);
	CreateComboBox(x, y + (4 * Y_OFFSET),  sizeof( Electronic )     / sizeof ( Electronic[0]     ), Electronic, 	&hwndComboBox[4][0]);
/*
	CreateComboBox(10, 10, ( sizeof(MS_Subbulakshmi)   / sizeof(MS_Subbulakshmi[0])), MS_Subbulakshmi, &hwndComboBox[0][0]);

	CreateComboBox(10, 20, ( sizeof(KA_KishoriAmonkar) / sizeof(KA_KishoriAmonkar[0])), KA_KishoriAmonkar, &hwndComboBox[1][0]);
*/
}

void CreateComboBox (int xpos, int ypos, int size, node_t *node, HWND *hwndComboBox)
{
#define PERCENT 		100.0f
#define COMBOBOX_WIDTH  0.15
#define COMBOBOX_HEIGHT 0.15

	xpos = ((float)xpos / PERCENT) * windowWidth;
	ypos = ((float)ypos / PERCENT) * windowHeight;

	int comboBoxWidth  = COMBOBOX_WIDTH  * windowWidth; 	
	int comboBoxHeight = COMBOBOX_HEIGHT * windowHeight;	

    HWND hwndParent =  ghwnd; // Handle to the parent window


    HWND hwndCWComboBox = CreateWindow(WC_COMBOBOX, TEXT("***TESTING***"), 
         							  CBS_DROPDOWNLIST | CBS_HASSTRINGS | CBS_DISABLENOSCROLL | CBS_AUTOHSCROLL | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP,
         							  xpos, ypos, comboBoxWidth, comboBoxHeight, hwndParent, NULL, ghInstance, NULL);
	
	TCHAR Temp[255]; 
    memset(&Temp,0,sizeof(Temp));       
    for (int k = 0; k < size; k++)
    {
        wcscpy_s((wchar_t *)Temp, sizeof(Temp)/sizeof(TCHAR),  (wchar_t *)node[k].name);
        SendMessage(hwndCWComboBox,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) Temp); 
    }  

 // BOOL result =  ComboBox_SetCueBannerText(hwndCWComboBox, TEXT("Search"));
   SendMessage(hwndCWComboBox,(UINT) CB_SETCURSEL , (WPARAM)0, (LPARAM)0);  
 //   SendMessage(hwndCWComboBox, (UINT) CB_SETCUEBANNER, (WPARAM)0, (LPARAM) TEXT("Search"));
  
	FILE *fp;
		fopen_s(&fp, "Receipt", "w");

	//	fprintf(fp, " Error Message : %lp", result);
		fclose (fp);

    *hwndComboBox = hwndCWComboBox;
}

void SetMainThreadIndex(LPARAM lParam)
{
	for (int i = 0; i < MAX_MAIN_THREAD; i++)
		for (int j = 0; j < MAX_COMBOBOX_NEST; j++)
			if ((HWND)lParam == hwndComboBox[i][j])
			{	
				main_thread_index = i;
				break;
			}	
}

void GetIndexInComboBox(LPARAM lParam, int *indexComboBox, int *indexElement)
{
	int temp = 0;
	for (int i = 0; i < MAX_COMBOBOX_NEST; i++)
		if ((HWND)lParam == hwndComboBox[main_thread_index][i])
			*indexComboBox = i;

	temp = *indexComboBox;

	while ((temp + 1) < MAX_COMBOBOX_NEST)
	{
		if (hwndComboBox[main_thread_index][temp + 1])
			DestroyWindow(hwndComboBox[main_thread_index][temp + 1]);
		temp += 1;		
	}

    *indexElement = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);

}

bool GetNodeForString(int indexComboBox, int indexOfElement, int *number_of_elements, node_t **node)
{
	static node_t temp;

	maintain_indexElement[main_thread_index][indexComboBox] = indexOfElement;

	temp = main_node[main_thread_index];

	for (int i = 0; i <= indexComboBox; i++)
	{	
			if (i != indexComboBox)
				temp = temp.next[maintain_indexElement[main_thread_index][i]];
			else 
			{
				 temp = temp.next[indexOfElement];
				*node = temp.next;
				*number_of_elements = temp.size;
			}
	}

	if((**node).next == NULL)
	{
		product_selected[main_thread_index] = temp.name;
		cost_per_row[main_thread_index]     = atof((**node).name);
		return false;
	}
	else 
	{
		product_selected[main_thread_index] = NULL;
		cost_per_row[main_thread_index]     = 0;
		return true;
	}
	

/*
//	static int maintain_indexElement[3];
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
				if (cost_per_row[0] == 2000.00)
				{
					MessageBox(NULL, TEXT("HERE"), TEXT("HERE"), MB_OK);
				}
			}
			break;
			
	}
*/
}

void printFile(void)
{
	FILE *fp;
	double total = 0;


	fopen_s(&fp, "Receipt", "w");

	fprintf(fp, " Welcome Aashish\n\n");
	fprintf(fp, " Product Chosen \t\t SubType \t\t Price(Rs.)\n");

	for (int i = 0; i < (sizeof(main_node) / sizeof(main_node[0])); i++)
	{

		fprintf(fp, " %s \t\t", main_node[i].name);
		if (product_selected[i] != NULL)
			fprintf(fp, " %s ", product_selected[i]);
		fprintf(fp, " \t\t");
		fprintf(fp, " %f\n", cost_per_row[i]);
		total = total + cost_per_row[i];
	}	

	fprintf(fp, "\nTotal \t\t\t\t%f", total);

	fclose (fp);
}
