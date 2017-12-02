#include <iostream>

#define MY_BITMAP 101

using namespace std;

double cost_per_row[2] = {0};


typedef struct type node_t;
struct type 
{
	TCHAR  *name;
	node_t *next;
};

node_t MS_BV_COST[]				= {TEXT("2000.00"), NULL};
node_t MS_BK_COST[]				= {TEXT("3000.00"), NULL};
node_t MS_TV_COST[]				= {TEXT("2500.00"), NULL};
node_t MS_TK_COST[]				= {TEXT("3000.00"), NULL};

node_t MS_BharaviVaranam[] 		= {TEXT("ABC"), MS_BV_COST};
node_t MS_BhairaviKeertanam[] 	= {TEXT("PQR"), MS_BK_COST};
node_t MS_TodiVaranam[] 		= {TEXT("DEF"), MS_TV_COST};
node_t MS_TodiKeertanam[]		= {TEXT("UVW"), MS_TK_COST};

node_t MS_Bhairavi[]  	 		= {{TEXT("MS_Bhairavi_Varanam"), 	 MS_BharaviVaranam},
								   {TEXT("MS_Bhairavi_Keertanam"), 	 MS_BhairaviKeertanam}};

node_t MS_Todi[]  		 		= {{TEXT("MS_Todi_Varanam"),  	 	 MS_TodiVaranam},
						  		   {TEXT("MS_Todi_Keertanam"), 		 MS_TodiKeertanam}};

node_t MS_Subbulakshmi[] 		= {{TEXT("Bhairavi"), 				 MS_Bhairavi}, 
			     				   {TEXT("Todi"),  					 MS_Todi 	}}; 


