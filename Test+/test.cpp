/*
 * test.cpp
 *
 *  Created on: Jun 7, 2014
 *      Author: parham
 */
#include <iostream>
#include "Employe.h"

using namespace std;

Types::Employe testFunc();
int sum(const int& a, const int& b);

int main(int argc, char **argv) {
	int arr[] = { 1, 2, 3 };
	cout << __func__ << endl;
	for (int i : arr) {
		cout << i << endl;
	}
	const Types::Employe& anEmploye = Types::Employe::getEmploye();
	cout << anEmploye.getName() << " " << anEmploye.getSalary() << endl;
	Types::Employe empl1(testFunc());
	cout << "Main empl 1 : " << &empl1 << endl;
	cout << empl1.getName() << " " << empl1.getSalary() << endl;
	int a = 10, b = 10;
	int& c = a;
	cout << a << " " << b << " " << c << " " << endl;
	c = 20;
	cout << a << " " << b << " " << c << " " << endl;
	sum(sum(a, b), b);
	return 0;
}

inline Types::Employe testFunc() {
	Types::Employe empl = Types::Employe::getEmploye();
	empl.setName("Parham");
	cout << "TestFunc empl : " << &empl << endl;
	return empl;
}

int sum(const int& a, const int& b) {
	cout << "Sum is calling ...." << endl;
	return a + b;
}
