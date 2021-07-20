#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Include file for standart input/output


void printIntArray(int* array, unsigned int size); 

int merge(int arr[], int l, int m, int r) {
  int subarray1[m-l+1];
  int subarray2[r-(m+1)+1];
  
  int indexSub1 = 0;
  int indexSub2 = 0;
  int mixedUpness = 0;
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

    if(subarray1[indexSub1] > subarray2[indexSub2]){

      arr[indexParent] = subarray2[indexSub2];
      mixedUpness = mixedUpness + (m-l - indexSub1 + 1);
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

  return mixedUpness;
}

int mergeandCalculate(int* array, int l, int r){
	int i = 0;
  if(r > l){

    int m = ( r + l ) /2;
    i = i + mergeandCalculate(array, l, m);
    i = i + mergeandCalculate(array, m+1, r);
    i = i + merge(array, l, m, r);


  }

  return i;

}



int sortIntegers(int* array, unsigned int size){
  	int i = mergeandCalculate(array, 0, size-1);
  	return i;




}


void printIntArray(int* array, unsigned int size){
  unsigned int i; // Note: 'unsigned int' is a datatype for storing positive integers.
  for(i = 0; i < size; i=i+1){
    printf("%d ",array[i]);
  }
  printf("\n");
}

int main(int argc, char* argv[]){
	int example1[] = {4, 8, 1, 2, 3, 5, 7, 6};
	int example2[] = {100, 87, 65, 10, 54, 42, 27, 37};

	int mixedUpness1=sortIntegers(example1, 8);
	printf("The Mixed-Up-ness for example1 is %d\n", mixedUpness1);
	printIntArray(example1, 8);
	int mixedUpness2 = sortIntegers(example2, 8);
	printf("The Mixed-Up-ness for example2 is %d\n", mixedUpness2);
	printIntArray(example1, 8);



  return 0;
}


