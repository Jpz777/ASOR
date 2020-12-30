#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){

int p_h[2];
int h_p[2];
char returnlq;

if(pipe(p_h)==-1){ 
	perror("Pipe Failed in p_h"); 
	return 1; 
}

if(pipe(h_p)==-1){ 
	perror("Pipe Failed in h_p"); 
	return 1; 
}

pid_t pid = fork();

if(pid == -1){ //error
	perror("fork");
}
else if(pid == 0){ //hijo

close(p_h[1]);
close(h_p[0]);

char buffer;
int i;

for(i = 0; i <= 10; ++i){
	read(p_h[0], &buffer, 1);
	sleep(1);
	if(i != 10)
		returnlq = 'l';
	else 
		returnlq = 'q';
	write(h_p[1], &returnlq, 1);
}

close(p_h[0]);
close(h_p[1]);

}
else{ //padre

close(p_h[0]);
close(h_p[1]);

char buffer;
char word[256];

while(buffer != 'q'){
	printf("Dame una palabra: ");
	fgets(word, sizeof(word), stdin);
	write (p_h[1], &word, 1);
	read(h_p[0], &buffer, 1);
	printf("He recbido %c\n", buffer);
}

close(p_h[1]);
close(h_p[0]);

}
return 0;
}