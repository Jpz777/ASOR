#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

struct stat fileStat;

if(stat(argv[1],&fileStat) < 0) {
	printf("No es un fichero o directorio\n");   
	return 1;
}

int fd;

char* sys = malloc(sizeof(char)*(5 + strlen(argv[1])));
strcpy(sys, argv[1]);
sys = strcat(sys, ".sym");

char* rig = malloc(sizeof(char)*(5 + strlen(argv[1])));
strcpy(rig, argv[1]);
rig = strcat(rig, ".hard");



if((fileStat.st_mode & S_IFMT) == S_IFREG){
	if (symlink(argv[1], sys) != 0) {
		printf("No se ha creado el enlace simbolico\n");
	}
	if (link(argv[1], rig) != 0) {
		printf("No se ha creado el enlace rigido\n");
	}
}else{
	printf("No es un fichero ordinario\n");
}
return 0;
}