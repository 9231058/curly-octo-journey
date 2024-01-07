#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void* funcThread(void* pointer);
void funcSIG(int signumber, siginfo_t* info, void* pointer);

int main() {
	pid_t pid = getpid();
	pid_t ppid = getppid();
	printf("My PID is: %ld\n", (long) pid);
	printf("My parent PID is : %ld\n", (long) ppid);
	struct sigaction handler;
	handler.sa_sigaction = funcSIG;
	sigaction(SIGTERM, &handler, NULL);
	pthread_t thread;
	static int arr[] = { 10, 20, 30 };
	pthread_create(&thread, NULL, funcThread, arr);
	int i = 0;
	for (i = 0; i < 3; i++) {
		printf("%s : %d\n", __func__, arr[i]);
	}
	printf("END\n");
	void* returnFrom;
	pthread_join(thread, &returnFrom);
	printf("%p : %d\n", returnFrom, *(int*) returnFrom);
	while (1) {

	}
	return 0;
}

void* funcThread(void* pointer) {
	int* newPointer = (int*) pointer;
	int i = 0;
	for (i = 0; i < 3; i++) {
		printf("%s : %d\n", __func__, *(newPointer + i));
	}
	static int x = 10;
	return &x;
}
void funcSIG(int signumber, siginfo_t* info, void* pointer) {
	printf("You are bothering me .... ");
	printf("%d ", signumber);
	printf("%d : %d : %d\n", info->si_code, info->si_errno, info->si_signo);
	exit(0);
}
