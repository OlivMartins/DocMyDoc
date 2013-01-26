#include <stdio.h>
#include <stdlib.h>
#include "docmycode.h"


void init_tab(char tab[MAX_LIGNES]){
	int i =0;
	for(i=0;i<MAX_LIGNES;i++)
		tab[i] = 0;
}
int display_tab(char tab[TAILLE_TAB]){
	int i;
	for(i = 0;i<TAILLE_TAB;i++){
		if(tab[i] == '\n'){
			puts("");
			return 0;
		}
		if(tab[i] == ' ' && tab[i+1] == ' ')
			printf("");
		else{
			printf("%c",tab[i]);
		}
	}
	
	return 0;
}
void is_a_com(char tab[TAILLE_TAB]){
	int i=0;
	int com_slash = 0,com_normal=0;
	for(i=0;i<MAX_LIGNES;i++){
		if(tab[i-2] == '/' && tab[i-1] == '/' && tab[i] == '/'){
				// Gérer le cas ou on est déjà dans un com et qu'il y a 3 slash
			if(com_slash == 0 && com_normal == 0){
				com_slash = 1;

				//puts("COMMENTAIRE AVEC TRIPLE /");
			}
			else{
				//puts("On est déjà dans un commentaire");
			}
		}
		if(tab[i-2] == '/' && tab[i-1] == '*' && tab[i] == '*'){
			com_normal = 1;
			//puts("COMMENTAIRE NORMAL");
		}
		if(tab[i-1] == '*' && tab[i] == '/'){
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
	
}

int open_file(char *nom_fichier){
	
	char tab[MAX_LIGNES],tab_fn[TAILLE_TAB],tab_br[TAILLE_TAB],tab_fi[TAILLE_TAB],tab_au[TAILLE_TAB],tab_vers[TAILLE_TAB];
	char tab_date[TAILLE_TAB],tab_param[TAILLE_TAB],tab_rt[TAILLE_TAB],tab_bug[TAILLE_TAB],tab_det[300];
	int com_slash = 0,com_normal=0;
	int i=0;
	int au=0,pm = 0,date = 0,rt = 0,bug = 0,vers = 0,fn=0,j=0,br = 0,fi=0,det = 0,k=4;
	FILE *file = NULL;
	file = fopen(nom_fichier,"r");
	printf("Openning %s... ",nom_fichier);
	getchar();
	if(file == NULL){
		fprintf(stderr,"Error : This file don't exist \n");
		return -1;
	}
	/*else{
		init_tab(&tab[0]);
		puts("OK ! \nAnalyse en cours...");
		while(i<MAX_LIGNES){

			tab[i] = fgetc(file);
	
			if(tab[i-2] == '/' && tab[i-1] == '/' && tab[i] == '/'){
				// Gérer le cas ou on est déjà dans un com et qu'il y a 3 slash
				if(com_slash == 0 && com_normal == 0){
					com_slash = 1;
					//puts("COMMENTAIRE AVEC TRIPLE /");
				}
				else{
					//puts("On est déjà dans un commentaire");
				}
			}
			if(tab[i-2] == '/' && tab[i-1] == '*' && tab[i] == '*'){
				com_normal = 1;
				//puts("COMMENTAIRE NORMAL");
			}
			if(tab[i-1] == '*' && tab[i] == '/'){
				com_normal = 0;
				//puts("FIN COMMENTAIRE NORMAL");
			}
			if(tab[i] == '\n'){
				//puts("Retour a la ligne");
				com_slash = 0;
			}
			// Commencement de l'analyse du fichier passer en paramètre
			if(com_slash == 1 || com_normal == 1){
				
				if(tab[i-2] == '\\' && tab[i-1] == 'f' && tab[i] == 'n'){
					//puts("Prototype de la fonction..");
					fn = 1;
					while(fn == 1){
						tab_fn[j] = fgetc(file);
						
						if(tab_fn[j] == '\n'){
							fn=0;
							com_slash = 0;
						}
						
						j++;
					};
				}
				if(tab[i-5] == '\\' && tab[i-4] == 'b' && tab[i-3] == 'r' && tab[i-2] == 'i' && tab[i-1] == 'e' && tab[i] == 'f'){
					//puts("Brief..");
					j=0;
					br = 1;
					while(br == 1){
						tab_br[j] = fgetc(file);
							
						if(tab_br[j] == '\n')
						{
							br = 0;
							com_slash = 0;
						}
						j++;
					}
				}
				if(tab[i-5] == '\\' && tab[i-4] == 'p' && tab[i-3] == 'a' && tab[i-2] == 'r' && tab[i-1] == 'a' && tab[i] == 'm'){
					//puts("Paramètres..");
					j=0;
					pm = 1;
					while(pm == 1){
						tab_param[j] = fgetc(file);
						
						if(tab_param[j] == '\n')
						{
							pm = 0;
							com_slash = 0;
						}
						/*if(tab_param[j] == '\t' || (tab_param[j-1] == ' ' && tab_param[j] == ' '))
						{	
							
							
						}*/
/*						j++;
					}
				}
/*				if(tab[i-6] == '\\' && tab[i-5] == 'a' && tab[i-4] == 'u' && tab[i-3] == 't' && tab[i-2] == 'h' && tab[i-1] == 'o' && tab[i] == 'r'){
					//puts("Author..");
					j=0;
					au = 1;
					while(au == 1){
						tab_au[j] = fgetc(file);
						if(tab_au[j] == '\n')
						{
							au = 0;
							com_slash = 0;
						}
						j++;
					}
				}
				if(tab[i-7] == '\\' && tab[i-6] == 'v' && tab[i-5] == 'e' && tab[i-4] == 'r' && tab[i-3] == 's' && tab[i-2] == 'i' && 
					tab[i-1] == 'o' && tab[i] == 'n'){
					//puts("Version..");
					j=0;
					vers = 1;
					while(vers == 1){
						
						tab_vers[j] = fgetc(file);
						if(tab_vers[j] == '\n')
						{
							vers = 0;
							com_slash = 0;
						}
						j++;
					}
				}
				if(tab[i-7] == '\\' && tab[i-6] == 'd' && tab[i-5] == 'e' && tab[i-4] == 't' && tab[i-3] == 'a' && tab[i-2] == 'i' && 
					tab[i-1] == 'l' && tab[i] == 's'){
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
/*						if(tab_det[j] == '\n' && (tab_det[j+1] == '/' && tab_det[j+2] == '/' && tab_det[j+3] == '/')   ){
							
								while(tab_det[j+k] != '\n'){
									tab_det[j+k] = fgetc(file);
									
									if(tab_det[j+k] == '\n'){
										det = 0;
										com_slash = 0;
										
									}
									k++;
								}
							}
						
						if(tab_det[j] == '\\')
							det = 0;
						j++;
					}
				}
				if(tab[i-4] == '\\' && tab[i-3] == 'd' && tab[i-2] == 'a' && tab[i-1] == 't' && tab[i] == 'e'){
					//puts("Date..");
					j=0;
					date = 1;
					while(date == 1){
						tab_date[j] = fgetc(file);

						if(tab_date[j] == '\n'){
							date = 0;
							com_slash = 0;
						}
						
						j++;
					}
					
				}
				if(tab[i-4] == '\\' && tab[i-3] == 'f' && tab[i-2] == 'i' && tab[i-1] == 'l' && tab[i] == 'e'){
					//puts("File..");
					j=0;
					fi = 1;
					while(fi == 1){
						tab_fi[j] = fgetc(file);
						if(tab_fi[j] == '\n'){
							fi = 0;
							com_slash = 0;
						}
						j++;
					}
					
				}
				if(tab[i-3] == '\\' && tab[i-2] == 'b' && tab[i-1] == 'u' && tab[i] == 'g' ){
					//puts("Bug..");
					j=0;
					bug = 1;
					while(bug == 1){
						tab_bug[j] = fgetc(file);

					
						
						if(tab_bug[j] == '\n'){
							bug = 0;
							com_slash = 0;
						}
						j++;
					}
				}
				// return 
				if(tab[i-6] == '\\' && tab[i-5] == 'r' && tab[i-4] == 'e' && tab[i-3] == 't' && tab[i-2] == 'u' && tab[i-1] == 'r' 
					&& tab[i] == 'n'){
					//puts("Return..");
					j=0;
					rt = 1;
					while(rt == 1){
						tab_rt[j] = fgetc(file);
						//printf("%c",tab_rt[j]);	
						if(tab_rt[j] == '\n')
						{
							rt = 0;
							com_slash = 0;
						}
						j++;
					}
				}

			}
			i++;
		};
	} 
	fclose(file);
	*/
/*	display_tab(tab_fn);
	display_tab(tab_au);
	display_tab(tab_date);
	display_tab(tab_fi);
	display_tab(tab_bug);
	display_tab(tab_br);
	display_tab(tab_det);
	display_tab(tab_vers);
*/

	fclose(file);
	return 0;

}