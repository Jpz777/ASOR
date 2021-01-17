#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <errno.h>
#include <signal.h>

void proc_exit(){
	while(wait(NULL) > 0);
}

int main(int argc, char ** argv){

if(argc != 3) {
	printf("Se necesitan tres parametros\n");
	return 1;
}

struct addrinfo hints;
struct addrinfo *result, *rp;
int sfd, s;

memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
hints.ai_socktype = SOCK_STREAM;	/* Datagram socket */
hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
hints.ai_protocol = 0;          /* Any protocol */
hints.ai_canonname = NULL;
hints.ai_addr = NULL;
hints.ai_next = NULL;

s = getaddrinfo(argv[1], argv[2], &hints, &result);

if (s != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	exit(EXIT_FAILURE);
}

for (rp = result; rp != NULL; rp = rp->ai_next) {
	sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if (sfd == -1)
		continue;

	if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
		break;

	close(sfd);
}
freeaddrinfo(result);

if (rp == NULL) {               /* No address succeeded */
   fprintf(stderr, "Could not connect\n");
   exit(EXIT_FAILURE);
}

if(listen(sfd, 3) == -1){
	printf("No se ha podido ejecutar el listen\n");
	return 1;
}

ssize_t num_bytes;
struct sockaddr_storage peer_addr;
socklen_t peer_addr_len = sizeof(struct sockaddr_storage);
char host[NI_MAXHOST], service[NI_MAXSERV];
char buffer[80]; /* t, d, q commands */
int clisd;

signal (SIGCHLD, proc_exit);

while(1){
	
	clisd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_len);
	if(clisd == -1){
		printf("No se ha podido ejecutar el accept\n");
		return 1;
	}
	
	pid_t pid = fork();
	
	if(pid == -1){ //error
		perror("fork");
	}
	else if(pid == 0){
		while(1){
			getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service,
			   NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

			if (s == 0)
				printf("Conexión desde %s %s\n", host, service);
			else {
				fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			} 
			num_bytes = recv(clisd, buffer, 80, 0);
			while(num_bytes != 0) {
				buffer[num_bytes] = '\0';
				//printf("\tMensaje: %s\n", buffer);
				send(clisd, buffer, num_bytes, 0);
				num_bytes = recv(clisd, buffer, 80, 0);
			}
			printf("Conexión terminada\n");
			close(clisd);
		}
	}
	else{
		close(clisd);
	}
}

close(sfd);
return 0;
}