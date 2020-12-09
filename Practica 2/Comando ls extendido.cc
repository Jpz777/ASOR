#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

DIR *dir;
struct dirent* d;
struct stat fileStat;
unsigned long int totalSizeFile = 0;

dir = opendir(argv[1]);

if (dir == NULL){
	printf("Error: No se puede abrir el directorio\n");
	return 1;
}

if(stat(argv[1],&fileStat) < 0)    
	return 1;

while(d = readdir(dir)){
        lstat(d->d_name, &fileStat);
		
		if((fileStat.st_mode & S_IFMT) == S_IFREG){
			printf("%s *\n", d->d_name);
			totalSizeFile += fileStat.st_size;
		}else if((fileStat.st_mode & S_IFMT) == S_IFDIR){
			printf("%s /\n", d->d_name);
		}else if((fileStat.st_mode & S_IFMT) == S_IFLNK){
			char *path = malloc(sizeof(char)*(strlen(argv[1]) + strlen(d->d_name) + 3));
			strcpy(path, argv[1]);
			strcat(path, "/");
			strcat(path, d->d_name);
			char *linkname = malloc(fileStat.st_size + 1);
			readlink(path, linkname, fileStat.st_size + 1);
			printf("%s -> %s\n", d->d_name, linkname);
			totalSizeFile += fileStat.st_size;
		}
}

printf("El peso total es de %i kb\n", totalSizeFile/1024);

return 0;
}