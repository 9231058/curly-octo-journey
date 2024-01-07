/*
 * Practical.c
 *
 *  Created on: Jun 3, 2014
 *      Author: parham
 */
#include <stdio.h>
#include <stdlib.h>

void DieWithUserMessage(const char* message, const char* detail) {
	fprintf(stderr, "%s:%s\n", message, detail);
	exit(1);
}
void DieWithSystemMessage(const char* message) {
	perror(message);
	exit(1);
}

