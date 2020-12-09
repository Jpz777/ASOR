#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
int fd;

fd = open("micasa", O_CREAT, 0640);

return 0;
}