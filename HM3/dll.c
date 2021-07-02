#include <stdio.h>
#include <stdlib.h>

//Create two structs, node and slist firstly
typedef struct node
{
	int data;
	struct  node* next;
	struct  node* prev;
}node_t;

typedef struct slist
{
	node_t* head;
	node_t* tail;
	int size;
}slist_t;

//makeNode function to create a new node.
node_t* makeNode(int data){

    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL) {
        return NULL;
        }
    newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL; 

	return newNode;
}


//Make a Slist
slist_t* makeSlist(){

	slist_t* newList =(slist_t*)malloc(sizeof(slist_t));
	if(newList == NULL){
	return NULL;
	}
	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;
	return newList;
}

//insert elements to the linked list
int add(slist_t* slist, int pos, int value){


	if(slist ==NULL || pos<0 || pos> slist-> size){
		return 0;
	}
	
	//Create a new node
	node_t* newNode= makeNode(value);
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
	
	node_t* formerNode = slist->head;
	for(int i=0; i<pos-1; i++)
	{
		formerNode = formerNode->next;
	}	
	node_t* nextNode = formerNode-> next;
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
int delete(slist_t* slist, int pos){

	if(slist == NULL|| pos <0 || pos >= slist->size){
		return 0;
	}
	
	//aftDelNode: the node after the deleted position
	node_t* aftDelNode;
	//delNode: the node at the deleted position
	node_t* delNode  = slist -> head;
	//befDelNode: the node before deleted position
	node_t* befDelNode = slist-> head;

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
void search(slist_t* slist, int num){
	if(slist == NULL){
		printf("Error\n");
		return;
	}

	node_t* node = slist->head;
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
void printNode(node_t* node){
	node_t* itr = node;
	while(itr != NULL){
	
		printf("%d ", itr-> data);
		itr = itr-> next;
	}
	printf("\n");
}

//freeSlist to free every part stored in the heap
void freeSlist(slist_t* slist){
	if (slist == NULL){
	return; 
	}
	node_t* node = slist->head;
	node_t* pn;
	while(node!=NULL){
		pn = node -> next;	
		free(node);
		node = pn;		
	}
	free(slist);
}

//printSlist to print the data in the list
void printSlist(slist_t* slist){
	if(slist == NULL){
		return;
	}
	node_t* node = slist->head;
	
	for(int i=0; i<slist->size; i++){
	
		printf("%d ", node->data);

		node = node->next;
	}
	printf("\n");
	}

//makeQueue to establish a new queue using DLL
slist_t* makeQueue(){
	slist_t* queue = makeSlist();
	return queue;
}

//inQueue function to add elements to the queue
void inQueue(slist_t* queue, int element){
	add(queue, queue-> size, element);
}
//outQueue function to remove the first element to the queue

void outQueue(slist_t* queue){
	delete(queue, 0);
}

//makeStack function to create a new stack
slist_t* makeStack(){
	slist_t* stack = makeSlist();
	return stack;
}

//inStack function to add elements in stack by order
void inStack(slist_t* stack, int element){
	add(stack, stack-> size, element);
}

//outStack function to remove elements on the stacks in order
void outStack(slist_t* stack){
	delete(stack, stack->size-1);
}

//main function to test the usage of stack and queue

int main(int args, char** argv){
	
	
	
	printf("firstly test the queue used by DLL, make a new queue\n");
	printf("and add data from the given text file\n");
	//firstly make an empty queue
	slist_t* queue = makeQueue();
	FILE* fp = fopen(argv[1], "r");
	int buffer;
	//load the data from the file
	while(1==fscanf(fp, "%d", &buffer)){
		//put the element in the queue in order
		inQueue(queue, buffer);
	}
	fclose(fp);
	printSlist(queue);

	printf("Now, test for outQueue. remove two elements\n");
	outQueue(queue);
	outQueue(queue);
	printSlist(queue);

	printf("Now, test for the outStack\n");
	outStack(queue);
	printSlist(queue);


	outStack(queue);
	printSlist(queue);
	freeSlist(queue);

	
	return 0;



}