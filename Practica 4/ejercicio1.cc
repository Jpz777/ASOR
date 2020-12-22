#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv){

if(argc != 5) {
	printf("Se necesitan cinco parametros\n");
	return 1;
}

int pipefd[2];
char *comand1[] = {argv[1], argv[2], NULL};
char *comand2[] = {argv[3], argv[4], NULL};

if(pipe(pipefd)==-1){ 
	perror("Pipe Failed"); 
	return 1; 
}

pid_t pid = fork();

if(pid == -1){ //error
	perror("fork");
}
else if(pid == 0){ //hijo
printf("Soy el hijo\n");

close(pipefd[1]);

dup2(pipefd[0], STDOUT_FILENO);

if(execvp(comand2[0], comand2) == -1){
	printf("El hijo no se ha ejecutado\n");
	return 1;
}
else{ 
	printf("El hijo se ha ejecutado\n");
}

}
else{ //padre
printf("Soy el padre\n");

close(pipefd[0]);

dup2(pipefd[1], STDIN_FILENO);

if(execvp(comand1[0], comand1) == -1){
	printf("El padre no se ha ejecutado\n");
	return 1;
}
else {
	printf("El padre se ha ejecutado\n");
}

}
  
}