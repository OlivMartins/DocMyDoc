#include <stdio.h>
#include <stdlib.h>
#include "docmycode.h"


void init_tab(char tab[MAX_LIGNES]){
	int i =0;
	for(i=0;i<MAX_LIGNES;i++)
		tab[i] = 0;
}

				/****************************************************************************************************
															DISPLAY
				****************************************************************************************************/

int display_tab(char tab[TAILLE_TAB],char *nom){
	int i;
	printf("%s...\n",nom);
	for(i = 1;i<TAILLE_TAB;i++){
		if(tab[i] == '\n'){
			puts("");
			return 0;
		}
		
		if (tab[i] >= 65 && tab[i] <= 122)
			printf("%c",tab[i]);
		if(tab[i] == '(' || tab[i] == ')' || tab[i] == '.' || (tab[i] == ' ' && tab[i+1] != ' ') || tab[i] == '\'' || (tab[i] >= '0' && 
			tab[i] <= '9')){
				printf("%c",tab[i]);
		}
		if(tab[i] < 65 && tab[i] > 122 && tab[i] != '(' && tab[i] != ')')
			printf("");
	}
	
	return 0;
}
/*void is_a_com(char tab[TAILLE_TAB]){
	int i=0;
	int com_slash = 0,com_normal=0;
	for(i=0;i<MAX_LIGNES;i++){
		if(tab1[i-2] == '/' && tab1[i-1] == '/' && tab[i] == '/'){
				// Gérer le cas ou on est déjà dans un com et qu'il y a 3 slash
			if(com_slash == 0 && com_normal == 0){
				com_slash = 1;

				//puts("COMMENTAIRE AVEC TRIPLE /");
			}
			else{
				//puts("On est déjà dans un commentaire");
			}
		}
		if(tab1[i-2] == '/' && tab1[i-1] == '*' && tab[i] == '*'){
			com_normal = 1;
			//puts("COMMENTAIRE NORMAL");
		}
		if(tab1[i-1] == '*' && tab[i] == '/'){
			com_normal = 0;
			//puts("FIN COMMENTAIRE NORMAL");
		}
		if(tab[i] == '\n'){
			//puts("Retour a la ligne");
			com_slash = 0;
		}
		// Commencement de l'analyse du fichier passer en paramètre
		if(com_slash == 1 || com_normal == 1){
			analyze_tab(tab);
		}
	}
	
}*/

