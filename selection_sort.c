//CS5008
//Luyi Xiao
//HW 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//First , create a function doing select sort

void selectionSort(int thing[], int  size) {

	//Loop every element in the array	
	for(int i= 0 ; i < size-1 ; i++) {
		
		int min = thing[i];		
		int index = i;
		//Compare this certain element with the elements after it in the array
		for(int j = i + 1 ;j < size; j++){
			
			//Once the certain element is larger than one element after it in the array, switch the position between both of them
			if(thing[j]< min) {
			min = thing[j];
			index = j;			
			}
			thing[j] = thing[i];
			thing[i] = min;
			

		}
	}
	
		
}

//main 
int  main(){
	int my_list[10];
	//create an array contains 10 random int  elements
	for( int k = 0; k<10 ; k++){
		my_list[k] = rand() % 100;
	}

	//Get the size of the array
	int size = sizeof(my_list)/sizeof(my_list[0]);
	//print the original array
	for(int loop1=0; loop1<size ; loop1++){
		printf("%d ", my_list[loop1]);
	}
	printf("\n");
	
	//Sort the list using the function
	selectionSort(my_list, size);

	//print the array after sorting
	for(int loop2=0; loop2<size; loop2++){

		printf("%d ", my_list[loop2]);
	}
	printf("\n");
	return 0;

}
