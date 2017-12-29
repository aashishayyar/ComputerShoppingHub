#include <iostream>

#define VIOLIN1 101
#define VIOLIN2 102
#define TABLA   103

using namespace std;

int screen = 0;
bool valid_region = false;

#define MAX_COMBOBOX_NEST  3
#define MAX_MAIN_THREAD	   5		

float  cost_per_row[MAX_MAIN_THREAD] = {0};
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

/*
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


											|-> KA_MiyanKiMalhar 		|-> XYZ 					|-> 2000
						|-> KA_Solo  	    |
						|					|-> KA_MiyanKiTodi 			|-> LMN 					|-> 3000
	KA_KishoriAmonkar   |
						|					|-> KA_BMK 					|-> Raag Puriya Dhanashree 	|-> 2500
						|-> KA_JugalBandi 	| 		
											|->	KA_HPC 					|-> GHI 					|-> 3000


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



				|-> M S Subbulakshmi
	main_node   | 
				|-> Kishori Amonkar 
				

node_t main_node[] 				= {{TEXT("M S Subbulakshmi"), 					 MS_Subbulakshmi,		 ARRAY_SIZE(MS_Subbulakshmi)},
								   {TEXT("Kishori Amonkar"), 		 KA_KishoriAmonkar,		 ARRAY_SIZE(KA_KishoriAmonkar)}};
*/

/* LEVEL 4 */
								   // Plucked Strings
node_t BulbulTarang[] 		= { TEXT("12345"), NULL, 0};  								   
node_t Dotar[] 				= { TEXT("23456"), NULL, 0};
node_t Ektara[] 			= { TEXT("34567"), NULL, 0};
node_t Jhallari[] 			= { TEXT("45678"), NULL, 0};
node_t Khamak[] 			= { TEXT("56789"), NULL, 0};
node_t Chitravina[] 		= { TEXT("67890"), NULL, 0};
node_t Katho[] 				= { TEXT("78900"), NULL, 0};
node_t Sarod[] 				= { TEXT("88990"), NULL, 0};
node_t Sitar[] 				= { TEXT("99009"), NULL, 0};
node_t Surbahar[] 			= { TEXT("15026"), NULL, 0};
node_t Surshringar[] 		= { TEXT("24678"), NULL, 0};
node_t Swarabat[] 			= { TEXT("14253"), NULL, 0};
node_t Swarmandal[] 		= { TEXT("87353"), NULL, 0};
node_t Tambura[] 			= { TEXT("17352"), NULL, 0};
node_t Tumbi[] 				= { TEXT("28354"), NULL, 0};
node_t Tuntuna[] 			= { TEXT("91538"), NULL, 0};
node_t MagadiVeena[] 		= { TEXT("35135"), NULL, 0};
node_t HansaVeena[] 		= { TEXT("54216"), NULL, 0};
node_t MohanVeena[] 		= { TEXT("52313"), NULL, 0};
node_t NakulaVeena[] 		= { TEXT("32135"), NULL, 0};
node_t Nanduni[] 			= { TEXT("95623"), NULL, 0};
node_t PamiriRubab[] 		= { TEXT("24521"), NULL, 0};
node_t RudraVeena[] 		= { TEXT("36523"), NULL, 0};
node_t SaraswatiVeena[] 	= { TEXT("25845"), NULL, 0};
node_t VichitraVeena[]		= { TEXT("15975"), NULL, 0};
node_t Yazh[] 				= { TEXT("84561"), NULL, 0};
node_t RanjanVeena[] 		= { TEXT("14785"), NULL, 0};
node_t Rubab[] 				= { TEXT("62452"), NULL, 0};
node_t TriveniVeena[] 		= { TEXT("32165"), NULL, 0};

									// BowedStrings
node_t Chikara[] 			= { TEXT("48567"), NULL, 0};
node_t Dilruba[] 			= { TEXT("64235"), NULL, 0};

node_t EktaraViolin[] 		= { TEXT("14567"), NULL, 0};
node_t FourString[] 		= { TEXT("48759"), NULL, 0};
node_t SevenString[] 		= { TEXT("88696"), NULL, 0};

