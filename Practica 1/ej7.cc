#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){
	int valuemaxinput = fpathconf(0, _PC_MAX_INPUT );
	int valuemaxlink = fpathconf(0, _PC_LINK_MAX);
	int valuenamepathconf = fpathconf(0, _PC_NAME_MAX);
	if(valuemaxlink >= 0 && valuemaxinput >= 0 && valuenamepathconf >= 0){
		printf ("Número máximo de un enlace %i \n", valuemaxinput);
		printf ("Tamaño máximo de una ruta %i bytes\n", valuemaxinput);
		printf ("Tamaño máximo de un nombre de fichero %i bytes", valuenamepathconf);
	}
	else
		printf("Error: %s", strerror(errno));
	return 1;
}