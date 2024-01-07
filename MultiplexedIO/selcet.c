/*
 * selcet.c
 *
 *  Created on: Jun 22, 2014
 *      Author: parham
 */
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5
#define BUF_LEN 1024

int main(int argc, char **argv) {
	struct timeval tv;
	fd_set readfds;
	int ref;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;
	ref = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
	if (ref == -1) {
		perror("select");
		return 1;
	} else if (!ref) {
		printf("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}
	if (FD_ISSET(STDIN_FILENO, &readfds)) {
		char buf[BUF_LEN + 1];
		int len;
		len = read(STDIN_FILENO, buf, BUF_LEN);
		if (len == -1) {
			perror("read");
			return 1;
		}
		if (len) {
			buf[len] = '\0';
			printf("read : %s\n", buf);
		}
		return 0;
	}
	fprintf(stderr, "This should not happen!\n");
	return 1;
}