node_t Esraj[] 				= { TEXT("95316"), NULL, 0};
node_t Kamaicha[] 			= { TEXT("45612"), NULL, 0};
node_t Taus[] 				= { TEXT("65781"), NULL, 0};
node_t Onavillu[] 			= { TEXT("65422"), NULL, 0};
node_t Behala[] 			= { TEXT("48579"), NULL, 0};
node_t Pena[] 				= { TEXT("15976"), NULL, 0};
node_t PulluvanVeena[] 		= { TEXT("46791"), NULL, 0};
node_t Ravanahatha[] 		= { TEXT("28391"), NULL, 0};
node_t FolkSarangi[] 		= { TEXT("71829"), NULL, 0};
node_t ClassicalSarangi[] 	= { TEXT("64975"), NULL, 0};
node_t Sarinda[] 			= { TEXT("24673"), NULL, 0};
node_t TarShehnai[] 		= { TEXT("16495"), NULL, 0};

									// Chord_Miscellaneous
node_t StruckTanpura[] 		= { TEXT("65543"), NULL, 0};
node_t PulluvanKutam[] 		= { TEXT("15354"), NULL, 0};
node_t Santoor[] 			= { TEXT("15658"), NULL, 0};
	
									// 	Single Reed	
node_t Pepa[] 				= { TEXT("75864"), NULL, 0};
node_t Pungi[] 				= { TEXT("36251"), NULL, 0};

									// Double Reed
node_t Kuzhal[] 			= { TEXT("68753"), NULL, 0};
node_t Mukhavina[] 			= { TEXT("65432"), NULL, 0};
node_t Nadaswaram[] 		= { TEXT("16548"), NULL, 0};
node_t Shehnai[] 			= { TEXT("75465"), NULL, 0};
node_t Sundari[] 			= { TEXT("62311"), NULL, 0};
node_t Tangmuri[] 			= { TEXT("54846"), NULL, 0};

									// Flute
node_t Alghoza[] 			= { TEXT("53183"), NULL, 0};
node_t Bansuri[] 			= { TEXT("53257"), NULL, 0};
node_t Venu[] 				= { TEXT("95613"), NULL, 0};

									// Bagpipes
node_t Mashak[] 			= { TEXT("23547"), NULL, 0};
node_t Titti[] 				= { TEXT("95613"), NULL, 0};
node_t SrutiUpanga[] 		= { TEXT("23467"), NULL, 0};

									// FreeReed
node_t Gogona[] 			= { TEXT("88592"), NULL, 0};
node_t Morsing[] 			= { TEXT("43152"), NULL, 0};

									// FreeReedAndBellows
node_t ShrutiBox[] 			= { TEXT("38296"), NULL, 0};
node_t Harmonium[] 			= { TEXT("85422"), NULL, 0};

									// Brass
node_t Ekkalam[] 			= { TEXT("58387"), NULL, 0};
node_t Karnal[] 			= { TEXT("44242"), NULL, 0};
node_t Ramsinga[] 			= { TEXT("45758"), NULL, 0};
node_t Kahal[] 				= { TEXT("42182"), NULL, 0};
node_t Nagphani[] 			= { TEXT("15867"), NULL, 0};
node_t Turi[] 				= { TEXT("65243"), NULL, 0};

									// HandDrums
node_t Dhad[] 				= { TEXT("48798"), NULL, 0};
node_t Damru[] 				= { TEXT("37215"), NULL, 0};
node_t Dimadi[] 			= { TEXT("49567"), NULL, 0};
node_t Dhol[] 				= { TEXT("5864"), NULL, 0};
node_t Dholak[] 			= { TEXT("35436"), NULL, 0};
node_t Dholki[] 			= { TEXT("43756"), NULL, 0};
node_t Duggi[] 				= { TEXT("51612"), NULL, 0};
node_t GadaSingari[] 		= { TEXT("86894"), NULL, 0};
node_t Ghumot[] 			= { TEXT("21375"), NULL, 0};
node_t Gummeta[] 			= { TEXT("51974"), NULL, 0};
node_t Kanjira[] 			= { TEXT("12507"), NULL, 0};
node_t Khol[] 				= { TEXT("54213"), NULL, 0};
node_t Dhopar[] 			= { TEXT("57664"), NULL, 0};
node_t Madal[] 				= { TEXT("54887"), NULL, 0};
node_t Maddale[]		 	= { TEXT("33736"), NULL, 0};
node_t Maram[] 				= { TEXT("31225"), NULL, 0};
node_t Mizhavu[] 			= { TEXT("89867"), NULL, 0};
node_t Mridangam[] 			= { TEXT("73457"), NULL, 0};
node_t Naal[] 				= { TEXT("21320"), NULL, 0};
node_t Pakhavaj[] 			= { TEXT("79854"), NULL, 0};
node_t Jori[] 				= { TEXT("43568"), NULL, 0};
node_t PanchamukhaVadyam[] 	= { TEXT("37012"), NULL, 0};
node_t Pung[] 				= { TEXT("42152"), NULL, 0};
node_t Maddalam[] 			= { TEXT("68291"), NULL, 0};
node_t GobletDrum[] 		= { TEXT("37685"), NULL, 0};
node_t Tabla[] 				= { TEXT("87461"), NULL, 0};
node_t TablaTarang[] 		= { TEXT("43216"), NULL, 0};
node_t Tamte[] 				= { TEXT("15168"), NULL, 0};
node_t ThanthiPanai[] 		= { TEXT("47542"), NULL, 0};
node_t Thimila[] 			= { TEXT("32168"), NULL, 0};
node_t Tumbak[] 			= { TEXT("61321"), NULL, 0};
node_t Tumdak[] 			= { TEXT("32464"), NULL, 0};
node_t Udukku[] 			= { TEXT("67531"), NULL, 0};

								// HandFrameDrums
