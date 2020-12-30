#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv){

if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

int fd;

fd = open(argv[1], O_WRONLY);

if (fd == -1) {
	printf("No se ha creado el archivo\n");
	return 1;
}

write(fd, argv[1], strlen(argv[1]));
close(fd);

return 0;
}