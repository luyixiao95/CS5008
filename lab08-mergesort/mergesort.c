// Task: Implement the 'sortIntegers' function below

// =================== Libraries ==================
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Include file for standart input/output

#define EXPERIMENT 1 // use this for the experimentation in this lab

// =============== Helper Functions ===============

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) {
  int subarray1[m-l+1];
  int subarray2[r-(m+1)+1];
  
  int indexSub1 = 0;
  int indexSub2 = 0;
  for(int i = l; i<= m; i++){

    subarray1[indexSub1] = arr[i];
    indexSub1++;
  }

  for(int j = m+1; j <= r; j++){

    subarray2[indexSub2] = arr[j];
    indexSub2 ++ ;
  }

  indexSub1 = 0;
  indexSub2 = 0;
  int indexParent = l;
  while(indexSub1 < m-l+1 && indexSub2 < r-m){

    if(subarray1[indexSub1] >= subarray2[indexSub2]){

      arr[indexParent] = subarray2[indexSub2];
      indexSub2 ++;
    }

    else{

      arr[indexParent] = subarray1[indexSub1];
      indexSub1 ++;
    }

    indexParent ++ ;

  }

  while(indexSub1 < m-l+1) {

    arr[indexParent] = subarray1[indexSub1];
    indexSub1 ++;
    indexParent ++;

  }

  while(indexSub2 < r-m) {

    arr[indexParent] =subarray2[indexSub2];
    indexSub2 ++;
    indexParent ++;
  }


}

void mergeSort(int* array, int l, int r){

  if(r > l){

    int m = ( r + l ) /2;
    mergeSort(array, l, m);
    mergeSort(array, m+1, r);
    merge(array, l, m, r);


  }

  return;
}


// Provided below is a sort function. We have also
// provided a template for how to document functions
// to help organize your code.
// Name: sortIntegers
// Input(s):
//          (1) 'array' is a pointer to an integer address. 
//              This is the start of some 'contiguous block of memory' that we will sort.
//          (2) 'size' tells us how big the array of data is we are sorting.
// Output: No value is returned, but 'array' should be modified to store a sorted array of numbers.
void sortIntegers(int* array, unsigned int size){
    // TODO: make a call to your mergeSort function here
  mergeSort(array, 0, size-1);
  return;



}


// Input: A pointer to an array (i.e. the array itself points to the first index)
//        The size of the array (Because we do not know how big the array is automatically)
void printIntArray(int* array, unsigned int size){
  unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
  for(i = 0; i < size; i=i+1){
    printf("%d ",array[i]);
  }
  printf("\n");
}

int main(int argc, char* argv[]){
#if EXPERIMENT==0
  // Some test data sets.
  int dataset1[] = {0,1,2,3,4,5,6,7,8,9,10};
  int dataset2[] = {10,9,8,7,6,5,4,3,2,1,0};
  int dataset3[] = {0,3,2,1,4,7,6,5,8,9,10};
  int dataset4[] = {2,1,1,1,1,1,1,1,1,1,1};
  int dataset5[] = {100,201,52,3223,24,55,623,75,8523,-9,150};
  int dataset6[] = {-1,1,2,-3,4,5,-6,7,8,-9,10};
  
  // Sort our integer array
  sortIntegers(dataset1, 11);
  sortIntegers(dataset2, 11);
  sortIntegers(dataset3, 11);
  sortIntegers(dataset4, 11);
  sortIntegers(dataset5, 11);
  sortIntegers(dataset6, 11);
  
  // Print out an array
  printIntArray(dataset1, 11);
  printIntArray(dataset2, 11);
  printIntArray(dataset3, 11);
  printIntArray(dataset4, 11);
  printIntArray(dataset5, 11);
  printIntArray(dataset6, 11);

#else

  if (argc != 2) {
    printf("One argument expected: ./insertion 1000\n");
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
  sortIntegers(random,size);
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
