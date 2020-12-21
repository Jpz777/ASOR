#include <stdio.h>      
#include <stdlib.h> 

int main(int argc, char **argv) {
if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

if (execvp(argv[1], argv + 1) == -1)
	printf("No se ha ejecutado el comando\n");

printf("El comando terminó de ejecutarse\n");

return 0;
}

//La manera de ejecutar es ./ficheroejecutable "ls -l"
//No se ejecuta el printf dado que el execvp reemplaza la imagen del proceso actual con una nueva imagen del proceso