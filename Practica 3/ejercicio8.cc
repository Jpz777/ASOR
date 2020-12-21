#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {

if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

pid_t pid = fork();

if(pid == -1){ //Error
	perror("fork");
}
else if(pid == 0){ //Hijo
	printf("El hijo se ha ejecutado\n");

	pid_t newsid = setsid();
	
	int outestandarfile = open("/tmp/daemon.out", O_CREAT| O_RDWR, 0640);
	int errorfile = open("/tmp/daemon.err", O_CREAT | O_RDWR, 0640);
	int inestandarfile = open("/dev/null", O_CREAT | O_RDWR, 0640);	
	
	if(dup2(outestandarfile, STDOUT_FILENO) == -1){
		perror("Fallo en el dup2");
		return 0;
	}
	if(dup2(errorfile, STDERR_FILENO) == -1){
		perror("Fallo en el dup2");
		return 0;
	}
	if(	dup2(inestandarfile, STDIN_FILENO) == -1){
		perror("Fallo en el dup2");
		return 0;
	}
	
	if (execvp(argv[1], argv + 1) == -1)
		perror("No se ha ejecutado el comando");
	
}
else{ //Padre
	printf("El padre se ha ejecutado\n");
}

return 0;
}