node_t Daff[] 				= { TEXT("12368"), NULL, 0};
node_t Dimdi[] 				= { TEXT("95484"), NULL, 0};
node_t Kansi[] 				= { TEXT("10524"), NULL, 0};
node_t PatayaniThappu[] 	= { TEXT("48972"), NULL, 0};

								// StickAndHandDrums
node_t Chenda[] 			= { TEXT("13687"), NULL, 0};
node_t Davul[]		 		= { TEXT("54132"), NULL, 0};
node_t Dhak[] 				= { TEXT("79876"), NULL, 0};
node_t Dhimay[] 			= { TEXT("65485"), NULL, 0};
node_t Dholi[] 				= { TEXT("85647"), NULL, 0};
node_t Dollu[] 				= { TEXT("13541"), NULL, 0};
node_t Idakka[] 			= { TEXT("16854"), NULL, 0};
node_t Thavil[] 			= { TEXT("87432"), NULL, 0};
node_t Udukai[] 			= { TEXT("65421"), NULL, 0};
node_t Urumi[] 				= { TEXT("87413"), NULL, 0};

								// StickDrums
node_t Chande[] 			= { TEXT("43216"), NULL, 0};
node_t KachhiDhol[] 		= { TEXT("42687"), NULL, 0};
node_t Nagara[] 			= { TEXT("62165"), NULL, 0};
node_t Pambai[] 			= { TEXT("52125"), NULL, 0};
node_t Halgi[] 				= { TEXT("35466"), NULL, 0};
node_t Sambal[] 			= { TEXT("54212"), NULL, 0};
node_t StickDaff[] 			= { TEXT("66789"), NULL, 0};
node_t Tamak[] 				= { TEXT("30245"), NULL, 0};
node_t Tasha[] 				= { TEXT("23092"), NULL, 0};
node_t Urumee[] 			= { TEXT("78541"), NULL, 0};

								// Melodic
node_t JalTarang[] 			= { TEXT("56864"), NULL, 0};
node_t KanchTarang[] 		= { TEXT("46523"), NULL, 0};
node_t KashthaTarang[]	 	= { TEXT("34521"), NULL, 0};

								// Idiophones_Miscellaneous
node_t Chimpta[] 			= { TEXT("45612"), NULL, 0};
node_t Chengila[] 			= { TEXT("16451"), NULL, 0};
node_t Elathalam[] 			= { TEXT("53416"), NULL, 0};
node_t Geger[] 				= { TEXT("85416"), NULL, 0};
node_t Ghatam[] 			= { TEXT("63416"), NULL, 0};
node_t Ghungroo[] 			= { TEXT("45241"), NULL, 0};
node_t Khartal[] 			= { TEXT("54120"), NULL, 0};
node_t Manjeera[] 			= { TEXT("10498"), NULL, 0};
node_t Nut[] 				= { TEXT("32745"), NULL, 0};
node_t Sankarjang[] 		= { TEXT("98451"), NULL, 0};
node_t Thali[]		 		= { TEXT("16587"), NULL, 0};
node_t ThattukazhiMannai[]	= { TEXT("45132"), NULL, 0};
node_t YakshaganaBells[] 	= { TEXT("65865"), NULL, 0};

