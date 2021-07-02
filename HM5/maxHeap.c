//Luyi Xiao
//HM5 CS 5008
//June 12, 2021

#include <stdio.h>
#include <stdlib.h>

//Create a node struct which is the basic part in slist
typedef struct node {
	int data;
	struct node* next;
} node_t;

//Create a singlar linked list struct (SLL)
typedef struct slist{

	node_t* head;
	node_t* tail;
	int size;
} slist_t;

//define a function makeSlist to create a slist with size = 1 and return.
//Notice: As the first position of the maxHeap should be empty, we set the new slist's size be 1.
slist_t* makeSlist(){

	slist_t* newSlist = (slist_t*)malloc(sizeof(slist_t));
	if(newSlist == NULL){
		return NULL;
	}
	newSlist-> head = NULL;
	newSlist-> tail = NULL;
	newSlist-> size = 1;

	return newSlist;
}

//makeNode function to make a node with data value in it 
node_t* makeNode(int data){

	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if(newNode == NULL){
		return NULL;
	}
	newNode -> data = data;
	newNode -> next = NULL;
	return newNode;
}


//search function to search the node at the given position
node_t* search(slist_t* sll, int pos){

	node_t* newNode = sll-> head;
	if(pos<= 0 || pos > sll-> size-1){ return NULL ;}

	for(int i =1; i <pos; i++){

		newNode = newNode -> next;
	}

	return newNode;
}

//getData function to get the data at certain position of an SLL
int getData(slist_t* sll, int pos){
	if( pos < 1 || pos > sll-> size-1){ return 0 ; }

	node_t* newNode = search(sll, pos);
	int data = newNode-> data;
	return data;
}

//changeData function is to change the data at a given pos to a new Value (newValue)
int changeData(slist_t* sll, int pos, int newValue){
	if(pos<1 || pos> sll-> size-1){return  0;}
	node_t* newNode = search(sll, pos);
	newNode-> data = newValue;

	return 1;
}

//exchangeData function is to exchange the data of two nodes in the sll.
//This is really useful in rearrenging the maxHeap list.
int exchangeData(slist_t* sll, int pos1, int pos2){

	node_t* node1 = search(sll, pos1);
	node_t* node2 = search(sll, pos2);

	int temp = node1-> data;
	node1-> data = node2 -> data;
	node2-> data = temp;

	return 1;
}

