#include <iostream>

#define MY_BITMAP 101

using namespace std;


#define MAX_COMBOBOX_NEST  3
#define MAX_MAIN_THREAD	   3		

double  cost_per_row[MAX_MAIN_THREAD] = {0};
TCHAR  *product_selected[MAX_MAIN_THREAD] = {NULL}; 

HWND hwndComboBox[MAX_MAIN_THREAD][MAX_COMBOBOX_NEST];

int main_thread_index;
int maintain_indexElement[MAX_MAIN_THREAD][MAX_COMBOBOX_NEST];

typedef struct type node_t;
struct type 
{
	TCHAR  *name;
	node_t *next;
	size_t  size;
};

#define ARRAY_SIZE(node) sizeof(node)/sizeof(node[0])

/*
									|-> MS_BharaviVaranam 		|-> ABC |-> 2000
					|-> MS_Bhairavi |
					|				|-> MS_BhairaviKeertanam 	|-> PQR |-> 3000
	MS_Subbulakshmi |
					|				|-> MS_TodiVaranam 			|-> DEF |-> 2500
					|-> MS_Todi 	| 		
									|->	MS_TodiKeertanam 		|-> UVW |-> 3000
*/

node_t PleaseSelect[] 			= {TEXT("0000.00"), NULL, 0};

node_t MS_BV_COST[]				= {TEXT("2000.00"), NULL, 0};
node_t MS_BK_COST[]				= {TEXT("3000.00"), NULL, 0};
node_t MS_TV_COST[]				= {TEXT("2500.00"), NULL, 0};
node_t MS_TK_COST[]				= {TEXT("3000.00"), NULL, 0};

node_t MS_BharaviVaranam[] 		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)},
								   {TEXT("ABC"), 					 MS_BV_COST, 			ARRAY_SIZE(MS_BV_COST)}};
node_t MS_BhairaviKeertanam[] 	= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)},
								   {TEXT("PQR"), 					 MS_BK_COST, 			ARRAY_SIZE(MS_BK_COST)}};
node_t MS_TodiVaranam[] 		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)},
								   {TEXT("DEF"), 					 MS_TV_COST, 			ARRAY_SIZE(MS_TV_COST)}};
node_t MS_TodiKeertanam[]		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)},
								   {TEXT("UVW"), 					 MS_TK_COST, 			ARRAY_SIZE(MS_TK_COST)}};

node_t MS_Bhairavi[]  	 		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)},
								   {TEXT("Bhairavi Varanam"), 	 	 MS_BharaviVaranam, 	ARRAY_SIZE(MS_BharaviVaranam)},
								   {TEXT("Bhairavi Keertanam"), 	 MS_BhairaviKeertanam, 	ARRAY_SIZE(MS_BhairaviKeertanam)}};

node_t MS_Todi[]  		 		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)},
								   {TEXT("Todi Varanam"),  	 	 	 MS_TodiVaranam, 	 	ARRAY_SIZE(MS_TodiVaranam)},
						  		   {TEXT("Todi Keertanam"), 		 MS_TodiKeertanam, 		ARRAY_SIZE(MS_TodiKeertanam)}};

node_t MS_Subbulakshmi[] 		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)},
								   {TEXT("Raag Bhairavi"), 			 MS_Bhairavi, 		 	ARRAY_SIZE(MS_Bhairavi)},
			     				   {TEXT("Raag Todi"),  			 MS_Todi,			 	ARRAY_SIZE(MS_Todi)}}; 

/*
											|-> KA_MiyanKiMalhar 		|-> XYZ 					|-> 2000
						|-> KA_Solo  	    |
						|					|-> KA_MiyanKiTodi 			|-> LMN 					|-> 3000
	KA_KishoriAmonkar   |
						|					|-> KA_BMK 					|-> Raag Puriya Dhanashree 	|-> 2500
						|-> KA_JugalBandi 	| 		
											|->	KA_HPC 					|-> GHI 					|-> 3000
*/

node_t KA_MKM_Cost[] 			= {TEXT("2000.00"), NULL, 0};
node_t KA_MKT_Cost[] 			= {TEXT("3000.00"), NULL, 0};
node_t KA_BMK_Cost[] 			= {TEXT("4500.00"), NULL, 0};
node_t KA_HPC_Cost[] 			= {TEXT("1000.00"), NULL, 0};

node_t KA_MiyanKiMalhar[] 		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			 ARRAY_SIZE(PleaseSelect)},
								   {TEXT("XYZ"),  					 KA_MKM_Cost, 			 ARRAY_SIZE(KA_MKM_Cost)}};
node_t KA_MiyanKiTodi[] 		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			 ARRAY_SIZE(PleaseSelect)},
								   {TEXT("LMN"), 					 KA_MKT_Cost, 			 ARRAY_SIZE(KA_MKT_Cost)}};
node_t KA_BMK[] 				= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			 ARRAY_SIZE(PleaseSelect)},
								   {TEXT("Raag Puriya Dhanashree"),  KA_BMK_Cost, 			 ARRAY_SIZE(KA_BMK_Cost)}};
node_t KA_HPC[] 				= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			 ARRAY_SIZE(PleaseSelect)},
								   {TEXT("GHI"), 					 KA_HPC_Cost, 			 ARRAY_SIZE(KA_HPC_Cost)}};

node_t KA_Solo[] 				= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			 ARRAY_SIZE(PleaseSelect)},
								   {TEXT("Miyan Ki Malhar"), 		 KA_MiyanKiMalhar,		 ARRAY_SIZE(KA_MiyanKiMalhar)},
								   {TEXT("Miyan Ki Todi"), 			 KA_MiyanKiTodi,	     ARRAY_SIZE(KA_MiyanKiTodi)}};

node_t KA_JugalBandi[]			= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			 ARRAY_SIZE(PleaseSelect)},
								   {TEXT("Dr. BalamuraliKrishnan"), 	  KA_BMK,			 ARRAY_SIZE(KA_BMK)},
								   {TEXT("Pandit Hariprasad Chaurasiya"), KA_HPC,  			 ARRAY_SIZE(KA_HPC)}};

node_t KA_KishoriAmonkar[]		= {{TEXT("***PleaseSelect***"), 	 PleaseSelect, 			 ARRAY_SIZE(PleaseSelect)},
								   {TEXT("Solo"), 					 KA_Solo, 				 ARRAY_SIZE(KA_Solo)},
								   {TEXT("JugalBandi"), 			 KA_JugalBandi,			 ARRAY_SIZE(KA_JugalBandi)}};


/*
				|-> M S Subbulakshmi
	main_node   | 
				|-> Kishori Amonkar 
*/				

node_t main_node[] 				= {{TEXT("M S Subbulakshmi"), 					 MS_Subbulakshmi,		 ARRAY_SIZE(MS_Subbulakshmi)},
								   {TEXT("Kishori Amonkar"), 		 KA_KishoriAmonkar,		 ARRAY_SIZE(KA_KishoriAmonkar)}};