//node_t ABCD[] = { {TEXT("jhbxvjhxcnzvkvdnkjnvkbdzvkjbkjznvm x ,mvjn nvdnzkvdnljnxvzdvzdv"), Thali, ARRAY_SIZE(Thali)}, {TEXT(" "), NULL, 0}};
// 
/* LEVEL 3 */
node_t PluckedStrings[] = { {TEXT("***PleaseSelect***"), 	 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)	},
							{TEXT("Bulbul Tarang"), 		  	BulbulTarang, 			ARRAY_SIZE(BulbulTarang)	},
							{TEXT("Dotar, Dotora or Dotara"), 	Dotar, 					ARRAY_SIZE(Dotar)			},
							{TEXT("Ektara"), 				  	Ektara, 				ARRAY_SIZE(Ektara)			},
							{TEXT("Getchu Vadyam or Jhallari"), Jhallari, 				ARRAY_SIZE(Jhallari)		},
							{TEXT("Gopichand or Gopiyantra or Khamak"), Khamak, 		ARRAY_SIZE(Khamak)			},
							{TEXT("Gottuvadhyam or Chitravina"), Chitravina, 			ARRAY_SIZE(Chitravina)		},
							{TEXT("Katho"), 					Katho, 					ARRAY_SIZE(Katho)			},
							{TEXT("Sarod"), 					Sarod, 					ARRAY_SIZE(Sarod)			},
							{TEXT("Sitar"), 					Sitar, 					ARRAY_SIZE(Sitar)			},
							{TEXT("Surbahar"), 					Surbahar, 				ARRAY_SIZE(Surbahar)		},
							{TEXT("Surshringar"), 				Surshringar, 			ARRAY_SIZE(Surshringar)		},
							{TEXT("Swarabat"), 					Swarabat, 				ARRAY_SIZE(Swarabat)		},
							{TEXT("Swarmandal"), 				Swarmandal, 			ARRAY_SIZE(Swarmandal)		},
							{TEXT("Tambura"), 					Tambura, 				ARRAY_SIZE(Tambura)			},
							{TEXT("Tumbi"), 					Tumbi, 					ARRAY_SIZE(Tumbi)			},
							{TEXT("Tuntuna"), 					Tuntuna, 				ARRAY_SIZE(Tuntuna)			},
							{TEXT("Magadi Veena"), 				MagadiVeena, 			ARRAY_SIZE(MagadiVeena)		},
							{TEXT("Hansa Veena"), 				HansaVeena, 			ARRAY_SIZE(HansaVeena)		},
							{TEXT("Mohan Veena"), 				MohanVeena, 			ARRAY_SIZE(MohanVeena)		},
							{TEXT("Nakula Veena"), 				NakulaVeena, 			ARRAY_SIZE(NakulaVeena)		},
							{TEXT("Nanduni"), 					Nanduni, 				ARRAY_SIZE(Nanduni)			},
							{TEXT("Pamiri Rubab"), 				PamiriRubab, 			ARRAY_SIZE(PamiriRubab)		},
							{TEXT("Rudra Veena"), 				RudraVeena, 			ARRAY_SIZE(RudraVeena)		},
							{TEXT("Saraswati Veena"), 			SaraswatiVeena, 		ARRAY_SIZE(SaraswatiVeena)	},
							{TEXT("Vichitra Veena"), 			VichitraVeena, 			ARRAY_SIZE(VichitraVeena)	},
							{TEXT("Yazh"), 						Yazh, 					ARRAY_SIZE(Yazh)			},
							{TEXT("Ranjan Veena"), 				RanjanVeena, 			ARRAY_SIZE(RanjanVeena)		},
							{TEXT("Rubab (instrument)"), 		Rubab, 					ARRAY_SIZE(Rubab)			},
							{TEXT("Triveni Veena"), 			TriveniVeena, 			ARRAY_SIZE(TriveniVeena)	} };								   

node_t Violin[] 		= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("EktaraViolin"), 			EktaraViolin, 			ARRAY_SIZE(EktaraViolin) 		 },
							{TEXT("Four String"), 			FourString, 			ARRAY_SIZE(FourString)			 },
							{TEXT("Seven String"), 			SevenString, 			ARRAY_SIZE(SevenString)			 } };

