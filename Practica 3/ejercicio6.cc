#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <limits.h>
#include <time.h>

int main() {

pid_t pid = fork();

if(pid == -1){ //Error
	perror(“fork”);
}
else if(pid == 0){ //Hijo
	int newdir = chdir("/tmp");
	pid_t newsid = setsid();
	
	printf("Soy el hijo\n");
	printf("Identificador de proceso: %i\n", getpid());
	printf("Proceso Padre: %i\n", getppid());
	printf("Grupo de procesos y de sesión: %i\n", getsid(getpid()));
	struct rlimit rlp;
	getrlimit(RLIMIT_NOFILE, &rlp);
	printf("Limite de procesos: %i\n", rlp.rlim_max);

	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	} else {
		perror("getcwd() error");
		return 1;
	}
}
else{ //Padre
	sleep(100);
	printf("Soy el padre\n");
	printf("Identificador de proceso: %i\n", getpid());
	printf("Proceso Padre: %i\n", getppid());
	printf("Grupo de procesos y de sesión: %i\n", getsid(getpid()));
	struct rlimit rlp;
	getrlimit(RLIMIT_NOFILE, &rlp);
	printf("Limite de procesos: %i\n", rlp.rlim_max);

	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	} else {
		perror("getcwd() error");
		return 1;
	}
}

return 0;
}

/*
¿Qué sucede si el proceso padre termina antes que el hijo (observar el PPID del proceso hijo)? 
Si el proceso padre termina antes, el hijo se queda huérfano y lo acoge init
¿Y si el proceso que termina antes es el hijo (observar el estado del proceso hijo con ps)?
Como el hijo termina antes, no se queda huerfano. 
*/