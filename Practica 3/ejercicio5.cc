#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <limits.h>

int main() {

  printf("Identificador de proceso: %i\n", getpid());
  printf("Proceso Padre: %i\n", getppid());
  printf("Grupo de procesos y de sesión: %i\n", getsid(getpid()));
  struct rlimit rlp;
  getrlimit(RLIMIT_NOFILE, &rlp);
  printf("Limite de procesos: %i\n", rlp.rlim_max);
  
  char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}