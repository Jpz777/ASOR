#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){
	int valuestream = sysconf(_SC_STREAM_MAX);
	int valuechild = sysconf(_SC_CHILD_MAX);
	int valuearg = sysconf(_SC_ARG_MAX);
	if(valuestream >= 0 && valuechild >= 0 && valuearg >= 0){
		printf ("Longitud máxima de argumentos %i\n", valuearg);
		printf ("Número máximo de hijos %i\n", valuechild);
		printf ("Número máximo de ficheros %i", valuestream);
	}
	else
		printf("Error: %s", strerror(errno));
	return 1;
}