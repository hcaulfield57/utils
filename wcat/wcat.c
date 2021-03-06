#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int
main(int argc, char *argv[])
{
	int sockfd;
	int i, error;
	char buf[1024];
	struct addrinfo hints;
	struct addrinfo *res, *p;

	if(argc <= 1) {
		fprintf(stderr, "usage: wcat <website>\n");
		exit(1);
	}

	for(i = 1; i < argc; i++) {
		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		if((error = getaddrinfo(argv[i], "http", &hints, &res)) != 0)
			errx(1, "getaddrinfo error: %s", gai_strerror(error));
		for(p = res; p; p = p->ai_next) {
			if((sockfd = socket(p->ai_family, p->ai_socktype, 
				p->ai_protocol)) == -1) {
				continue;
			}
			if(connect(sockfd, p->ai_addr, p->ai_addrlen) == 0)
				break;
		}
		freeaddrinfo(res);
                snprintf(buf, sizeof buf, "GET /index.html HTTP/1.1\r\n");
		if(send(sockfd, buf, sizeof buf, 0) == -1)
			err(1, "send error");

		while(recv(sockfd, buf, sizeof buf, 0) > 0)
                    printf("%s", buf);
	}
	return 0;
}
