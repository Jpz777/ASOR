#include <stdio.h>      
#include <stdlib.h> 

int main(int argc, char **argv) {
if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

int i;
int lengthargv;

if (system(argv[1]) == -1) 
	printf("No se ha ejecutado el comando\n");

printf("El comando terminó de ejecutarse\n");

return 0;
}

//La manera de ejecutar es ./ficheroejecutable "ls -l"
//Se ejecuta el printf