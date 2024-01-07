/*
 * cgihello.cpp
 *
 *  Created on: Jun 10, 2014
 *      Author: parham
 */
#include <iostream>
#include <stdlib.h>
#include <pqxx/pqxx>
#include <cgicc/Cgicc.h>

using namespace std;
using namespace pqxx;

int main() {
	connection C(
			"dbname=home user=parham password=Parham13730321 hostaddr=192.168.1.100 port=5432");
	char* ip = getenv("REMOTE_ADDR");
	char* port = getenv("REMOTE_PORT");
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<html>\n";
	cout << "<head>\n";
	cout << "<title>Hello World - First CGI Program</title>\n";
	cout << "</head>\n";
	cout << "<body>\n";
	cout << "<h2> Hello World! This is my first CGI program </h2>\n";
	if (ip != NULL && port != NULL) {
		cout << "<div> Your IP address is : " << ip << " : " << port
				<< " </div>\n";
	}
	if (!C.is_open()) {
		cout << "<div> Cannot connect to database </div>\n";
	} else {
		cgicc::Cgicc cgi;
		cgicc::form_iterator user_name = cgi.getElement("userName");
		cgicc::form_iterator pass = cgi.getElement("password");
		string username;
		if (!user_name->isEmpty()) {
			username = **user_name;
		} else {
			username = "parham";
		}
		string password;
		if (!pass->isEmpty()) {
			password = **pass;
		} else {
			password = "Parham13730321";
		}
		nontransaction N(C);
		result R(N.exec("SELECT * FROM aut"));
		result::const_iterator iterator;
		for (iterator = R.begin(); iterator != R.end(); ++iterator) {
			if (iterator[0].as<string>().compare(username) == 0) {
				if (iterator[1].as<string>().compare(password) == 0) {
					cout << "<div> " << iterator[2].as<int>() << " </div>\n";
				}
			}
		}
	}
	cout << "</body>\n";
	cout << "</html>\n";
	return 0;
}

