#include <stdlib.h>   /* Pour la fonction system. */
#include <stdio.h>
#include "docmycode.h"


/*


/!\ Mieux gérer le \param et le \details /!\

A Voir :
	- si on peut pas optimiser les tab[i-4] etc... En faisant des switch peut être
	- Essayer d'optimiser tout les tableaux.. y en a trop et ça se répète très probable qu'il y est une optimisation à faire
	peut être avec une fonction qui prend un tableau en paramètre mais problème avec le fgetc faudrait ouvrir le fichier dans la fonction

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