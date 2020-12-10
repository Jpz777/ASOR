#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

struct flock fl,fl2;

fl2.l_type   = F_UNLCK;  /* unlock */
fl2.l_whence = SEEK_SET; /* beginning of file */
fl2.l_start  = 0;        /* offset from l_whence */
fl2.l_len    = 0;        /* length, 0 = to EOF */
fl2.l_pid    = getpid(); /* PID */	
	
fl.l_type   = F_WRLCK;  /* read/write lock */
fl.l_whence = SEEK_SET; /* beginning of file */
fl.l_start  = 0;        /* offset from l_whence */
fl.l_len    = 0;        /* length, 0 = to EOF */
fl.l_pid    = getpid(); /* PID */	

fcntl(fd, F_GETLK, &fl2);
if(fl2.l_type!=F_UNLCK)
{
	printf("Esta bloqueado");
}
else
{
	printf("No esta bloqueado\n");
	fcntl(fd, F_SETLKW, &fl);
	time_t rawtime = time(NULL);
	char timer[80]; 
	strftime(timer, 80, "%A, %d de %B de %Y, %R\n", localtime(&rawtime));
	write(fd,timer, strlen(timer));
	sleep(3);
}
printf("Se libera el cerrojo \n");
fl.l_type   = F_UNLCK;
fcntl(fd, F_SETLK, &fl); 

close(fd);

return 1;
}