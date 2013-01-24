all : docmycode

docmycode : docmycode.o main.o
	gcc -o docmycode docmycode.o main.o 
	
main.o : main.c docmycode.h
	gcc -o main.o -c main.c -W -Wall -ansi 

docmycode.o : docmycode.c
	gcc -o docmycode.o -c docmycode.c -W -Wall -ansi -std=c99

clear: 
	rm -rf *.o