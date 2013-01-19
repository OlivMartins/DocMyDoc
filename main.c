#include <stdio.h>
#include <stdlib.h>
#define MAX 100
/* 

					/!\ A FAIRE /!\ 


Paquet Debian : Bon tuto sur http://www.siteduzero.com/informatique/tutoriels/creer-un-paquet-deb/le-contenu-du-paquet
La configuration du control à revoir : qu'est-ce qui faut mettre au paramètre Depends?

Approfondir le projet c:
	/!\ Priorité /!\
		Faire des fonctions pour diminuer le gros problème en sous problèmes dc nvx fichier fonctions.c dc makefile
	
	le prof veut faire docmydoc fichier1.c fichier2.c fichier3.c
	- Peut être commencer par prendre en compte les noms des fichiers (avec argc et argv? a voir)
	- Voir les \ avec plus de deux caractères car \fn fonctionne mais \brief pas encore gérer. C'est fait de mannière "gourou"
	
Pour faire fonctionner les /// cmd : gcc fichier.c -Wall -ansi -std=c99 

*/

void init_tab(int tab[MAX]){
	int i =0;
	for(i=0;i<MAX;i++)
		tab[i] = 0;
}

void affichage(int tab[MAX]){
	int i=0;
	
	for(i=0;i<MAX;i++){
		if(tab[i] == 0){
			i++;
		}
		else{
			printf("tab[%d] = %d \n",i,tab[i]);
		}
	}
	
}
												
	
// Lecture d'un fichier avec la chaine entrer en paramètre du fichier : 
/*int open_file(char *nom_fichier){
	FILE *file = NULL;
	file = fopen(nom_fichier,"r");
	if(file == NULL){
		fprintf(stderr,"Error : File don't exist \n");
		return -1;
	}
	else{
		printf("Openning %s OK \n",nom_fichier);
	} 
	fclose(file);
	return 0;
}*/
/*

A mettre dans la fonction main pour l'ouverture d'un fichier avec le paramètre argv

for(i=argc;i>0;i--){
		argv++;
		argc--;
		if(argc > 0)
			open_file(*argv);
	}
*/


int main(int argc,char* argv[]){

	int car=0,car_before1=0,com=0,car_after1=0;
	int car_after[7];
	int fn=0,br=0;				
	int tab[MAX];
	int i=0;
	init_tab(&tab[0]);
	affichage(&tab[0]);
													

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
			if((car_before1 == '/' && car == '*') || (car_before1 == '/' && car == '/')){
				car_after1 = fgetc(doc);
				if(car_after1 == car && com == 0){
					printf("COMMENCEMENT COMMENTAIRE\n");
					com = 1;
					
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
							if(tab[i] == '\n')
								fn=1;	
							printf("%c",tab[i]);
							i++;
						}while(fn != 1 && i<100);
						puts("\tFin Fonction");
					}
					/* pour le i de file 
					if(car_after1 == 'i'){

					}
					*/
				}
				if(car_before1 == '\\' && car == 'b'){
					car_after1 == fgetc(doc);
					if(car_after1 == 'r'){
						car_after[0] = fgetc(doc);	
						if(car_after[0] == 'i'){
							car_after[1] = fgetc(doc);
							if(car_after[1] == 'e'){
								car_after[2] = fgetc(doc);
								if(car_after[2] == 'f'){
									puts("Brief spotted");
									do{
										tab[i] = fgetc(doc);
										if(tab[i] == '\n')
											br=1;	
										printf("%c",tab[i]);
										i++;
									}while(br != 1 && i<100);
								}
							}
						}
					}
				}
			}
			if(car_before1 == '*' && car == '/' && com == 1){
				puts("FERMETURE COMMENTAIRE");	
				com = 0;
				return 0;
			}

			car_before1 = car;
		}while(car != EOF);	
		fclose(doc);
	}
return 0;
}
