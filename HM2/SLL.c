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

slist_t* makeSlist(){

	slist_t* newList =(slist_t*)malloc(sizeof(slist_t));
	if(newList != NULL){
	return 0;
	}
	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;
	return newList;
}


node_t* makeNode(int data){

        node_t* newNode = (node_t*)malloc(sizeof(node_t));
        if (newNode == NULL) {
        return NULL;
        }
        newNode->data = data;
	newNode-> next = NULL;

	return newNode;
}

void freeNode(node_t* node) {
        if (node == NULL) {
        return; }

        free(node);
}


//get the node at the nth place of the slist
node_t*  getCertainNode(slist_t* slist , int n){
	
	if(slist ==NULL){
		return NULL;
	}

	node_t* node = (node_t*)malloc(sizeof(node_t));
	if(node == NULL){
		return NULL;

	}

	node = slist->head;
	int i = 0;

	while(i<n){
		node = node-> next;
		n += 1;

	}


	return node;

}

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
	slist-> size =1;
	return 1;

	}

	if(slist-> head != NULL){
		newNode->next = slist-> head;
		slist-> head = newNode;
	
	
	slist-> size= slist->size+1;
	
	} 
	return 1;
}

int push_back(slist_t* slist, int value){
	if(slist == NULL){
	
		return 0;}
        
	node_t* newNode = makeNode(value);

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
                slist->tail->next = newNode;
                newNode-> next = NULL;

	  
	slist-> size = slist -> size + 1;

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
	}

	if (pos==slist->size-1){
	push_back(slist, value);
	}


	node_t* newNode= makeNode(value);
	node_t* formerNode = getCertainNode(slist, pos);
	node_t* nextNode = formerNode-> next;

	if(newNode ==NULL|| formerNode==NULL||nextNode == NULL){
	return 0;}

	formerNode->next = newNode;

	newNode->next = nextNode;

	slist->size +=1;

	freeNode(formerNode);


	return 1;


}




void printNode(node_t* node){
	node_t* itr = node;
	while(itr != NULL){
	
		printf("%d ", itr-> data);
		itr = itr-> next;
	}
	printf("\n");
}



void freeSlist(slist_t* slist){

	if (slist == NULL){
	return; 
	}
	


	node_t* node = slist->head;
	for(int i = 0; i < slist->size;i++){
		freeNode(node);
		node = node->next;
		
	}

	free(slist);
}

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


int main(){
	
//functions:makeSlist(), push_front(), push_back(), insert(), freeSList()	  
	
	

	slist_t* slist = makeSlist();
	push_front(slist, 1);
	printf("%d", slist->head->data);
//	push_back(slist, 3);
//	insert(slist, 1, 2);
// 	printSlist(slist);
	freeSlist(slist);

		
	
	return 0;

}


