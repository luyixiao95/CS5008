//Luyi Xiao
//CS 5008 Vector
//Revised by Vido's work

#include <stdio.h>
#include <stdlib.h>

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


// push_back function to add a new element at the end of the vector

int push_back(vector_t* vector, int element){
	if(vector == NULL){
		return 0;
	}
	
	if (vector-> data == NULL){
		return 0;
	}


	if (vector -> size == vector -> capacity){
		int resizeSuccess = resize(vector);
		if(resizeSuccess == 0) {
		return 0;
		}
	}

	vector->data[vector -> size] = element;
	vector->size +=1;
       	return 1;	
}


//insert function to add a new element in any place of the vector
int insert(vector_t* vector, int pos, int element){
	if(vector == NULL || pos < 0){
	return 0; 
}

	if(pos ==vector-> size){
		return push_back(vector, element);
	}
	
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

	return insert(vector, 0, element);

}

//delete function to delete a element in the certain position
int delete(vector_t* vector,  int pos){

	if (vector == NULL || pos >= vector-> size|| pos < 0){
		return 0;
	}

	if (pos == vector-> size -1){
		vector-> data[pos] = NULL;
		vector-> size -=1;
<<<<<<< HEAD
		return 0;
=======

		return 1;
>>>>>>> fa955ea7253c4f20585d0628e98ae618e23a1652
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

void search(vector_t* vector, int num){

	if (vector == NULL){
		return ;
	}

	for(int i=0; i< vector->size; i++){
		if(vector->data[i]==num){
		
			printf("The number %d is in the vector\n", num);
			return ;

		}
	
	}

	printf("Sorry, the number %d is not in the vector\n", num);
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

//Test when insert to the vector
int test_insert(){

	//for empty vectors
	vector_t* empVector1=makeVector(4);
	printf("for empty vectors: \n");
	//insert at the front
	insert(empVector1, 0, 1);
	if (empVector1->data[0] != 1){
		printf("inserting at the front falied\n");
	}

	else {printf("inserting at the front isn't  faieed\n");}
	
	
	freeVector(empVector1);


	//insert at the middle
	vector_t* empVector2 =makeVector(4);
	insert(empVector2, 3, 3);
	
	if (empVector2->data[3]!=3){
		printf("insert at the middle failed\n");

	}
	
	else{printf("insert at the middle isn't failed \n");}

	freeVector(empVector2);
	//insert at the end
	vector_t* empVector3 = makeVector(4);
	insert(empVector3, 4, 4);

	if (empVector3-> data[4] !=4){
		
		printf("insert at the end failed\n");

	}


	else {printf("insert at the end isn't failed\n");}

	freeVector(empVector3);
	
	//for vector with elements
	vector_t* fullVector=makeVector(4);
	for(int i= 0; i<4; i++){
	insert(fullVector, i, i);
	}
	

	insert(fullVector,4 , 4);
	insert(fullVector,0, 0);
	insert(fullVector,2, 2);


	if (fullVector -> data[0] !=0 ||  fullVector-> data[2]!= 2 || fullVector ->data[6] != 4 ){
	
	printf("There are failure when inserting to a full vector\n");}

	else {printf("Nothing is wrong when inserting an element to a full vector\n");}

	freeVector(fullVector);


	return 1;


}

int main(){
	test_insert();

//test delete and search;
	
	vector_t* vector = makeVector(4);
	insert(vector, 0, 0);
	insert(vector, 1, 1);
	insert(vector, 2, 2);
	insert(vector, 3, 3);


	print(vector);
	delete(vector, 2);
	delete(vector, 1);
	delete(vector, 1);
	print(vector);
	

	search(vector, 5);
	search(vector, 0);
	
	freeVector(vector);
	return 0;

}

//Use valgrind to make sure that there is no memeory leakage.