node_t BowedStrings[]   = { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Chikara"), 				Chikara, 				ARRAY_SIZE(Chikara)				 },
							{TEXT("Dilruba"), 				Dilruba, 				ARRAY_SIZE(Dilruba)				 },
							{TEXT("Violin"), 				Violin,					ARRAY_SIZE(Violin)		 		 },
							{TEXT("Esraj"), 				Esraj, 					ARRAY_SIZE(Esraj)				 },
							{TEXT("Kamaicha"), 				Kamaicha, 				ARRAY_SIZE(Kamaicha)			 },
							{TEXT("Mayuri Vina or Taus"), 	Taus, 					ARRAY_SIZE(Taus)				 },
							{TEXT("Onavillu"), 				Onavillu, 				ARRAY_SIZE(Onavillu)			 },
							{TEXT("Behala (violin type)"), 	Behala, 				ARRAY_SIZE(Behala) 				 },
							{TEXT("Pena or Bana"), 			Pena, 					ARRAY_SIZE(Pena)				 },
							{TEXT("Pulluvan Veena - one stringed violin"), PulluvanVeena, ARRAY_SIZE(PulluvanVeena)	 },
							{TEXT("Ravanahatha"), 			Ravanahatha, 			ARRAY_SIZE(Ravanahatha)			 },
							{TEXT("Folk Sarangi"), 			FolkSarangi, 			ARRAY_SIZE(FolkSarangi)			 },
							{TEXT("Classical Sarangi"), 	ClassicalSarangi, 		ARRAY_SIZE(ClassicalSarangi)	 },
							{TEXT("Sarinda"), 				Sarinda, 				ARRAY_SIZE(Sarinda)				 },
							{TEXT("Tar Shehnai"), 			TarShehnai, 			ARRAY_SIZE(TarShehnai)			 } };

node_t Chord_Miscellaneous[] = { {TEXT("***PleaseSelect***"), 	 			PleaseSelect, 	ARRAY_SIZE(PleaseSelect)	},
								 {TEXT("Gethu, Jhallari, struck tanpura"),  StruckTanpura, 	ARRAY_SIZE(StruckTanpura)  	},
								 {TEXT("Gubguba or Jamuku - aka khamak"), 	Khamak, 		ARRAY_SIZE(Khamak)			},
								 {TEXT("Pulluvan kutam"), 					PulluvanKutam, 	ARRAY_SIZE(PulluvanKutam)	},
								 {TEXT("Santoor - Hammered dulcimer"), 		Santoor, 		ARRAY_SIZE(Santoor)			} };													

node_t SingleReed[] 	= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Pepa"), 					Pepa, 					ARRAY_SIZE(Pepa)				 },
							{TEXT("Pungi or Been"), 		Pungi, 					ARRAY_SIZE(Pungi)				 } };

node_t DoubleReed[] 	= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Kuzhal"), 				Kuzhal, 				ARRAY_SIZE(Kuzhal)				 },
							{TEXT("Mukhavina"), 			Mukhavina, 				ARRAY_SIZE(Mukhavina)			 },
							{TEXT("Nadaswaram"), 			Nadaswaram, 			ARRAY_SIZE(Nadaswaram)			 },
							{TEXT("Shehnai"), 				Shehnai, 				ARRAY_SIZE(Shehnai)				 },
							{TEXT("Sundari"), 				Sundari, 				ARRAY_SIZE(Sundari)				 },
							{TEXT("Tangmuri"), 				Tangmuri, 				ARRAY_SIZE(Tangmuri)			 } };

node_t Flute[] 			= { {TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Alghoza - double flute"), Alghoza, 				ARRAY_SIZE(Alghoza)				 },
							{TEXT("Bansuri"), 				 Bansuri, 				ARRAY_SIZE(Bansuri)				 },
							{TEXT("Venu (Carnatic flute) Pullanguzhal"), Venu, 		ARRAY_SIZE(Venu)				 } };

node_t Bagpipes[] 		= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Mashak"), 				Mashak, 				ARRAY_SIZE(Mashak)				 },
							{TEXT("Titti"), 				Titti, 					ARRAY_SIZE(Titti)				 },
							{TEXT("Sruti upanga"), 			SrutiUpanga, 			ARRAY_SIZE(SrutiUpanga)			 } };

node_t FreeReed[] 		= { {TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Gogona"), 				Gogona, 				ARRAY_SIZE(Gogona)				 },
							{TEXT("Morsing"), 				Morsing, 				ARRAY_SIZE(Morsing)				 } };

node_t FreeReedAndBellows[] = { {TEXT("***PleaseSelect***"), 	  PleaseSelect, 	ARRAY_SIZE(PleaseSelect)		 },
								{TEXT("Shruti box"), 			  ShrutiBox, 		ARRAY_SIZE(ShrutiBox)			 },
								{TEXT("Harmonium (hand-pumped)"), Harmonium, 		ARRAY_SIZE(Harmonium)			 } };

node_t Brass[] 			= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Ekkalam"), 				Ekkalam, 				ARRAY_SIZE(Ekkalam)				 },
							{TEXT("Karnal"), 				Karnal, 				ARRAY_SIZE(Karnal)				 },
							{TEXT("Ramsinga"), 				Ramsinga, 				ARRAY_SIZE(Ramsinga)			 },
							{TEXT("Kahal"), 				Kahal, 					ARRAY_SIZE(Kahal)				 },
							{TEXT("Nagphani"), 				Nagphani, 				ARRAY_SIZE(Nagphani)			 },	
							{TEXT("Turi"), 					Turi, 					ARRAY_SIZE(Turi)				 } };

