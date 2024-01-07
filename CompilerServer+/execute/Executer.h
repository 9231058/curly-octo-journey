/*
 * Executer.h
 *
 *  Created on: Jul 19, 2014
 *      Author: parham
 */

#ifndef EXECUTER_H_
#define EXECUTER_H_

namespace Network {

class Executer {
private:
	int m_fd;
public:
private:
public:
	Executer(int fd);
	virtual ~Executer();
};

} /* namespace Network */

#endif /* EXECUTER_H_ */
