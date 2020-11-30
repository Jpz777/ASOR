#include <stdio.h>
#include <time.h>

int main(){
	time_t rawtime = time(NULL);
	struct tm *info = localtime( &rawtime );
	printf("Año %i", 1900 + (info->tm_year));
	return 1;
}