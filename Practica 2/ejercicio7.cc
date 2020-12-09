#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
mode_t oldmask;

oldmask = umask(0027);

int fd;

fd = open("micasa", O_CREAT, 0777);

mode_t mask;

mask = umask(oldmask);

return 0;
}