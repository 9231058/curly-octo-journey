/*
 * GetAddrInfo.c
 *
 *  Created on: Jun 5, 2014
 *      Author: parham
 */
#include "Practical.h"
#include "AddressUtility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char* argv[]) {
	if (argc != 3) {
		DieWithUserMessage("Parameter(s)", "<Address/Name> <Port/Service>");
	}
	char* addrString = argv[1];
	char* portString = argv[2];
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(struct addrinfo));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_protocol = IPPROTO_TCP;
	addrCriteria.ai_socktype = SOCK_STREAM;
	addrCriteria.ai_flags = AI_CANONNAME;
	struct addrinfo *addrList;
	int result = getaddrinfo(addrString, portString, &addrCriteria, &addrList);
	if (result != 0) {
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(result));
	}
	while (addrList != NULL) {
		printf("CNAME : %s\n", addrList->ai_canonname);
		printf("IP : ");
		PrintSocketAddress(addrList->ai_addr, stdout);
		fprintf(stdout, "\n");
		addrList = addrList->ai_next;
	}
	freeaddrinfo(addrList);
	return 0;
}

