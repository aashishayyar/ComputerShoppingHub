#include <iostream>

#define MY_BITMAP 101

using namespace std;

double cost_per_row[2] = {0};



#define MAX_COMBOBOX_NEST  3
#define MAX_MAIN_THREAD	   3		
HWND hwndComboBox[MAX_MAIN_THREAD][MAX_COMBOBOX_NEST];

int main_thread_index;
int maintain_indexElement[MAX_MAIN_THREAD][MAX_COMBOBOX_NEST];

typedef struct type node_t;
struct type 
{
	TCHAR  *name;
	node_t *next;
	
};

typedef int size_t
typedef struct metadata meta_t; 
struct metadata
{
	node_t *e_node;
	size_t  size;
};

/*
									|-> MS_BharaviVaranam 		|-> ABC |-> 2000
					|-> MS_Bhairavi |
					|				|-> MS_BhairaviKeertanam 	|-> PQR |-> 3000
	MS_Subbulakshmi |
					|				|-> MS_TodiVaranam 			|-> DEF |-> 2500
					|-> MS_Todi 	| 		
									|->	MS_TodiKeertanam 		|-> UVW |-> 3000
*/

node_t MS_BV_COST[]				= {TEXT("2000.00"), NULL};
node_t MS_BK_COST[]				= {TEXT("3000.00"), NULL};
node_t MS_TV_COST[]				= {TEXT("2500.00"), NULL};
node_t MS_TK_COST[]				= {TEXT("3000.00"), NULL};

node_t MS_BharaviVaranam[] 		= {TEXT("ABC"), MS_BV_COST};
node_t MS_BhairaviKeertanam[] 	= {TEXT("PQR"), MS_BK_COST};
node_t MS_TodiVaranam[] 		= {TEXT("DEF"), MS_TV_COST};
node_t MS_TodiKeertanam[]		= {TEXT("UVW"), MS_TK_COST};

node_t MS_Bhairavi[]  	 		= {{TEXT("Bhairavi Varanam"), 	 	 MS_BharaviVaranam 		 },
								   {TEXT("Bhairavi Keertanam"), 	 MS_BhairaviKeertanam 	}};

node_t MS_Todi[]  		 		= {{TEXT("Todi Varanam"),  	 	 	 MS_TodiVaranam 	 	 },
						  		   {TEXT("Todi Keertanam"), 		 MS_TodiKeertanam 		}};

node_t MS_Subbulakshmi[] 		= {{TEXT("Raag Bhairavi"), 			 MS_Bhairavi 			 },
			     				   {TEXT("Raag Todi"),  			 MS_Todi 				}}; 

/*
											|-> KA_MiyanKiMalhar 		|-> XYZ 					|-> 2000
						|-> KA_Solo  	    |
						|					|-> KA_MiyanKiTodi 			|-> LMN 					|-> 3000
	KA_KishoriAmonkar   |
						|					|-> KA_BMK 					|-> Raag Puriya Dhanashree 	|-> 2500
						|-> KA_JugalBandi 	| 		
											|->	KA_HPC 					|-> GHI 					|-> 3000
*/

node_t KA_MKM_Cost[] 			= {TEXT("2000.00"), NULL};
node_t KA_MKT_Cost[] 			= {TEXT("2000.00"), NULL};
node_t KA_BMK_Cost[] 			= {TEXT("2000.00"), NULL};
node_t KA_HPC_Cost[] 			= {TEXT("2000.00"), NULL};

node_t KA_MiyanKiMalhar[] 		= {TEXT("XYZ"),  					 KA_MKM_Cost 			 };
node_t KA_MiyanKiTodi[] 		= {TEXT("LMN"), 					 KA_MKT_Cost 			 };
node_t KA_BMK[] 				= {TEXT("Raag Puriya Dhanashree"),   KA_BMK_Cost 			 };
node_t KA_HPC[] 				= {TEXT("GHI"), 					 KA_HPC_Cost 			 };

node_t KA_Solo[] 				= {{TEXT("Miyan Ki Malhar"), 		 KA_MiyanKiMalhar		 },
								   {TEXT("Miyan Ki Todi"), 			 KA_MiyanKiTodi		    }};

node_t KA_JugalBandi[]			= {{TEXT("Dr. BalamuraliKrishnan"), 	  KA_BMK			 },
								   {TEXT("Pandit Hariprasad Chaurasiya"), KA_HPC  			}};

node_t KA_KishoriAmonkar[]		= {{TEXT("Solo"), 					 KA_Solo				 },
								   {TEXT("JugalBandi"), 			 KA_JugalBandi 			}};



node_t main_node[] 				= {{TEXT("MSS"), 					 MS_Subbulakshmi		  },
								   {TEXT("KA_KishoriAmonkar"), 		 KA_KishoriAmonkar		 }};

meta_t meta[] 					= {{main_node, 				2},
								   {MS_Subbulakshmi, 		2},
								   {MS_Bhairavi, 			2}, 
								   {MS_Todi, 				2},
								   {MS_BharaviVaranam, 		1},
								   {MS_BhairaviKeertanam, 	1},
								   {MS_TodiVaranam, 		1},
								   {MS_TodiKeertanam, 		1},
								   {MS_BV_COST, 			1},
								   {MS_BK_COST, 			1},
								   {MS_TV_COST, 			1},
								   {MS_TK_COST, 			1},
								   {KA_KishoriAmonkar, 		2},	
								   {KA_Solo, 				2},
								   {KA_JugalBandi, 			2},
								   {KA_MiyanKiMalhar, 		1},
								   {KA_MiyanKiTodi, 		1},
								   {KA_BMK, 				1},
								   {KA_HPC, 				1},
								   {KA_MKM_Cost, 			1},
								   {KA_MKT_Cost, 			1},
								   {KA_BMK_Cost, 			1},
								   {KA_HPC_Cost, 			1}, 
								   {NULL, 					0}};