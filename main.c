#include <stdio.h>
#include <stdlib.h>

/* 

					/!\ A FAIRE /!\ 

Fonction qui prend un nom de fichier en parametre et qui l'ouvre
Gérer le double étoiles pour le commencement d'un commentaire (/**) possible avec les fonctions ftell?fseek? gérer le seek_cur-2.
Faut-il faire le /// sachant que ça compile pas? 

*/


/*void open_file(FILE *file){
	*file = fopen(*file,"r");
	fclose(*file);
}*/
int main(int argc,char* argv[]){

	/*FILE * test;
	printf("Test\n");
	open_file(test);
	*/
	int car=0,tmp=0,com=0;
	int espace = 0,retouralaligne = 0;
	long curseur = 0;
	FILE* doc = fopen("doc.txt","r");
	if (doc==NULL)
		exit(1);
	else{
		fprintf(doc,"Hello World");
		do{
			if (car == 0)
				tmp = car;
			car = fgetc(doc);

			if(tmp == '/' && car == '*' ){
				printf("COMMENCEMENT COMMENTAIRE\n");
				com = 1;
				printf(" bool com = %d\n",com);
			}
			

			if(car == ' ')
				espace++;
			if(car == '\n')
				retouralaligne++;
			
			if(tmp == '*' && car == '/' && com == 1){
				printf("FERMETURE COMMENTAIRE\n");	
				com = 0;
				printf(" bool com2 = %d\n",com);
			}
			
			tmp = car;
			
		}while(car != EOF);
		
		fclose(doc);
	}

printf("espace = %d , retour a la ligne = %d \n",espace,retouralaligne);
return 0;
}
