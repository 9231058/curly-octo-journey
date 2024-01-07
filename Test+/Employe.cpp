/*
 * testclass.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: parham
 */
#include "Employe.h"
#include <iostream>

namespace Types {

Employe& Employe::getEmploye() {
	Employe* employe = new Employe();
	std::cout << employe << std::endl;
	return *(employe);
}

Employe::Employe() {
	salary = 10;
	name = "No Name";
	std::cout << "New employe is created" << std::endl;
}

Employe::Employe(Employe &employe) {
	salary = employe.salary;
	name = employe.name;
	std::cout << "Copy is calling ..... From : " << &employe << " To : " << this
			<< std::endl;
}

Employe::Employe(Employe &&employe) {
	salary = employe.salary;
	name = employe.name;
	std::cout << "Move is calling ..... From : " << &employe << " To : " << this
			<< std::endl;
}

Employe& Employe::operator =(Employe &employe) {
	salary = employe.salary;
	name = employe.name;
	std::cout << "Operator = (copy) in calling ...." << __func__ << std::endl;
	return *this;
}

Employe& Employe::operator =(Employe&& employe) {
	salary = employe.salary;
	name = employe.name;
	std::cout << "Operator = (move) in calling ...." << __func__ << std::endl;
	return *this;
}

Employe::~Employe() {
	std::cout << "Object : " << this << " is deleting .... " << std::endl;
}

void Employe::setName(std::string name) {
	this->name = name;
}

void Employe::setSalary(int salary) {
	this->salary = salary;
}
}
