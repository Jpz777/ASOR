#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

int fd, destino;

fd = open(argv[1], O_CREAT| O_RDWR, 0640);

if (fd == -1) {
	printf("No se ha creado el archivo\n");
	return 1;
}

destino = dup2(fd, 1);

printf("Hola mundo\n");
printf("Adios mundo\n");

int a, b, c;
a = 10;
b = 20;
c = a + b;
printf ("A = %i + B = %i: %i\n" , a, b, c);
printf("Error: %s", strerror(1));

close(fd);

/*
 ls> dirlist 2> & 1 : manda tanto la salida del comando como los errores al fichero dirlist
 ls 2> & 1> dirlist : manda solo la salida del comando al fichero dirlist, porque los errores se mandan primero y los pisa el comando.
*/

return 1;
}