#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char **argv)
{
unsigned int maj, min;

if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

struct stat fileStat;

if(stat(argv[1],&fileStat) < 0) {
	printf("No es un fichero o directorio\n");   
	return 1;
}

maj = major(fileStat.st_dev);
printf("Major: %i\n", maj);

min = minor(fileStat.st_dev);
printf("Minor: %i\n", min);

printf("Inodo: %d\n",fileStat.st_ino);

printf("Tipo fichero: %d\n",fileStat.st_mode);

if((fileStat.st_mode & S_IFMT) == S_IFREG){
	printf("Es un fichero ordinario.\n");
}else if((fileStat.st_mode & S_IFMT) == S_IFDIR){
	printf("Es un directorio.\n");
}else if((fileStat.st_mode & S_IFMT) == S_IFLNK){
	printf("Es un enlace simbolico.\n");
}

char timer[80]; 
strftime(timer, 80, "%A, %d de %B de %Y, %R", localtime(&fileStat.st_atime));
printf("Ultima vez que se accedio al fichero: %s\n",timer);

/*
st_mtime: ultima modificacion de datos del archivo
st_ctime: ultimo cambio de estado del archivo
*/

return 0;		
}