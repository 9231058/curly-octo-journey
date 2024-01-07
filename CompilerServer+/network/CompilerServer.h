/*
 * CompilerServer.h
 *
 *  Created on: Jul 19, 2014
 *      Author: parham
 */

#ifndef COMPILERSERVER_H_
#define COMPILERSERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace Network {

class CompilerServer {
private:
	in_port_t m_serverPort;
	int m_serverSocket;
public:
private:
public:
	CompilerServer();
	void run();
	virtual ~CompilerServer();
};

} /* namespace Client */

#endif /* COMPILERSERVER_H_ */
