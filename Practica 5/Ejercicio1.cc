#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char ** argv){

if(argc != 2) {
	printf("Se necesitan dos parametros\n");
	return 1;
}

struct addrinfo hints;
struct addrinfo *result, *rp;
int s;

memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
hints.ai_socktype = 0;			/* Any socket */
hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
hints.ai_protocol = 0;          /* Any protocol */
hints.ai_canonname = NULL;
hints.ai_addr = NULL;
hints.ai_next = NULL;

s = getaddrinfo(argv[1], NULL, &hints, &result);

if (s != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	exit(EXIT_FAILURE);
}

for (rp = result; rp != NULL; rp = rp->ai_next) {
	char host[NI_MAXHOST], service[NI_MAXSERV];
	
	s = getnameinfo(rp->ai_addr, rp->ai_addrlen, host, NI_MAXHOST, service,
		   NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
	if (s == 0)
		printf("%s	%i	%i\n", host, rp->ai_family, rp->ai_socktype);
	else {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
}
return 0;
}