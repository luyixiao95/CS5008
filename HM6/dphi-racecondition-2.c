#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//1 means forks on the table, 0 means that forks on the hand
int forks[5] = {-1, -1, -1, -1, -1};
int ph[5] = {0, 1, 2, 3, 4};
int eatTable[5] = {0, 0, 0, 0, 0};

void test(int pos){

	if(eatTable[pos]==eatTable[(pos+1)%5] || eatTable[pos]==eatTable[(pos+4)%5]) {
		printf("race condition happens!/n");
		pthread_exit(0);
	}
}
void* philo(void* arg){
	int  pos = *(int *) arg;
	int left = pos;
	int right = (pos +1) % 5;
	while(1){
		//Thinking at first
		printf("%d thinking\n", pos);
		//(random number [1, 3])
		sleep(1);
		//next, there are two types of philosophers

		if(pos% 2 == 0){
			if(forks[right] == -1){
				forks[right] = pos;
				printf("%d catching the right fork. \n", pos);
			}
			if(forks[right]== pos && forks[left] == -1){
				forks[left] = pos;
				printf("%d catching the left fork. \n", pos);
				printf("%d eating\n", pos);
				eatTable[pos] = 1;
				test(pos);
				sleep(1);
				test(pos);
				forks[left] = -1;
				printf("%d putting down the left fork. \n", pos);
				forks[right] = -1;
				printf("%d putting down the right fork. \n", pos);
				eatTable[pos] = 0;
				


			}		

		}
		// if the type of philosopher is odd
		else{
			if(forks[left] == -1){
				forks[left] = pos;
				printf("%d catching the left fork. \n", pos);
			}
			if(forks[left] == pos && forks[right] == -1){
				forks[right] = pos;
				printf("%d catching the right fork. \n", pos);
				printf("%d eating\n", pos);
				eatTable[pos] = 1;
				test(pos);
				sleep(1);
				test(pos);
				forks[right] = -1;
				printf("%d putting down the right fork. \n", pos);
				forks[left] = -1;
				printf("%d putting down the left fork. \n", pos);
				eatTable[pos]= 0;
				

			}

		}
	}

}
		int main(){
			//Prepare on creating;
			pthread_t p[5];

			//Create 5 threads 
			for(int i = 0; i< 5; i++){
				pthread_create(&p[i], NULL, philo, &ph[i]);
			}
			for(int i = 0; i < 5; i++){
				pthread_join(p[i], NULL);
			}


			return 0;
		}