node_t HandDrums[] 		= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Dhad"), 					Dhad, 					ARRAY_SIZE(Dhad)				 },
							{TEXT("Damru"), 				Damru, 					ARRAY_SIZE(Damru)				 },
							{TEXT("Dimadi"), 				Dimadi, 				ARRAY_SIZE(Dimadi)				 },
							{TEXT("Dhol"), 					Dhol, 					ARRAY_SIZE(Dhol)				 },
							{TEXT("Dholak"), 				Dholak, 				ARRAY_SIZE(Dholak)				 },
							{TEXT("Dholki"), 				Dholki, 				ARRAY_SIZE(Dholki)				 },
							{TEXT("Duggi"), 				Duggi, 					ARRAY_SIZE(Duggi)				 },
							{TEXT("Ghat singhari or Gada Singari"), GadaSingari,    ARRAY_SIZE(GadaSingari)			 },
							{TEXT("Ghumot"), 				Ghumot, 				ARRAY_SIZE(Ghumot)				 },
							{TEXT("Gummeta"), 				Gummeta, 				ARRAY_SIZE(Gummeta)				 },
							{TEXT("Kanjira"), 				Kanjira, 				ARRAY_SIZE(Kanjira)				 },
							{TEXT("Khol"), 					Khol, 					ARRAY_SIZE(Khol)				 },
							{TEXT("Kinpar and Dhopar (Tribal Drums)"), Dhopar, 		ARRAY_SIZE(Dhopar)				 },
							{TEXT("Madal"), 				Madal, 					ARRAY_SIZE(Madal)				 },
							{TEXT("Maddale"), 				Maddale, 				ARRAY_SIZE(Maddale)				 },
							{TEXT("Maram"), 				Maram, 					ARRAY_SIZE(Maram)				 },
							{TEXT("Mizhavu"), 				Mizhavu, 				ARRAY_SIZE(Mizhavu)				 },
							{TEXT("Mridangam"), 			Mridangam, 				ARRAY_SIZE(Mridangam)			 },
							{TEXT("Naal"), 					Naal, 					ARRAY_SIZE(Naal)				 },
							{TEXT("Pakhavaj"), 				Pakhavaj, 				ARRAY_SIZE(Pakhavaj)			 },
							{TEXT("Pakhavaj Jori - Sikh"),  Jori, 					ARRAY_SIZE(Jori)				 },
							{TEXT("Panchamukha Vadyam"), 	PanchamukhaVadyam, 		ARRAY_SIZE(PanchamukhaVadyam)	 },
							{TEXT("Pung"), 					Pung, 					ARRAY_SIZE(Pung)				 },	
							{TEXT("Shuddha Madalam or Maddalam"), Maddalam, 		ARRAY_SIZE(Maddalam)			 },
							{TEXT("Tabala / Tabl / Chameli - goblet drum"), GobletDrum, ARRAY_SIZE(GobletDrum)		 },
							{TEXT("Tabla"), 				Tabla, 					ARRAY_SIZE(Tabla)				 },
							{TEXT("Tabla Tarang"), 			TablaTarang, 			ARRAY_SIZE(TablaTarang)			 },
							{TEXT("Tamte"), 				Tamte, 					ARRAY_SIZE(Tamte)				 },
							{TEXT("Thanthi Panai"), 		ThanthiPanai, 			ARRAY_SIZE(ThanthiPanai)		 },
							{TEXT("Thimila"), 				Thimila, 				ARRAY_SIZE(Thimila)				 },
							{TEXT("Tumbak, Tumbaknari, Tumbaknaer"), Tumbak, 		ARRAY_SIZE(Tumbak)				 },
							{TEXT("Tumdak'"), 				Tumdak, 				ARRAY_SIZE(Tumdak)				 },
							{TEXT("Udukku"), 				Udukku, 				ARRAY_SIZE(Udukku)				 } };													 

