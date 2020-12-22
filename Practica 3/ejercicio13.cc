#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int delete = 1;

void stopdelete(int signal){
if (signal == SIGUSR1) 
	delete = 0;
}

int main(int argc, char **argv) {

if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

struct sigaction sigact;

sigact.sa_handler = stopdelete;

sigaction(SIGUSR1, &sigact, NULL); 

printf("Se pone %s segundos a dormir el ejecutable\n", argv[1]);

sleep(atoi(argv[1]));

if (delete == 1) {
	remove(argv[0]);
	printf("Se ha borrado el ejecutable\n");
}
else {
	printf("No se ha borrado el ejecutable\n");
}

return 0;
}