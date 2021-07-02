#include <stdio.h>
#include <stdlib.h>

//Create two structs, node and slist firstly
typedef struct nodeD
{
	int data;
	struct  nodeD* next;
	struct  nodeD* prev;
}node_d;

typedef struct dlist
{
	node_d* head;
	node_d* tail;
	int size;
}dlist_t;

//makeNode function to create a new node.
node_d* makeNodeD(int data){

    node_d* newNode = (node_d*)malloc(sizeof(node_d));
    if (newNode == NULL) {
        return NULL;
        }
    newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL; 

	return newNode;
}


//Make a Slist
dlist_t* makeDLL(){

	dlist_t* newList =(dlist_t*)malloc(sizeof(dlist_t));
	if(newList == NULL){
	return NULL;
	}
	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;
	return newList;
}

//insert elements to the linked list
int addinD(dlist_t* slist, int pos, int value){


	if(slist ==NULL || pos<0 || pos> slist-> size){
		return 0;
	}
	
	//Create a new node
	node_d* newNode= makeNodeD(value);
	//When the position is 0
	if(pos == 0){
		//if the slist is an empty one;
		if (slist-> size == 0){
			slist-> head = newNode;
			slist-> tail = newNode;
			slist-> size ++;
			return 1;

		}
		//if the slist isn't empty, derectly insert at the first pos
		newNode->next = slist->head;
		newNode->prev = NULL;
		slist->head->prev = newNode;
		slist->head = newNode;
		slist->size ++;
		return 1;
	}
	
	//if adding in the end

	if (pos==slist->size){
		slist->tail->next = newNode;
		newNode->prev = slist->tail;
		slist->tail = newNode;
		slist->size ++;
		return 1;
	}
	
	node_d* formerNode = slist->head;
	for(int i=0; i<pos-1; i++)
	{
		formerNode = formerNode->next;
	}	
	node_d* nextNode = formerNode-> next;
	if(newNode ==NULL || formerNode==NULL || nextNode == NULL)
	{
		return 0;
	}
	//for other situations
	newNode->next = nextNode;
	newNode-> prev = formerNode;
	nextNode-> prev = newNode;
	formerNode-> next = newNode;
	
	slist->size ++;

	return 1;

}

//Delete an element in a certain pos
int deleteD(dlist_t* slist, int pos){

	if(slist == NULL|| pos <0 || pos >= slist->size){
		return 0;
	}
	
	//aftDelNode: the node after the deleted position
	node_d* aftDelNode;
	//delNode: the node at the deleted position
	node_d* delNode  = slist -> head;
	//befDelNode: the node before deleted position
	node_d* befDelNode = slist-> head;

	//if delete at the first place
	if(pos == 0){
		delNode = NULL;
		slist-> head = slist-> head -> next;
		slist-> head->prev = NULL;
		slist-> size--;
		free(delNode);
		return 1;
	}

	//if the delete pos is at the end
	if(pos == slist->size-1){
		int i = 0;
		delNode = slist -> tail;
		befDelNode = delNode->prev;
		free(delNode);
		delNode = NULL;
		befDelNode-> next = NULL;
		slist-> tail = befDelNode;
		slist-> size --;
		return 1;
	
	}

	//for other situations
	int i = 0;
	//find befDelNode at first
	while(i < pos-1){
		befDelNode =  befDelNode -> next;
		i += 1;
	}

	delNode = befDelNode -> next;
	aftDelNode = delNode -> next;
	
	delNode = NULL;
	free(delNode);

	befDelNode->next = aftDelNode;
	aftDelNode->prev = befDelNode;
	slist->size -=1;
	return 1;
	
}
//search function to search if an element is in the list.
void searchD(dlist_t* slist, int num){
	if(slist == NULL){
		printf("Error\n");
		return;
	}

	node_d* node = slist->head;
	for(int i = 0; i < slist-> size; i++ ){
		if (node->data == num ){
			printf("The element %d is in the list\n", num);
			return;
		}	
		node = node-> next;
	}
	printf("Sorry, the element %d is not in the list\n", num);
	return;
}

//printNode function to print the element in the node
void printNodeD(node_d* node){
	node_d* itr = node;
	while(itr != NULL){
	
		printf("%d ", itr-> data);
		itr = itr-> next;
	}
	printf("\n");
}

//freeSlist to free every part stored in the heap
void freeDLL(dlist_t* slist){
	if (slist == NULL){
	return; 
	}
	node_d* node = slist->head;
	node_d* pn;
	while(node!=NULL){
		pn = node -> next;	
		free(node);
		node = pn;		
	}
	free(slist);
}

//printSlist to print the data in the list
void printDLL(dlist_t* slist){
	if(slist == NULL){
		return;
	}
	node_d* node = slist->head;
	
	for(int i=0; i<slist->size; i++){
	
		printf("%d ", node->data);

		node = node->next;
	}
	printf("\n");
	}

//makeQueue to establish a new queue using DLL
dlist_t* makeQueueDLL(){
	dlist_t* queue = makeDLL();
	return queue;
}

//inQueue function to add elements to the queue
void inQueueDLL(dlist_t* queue, int element){
	addinD(queue, queue-> size, element);
}
//outQueue function to remove the first element to the queue

void outQueueDLL(dlist_t* queue){
	deleteD(queue, 0);
}

//makeStack function to create a new stack
dlist_t* makeStackDLL(){
	dlist_t* stack = makeDLL();
	return stack;
}

//inStack function to add elements in stack by order
void inStackDLL(dlist_t* stack, int element){
	addinD(stack, stack-> size, element);
}

//outStack function to remove elements on the stacks in order
void outStackDLL(dlist_t* stack){
	deleteD(stack, stack->size-1);
}

//main function to test the usage of stack and queue