node_t HandFrameDrums[] = { {TEXT("***PleaseSelect***"), 	 PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Daff, duff, daf or duf"), Daff, 					ARRAY_SIZE(Daff)				 },
							{TEXT("Dimdi or dimri "), 		Dimdi, 					ARRAY_SIZE(Dimdi)				 },
							{TEXT("Kanjira "), 				Kanjira, 				ARRAY_SIZE(Kanjira)				 },
							{TEXT("Kansi"), 				Kansi, 					ARRAY_SIZE(Kansi)				 },
							{TEXT("Patayani thappu"), 		PatayaniThappu, 		ARRAY_SIZE(PatayaniThappu)		 } };

node_t StickAndHandDrums[] = { 	{TEXT("***PleaseSelect***"), 	 PleaseSelect, 		ARRAY_SIZE(PleaseSelect)		 },
								{TEXT("Chenda"), 			Chenda, 				ARRAY_SIZE(Chenda)				 },
								{TEXT("Davul"), 			Davul,					ARRAY_SIZE(Davul)				 },
								{TEXT("Dhak"), 				Dhak, 					ARRAY_SIZE(Dhak)				 },
								{TEXT("Dhimay"), 			Dhimay, 				ARRAY_SIZE(Dhimay)				 },
								{TEXT("Dhol"), 				Dhol, 					ARRAY_SIZE(Dhol)				 },
								{TEXT("Dholi"), 			Dholi, 					ARRAY_SIZE(Dholi)				 },
								{TEXT("Dollu"), 			Dollu, 					ARRAY_SIZE(Dollu)				 },
								{TEXT("Idakka"), 			Idakka, 				ARRAY_SIZE(Idakka)				 },
								{TEXT("Thavil"), 			Thavil, 				ARRAY_SIZE(Thavil)				 },
								{TEXT("Udukai"), 			Udukai, 				ARRAY_SIZE(Udukai)				 },
								{TEXT("Urumi (drum)"), 		Urumi, 					ARRAY_SIZE(Urumi)				 } };

node_t StickDrums[] 	= { {TEXT("***PleaseSelect***"), 	 PleaseSelect, 		ARRAY_SIZE(PleaseSelect)			 },
							{TEXT("Chande"), 			Chande, 				ARRAY_SIZE(Chande)				 	 },
							{TEXT("Davul"), 			Davul, 					ARRAY_SIZE(Davul)					 },
							{TEXT("Kachhi Dhol"), 		KachhiDhol, 			ARRAY_SIZE(KachhiDhol)				 },
							{TEXT("Nagara"), 			Nagara, 				ARRAY_SIZE(Nagara)					 },
							{TEXT("Pambai"), 			Pambai, 				ARRAY_SIZE(Pambai)					 },
							{TEXT("Parai thappu, halgi"), Halgi, 				ARRAY_SIZE(Halgi)					 },
							{TEXT("Sambal"), 			Sambal, 				ARRAY_SIZE(Sambal)				 	 },
							{TEXT("Stick daff or stick duff "), StickDaff, 		ARRAY_SIZE(StickDaff)				 },
							{TEXT("Tamak'"), 			Tamak, 					ARRAY_SIZE(Tamak)					 },
							{TEXT("Tasha"), 			Tasha, 					ARRAY_SIZE(Tasha)					 },
							{TEXT("Urumee"), 			Urumee, 				ARRAY_SIZE(Urumee)					 } };

node_t Melodic[] 		= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Jal tarang"), 			JalTarang, 				ARRAY_SIZE(JalTarang)			 },
							{TEXT("Kanch tarang"), 			KanchTarang, 			ARRAY_SIZE(KanchTarang)			 },
							{TEXT("Kashtha tarang"), 		KashthaTarang, 			ARRAY_SIZE(KashthaTarang)		 } };

