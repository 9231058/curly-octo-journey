/*
 * ServerException.h
 *
 *  Created on: Jul 19, 2014
 *      Author: parham
 */

#ifndef SERVEREXCEPTION_H_
#define SERVEREXCEPTION_H_

#include <exception>
#include <string>

namespace Network {

class ServerException: public std::exception {
private:
	std::string m_error;
	std::string m_message;
public:
private:
public:
	ServerException();
	ServerException(const std::exception&);
	ServerException(std::string message, std::string error);
	virtual const char* what() const noexcept override;
	virtual ~ServerException();
};

} /* namespace Network */

#endif /* SERVEREXCEPTION_H_ */
