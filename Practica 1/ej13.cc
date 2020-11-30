#include <sys/time.h>
#include <stdio.h>

int main() {
	struct timeval principio, fin;
	gettimeofday(&principio, NULL);
	for (int i = 0; i < 1000000 ; i++) {
	}
	gettimeofday(&fin, NULL);
	printf("Tiempo que tarda en contar un bucle de 1000000: %ld microsegundos\n", (fin.tv_usec - principio.tv_usec));
	return 0;
}