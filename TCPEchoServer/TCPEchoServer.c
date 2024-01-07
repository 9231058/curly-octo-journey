/*
 * TCPEchoServer.c
 *
 *  Created on: Jun 3, 2014
 *      Author: parham
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include "Practical.h"

static const int MAXPENDING = 5;

void* HandleTCPClient(void* pointer);

int main(int argc, char* argv[]) {
	int result;
	if (argc != 2) {
		DieWithUserMessage("Prameter(s)", "<Server Port>");
	}
	in_port_t serverPort = atoi(argv[1]);
	int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket < 0) {
		DieWithSystemMessage("socket() failed");
	}
	struct sockaddr_in serverAddress;
	memset(&serverAddress, sizeof(struct sockaddr_in), 0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(serverPort);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	result = bind(serverSocket, (struct sockaddr*) &serverAddress,
			sizeof(serverAddress));
	if (result < 0) {
		DieWithSystemMessage("bind() failed");
	}
	result = listen(serverSocket, MAXPENDING);
	if (result < 0) {
		DieWithSystemMessage("listen() failed");
	}
	for (;;) {
		struct sockaddr_in clientAddress;
		memset(&clientAddress, sizeof(struct sockaddr_in), 0);
		socklen_t clientAddressLen = sizeof(clientAddress);
		int clientSocket = accept(serverSocket,
				(struct sockaddr*) &clientAddress, &clientAddressLen);
		if (clientSocket < 0) {
			DieWithSystemMessage("accept() failed");
		}
		char clientIP[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientIP,
				sizeof(clientIP)) != NULL) {
			printf("Handling client %s/%d\n", clientIP,
					ntohs(clientAddress.sin_port));
		} else {
			printf("Unable to get client address");
		}
		pthread_t thread;
		pthread_create(&thread, NULL, HandleTCPClient, &clientSocket);
	}
	return 0;
}

void* HandleTCPClient(void* pointer) {
	int clientSocket = *((int*) pointer);
	char buffer[BUFSIZ];
	ssize_t numByteRcvd;
	do {
		numByteRcvd = recv(clientSocket, buffer, BUFSIZ - 1, 0);
		if (numByteRcvd < 0) {
			DieWithSystemMessage("recv() failed");
		}
		printf("%s", buffer);
		ssize_t numByteSend = send(clientSocket, buffer, numByteRcvd, 0);
		if (numByteSend < 0) {
			DieWithSystemMessage("send() failed");
		} else if (numByteSend != numByteRcvd) {
			DieWithUserMessage("send() failed",
					"sent unexpected number of bytes");
		}
	} while (numByteRcvd > 0);
	close(clientSocket);
	return NULL;
}

