#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node* next;
} node_t;

typedef struct slist{

	node_t* head;
	node_t* tail;
	int size;
} slist_t;

//define a function makeSlist to create an empty slist and return.
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

int getData(slist_t* sll, int pos){
	if( pos < 1 || pos > sll-> size-1){ return 0 ; }

	node_t* newNode = search(sll, pos);
	int data = newNode-> data;
	return data;
}

int changeData(slist_t* sll, int pos, int newValue){

	node_t* newNode = search(sll, pos);
	newNode-> data = newValue;

	return 1;
}

int exchangeData(slist_t* sll, int pos1, int pos2){

	node_t* node1 = search(sll, pos1);
	node_t* node2 = search(sll, pos2);

	int temp = node1-> data;
	node1-> data = node2 -> data;
	node2-> data = temp;

	return 1;
}


int add(slist_t* sll, int data){
	if(sll == NULL){ return 0;}

	node_t* newNode = makeNode(data);
	if (newNode == NULL){ return 0;}

	if (sll-> size == 1){

		sll->head = sll-> tail = newNode;
		sll->size ++;
		return 1;
	}

	sll->tail-> next = newNode;
	sll-> tail = newNode;
	sll-> size ++;
	int childpos = sll->size-1;
	int parentpos = childpos/2;


	while(getData(sll, parentpos)< getData(sll, childpos) && childpos > 1){

		exchangeData(sll, parentpos, childpos);

		childpos = parentpos;
		parentpos = childpos/2;

	}


	return 1;
}

int delete(slist_t* sll, int pos) {

	if (pos <= 0 || pos > sll->size-1 || sll == NULL){
		return 0;
	}

	if (sll-> size == 2){
		node_t* onlyNode = sll-> head;
		free(onlyNode);
		sll-> head = sll-> tail = NULL;
		sll-> size = 1;
		return 1;


	}

	if (sll-> size == 3){
		node_t* delNode = search(sll, pos);
		node_t* remainNode = search(sll, 3-pos);
		delNode = NULL;
		free(delNode);
		sll-> tail = sll-> head = remainNode;
		sll->size --;
		return 1;


	}

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


