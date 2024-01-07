/*
 * AddressUtility.h
 *
 *  Created on: Jun 5, 2014
 *      Author: parham
 */

#include <stdio.h>
#include <sys/socket.h>

#ifndef ADDRESSUTILITY_H_
#define ADDRESSUTILITY_H_
void PrintSocketAddress(const struct sockaddr* address, FILE *stream);
#endif /* ADDRESSUTILITY_H_ */
