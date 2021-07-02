// Implement your part 1 solution here
// gcc vfork.c -o vfork
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
void paint(int workid){
	printf("Artist %d is painting\n", workid);
}

int main(int argc, char** argv){

	int numberOfArtists = 8;
	pid_t pid;
	for(int i= 0; i < numberOfArtists; i++){

		pid = fork();
		if(pid == 0){
			paint(getpid());
			exit(1);
		}
	}
	int status = 0;
	while((pid = wait(&status))>0) {}
	printf("Parent is exiting");
	


	return 0;
	
}
