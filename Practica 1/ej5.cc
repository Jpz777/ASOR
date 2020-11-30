#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

struct utsname unameData;

int main(){
	if(uname(&unameData) == 0){
		printf ("Nombre sistema %s\n", unameData.sysname);
		printf ("Nombre nodo %s\n", unameData.nodename);
		printf ("Fecha sistema %s\n", unameData.release);
		printf ("Version sistema %s\n", unameData.version);
		printf ("Identificador hardware %s", unameData.machine);
	}
	else
		printf("Error: %s", strerror(errno));
	return 1;
}