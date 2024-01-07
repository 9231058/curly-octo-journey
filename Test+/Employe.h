/*
 * testclass.h
 *
 *  Created on: Jun 8, 2014
 *      Author: parham
 */

#ifndef TESTCLASS_H_
#include <string>

namespace Types {
class Employe {
public:
	static Employe& getEmploye();
private:
public:
private:
	int salary;
	std::string name;
public:
	Employe(Employe &employe);
	Employe(Employe &&employe);
	Employe& operator =(Employe &employe);
	Employe& operator =(Employe &&employe);
	~Employe();

	void setName(std::string name);
	void setSalary(int salary);
	std::string getName() const {
		return name;
	}
	int getSalary() const {
		return salary;
	}
private:
	Employe();
};
}
#define TESTCLASS_H_

#endif /* TESTCLASS_H_ */