node_t Idiophones_Miscellaneous[] 	= { {TEXT("***PleaseSelect***"), 	 PleaseSelect, 		ARRAY_SIZE(PleaseSelect) },
							{TEXT("Chimpta"), 				Chimpta, 				ARRAY_SIZE(Chimpta)				 },
							{TEXT("Chengila"), 				Chengila, 				ARRAY_SIZE(Chengila)			 },
							{TEXT("Elathalam"), 			Elathalam, 				ARRAY_SIZE(Elathalam)			 },
							{TEXT("Geger"), 				Geger, 					ARRAY_SIZE(Geger)				 },
							{TEXT("Ghatam and Matkam"), 	Ghatam, 				ARRAY_SIZE(Ghatam)				 },
							{TEXT("Ghungroo"), 				Ghungroo, 				ARRAY_SIZE(Ghungroo)			 },
							{TEXT("Khartal or Chiplya"), 	Khartal, 				ARRAY_SIZE(Khartal)				 },
							{TEXT("Manjeera or jhanj or taal"), Manjeera, 			ARRAY_SIZE(Manjeera)			 },
							{TEXT("Nut"), 					Nut, 					ARRAY_SIZE(Nut)					 },
							{TEXT("Sankarjang"), 			Sankarjang, 			ARRAY_SIZE(Sankarjang)			 },
							{TEXT("Thali"), 				Thali, 					ARRAY_SIZE(Thali)				 },
							{TEXT("Thattukazhi mannai"), 	ThattukazhiMannai, 		ARRAY_SIZE(ThattukazhiMannai)	 },
							{TEXT("Yakshagana bells"), 		YakshaganaBells, 		ARRAY_SIZE(YakshaganaBells)		 } };

node_t ElectronicTanpura_Cost[] = { TEXT("34579"), 	NULL, 0 };
node_t Talameter_Cost[] 		= { TEXT("75863"), 	NULL, 0 };
	
/* LEVEL 2 */
node_t Chordophones[]	= {	{TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Plucked Strings"),   	PluckedStrings, 		ARRAY_SIZE(PluckedStrings)  	 },
							{TEXT("Bowed Strings"),   		BowedStrings, 			ARRAY_SIZE(BowedStrings)  		 },
							{TEXT("Miscellaneous"),   		Chord_Miscellaneous, 	ARRAY_SIZE(Chord_Miscellaneous)  } };

node_t Aerophones[]		= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Single Reed"), 			SingleReed, 			ARRAY_SIZE(SingleReed)			 },
							{TEXT("Double Reed"), 			DoubleReed, 			ARRAY_SIZE(DoubleReed) 			 },
							{TEXT("Flute"), 				Flute, 					ARRAY_SIZE(Flute)				 },
							{TEXT("Bagpipes"), 				Bagpipes, 				ARRAY_SIZE(Bagpipes)			 },
							{TEXT("Free Reed"), 			FreeReed, 				ARRAY_SIZE(FreeReed)			 },
							{TEXT("Free Reed and Bellows"), FreeReedAndBellows, 	ARRAY_SIZE(FreeReedAndBellows)   },
							{TEXT("Brass"), 				Brass, 					ARRAY_SIZE(Brass)				 } };

node_t Membranophones[]	= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Hand Drums"), 			HandDrums, 				ARRAY_SIZE(HandDrums)			 },
							{TEXT("Hand Frame Drums"), 		HandFrameDrums, 		ARRAY_SIZE(HandFrameDrums)		 },
							{TEXT("Stick and Hand Drums"),  StickAndHandDrums, 		ARRAY_SIZE(StickAndHandDrums)	 },
							{TEXT("Stick Drums"), 			StickDrums, 			ARRAY_SIZE(StickDrums)			 } };

node_t Idiophones[]		= { {TEXT("***PleaseSelect***"), 	PleaseSelect, 			ARRAY_SIZE(PleaseSelect)		 },
							{TEXT("Melodic"), 				Melodic, 				ARRAY_SIZE(Melodic)				 },
							{TEXT("Miscellaneous"), 		Idiophones_Miscellaneous, 	ARRAY_SIZE(Idiophones_Miscellaneous) } };

node_t Electronic[] 	= { {TEXT("***PleaseSelect***"), 	 PleaseSelect, 					ARRAY_SIZE(PleaseSelect)			 },
							{TEXT("Electronic tanpura"), 	ElectronicTanpura_Cost, 		ARRAY_SIZE(ElectronicTanpura_Cost)	 },
							{TEXT("Talameter"), 			Talameter_Cost, 				ARRAY_SIZE(Talameter_Cost)			 } };

/* LEVEL 1 */
node_t main_node[]  	= {	{TEXT("Chordophones"),   	Chordophones, 	ARRAY_SIZE(Chordophones)  },
						   	{TEXT("Aerophones"), 		Aerophones, 	ARRAY_SIZE(Aerophones)    },
						   	{TEXT("Membranophones"), 	Membranophones, ARRAY_SIZE(Membranophones)},
							{TEXT("Idiophones"), 	 	Idiophones, 	ARRAY_SIZE(Idiophones)    },
							{TEXT("Electronic"), 		Electronic, 	ARRAY_SIZE(Electronic)	  } }; 		

										   