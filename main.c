#include <stdlib.h>   /* Pour la fonction system. */
#include <stdio.h>
#include "docmycode.h"


/*


/!\ Mieux gérer le \param et le \details /!\
/!\ Faire une fonction qui supprime les espaces, tabulations inutiles /!\
/!\ Faire une fonction qui prend en paramètre un tableau et affiche son contenu /!\
/!\ Si tab[i] == '\\' on appelle une fonction qui analyse ce qu'il y a après jusqu'à \n (sauf pour details cas particulier) /!\
/!\ Faire une fonction pour reconnaitre quel type de commentaire on a affaire : avec /// ou / ** ? /!\
A Voir :
	- si on peut optimiser les tab[i-4] etc... En faisant des switch? fonctions comprenant un tableau en paramètre ? => avec les fonctions
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