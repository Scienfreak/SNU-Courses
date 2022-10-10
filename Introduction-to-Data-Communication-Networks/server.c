#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h> // get ip address in 64 bit machine
#include <sys/socket.h>
#include <netinet/in.h>

#define MY_IP_ADDRESS 0
#define BACKLOG 10

void respond(int);

int main(int argc, char* argv[]) {

	short port = 8080;
	
	// make socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// socket option change: used for prevent error such as "address already in use"
	int tr = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}

	// bind socket, print error when fail
	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);	
	
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("Bind error");
		exit(1);
	}

	// listen socket, print error when fail
	if (listen(sockfd, BACKLOG) == -1) {
		perror("Listen error");
		exit(1);
	}

	// accept - halt until client requests
	struct sockaddr_in clnt_addr;
	bzero((char *) &clnt_addr, sizeof(clnt_addr));
	int newsockfd;

	while(1) {
		newsockfd = accept(sockfd, (struct sockaddr *) &clnt_addr, sizeof(clnt_addr));
		if (newsockfd == -1) {
			perror("Accept error");
			exit(1);
		}

		respond(newsockfd);
	}

}

void respond(int sock) {
	char message[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html;\r\n\r\n<html><body>Hello World!</body></html>\r\n\r\n";
	int length = strlen(message);
	int bytes;
	while (length > 0) {
		bytes = send(sock, message, bytes, 0);
		printf("send bytes : %d\n", bytes);
		length = length - bytes;
	}
	printf("close\n");
	shutdown(sock, SHUT_RDWR);
	close(sock);
}

