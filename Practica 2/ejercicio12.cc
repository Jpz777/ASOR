#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

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
printf ("A = %i + B = %i: %i" , a, b, c);

close(fd);

return 1;
}