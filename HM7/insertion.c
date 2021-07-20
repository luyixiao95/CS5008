#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define EXPERIMENT 1

//Swap the integers in address a and b
void swap(int* a, int* b){

	int buffer = *b;
	*b = *a;
	*a = buffer;
}

//insertSort function to sort the integer array by insert function.
 void insertionSort(int* array, unsigned int size){

 	for(int i = 1 ; i < size; i ++){
 		for(int j = i; j > 0; j --){

 			if(array[j] < array[j-1] ){

 				swap(&array[j], &array[j-1]);
 			

 			}
 		}



 	}
 }

//Print every element of the array in order

void printIntArray(int* array, unsigned int size){

	  unsigned int i;
	  for(i = 0 ; i < size ; i++){
	    printf("%d ", array[i]);
	  }
	  printf("\n");
	}

int main(int argc, char* argv[]){
	#if EXPERIMENT==0


	int dataset1[] = {0,1,2,3,4,5,6,7,8,9,10};
	int dataset2[] = {10,9,8,7,6,5,4,3,2,1,0};
	int dataset3[] = {0,3,2,1,4,7,6,5,8,9,10};
	int dataset4[] = {2,1,1,1,1,1,1,1,1,1,1};
	int dataset5[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
	int dataset6[] = {-1,1,2,-3,4,5,-6,7,8,-9,10};
	  
	insertionSort(dataset1, 11);
	insertionSort(dataset2, 11);
	insertionSort(dataset3, 11);
	insertionSort(dataset4, 11);
	insertionSort(dataset5, 11);
	insertionSort(dataset6, 11);
	  
	  // Print out an array
	printIntArray(dataset1, 11);
	printIntArray(dataset2, 11);
	printIntArray(dataset3, 11);
	printIntArray(dataset4, 11);
	printIntArray(dataset5, 11);
	printIntArray(dataset6, 11);

	#else
	

	  if (argc != 2) {
	    printf("One argument expected: ./bubblesort 1000\n");
	    return 1;
	  }
	

	  // Convert the argument of the program into an integer
	  const int size = atoi(argv[1]);
	  // Generate a random seed
	  time_t t;
	  srand((unsigned)time(&t));
	  // Allocate memory
	  int* random = (int*)malloc(sizeof(int)*size);
	

	  // Populate our test data set
	  for(int i = 0 ; i < size ; i++) {
	    // Generate random values from 0 to 99
	    random[i] = rand()%size; 
	  }
	

	  // You can uncomment if you'd like to see the size sorted
	  // printf("Before the sort: ");
	  // printIntArray(random, size);
	

	  // Setup timers  
	  struct timespec begin, end;
	  // Get the time before we start
	  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
	  // Perform the sort
	  insertionSort(random, size);
	  // Get the time after we are done
	  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	

	  double time_taken = (end.tv_nsec - begin.tv_nsec) / 1000000000.0 +
	            (end.tv_sec  - begin.tv_sec);
	  printf ("Total time = %f seconds\n", time_taken);
	

	  // Confirm the sort worked
	  // printf("After the sort: ");
	  // printIntArray(random, size);
	  
	  // Free our random array
	  free(random);
	

	#endif
	

	  return 0;
	}

