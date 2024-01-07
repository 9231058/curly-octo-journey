/*
 * CompilerServer.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: parham
 */

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

#include "CompilerServer.h"
#include "domain/exception/ServerException.h"

namespace Network {

CompilerServer::CompilerServer() {
	m_serverPort = 1373;
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket < 0) {
		throw(new ServerException("socket()", strerror(errno)));
	}
}

void CompilerServer::run() {
	int result;
	struct sockaddr_in serverAddress;
	memset(&serverAddress, sizeof(struct sockaddr_in), 0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(m_serverPort);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	result = bind(m_serverSocket, (struct sockaddr*) &serverAddress,
			sizeof(serverAddress));
	if (result < 0) {
		throw(new ServerException("bind()", strerror(errno)));
	}
	result = listen(m_serverSocket, 5);
	if (result < 0) {
		throw(new ServerException("listen()", strerror(errno)));
	}
	while (true) {
	}
}

CompilerServer::~CompilerServer() {
}

} /* namespace Client */
