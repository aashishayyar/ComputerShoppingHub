#include <iostream> 
#include <windows.h>

using namespace std;

typedef struct node node_t;
struct node
{
	TCHAR  *str;
	node_t *next;
};

node_t B[] = {TEXT("dvjbvd"), NULL};

node_t C[] = {TEXT("kjxvl"), NULL};

node_t A[] = {{TEXT("abc"), B},
			  {TEXT("def"), C}};


int main(void)
{

	cout << A[0].str << endl;
	cout << A[1].str << endl;
	cout << A[0].next[0].str << endl;

	TCHAR *str = TEXT("Varanam");

	TCHAR Temp[16];
	memset(&Temp,0,sizeof(Temp));
	wcscpy_s((wchar_t *)Temp, sizeof(Temp)/sizeof(TCHAR),  (wchar_t *)str);

//	cout << << endl;
//	cout << << endl;

}