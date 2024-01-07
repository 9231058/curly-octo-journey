/*
 * fork.c
 *
 *  Created on: Jun 26, 2014
 *      Author: parham
 */
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	pid_t pid;
	pid = fork();
	if (pid == -1) {
		perror("fork()");
	}
	if (!pid) {
		char * const args[] = { "ls", "-la", NULL };
		int result;
		result = execv("/bin/ls", args);
		if (result == -1) {
			perror("execv()");
			exit(1);
		}
	}
	if (pid > 0) {
		int status;
		pid = waitpid(pid, &status, WNOHANG);
		if (pid != 0) {
			if (WIFEXITED(status)) {
				printf("My child die\n");
			}
			if (WIFSIGNALED(status)) {
				printf("My child killed\n");
			}
		}
		else{
			printf("My child is alive\n");
		}
		printf("I am Parent ... do not mass with me ....\n");
	}
	return 0;

}

