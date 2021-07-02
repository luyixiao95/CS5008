// Type in and try example3.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	pid_t pid = fork();

	int x = 1;

	if(pid == 0){
		printf("Running parent forever (pretend I am a server): pid= %d\n", getpid());
		while(1);
	} else {
		printf("Terminate child: pid= %d\n", getpid());
		exit(0);
	}
return 0;
}
