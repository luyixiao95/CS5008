#include <stdio.h>
#include <stdlib.h>

//mixedUpness function to use BF way to calculate the mixedUp-ness
//value of a certain array
int mixedUpness(int* array, int size){
	int mixedUpness = 0;
	for(int i = 0; i< size-1; i++){

		for(int j = i+1; j < size; j++){

			if(array[i] > array[j]){
				mixedUpness ++;
			}
		}



	}


	return mixedUpness;
}


//PrintIntArray to print every element of the array
void printIntArray(int* array, unsigned int size){

	for(int i = 0; i < size; i++){

		printf("%d", array[i]);
	}

	printf("\n");
}

int main(int argc, char* argv[]){

	int example1[] = {4, 8, 1, 2, 3, 5, 7, 6};
	int example2[] = {100, 87, 65, 10, 54, 42, 27, 37};

	int mixedUpness1 = mixedUpness(example1, 8);
	printf("The Mixed-Up-ness for example1 is %d\n", mixedUpness1);
	int mixedUpness2 = mixedUpness(example2, 8);
	printf("The Mixed-Up-ness for example2 is %d\n", mixedUpness2);

	return 0 ;

}