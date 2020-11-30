#include <stdio.h>
#include <time.h>

int main(){
	time_t timer = time(NULL);
	printf("Tiempo %s\n", ctime(&timer));
	return 1;
}