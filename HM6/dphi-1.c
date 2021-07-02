#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t forks[5];
int ph[5] = {0, 1, 2, 3, 4};

void* philo(void* arg){
	int  pos = *(int *) arg;
	int left = pos;
	int right = (pos +1)% 5;
	while(1){
		//Thinking at first
		printf("%d thinking\n", pos);
		int thinkTime = rand()%3+1;
		//(random number [1, 3])

		//next, there are two types of philosophers

		if(pos% 2 == 0){
			sem_wait(&forks[right]);
			printf("%d catching the right fork. \n", pos);
			sem_wait(&forks[left]);
			printf("%d catching the left fork. \n", pos);
			//As this philosopher passes the two semaphore waits, it now can eat. 
			int eatTime =  rand()%3 +1; //random number [1, 3]
			printf("%d eating\n", pos);


			//Next firstly put down the left fork, then put down the right fork.

			sem_post(&forks[left]);
			printf("%d putting down the left fork. \n", pos);
			sem_post(&forks[right]);
			printf("%d putting down the right fork. \n", pos);

		}
		// if the type of philosopher is odd
		else{
			sem_wait(&forks[left]);
			printf("%d catching the left fork. \n", pos);
			sem_wait(&forks[right]);
			printf("%d catching the right fork. \n", pos);
			//As this philosopher passes the two semaphore waits, it now can eat. 
			int eatTime =  rand()%3 +1; //random number [1, 3]
			printf("%d eating\n", pos);


			//Next firstly put down the right fork, then put down the left fork.

			sem_post(&forks[right]);
			printf("%d putting down the right fork. \n", pos);
			sem_post(&forks[left]);
			printf("%d putting down the left fork. \n", pos);

		}
}

}
		int main(){
			//Prepare on creating;
			pthread_t p[5];
			//Initialize 5 sems
			for(int i = 0; i< 5; i++){
				sem_init(&forks[i], 0, 1);
			}
			//Create 5 threads 
			for(int i = 0; i< 5; i++){
				pthread_create(&p[i], NULL, philo, &ph[i]);
			}
			for(int i = 0; i < 5; i++){
				pthread_join(p[i], NULL);
			}

			//Destory

			for (int i = 0 ; i < 5; i++){
				sem_destroy(&forks[i]);
			}

			return 0;
		}


