#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#define SLEEP_SECS 5

int main() {
sigset_t blk_set;

sigemptyset(&blk_set);
sigaddset(&blk_set, SIGINT);
sigaddset(&blk_set, SIGTSTP);

sigprocmask(SIG_BLOCK, &blk_set, NULL);

printf("El proceso se duerme %i segundos\n", SLEEP_SECS);
sleep(SLEEP_SECS);
printf("El proceso se ha despertado\n", SLEEP_SECS);

sigset_t sigset;

if(sigpending(&sigset) != 0 )
    perror( "sigpending() error\n" );

if(sigismember(&sigset, SIGINT)){
    printf("La señal SIGINT sigue pendiante\n");
	sigdelset(&blk_set, SIGTSTP);
}
else {
    printf("La señal SIGINT no sigue pendiante\n");
}
if(sigismember(&sigset, SIGTSTP)) {
    printf("La señal SIGTSTP sigue pendiante\n");
    sigdelset(&blk_set, SIGINT);
}
else {
    printf("La señal SIGSTP no sigue pendiante\n");
}

sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

return 0;
}