int open_file(char *nom_fichier){
	
	char tab1[MAX_LIGNES];
	
	char tab_det[300];
	char tab[10][TAILLE_TAB];
	int com_slash = 0,com_normal=0;
	int i=0,j=0;

	/** 
	
	Le tableau temporaire sert à afficher le texte des balises spéciales utilisées plusieurs fois dans le code
		ex: \oncontinue int func() et suivi de sa pour la function() dans doc.txt
	Initialisation du tableau temporaire 
	
	*/
	int tmp[9];
	for(i=0;i<10;i++)
		tmp[i] = 0;
	

	int det = 0,k=4;
	int oncontinue = 0;
	FILE *file = NULL;
	file = fopen(nom_fichier,"r");
	printf("Openning %s... ",nom_fichier);
	getchar();
	if(file == NULL){
		fprintf(stderr,"Error : This file don't exist \n");
		return -1;
	}
	else{
		init_tab(&tab1[0]);
		puts("OK ! \nAnalyse en cours...");
		while(i<MAX_LIGNES){

			tab1[i] = fgetc(file);
	
			if(tab1[i-2] == '/' && tab1[i-1] == '/' && tab1[i] == '/'){
				// Gérer le cas ou on est déjà dans un com et qu'il y a 3 slash
				if(com_slash == 0 && com_normal == 0){
					com_slash = 1;
					//puts("COMMENTAIRE AVEC TRIPLE /");
				}
				else{
					//puts("On est déjà dans un commentaire");
				}
			}
			if(tab1[i-2] == '/' && tab1[i-1] == '*' && tab1[i] == '*'){
				com_normal = 1;
				//puts("COMMENTAIRE NORMAL");
			}
			if(tab1[i-1] == '*' && tab1[i] == '/'){
				com_normal = 0;
				//puts("FIN COMMENTAIRE NORMAL");
			}
			if(tab1[i] == '\n'){
				//puts("Retour a la ligne");
				com_slash = 0;
			}
			
			// Beginning of the analyze of file with parameters 
			if(com_slash == 1 || com_normal == 1){
				
				/****************************************************************************************************
															FUNCTION
				****************************************************************************************************/

				if(tab1[i-2] == '\\' && tab1[i-1] == 'f' && tab1[i] == 'n'){
					//puts("Prototype de la fonction..");
					oncontinue = 1;
					j=0;

					if(tmp[0] != 0 && j == 0)
						j = tmp[0];
					
					while(oncontinue == 1){

						tab[0][j] = fgetc(file);
						if(tab[0][j] == '\n'){
							oncontinue = 0;
							com_slash = 0;
							tmp[0] = j;
						}
						j++;
						
					};
				}

				/****************************************************************************************************
															BRIEF
				****************************************************************************************************/

				if(tab1[i-5] == '\\' && tab1[i-4] == 'b' && tab1[i-3] == 'r' && tab1[i-2] == 'i' && tab1[i-1] == 'e' && tab1[i] == 'f'){
					//puts("Brief..");
					j=0;
					oncontinue = 1;
					if(tmp[1] != 0 && j == 0)
						j = tmp[1];
					while(oncontinue == 1){
						tab[1][j] = fgetc(file);
							
						if(tab[1][j] == '\n')
						{
							oncontinue = 0;
							com_slash = 0;
							tmp[1] = j;
						}
						j++;
					}
				}

				/****************************************************************************************************
															Parameters
				****************************************************************************************************/

				if(tab1[i-5] == '\\' && tab1[i-4] == 'p' && tab1[i-3] == 'a' && tab1[i-2] == 'r' && tab1[i-1] == 'a' && tab1[i] == 'm'){
					//puts("Paramètres..");
					j=0;
					oncontinue = 1;
					if(tmp[2] != 0 && j == 0)
						j = tmp[2];
					while(oncontinue == 1){
						tab[2][j] = fgetc(file);
						
						if(tab[2][j] == '\n')
						{
							oncontinue = 0;
							com_slash = 0;
							tmp[2] = j;
						}
						/*if(tab_param[j] == '\t' || (tab_param[j-1] == ' ' && tab_param[j] == ' '))
						{	
							
							
						}*/
						j++;
					}
				}


				/****************************************************************************************************
															AUTHOR
				****************************************************************************************************/


				if(tab1[i-6] == '\\' && tab1[i-5] == 'a' && tab1[i-4] == 'u' && tab1[i-3] == 't' && tab1[i-2] == 'h' && tab1[i-1] == 'o' 
					&& tab1[i] == 'r'){
					//puts("Author..");
					j=0;
					oncontinue = 1;
					if(tmp[3] != 0 && j == 0)
						j = tmp[3];
					while(oncontinue == 1){
						tab[3][j] = fgetc(file);
						if(tab[3][j] == '\n')
						{
							oncontinue = 0;
							com_slash = 0;
							tmp[3] = j;
						}
						j++;
					}
				}

				/****************************************************************************************************
															VERSION
				****************************************************************************************************/

				if(tab1[i-7] == '\\' && tab1[i-6] == 'v' && tab1[i-5] == 'e' && tab1[i-4] == 'r' && tab1[i-3] == 's' && tab1[i-2] == 'i' && 
					tab1[i-1] == 'o' && tab1[i] == 'n'){
					//puts("Version..");
					j=0;
					oncontinue = 1;

					if(tmp[4] != 0 && j == 0)
						j = tmp[4];

					while(oncontinue == 1){
						
						tab[4][j] = fgetc(file);
						if(tab[4][j] == '\n')
						{
							oncontinue = 0;
							com_slash = 0;
							tmp[4] = j;
						}
						j++;
					}
				}

				/****************************************************************************************************
															DETAILS
				****************************************************************************************************/

				if(tab1[i-7] == '\\' && tab1[i-6] == 'd' && tab1[i-5] == 'e' && tab1[i-4] == 't' && tab1[i-3] == 'a' && tab1[i-2] == 'i' && 
					tab1[i-1] == 'l' && tab1[i] == 's'){
					//puts("Details..");
					j=0;
					det = 1;
					

					while(det == 1){
						
						tab_det[j] = fgetc(file);
						
						/* 
						Dans le cas ou com_slash = 1 :
						Si il y a un retour a la ligne mais que les trois prochains caractères sont le slash alors on continue le details 
						car c'est toujours un commentaire
						/!\ A voir pour le com_normal /!\
						*/

						if(tab_det[j] == '\n' && (tab_det[j+1] == '/' && tab_det[j+2] == '/' && tab_det[j+3] == '/')   ){
							
								while(tab_det[j+k] != '\n'){
									tab_det[j+k] = fgetc(file);
									
									if(tab_det[j+k] == '\n'){
										det = 0;
										com_slash = 0;			
									}
									k++;
								}

							}
						if(tab_det[j] == '\n')
							det = 0;
						if(tab_det[j] == '\\')
							det = 0;
						j++;
					}
				}

				/****************************************************************************************************
															DATE
				****************************************************************************************************/

				if(tab1[i-4] == '\\' && tab1[i-3] == 'd' && tab1[i-2] == 'a' && tab1[i-1] == 't' && tab1[i] == 'e'){
					//puts("Date..");
					j=0;
					oncontinue = 1;
					if(tmp[5] != 0 && j == 0)
						j = tmp[5];
					while(oncontinue == 1){
						tab[5][j] = fgetc(file);

						if(tab[5][j] == '\n'){
							oncontinue = 0;
							com_slash = 0;
							tmp[5] = j;
						}
						
						j++;
					}
					
				}

				/****************************************************************************************************
															FILE
				****************************************************************************************************/

				if(tab1[i-4] == '\\' && tab1[i-3] == 'f' && tab1[i-2] == 'i' && tab1[i-1] == 'l' && tab1[i] == 'e'){
					//puts("File..");
					j=0;
					oncontinue = 1;
					if(tmp[6] != 0 && j == 0)
						j = tmp[6];
					while(oncontinue == 1){
						tab[6][j] = fgetc(file);
						if(tab[6][j] == '\n'){
							oncontinue = 0;
							com_slash = 0;
							tmp[6] = j;
						}
						j++;
					}
					
				}

				/****************************************************************************************************
															BUG
				****************************************************************************************************/

				if(tab1[i-3] == '\\' && tab1[i-2] == 'b' && tab1[i-1] == 'u' && tab1[i] == 'g' ){
					//puts("Bug..");
					j=0;
					oncontinue = 1;
					if(tmp[7] != 0 && j == 0)
						j = tmp[7];
					while(oncontinue == 1){
						tab[7][j] = fgetc(file);
						if(tab[7][j] == '\n'){
							oncontinue = 0;
							com_slash = 0;
							tmp[7] = j;
						}
						j++;
					}
				}

				/****************************************************************************************************
															RETURN
				****************************************************************************************************/

				if(tab1[i-6] == '\\' && tab1[i-5] == 'r' && tab1[i-4] == 'e' && tab1[i-3] == 't' && tab1[i-2] == 'u' && tab1[i-1] == 'r' 
					&& tab1[i] == 'n'){
					//puts("Return..");
					j=0;
					oncontinue = 1;
					if(tmp[8] != 0 && j == 0)
						j = tmp[8];
					while(oncontinue == 1){
						tab[8][j] = fgetc(file);
							
						if(tab[8][j] == '\n')
						{
							oncontinue = 0;
							com_slash = 0;
							tmp[8] = j;
						}
						j++;
					}
				}

			}
			i++;
		};
	} 
	fclose(file);
	
	display_tab(tab[6],"File");
	
	display_tab(tab[0],"Function");
	
	display_tab(tab[3],"Author");
	
	display_tab(tab[5],"Date");
	
	display_tab(tab[7],"Bug");
	
	display_tab(tab[1],"Brief");
	
	display_tab(tab[2],"Paramaters");

	display_tab(tab_det,"Details");
	
	display_tab(tab[4],"Version");

	display_tab(tab[8],"Return");


	
	return 0;

}