#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(){
	if (setuid(0) == -1)
		printf("Error: %s", strerror(errno));
	return 1;
}
