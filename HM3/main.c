#include <stdio.h>
#include "vector.h"
#include "sll.h"
#include "dll.h"

int main(int args, char **argv){
	FILE* fp = fopen(argv[1], "r");
	//create a new queue
	vector_t* queue = makeQueueV(10);
	printf("For vector.h, test queue and stack io\n");
	printf("firstly add all the elements to the queue by order:\n");
	//import the data of the file
	int buffer;
	while(1==fscanf(fp, "%d", &buffer)){
		inQueueV(queue, buffer);

	}

	fclose(fp);
	printV(queue);
	printf("next, remove the first two elements in order as a rule of queue:\n");
	//Out
	outQueueV(queue);
	outQueueV(queue);
	printV(queue);

	//Free

	printf("test stack\n");

	//test outStack
	outStackV(queue);
	printV(queue);
	freeVector(queue);


	//Test for sll.h
	printf("\n");
	FILE* fp2 = fopen(argv[1], "r");
	//create a new queue
	slist_t* queue2 = makeQueueSLL();
	printf("For sll.h, test queue and stack io\n");
	printf("firstly add all the elements to the queue by order:\n");
	//import the data of the file
	int buffer2;
	while(1==fscanf(fp2, "%d", &buffer2)){
		inQueueSLL(queue2, buffer2);

	}

	fclose(fp2);


	printSLL(queue2);
	printf("next, remove the first two elements in order as a rule of queue:\n");
	//Out
	outQueueSLL(queue2);
	outQueueSLL(queue2);
	printSLL(queue2);

	printf("stack removal\n");
	outStackSLL(queue2);
	printSLL(queue2);
	freeSLL(queue2);



	//Test for dll.h


	printf("\n");
	FILE* fp3 = fopen(argv[1], "r");
	//create a new queue
	dlist_t* queue3 = makeQueueDLL();
	printf("For dll.h, test queue and stack io\n");
	printf("firstly add all the elements to the queue by order:\n");
	//import the data of the file
	int buffer3;
	while(1==fscanf(fp3, "%d", &buffer3)){
		inQueueDLL(queue3, buffer3);

	}

	fclose(fp3);


	printDLL(queue3);
	printf("next, remove the first two elements in order as a rule of queue:\n");
	//Out
	outQueueDLL(queue3);
	outQueueDLL(queue3);
	printDLL(queue3);

	printf("stack removal\n");
	outStackDLL(queue3);
	printDLL(queue3);

}
