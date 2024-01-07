/*
 * IOExeption.h
 *
 *  Created on: Jul 1, 2014
 *      Author: parham
 */

#ifndef IOEXEPTION_H_
#define IOEXEPTION_H_

#include <exception>
#include <string>

namespace File {

class IOExeption: public std::exception {
private:
	std::string error;
	std::string message;
public:
private:
public:
	IOExeption();
	IOExeption(std::string message, std::string error);
	virtual const char* what() const noexcept override;
	virtual ~IOExeption();
};

} /* namespace File */

#endif /* IOEXEPTION_H_ */
