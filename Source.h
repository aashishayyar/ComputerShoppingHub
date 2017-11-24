#include <iostream>

#define MY_BITMAP 101

using namespace std;

typedef struct type node_t;
struct type 
{
	TCHAR  *name;
	node_t *next;
};

node_t MS_BharaviVaranam[] 		= {TEXT("ABC"), NULL};
node_t MS_BhairaviKeertanam[] 	= {TEXT("PQR"), NULL};
node_t MS_TodiVaranam[] 		= {TEXT("DEF"), NULL};
node_t MS_TodiKeertanam[]		= {TEXT("UVW"), NULL};

node_t MS_Bhairavi[]  	 		= {{TEXT("MS_Bhairavi_Varanam"), 	 MS_BharaviVaranam},
								   {TEXT("MS_Bhairavi_Keertanam"), 	 MS_BhairaviKeertanam}};

node_t MS_Todi[]  		 		= {{TEXT("MS_Todi_Varanam"),  	 	 MS_TodiVaranam},
						  		   {TEXT("MS_Todi_Keertanam"), 		 MS_TodiKeertanam}};

node_t MS_Subbulakshmi[] 		= {{TEXT("Bhairavi"), 				 MS_Bhairavi}, 
			     				   {TEXT("Todi"),  					 MS_Todi 	}}; 


