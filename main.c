#include <stdio.h>
#include <stdlib.h>
#define MAX_LIGNES 426
#define TAILLE_TAB 100

void init_tab(char tab[MAX_LIGNES]){
	int i =0;
	for(i=0;i<MAX_LIGNES;i++)
		tab[i] = 0;
}

int open_file(char *nom_fichier){
	
	char tab[MAX_LIGNES],tab_fn[TAILLE_TAB],tab_br[TAILLE_TAB],tab_fi[TAILLE_TAB],tab_au[TAILLE_TAB],tab_vers[TAILLE_TAB];
	char tab_date[TAILLE_TAB],tab_param[TAILLE_TAB],tab_rt[TAILLE_TAB],tab_bug[TAILLE_TAB],tab_det[TAILLE_TAB];
	int com_slash = 0,com_normal=0;
	int i=0;
	int au=0,pm = 0,date = 0,rt = 0,bug = 0,vers = 0,fn=0,j=0,br = 0,fi=0,det = 0;
	FILE *file = NULL;
	file = fopen(nom_fichier,"r");
	printf("Openning %s... ",nom_fichier);
	getchar();
	if(file == NULL){
		fprintf(stderr,"Error : This file don't exist \n");
		return -1;
	}
	else{
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
					puts("Prototype de la fonction..");
					fn = 1;
					while(fn == 1){
						tab_fn[j] = fgetc(file);
						
						if(tab_fn[j] == '\n'){
							fn=0;
							com_slash = 0;
						}
						printf("%c",tab_fn[j]);		
						j++;
					};
				}
				if(tab[i-5] == '\\' && tab[i-4] == 'b' && tab[i-3] == 'r' && tab[i-2] == 'i' && tab[i-1] == 'e' && tab[i] == 'f'){
					puts("Brief..");
					j=0;
					br = 1;
					while(br == 1){
						tab_br[j] = fgetc(file);
						printf("%c",tab_br[j]);	
						if(tab_br[j] == '\n')
						{
							br = 0;
							com_slash = 0;
						}
						j++;
					}
				}
				if(tab[i-5] == '\\' && tab[i-4] == 'p' && tab[i-3] == 'a' && tab[i-2] == 'r' && tab[i-1] == 'a' && tab[i] == 'm'){
					puts("Paramètres..");
					j=0;
					pm = 1;
					while(pm == 1){
						tab_param[j] = fgetc(file);
						printf("%c",tab_param[j]);	
						if(tab_param[j] == '\n')
						{
							pm = 0;
							com_slash = 0;
						}
						j++;
					}
				}
				if(tab[i-6] == '\\' && tab[i-5] == 'a' && tab[i-4] == 'u' && tab[i-3] == 't' && tab[i-2] == 'h' && tab[i-1] == 'o' && tab[i] == 'r'){
					puts("Author..");
					j=0;
					au = 1;
					while(au == 1){
						tab_au[j] = fgetc(file);
						printf("%c",tab_au[j]);	
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
					puts("Version..");
					j=0;
					vers = 1;
					while(vers == 1){
						
						tab_vers[j] = fgetc(file);
						
						printf("%c",tab_vers[j]);	
						
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
					puts("Details..");
					j=0;
					det = 1;

					while(det == 1){
						
						tab_det[j] = fgetc(file);
						
						printf("%c",tab_det[j]);	
						
						if(tab_det[j] == '\n'){
							com_slash = 0;
							det = 0;
						}
						j++;
					}
				}
				if(tab[i-4] == '\\' && tab[i-3] == 'd' && tab[i-2] == 'a' && tab[i-1] == 't' && tab[i] == 'e'){
					puts("Date..");
					j=0;
					date = 1;
					while(date == 1){
						tab_date[j] = fgetc(file);

						printf("%c",tab_date[j]);

						if(tab_date[j] == '\n'){
							date = 0;
							com_slash = 0;
						}
						
						j++;
					}
				}
				if(tab[i-4] == '\\' && tab[i-3] == 'f' && tab[i-2] == 'i' && tab[i-1] == 'l' && tab[i] == 'e'){
					puts("File..");
					j=0;
					fi = 1;
					while(fi == 1){
						tab_fi[j] = fgetc(file);

						printf("%c",tab_fi[j]);	
						
						if(tab_fi[j] == '\n'){
							fi = 0;
							com_slash = 0;
						}
						j++;
					}
				}
				if(tab[i-3] == '\\' && tab[i-2] == 'b' && tab[i-1] == 'u' && tab[i] == 'g' ){
					puts("Bug..");
					j=0;
					bug = 1;
					while(bug == 1){
						tab_bug[j] = fgetc(file);

						printf("%c",tab_bug[j]);	
						
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
					puts("Return..");
					j=0;
					rt = 1;
					while(rt == 1){
						tab_rt[j] = fgetc(file);
						printf("%c",tab_rt[j]);	
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
	return 0;
}

int main(int argc,char *argv[]){
	int i;
	int paramfichieron = 1;
	/*
	********************************************* 
	Pour tester les fichiers entrer en paramètres 
	*********************************************
	*/
	for(i=argc;i>0;i--){
		argv++;
		argc--;
		if(argc == 0 && paramfichieron == 1){
			fprintf(stderr,"Error : No file put on paramater\n");
			return -1;
		}
		if(argc > 0){
			paramfichieron = 0;
			open_file(*argv);
		}
	}
	
	/*
	*****************
	Fin Test Fichiers
	*****************
	*/
	
	
	return 0;
}