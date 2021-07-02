//Luyi Xiao
//CS 5008, SLL
//Revised by Vido


#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;

}node_t;

typedef struct slist{
	node_t* head;
	node_t* tail;
	int size;

}slist_t;

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

// Make a node
node_t* makeNode(int data){

        node_t* newNode = (node_t*)malloc(sizeof(node_t));
        if (newNode == NULL) {
        return NULL;
        }
        newNode->data = data;
	newNode-> next = NULL;

	return newNode;
}

//When adding node on the first place of the SLL
int push_front(slist_t* slist, int value){
	if(slist == NULL){
	return 0;
	}

	node_t* newNode = makeNode(value);

	if(newNode == NULL){
		return 0;
	}

	if(slist->head == NULL && slist->tail == NULL){
	
	slist-> head = newNode;
	slist-> tail = newNode;
	newNode-> next = NULL;
	slist-> size =1;
	return 1;

	}

	if(slist-> head != NULL){
		newNode->next = slist-> head;
		slist-> head = newNode;
		slist-> size= slist-> size +1 ;
	}
	return 1;
	
}



//When adding node at the end of the list
int push_back(slist_t* slist, int value){
	if(slist == NULL){
	
		return 0;}
        
	node_t* newNode = makeNode(value);
	node_t* lastNode = slist-> head;
	while(lastNode->next != NULL){
	
	lastNode = lastNode -> next;
	}

        if(newNode == NULL){
            return 0;
        }

        if(slist->head == NULL && slist->tail == NULL){

        	slist-> head = newNode;
        	slist-> tail = newNode;
        	slist-> size =1;
			return 1;
	}

        if(slist-> tail != NULL){
                
        lastNode-> next =newNode;	
	  	slist-> tail =newNode;
		newNode -> next = NULL;

		slist-> size += 1;

	}

	return 1;

}


//insert elements to the linked list
int insert(slist_t* slist, int pos, int value){


	if(slist ==NULL || pos<0){
	
		return 0;
	
	}
	
	if(pos == 0){
	
	push_front(slist, value);
		return 1;

	}

	if (pos==slist->size){
	push_back(slist, value);
		return 1;
	}


	node_t* newNode= makeNode(value);
	
	node_t* formerNode = slist->head;

	for(int i=0; i<pos-1; i++)
	{
	
	formerNode = formerNode->next;

	}	

	node_t* nextNode = formerNode-> next;

	if(newNode ==NULL|| formerNode==NULL||nextNode == NULL){
		return 0;}

	newNode-> data = value;	
	newNode->next = nextNode;
	formerNode-> next = newNode;
	
	slist->size +=1;

	return 1;


}

//delete an element in the list with certain position
int delete(slist_t* slist, int pos){

	if(slist == NULL|| pos <0 || pos >= slist->size){
		return 0;
	}
	
	
	node_t* AftDelNode;
	
	node_t* delNode  = slist -> head;
	node_t* befDelNode = slist-> head;

	if(pos == 0){
		delNode = NULL;
		slist-> head = slist-> head -> next;
		slist-> size-=1;
		free(delNode);
		return 1;
	}


	if(pos == slist->size-1){
		int i = 0;

		while(i < slist-> size-2){
			befDelNode = befDelNode -> next;
		       i+=1;	
		}
		//Find out the new tail node
		delNode = befDelNode -> next;
		free(delNode);
		slist-> tail = befDelNode;
		befDelNode-> next = NULL;
		slist-> size -=1;
		return 1;
	
	}

	int i = 0;
	while(i < pos-1){
	
		befDelNode =  befDelNode -> next;
		i += 1;

	}

	delNode = befDelNode -> next;
	AftDelNode = delNode -> next;
	
	delNode = NULL;
	free(delNode);

	befDelNode->next = AftDelNode;
	slist->size -=1;
	return 1;
	

}

//search if a number is in a list

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

//makeQueue to establish a new queue using SLL
slist_t* makeQueue(){
	slist_t* queue = makeSlist();
	return queue;
}

//inQueue function to add elements to the queue
void inQueue(slist_t* queue, int element){
	insert(queue, queue-> size, element);
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
	push_back(stack, element);
}

//outStack function to remove elements on the stacks in order
void outStack(slist_t* stack){
	delete(stack, stack->size-1);
}

//main function to test the usage of stack and queue

int main(int args, char** argv){
	
	
	
	printf("firstly test the queue used by SLL, make a new queue\n");
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

	


	printf("Next, test the stack\n");
	outStack(queue);
	outStack(queue);
	printSlist(queue);
	freeSlist(queue);
	return 0;

}


