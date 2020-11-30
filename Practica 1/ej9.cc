#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  printf("UID real %d\n", getuid());
  printf("UID effectivo %d", geteuid());
  //Si en los permisos sale una s como "-rwsr-xr-x"
  return 1;
}