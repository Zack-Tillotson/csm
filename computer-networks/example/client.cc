#include "includes.h"

#define MAXLINE 1024
#define PORT 13

int main(int argc, char **argv) {

	if (argc != 2) {
		cout << "useage " << argv[0] << " <ipaddress> " << endl;
		exit(-1);
	}

	int	sockfd = -1;
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "socket error: " << strerror(errno) <<  endl;
		exit(-1);
	}

	struct	sockaddr_in	servaddr;
	bzero(&servaddr, sizeof(servaddr));  
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);


	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		cout << "inet_pton: " << strerror(errno) <<  endl;
		exit(-1);
	}

	if (connect(sockfd, (sockaddr*) &servaddr, sizeof(servaddr)) < 0) {
		cout << "connect: " << strerror(errno) <<  endl;
		exit(-1);
	}

	int	n = 0;
	char	recvline[MAXLINE + 1];
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		cout << recvline;
	}

	if (n < 0) {
		cout << "No response from server." <<  endl;
		exit(-1);
	}

	exit(0);
}
