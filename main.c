#include <stdio.h>
#include <stdlib.h>
#define MAX 100
/* 

					/!\ A FAIRE /!\ 

Pour faire fonctionner les /// cmd : gcc fichier.c -Wall -ansi -std=c99 

*/



												/* Remove for testing the board */
void init_tab(int tab[MAX]){
	int i =0;
	for(i=0;i<MAX;i++)
		tab[i] = 0;
}
void affichage(int tab[MAX]){
	int i=0;
	printf("**********************\n");
	printf("INITIALISATION TABLEAU\n");
	printf("**********************\n");
	for(i=0;i<MAX;i++){
		
		printf("tab[%d] = %d \n",i,tab[i]);
	}
	printf("**********************\n");
	printf("	FIN TABLEAU\n");
	printf("**********************\n");
}
												/* Remove for testing the board2 */

// Création d'un fichier avec la chaine entrer en paramètre du fichier : 
/*void open_file(char *nom_fichier){
	FILE *file=NULL;
	*file = fopen(nom_fichier,"w+"); /!\ ATTENTION EFFACE TOUT LE FICHIER nom_fichier et créer un nouveau avec w+ /!\
	*file = fopen(nom_fichier,"r"); /!\ Lit le fichier nom_fichier mais il doit être crée en amont il ne le crée pas tout seul /!\
	fclose(*file);
}*/
int main(int argc,char* argv[]){

	int car=0,car_before1=0,com=0,car_after1=0;
	int espace = 0,retouralaligne = 0,fn=0;				
	int tab[MAX];
	init_tab(&tab[0]);
	affichage(&tab[0]);
													
	int i=0;
	FILE* doc = fopen("doc.txt","r");
	if (doc==NULL)
		exit(1);
	else{
		
		do{
			
			car = fgetc(doc);

			/* 
				Car = Caractère actuel , car_before1 = car-1 et car_after1 = car+1 j'ai fait sa pour détecter les /**,les /fn
				Ex : 
					- /fn => car_before1 = '/' , car = 'f' , car_after1 = 'n' 
			*/

			if(car_before1 == '/' && car == '*'){
				car_after1 = fgetc(doc);
				if(car_after1 == car && com == 0){
					printf("COMMENCEMENT COMMENTAIRE\n");
					com = 1;
					printf("bool com = %d\n",com);
				}
			}
			/* TEST => /!\ IF CAR = \ WE WANT TO KEEP EVERY CHARACTERE IN A BOARD UP TO THE CHARACTERE \n */
			/*if(com == 1){
				if(car == '\\'){
					do{
						tab[i] = fgetc(doc);
						i++;
						if(tab[i] != ' ' && tab[i] != '*' && tab[i] != 0)
							printf("tab[%d] = %d \n",i,tab[i]);
					}while(tab[i] != 10);
					
				}
			}*/
			if(com == 1 ){
				if(car_before1 == '\\' && car == 'f'){
					car_after1 = fgetc(doc);
					
					if(car_after1 == 'n'){
						puts("\tFonction prototype");
						do{
							tab[i] = fgetc(doc);
							printf("tab[%d] = %c \n",i,tab[i]);
							i++;
							if(i==27)
								
						}while(fn != 1 && i<100);
					}
				}
				if(car == ' ')
					espace++;
				if(car == '\n')
					retouralaligne++;
			}

			if(car_before1 == '*' && car == '/' && com == 1){
				puts("FERMETURE COMMENTAIRE");	
				com = 0;
				printf(" bool com2 = %d\n",com);
				return 0;
			}

			car_before1 = car;
		}while(car != EOF);	
		fclose(doc);
	}
return 0;
}
