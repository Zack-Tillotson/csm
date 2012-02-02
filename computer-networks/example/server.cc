#include "includes.h"

#define MAXLINE 1024
#define PORT 9873

int main(int argc, char **argv) {

       if (argc != 1) {
                cout << "useage " << argv[0] << endl;
                exit(-1);
        }

	// ********************************************************************
	// * Creating the inital socket is the same as in a client.
	// ********************************************************************
	int     listenfd = -1;
        if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                cout << "Failed to create listening socket " << strerror(errno) <<  endl;
                exit(-1);
        }


	// ********************************************************************
	// * The same address structure is used, however we use a wildcard
	// * for the IP address since we don't know who will be connecting.
	// ********************************************************************
	struct sockaddr_in	servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(PORT);	


	// ********************************************************************
	// * Binding configures the socket with the parameters we have
	// * specified in the servaddr structure.  This step is implicit in
	// * the connect() call, but must be explicitly listed for servers.
	// ********************************************************************
	if (bind(listenfd, (sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
	       cout << "bind() failed: " << strerror(errno) <<  endl;
               exit(-1);
        }
	cout << "Process has bound fd " << listenfd << " to port " << PORT << endl;


	// ********************************************************************
        // * Setting the socket to the listening state is the second step
	// * needed to being accepting connections.  This creates a que for
	// * connections and starts the kernel listening for connections.
        // ********************************************************************
	int listenq = 1;
	if (listen(listenfd, listenq) < 0) {
	       cout << "listen() failed: " << strerror(errno) <<  endl;
               exit(-1);
        }
	cout << "We are now listening for new connections" << endl;


	// ********************************************************************
        // * The accept call will sleep, waiting for a connection.  When 
	// * a connection request comes in the accept() call creates a NEW
	// * socket with a new fd that will be used for the communication.
        // ********************************************************************
	while (1) {
		int connfd = -1;
		if ((connfd = accept(listenfd, (sockaddr *) NULL, NULL)) < 0) {
	       		cout << "accept() failed: " << strerror(errno) <<  endl;
               		exit(-1);
        	}

        	time_t 	ticks = time(NULL);
		char	buff[MAXLINE];
		int	bytesSent = 0;
        	snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        	if ((bytesSent = write(connfd, buff, strlen(buff))) != strlen(buff)) {
	       		cout << "write terminated early, sent " << bytesSent << " error is " << strerror(errno) <<  endl;
               		exit(-1);
        	}
		cout << "We sent " << bytesSent << " off to the client" << endl;
		close(connfd);
	}
}
