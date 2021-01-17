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

ssize_t num_bytes;
struct sockaddr_storage peer_addr;
socklen_t peer_addr_len = sizeof(struct sockaddr_storage);
char host[NI_MAXHOST], service[NI_MAXSERV];
char buffer[2]; /* t, d, q commands */


while(1){
	num_bytes = recvfrom(sfd, buffer, 2, 0, (struct sockaddr *) &peer_addr, &peer_addr_len);

	getnameinfo((struct sockaddr *) &peer_addr, peer_addr_len, host, NI_MAXHOST, service,
		   NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
	if (s == 0)
		printf("%i bytes de %s:%s\n", num_bytes, host, service);
	else {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	} 
	
	if(buffer[0] == 'q'){
		printf("Saliendo...\n");
		exit(0);
	}
	else if (buffer[0] == 't'){
		time_t rawtime = time(NULL);
		struct tm *info = localtime( &rawtime );
		char timer[80];
		ssize_t num_bytes_time = strftime(timer, 80, "%I:%M:%S %p", localtime(&rawtime));
		
		sendto(sfd, timer, num_bytes_time, 0, (struct sockaddr *) &peer_addr, peer_addr_len);
	}
	else if (buffer[0] == 'd'){
		time_t rawtime = time(NULL);
		struct tm *info = localtime( &rawtime );
		char date[80];
		ssize_t num_bytes_date = strftime(date, 80, "%Y-%m-%d", localtime(&rawtime));
		
		sendto(sfd, date, num_bytes_date, 0, (struct sockaddr *) &peer_addr, peer_addr_len);
	}
	else {
		printf("Comando no soportado %d\n", buffer[0]);
	}
}
close(sfd);
return 0;
}