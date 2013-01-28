#include <stdlib.h>   /* Pour la fonction system. */
#include <stdio.h>
#include "docmycode.h"


/*
************************************************************************************
*																				   *
*								Optimisation v1				 					   *
*																				   *
************************************************************************************

- Plus 150 tableaux, juste un tableau temporaire et un tableau à deux dimensions
- Faire une fonction qui prend en paramètre un tableau et affiche son contenu : done => display_tab
- Création d'une fonction is_a_com mais pas encore utilisé
- Prototype de analyze tab done

************************************************************************************

Optimisation v1 fait le 28/01/2013  


************************************************************************************
*																				   *
*								Optimisation v1.1: A suivre...					   *
*																				   *
************************************************************************************

Ce code se répète en faire une fonction analyze_tab et gérer le tableau en deux dimensions. Peut être en faisant une boucle?

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

- Utiliser les mallocs 
- Si tab[i] == '\\' on appelle une fonction qui analyse ce qu'il y a après jusqu'à \n (sauf pour details cas particulier)
- Améliorer la fonction display_tab 

************************************************************************************


/!\ Mieux gérer le \param et le \details /!\
Faire une fonction qui prend en paramètre un tableau et affiche son contenu : done 

/!\ Si tab[i] == '\\' on appelle une fonction qui analyse ce qu'il y a après jusqu'à \n (sauf pour details cas particulier) /!\ not yet
/!\ Faire une fonction pour reconnaitre quel type de commentaire on a affaire : avec /// ou / ** ? /!\
A Voir :
	- Si on ouvre un fichier et qu'on n'appelle pas fclose peut être qu'on peut manipuler le fichier ouvert. 
	
	
*/


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