#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	time_t rawtime = time(NULL);
	char timer[80]; 
	strftime(timer, 80, "%A, %d de %B de %Y, %R", localtime(&rawtime));
	printf("%s\n", timer);
	return 1;
}