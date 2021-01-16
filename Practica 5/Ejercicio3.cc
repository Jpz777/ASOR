#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>

int main(int argc, char ** argv){

if(argc != 4) {
	printf("Se necesitan cuatro parametros\n");
	return 1;
}

struct addrinfo hints;
struct addrinfo *result, *rp;
int sfd, s;

memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
hints.ai_socktype = SOCK_DGRAM;	/* Datagram socket */
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

freeaddrinfo(result);

struct sockaddr_storage peer_addr;
socklen_t peer_addr_len;
char host[NI_MAXHOST], service[NI_MAXSERV];

sendto(sfd, argv[3], 2, 0, result->ai_addr, result->ai_addrlen);

if(*argv[3] == 'd' || *argv[3] == 't'){
	char buffer[80];
	ssize_t bytes = recvfrom(sfd, buffer, 80, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);
	buffer[bytes] = '\0';
	printf( "%s\n", buffer);
}
close(sfd);
return 0;
}