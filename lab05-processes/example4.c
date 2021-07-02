// Type in and try example4.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	int child_status;  

	if(fork()==0){

		printf("Child_runs!\n");
		exit(5);}
		else
		{
			printf("Hello from parents!\n" );
			wait(&child_status);
			if(WEXITSTATUS(child_status)>=0){
				printf("Child exited with the following child_status %d\n", 
				WEXITSTATUS(child_status)); //get the exit value of the child status

			}

			printf("This prints the last always.\n");

			return 0;
		}
	}
