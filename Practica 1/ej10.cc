#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

int main(){
	struct passwd* uid = getpwuid(getuid());
	printf("UID real %d\n", getuid());
	printf("UID effectivo %d\n", geteuid());
	if((uid = getpwuid(getuid())) == NULL) {
		perror("getpwuid() error");
	}
	else {
		printf("Nombre de usuario %s\n", uid->pw_name);
		printf("Información de usuario %s\n", uid->pw_gecos);
		printf("Directorio home %s\n", uid->pw_dir);
	}
	return 1;
}