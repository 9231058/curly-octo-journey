/*
 * TCPEchoClient.c
 *
 *  Created on: Jun 3, 2014
 *      Author: parham
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

int main(int argc, char* argv[]) {
	int result;
	if (argc < 3 || argc > 4) {
		DieWithUserMessage("Parameter(s)",
				"<Server Address> <Echo Word> [<Server Port>]");
	}
	char* serverIP = argv[1];
	char* echoString = argv[2];
	in_port_t serverPort = (argc == 4) ? atoi(argv[3]) : 7;
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		DieWithSystemMessage("socket() failed");
	}
	struct sockaddr_in serverAddress;
	memset(&serverAddress, sizeof(struct sockaddr_in), 0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(serverPort);
	result = inet_pton(AF_INET, serverIP, &serverAddress.sin_addr.s_addr);
	if (result == 0) {
		DieWithUserMessage("inet_pton() failed", "invalid address string");
	} else if (result < 0) {
		DieWithSystemMessage("inet_pton() failed");
	}
	result = connect(sock, (struct sockaddr*) &serverAddress,
			sizeof(serverAddress));
	if (result < 0) {
		DieWithSystemMessage("connect() failed");
	}
	size_t echoStringLen = strlen(echoString);
	//ssize_t numByte = send(sock, echoString, echoStringLen, 0);
	ssize_t numByte = write(sock, echoString, echoStringLen);
	if (numByte < 0) {
		DieWithSystemMessage("send() failed");
	} else if (numByte != echoStringLen) {
		DieWithUserMessage("send()", "unexpected number of bytes");
	}
	unsigned int totalByteReceive = 0;
	printf("Received :\n");
	numByte = 0;
	do {
		char buffer[BUFSIZ];
		numByte = recv(sock, buffer, BUFSIZ - 1, 0);
		printf("%s\n", buffer);
		totalByteReceive += numByte;
	} while (numByte > 0);
	printf("Total byte received : %d", totalByteReceive);
	close(sock);
	return 0;
}
