/*
 * ServerException.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: parham
 */

#include "ServerException.h"

namespace Network {

ServerException::ServerException() {
	m_error = "";
	m_message = "";
}

ServerException::ServerException(const std::exception& except) {
	m_error = except.what();
	m_message = "";
}

ServerException::ServerException(std::string message, std::string error) {
	m_error = error;
	m_message = message;
}

const char* ServerException::what() const noexcept {
	std::string what = m_message + ":" + m_error;
	return what.c_str();
}

ServerException::~ServerException() {
}

} /* namespace Network */
