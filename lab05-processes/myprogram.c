// Take a look at some of the previous examples to create your own program!
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

	pid_t pid1 = fork();
	pid_t pid2 = fork();
	pid_t pid3 = fork();
	int child_status;

	char* myargv1[] = {"/bin/ls", NULL};
	char* myargv2[] = {"/bin/pwd", NULL};
	char* myargv3[] = {"/bin/man", NULL};
	if (pid1 == 0) {
		sleep(1);
		execve(myargv1[0], myargv1, NULL);
		exit(1);
	}
	if (pid2 == 0){
		sleep(2);
		execve(myargv2[0], myargv2, NULL);
		exit(2);
	}
	if (pid3 == 0){
		sleep(4);
		execve(myargv3[0], myargv3, NULL);
		exit(3);
	}


		wait(NULL);


	

	return 0;
}