/*
 * IOExeption.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: parham
 */

#include "IOExeption.h"

#include <string>

namespace File {

IOExeption::IOExeption() {
	error = "";
	message = "";
}

IOExeption::IOExeption(std::string message, std::string error) {
	this->error = error;
	this->message = message;
}

const char* IOExeption::what() const noexcept {
	std::string what = message + " : " + error;
	return what.c_str();
}

IOExeption::~IOExeption() {
}

} /* namespace File */
