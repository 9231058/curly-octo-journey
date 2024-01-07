/*
 * UDPEchoClient.c
 *
 *  Created on: Jul 5, 2014
 *      Author: parham
 */
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include "Practical.h"

#define MAXSTRINGLENGTH BUFSIZ

int main(int argc, char **argv) {
	if (argc < 3 || argc > 4) {
		DieWithUserMessage("Parameter(s)",
				"<Server Address/Name> <Echo Word> [<Server Port/Service>]");
	}
	char* serverAddress = argv[1];
	char* echoString = argv[2];
	size_t echoStringLen = strlen(echoString);
	if (echoStringLen > MAXSTRINGLENGTH) {
		DieWithUserMessage(echoString, "string too long");
	}
	char* serverPort = (argc == 4) ? argv[3] : "echo";
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(struct addrinfo));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_socktype = SOCK_DGRAM;
	addrCriteria.ai_protocol = IPPROTO_UDP;
	struct addrinfo* serverAddressInfo;
	int result = getaddrinfo(serverAddress, serverPort, &addrCriteria,
			&serverAddressInfo);
	if (result != 0) {
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
	}
	int sock = socket(serverAddressInfo->ai_family,
			serverAddressInfo->ai_socktype, serverAddressInfo->ai_protocol);
	if (sock < 0) {
		DieWithSystemMessage("socket() failed");
	}
	ssize_t numByte = sendto(sock, echoString, echoStringLen, 0,
			serverAddressInfo->ai_addr, serverAddressInfo->ai_addrlen);
	if (numByte < 0) {
		DieWithSystemMessage("sendto() failed");
	} else if (numByte != echoStringLen) {
		DieWithUserMessage("sendto() error", "sent unexpected number of bytes");
	}
	struct sockaddr_in receiveAddress;
	socklen_t receiveAddressLen = sizeof(struct sockaddr_in);
	char buffer[MAXSTRINGLENGTH];
	printf("waiting for recvfrom()\n");
	numByte = recvfrom(sock, buffer, MAXSTRINGLENGTH - 1, 0,
			(struct sockaddr*) &receiveAddress, &receiveAddressLen);
	freeaddrinfo(serverAddressInfo);
	buffer[echoStringLen] = '\0';
	printf("Received: %s\n", buffer);
	close(sock);
	return 0;
}

