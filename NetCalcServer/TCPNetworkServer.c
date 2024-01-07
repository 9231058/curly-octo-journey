/*
 * TCPNetworkServer.c
 *
 *  Created on: Jun 3, 2014
 *      Author: parham
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const static int MAXPENDING = 5;

void TCPHandler(int clientSocket);
int Solve(char* op, int op1, int op2);

int main(int argc, char* argv[]) {
	int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(1373);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(serverSocket, (struct sockaddr*) &serverAddress,
			sizeof(serverAddress));
	listen(serverSocket, MAXPENDING);
	for (;;) {
		struct sockaddr_in clientAddress;
		memset(&clientAddress, sizeof(struct sockaddr_in), 0);
		socklen_t clientAddressLen = sizeof(clientAddress);
		int clientSocket = accept(serverSocket,
				(struct sockaddr*) &clientAddress, &clientAddressLen);
		TCPHandler(clientSocket);
	}
	return 0;
}

void TCPHandler(int clientSocket) {
	FILE* clientSocketFile = fdopen(clientSocket, "r+");
	char request[BUFSIZ];
	fgets(request, BUFSIZ - 1, clientSocketFile);
	char operator[BUFSIZ];
	int operand1 = 0;
	int operand2 = 0;
	sscanf(request, "%s %d %d", operator, &operand1, &operand2);
	fprintf(clientSocketFile, "%d\n", Solve(operator, operand1, operand2));
	fflush(clientSocketFile);
	fclose(clientSocketFile);
}

int Solve(char* op, int op1, int op2) {
	if (strcmp(op, "PLUS") == 0) {
		return op1 + op2;
	} else if (strcmp(op, "MINUS") == 0) {
		return op2 - op1;
	} else if (strcmp(op, "EXP") == 0) {
		return 0;
	} else if (strcmp(op, "DIV") == 0) {
		return op2 / op1;
	} else if (strcmp(op, "MULT") == 0) {
		return op1 * op2;
	}
	return 0;
}
