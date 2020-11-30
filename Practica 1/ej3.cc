#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(){
	for(int i = 0; i < n; ++i)
		printf("Error: %d %s", i, strerror(i));
	return 1;
}
