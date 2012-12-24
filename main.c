#include <stdio.h>
#include <stdlib.h>
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
	
	FILE* doc = fopen("doc.txt","r");
	if (doc==NULL)
		exit(1);
	else{
		fprintf(doc,"Hello World");
		do{
			if (car == 0)
				tmp = car;
			car = fgetc(doc);
			
			if(tmp == '/' && car == '*'){
				printf("COMMENCEMENT COMMENTAIRE\n");
				com = 1;
				printf(" bool com = %d\n",com);
			}
			
			if(tmp == '*' && car == '/' && com == 1){
				printf("FERMETURE COMMENTAIRE\n");	
				com = 0;
				printf(" bool com2 = %d\n",com);
			}
			
			tmp = car;
		
		}while(car != EOF);
		
		fclose(doc);
	}


return 0;
}