//add function to add an element in the sll
//There are two steps in add function: First, add an node that contains the data value to the end of the maxHeap
//Then re-arrenge the maxHeap to the right order.
int add(slist_t* sll, int data){
	if(sll == NULL){ return 0;}

	node_t* newNode = makeNode(data);
	if (newNode == NULL){ return 0;}

	//in this function, we divide into two situations to establish this. First, if the size is 1, it contains no effective value
	//So we just let the head and tail of the sll be the newnode; 


	if (sll-> size == 1){

		sll->head = sll-> tail = newNode;
		sll->size ++;
		return 1;
	}

	//Second, if the size is larger than 1; we need to add the new node at last, and then rearrange it.
	sll->tail-> next = newNode;
	sll-> tail = newNode;
	sll-> size ++;
	//The child position of the new node is now the last pos of the sll, and we need to search with every parent class of 
	//this child pos until the parent element is larger than(or equal to ) child element. 
	int childpos = sll->size-1;
	int parentpos = childpos/2;

	//The while loop will stop when the parent value is larger than or equal to child element 
	//or the child positon is equal to 1(as the least pos of the child pos is 2)

	while(getData(sll, parentpos)< getData(sll, childpos) && childpos > 1){

		exchangeData(sll, parentpos, childpos);
		//The new child pos is equal to the parent pos 
		childpos = parentpos;
		parentpos = childpos/2;

	}


	return 1;
}
//delete function is to delete an element of the node, and rearrange the maxHeap
int delete(slist_t* sll, int pos) {

	if (pos <= 0 || pos > sll->size-1 || sll == NULL){
		return 0;
	}
	//In delete funciton, we discussed about 4 possibilities : maxHeap with one value(size = 2);
	//maxHeap with two values (size = 3); deleted the last element of the heap;
	//and maxHeap with more than two values (size > 3);
	//As for the last possibility it may need to change some fields from three nodes - before delete node, 
	//delete node and after delete node
	
	//When with one value or size = 2, after deleting, it became a blank maxHeap

	if (sll-> size == 2){
		node_t* onlyNode = sll-> head;
		free(onlyNode);
		sll-> head = sll-> tail = NULL;
		sll-> size = 1;
		return 1;


	}

	//When with one value or size = 2, it became a maxHeap with only one value

	if (sll-> size == 3){
		node_t* delNode = search(sll, pos);
		node_t* remainNode = search(sll, 3-pos);
		delNode = NULL;
		free(delNode);
		sll-> tail = sll-> head = remainNode;
		sll->size --;
		return 1;


	}


	//When deleting the last element of the heap, it doesnt need more complex operations. 
	if (pos == sll-> size-1){

		node_t* delNode = sll-> tail;
		node_t* befDelNode = search(sll, sll->size-2);

		delNode = NULL;
		free(delNode);

		sll->tail = befDelNode;
		befDelNode-> next = NULL;
		sll-> size --;

		return 1;

	}

	//In the most common possibilities, we need to delete the node that is targeted, and move the last node to the deleted one
	//and then connect the next field again.

	node_t* delNode =  search(sll, pos);
	node_t* aftDelNode = search(sll, pos+1);
	delNode =NULL;

	free(delNode);
	node_t* insertNode = sll-> tail;
	insertNode-> next = aftDelNode;

	node_t* befLastNode = search(sll, sll->size-2);
	sll-> tail = befLastNode;
	befLastNode-> next = NULL;

	sll -> size --;

	if (pos == 1){
		sll-> head = insertNode;
	}

	else{
	node_t* befDelNode = search(sll, pos-1); 
	befDelNode -> next = insertNode;
	}

	//compare and replace
	int parentpos = pos;
	int childpos1 = pos*2;
	int childpos2 = pos*2 +1;
	

	while((getData(sll, parentpos) < getData(sll, childpos1) 
		|| getData(sll, parentpos) < getData(sll, childpos2) )
		&& childpos1<=sll-> size){

		if (getData(sll, parentpos) < getData(sll, childpos1) ) {
			exchangeData(sll, parentpos, childpos1);
			parentpos = childpos1;
		}
		else{

			exchangeData(sll, parentpos, childpos2);
			parentpos = childpos2;
		}

		childpos1 = parentpos*2;
		childpos2 = parentpos*2 +1;


	}

	return 1;


}




//freeSlist function to free every malloc addresses
int freeSlist(slist_t* sll){

	if (sll == NULL){

		return 0;
	}

	node_t* newNode = sll-> head;
	while(newNode){
	node_t* np = newNode;
	newNode = newNode -> next;
	free(np);

}

	free(sll);


	return 1;

}



//printS funcition to print every value
int printS(slist_t* sll){

	if (sll == NULL){
		return 0;
	}
	node_t* newNode = sll -> head;
	while(newNode){
		printf("%d ", newNode-> data);
		newNode = newNode -> next;
	}
	printf("\n");
	return 1;
}



int main(){
	slist_t* maxHeap = makeSlist();
	add(maxHeap, 4);
	printS(maxHeap);
	add(maxHeap, 5);
	printS(maxHeap);
	add(maxHeap, 3);
	printS(maxHeap);
	add(maxHeap, 4);
	printS(maxHeap);
	add(maxHeap, 6);
	printS(maxHeap);
	add(maxHeap, 7);
	printS(maxHeap);


	delete(maxHeap, 2);
	printS(maxHeap);
	delete(maxHeap, 1);
	printS(maxHeap);
	freeSlist(maxHeap);
	return 0;

}