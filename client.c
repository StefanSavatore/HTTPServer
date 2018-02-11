#include <netdb.h>
#include "lib.h"
#include "r_w_func.c"

ssize_t readLine(int fd, void *buffer, size_t n);

int main(int argc, char const *argv[])
{
	char* requestStr;
	char seqNumStr[INT_LEN];
	int cfd;
	ssize_t numRead;
	struct addrinfo hints;
	struct addrinfo *result, *rp;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;

	getaddrinfo(argv[1], PORT_NUM, &hints, &result);

	for(rp = result; rp != NULL; rp = rp->ai_next){
		cfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if(cfd == -1)
			continue;
		if(connect(cfd, rp->ai_addr, rp->ai_addrlen) != -1)
			break;
		close(cfd);
	}

	freeaddrinfo(result);

	snprintf(seqNumStr, sizeof(seqNumStr), "A Message.");
	requestStr = seqNumStr;
	write(cfd, requestStr, strlen(requestStr));

	return 0;
}
