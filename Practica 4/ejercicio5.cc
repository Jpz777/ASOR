#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(){

char * pipe_name1;
char * pipe_name2;
char buffer[256];

pipe_name1 = "examplepipe1";
pipe_name2 = "examplepipe2";

mkfifo(pipe_name1,0666);
mkfifo(pipe_name2,0666);

int fd1, fd2, max_num_fd;

fd1 = open(pipe_name1, O_RDONLY | O_NONBLOCK);
fd2 = open(pipe_name2, O_RDONLY | O_NONBLOCK);

if (fd1 == -1) {
	printf("No se ha creado el archivo\n");
	return 1;
}

if (fd2 == -1) {
	printf("No se ha creado el archivo\n");
	return 1;
}

fd_set rfds;
struct timeval tv;
int retval;
char * curr_pipe;
int num_curr_pipe;

while(retval != -1){
	FD_ZERO(&rfds);
	FD_SET(fd1, &rfds);
	FD_SET(fd2, &rfds);
	
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	
	int i;
	int num_read, num;
	
	if(fd1 < fd2)
		max_num_fd = fd2 + 1;
	else 
		max_num_fd = fd1 + 1;
	
	retval = select(max_num_fd, &rfds, NULL, NULL, &tv);

	if (retval == -1){
		perror("select()");
		return 1;
	}
	else if (retval){
		if(FD_ISSET(fd1, &rfds)) {
			curr_pipe = pipe_name1;
			num_curr_pipe = fd1;
			num = 1;
		} else if(FD_ISSET(fd2, &rfds)) {
			curr_pipe = pipe_name2;
			num_curr_pipe = fd2;
			num = 2;
		}
		
		num_read = read(num_curr_pipe, &buffer, 256);
		buffer[num_read] = '\0';
		
		if(num_read == -1){
			printf("Lectura erronea\n");
			return 1;
		}
		else if(num_read == 0 && curr_pipe == pipe_name1){
			close(fd1);
			fd1 = open(pipe_name1, O_RDONLY | O_NONBLOCK);
			if (fd1 == -1) {
				printf("No se ha creado el archivo\n");
				close(fd1);
				close(fd2);
				return 1;
			}
		}
		else if(num_read == 0 && curr_pipe == pipe_name2){
			close(fd2);
			fd2 = open(pipe_name2, O_RDONLY | O_NONBLOCK);
			if (fd2 == -1) {
				printf("No se ha creado el archivo\n");
				close(fd1);
				close(fd2);
				return 1;
			}
		}
		else
			printf("La tuberia %i saca por pantalla: %s", num, buffer);
	}
	else
		printf("Ningún dato nuevo en 10 seg.\n");
}

close(fd1);
close(fd2);

return 0;
}