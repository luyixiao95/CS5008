//Luyi Xiao
//CS 5008 Vector
//Revised by Vido's work

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vector{
	int* data;
	int size;
	int capacity;

}vector_t;


//function to create a vector
vector_t* makeVector(int initCapacity){
	vector_t* vector = (vector_t*)malloc(sizeof(vector_t));

	if (vector == NULL){
		return NULL;}

	vector->data = (int*)malloc(sizeof(int) * initCapacity);
	vector->size = 0;
	vector->capacity = initCapacity;
	return vector;	
}

//To test if the vector is empty

bool isEmpty(vector_t* vector){

	if (vector-> data == NULL){
		return true;
	}
	return false;

}

//resize function to expand the vector's capacity for 2 times
int resize(vector_t* vector){
	if (vector == NULL){
		return 0;
	}

	vector -> capacity = vector-> capacity * 2 ;

	int* newData = (int*) malloc(sizeof(int) * vector-> capacity);
	if (newData == NULL || vector -> data == NULL){
		return 0;
	}
	
	for(int i=0; i < vector -> size; i++){
	
		newData[i] = vector->data[i];
	}
	
	free(vector -> data);
	vector->data = newData;
	return 1;

}


// append function to add a new element at the end of the vector

int append(vector_t* vector, int element){
	if(vector == NULL){
		return 0;
	}
	
	if (vector-> data == NULL){
		return 0;
	}

	//If the size of the vector is equal to the capacity, expand the size of the vector
	//Using resize function

	if (vector -> size == vector -> capacity){
		int resizeSuccess = resize(vector);
		if(resizeSuccess == 0) {
		return 0;
		}
	}

	//Add the new element at the end of the vector
	vector->data[vector -> size] = element;
	vector->size +=1;
       	return 1;	
}


//add function to add a new element in any place of the vector
int add(vector_t* vector, int pos, int element){
	if(vector == NULL || pos < 0){
	return 0; 
}

	if(pos ==vector-> size){
		return append(vector, element);
	}
	//Resize the vector if it is full
	if(vector->size == vector-> capacity){
		int successOnResize = resize(vector);
		if (successOnResize ==0){
		return 0;}
		}

	if(vector->data == NULL){
		return 0;
	}

	for (int i = vector->size +1; i>=pos; i--){
		vector->data[i+1]=vector-> data[i];
	}


	vector->data[pos]=element;
	vector->size +=1;
	return 1;

	}

//push_front function to add a new element in the beginning of the vector
int push_front(vector_t* vector, int element){

	return add(vector, 0, element);

}

//delete function to delete a element in the certain position
int delete(vector_t* vector,  int pos){

	if (vector == NULL || pos >= vector-> size|| pos < 0){
		return 0;
	}

	if (pos == vector-> size -1){
		vector-> data[pos] = NULL;
		vector-> size -=1;

		return 1;
	}
	
	vector->data[pos]=NULL;
	for(int i = pos +1; i < vector-> size; i++){
		vector-> data[i-1]=vector-> data[i];
	}

	vector-> data[vector-> size-1] = NULL;
        vector -> size -=1;
	return 1;
}

//Search function to search if an element is inside the vector

bool contains(vector_t* vector, int num){

	if (vector == NULL){
		return false;
	}

	for(int i=0; i< vector->size; i++){
		if(vector->data[i]==num){
		
			printf("The number %d is in the vector\n", num);
			return true;

		}
	
	}

	printf("Sorry, the number %d is not in the vector\n", num);
	return false;

}



//Print function to print all elements in the vector
void print(vector_t* vector){

	if (vector == NULL){
	
		return;
	}

	if (vector -> data == NULL){
		return; 
	}

	for(int i=0; i < vector->size; i++){
	
		printf("%d ", vector->data[i]);
	
	}

	printf("\n");

}

//free vector to free all things stored in the heap memory
void freeVector(vector_t* vector){
	if ( vector == NULL){
		return ;
	}
		
	if (vector-> data !=NULL){
		free(vector->data);
	}

	free(vector);

}


//inQueue function to add an element to the queue
void inQueue(vector_t* queue, int element){
	append(queue, element);
}

//outQueue function to remove the first element in the queue
void outQueue(vector_t* queue){

	delete(queue, 0);
}

//inStack function to add an element to a stack
void inStack(vector_t* stack, int element){
	append(stack, element);
}
//outStack fucntion to remove the last element in the stack
void outStack(vector_t* stack){
	delete(stack, stack->size-1);
}


//The main function is to add the data from the text.txt to the vector 
int main(int args, char **argv){
	FILE* fp = fopen(argv[1], "r");
	//create a new queue
	vector_t* queue = makeVector(10);
	printf("Test for queue io\n");
	printf("firstly add all the elements to the queue by order:\n");
	//import the data of the file
	int buffer;
	while(1==fscanf(fp, "%d", &buffer)){
		inQueue(queue, buffer);

	}

	fclose(fp);

	print(queue);
	printf("next, remove the first two elements in order as a rule of queue:\n");
	//Out
	outQueue(queue);
	outQueue(queue);
	print(queue);

	//Free

	printf("test stack\n");

	//test outStack
	outStack(queue);
	print(queue);
	freeVector(queue);

}

	
