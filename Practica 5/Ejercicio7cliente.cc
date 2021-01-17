#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

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

sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

connect(sfd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

freeaddrinfo(result);

ssize_t num_bytes;
char host[NI_MAXHOST], service[NI_MAXSERV];
char buffer[80], buffer_recv[80];
int clisd;


while(1){
	num_bytes = read(0, buffer, 80);
	if (buffer[0] == 'Q' && num_bytes ==2)
		exit(0);
	buffer[num_bytes] = '\0';
	send(sfd, buffer, num_bytes, 0);
	num_bytes = recv(sfd, buffer_recv, 80, 0);
	buffer_recv[num_bytes] = '\0';
	printf("%s", buffer_recv);
}

close(sfd);
return 0;
}