#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int value;
	int key;
	struct node* next;
	struct node* before;
	struct node* after;

} node_t;

typedef struct bucket{
	node_t* old;
	node_t* new;
}bucket_t;

int hashkey(int key, int length){

	return key%length;
}

typedef int(*hashkey_pointer)(int key, int length);

typedef struct linkedHashMap
{	
	node_t* header;
	bucket_t* bucket;
	int size;
	int capacity;
	int threshold;
	int loadFactor;
	hashkey_pointer p;


}linkedHashMap_t ;

node_t* makenode(int key, int value){

	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	newNode->key = key;
	newNode->value = value;
	newNode -> next = newNode -> before = newNode -> after = NULL;

	return newNode;

} 


linkedHashMap_t* makeLinkedHashMap(int capacity, float loadFactor){
	linkedHashMap_t* newLHM = (linkedHashMap_t*) malloc(sizeof(linkedHashMap_t));
	newLHM -> capacity = capacity;
	newLHM -> loadFactor = loadFactor;
	newLHM -> threshold = capacity * loadFactor;
	newLHM->bucket = (bucket_t*) malloc(sizeof(bucket_t)*capacity);
	newLHM-> header = makenode(0, 0);
	newLHM-> header-> before = NULL;
	newLHM-> header-> after =  NULL;
	newLHM-> header-> next = NULL;
	newLHM-> size = 0;
	newLHM-> p = hashkey;

	//for(int i=0; i < newLHM-> capacity; i++){
		//newLHM -> bucket[i].old = NULL;
		//newLHM -> bucket[i].new = NULL;
	//}


	return newLHM;


}

//delete the hashmap and free the element inside it.
void deleteLHM(linkedHashMap_t* lhm){
	node_t* iterator = lhm-> header-> after;
	for(int i=0; i< lhm-> size; i++){
		node_t* nextIterator = iterator-> after;
		iterator = NULL;
		free(iterator);
		iterator = nextIterator;
	}

	lhm->bucket = NULL;
	free(lhm->bucket);
	lhm->header = NULL;
	free(lhm->header);
	lhm = NULL;
	free(lhm);

	return;

}
void addtoLHM(linkedHashMap_t* lhm, int key, int value);


linkedHashMap_t* resize(linkedHashMap_t* olhm){
	//build a new resize linkedhashmap
	linkedHashMap_t* nlhm = makeLinkedHashMap(olhm->capacity*2, olhm->loadFactor);

	//remove all the element from the old lhm to the new lhm.

	node_t* iterator = olhm -> header -> after;
	for(int i =0; i< olhm->size; i++){
		addtoLHM(nlhm, iterator-> key, iterator-> value);
		iterator = iterator-> next;


	}
	deleteLHM(olhm);
	return nlhm;

}



void addtoLinkList(linkedHashMap_t* lhm, node_t* node){

	int hashkey = lhm->p(node->key, lhm->capacity);

	if(lhm-> size == 0){
		return;
	}
	
		
			node_t* lastnode = lhm->header->before;
			lastnode -> after = node;
			node -> before = lastnode;
			node -> after = lhm->header;
			lhm-> header -> before = node;
			return;

}

void addtoBucket(linkedHashMap_t* lhm, node_t* node){

	int hashkey = lhm->p(node->key, lhm-> capacity);
	if(lhm->size ==0){
		return;
	}

	if(lhm -> bucket[hashkey].old == NULL &&lhm -> bucket[hashkey].new == NULL){

		lhm -> bucket[hashkey].old = lhm -> bucket[hashkey].new = node;
		return;

	}

	lhm->bucket[hashkey].old =  lhm->bucket[hashkey].new;
	lhm->bucket[hashkey].new = node;
	node -> next = lhm->bucket[hashkey].old;
	return;

}

void addtoLHM(linkedHashMap_t* lhm, int key, int value){

	if(lhm->size>= lhm->threshold){

		lhm = resize(lhm);

	}

	node_t* addNode = makenode(key, value);
	int hashkey = lhm->p(key, lhm-> capacity);
	
	if(lhm->size == 0){
		lhm->bucket[hashkey].old = lhm->bucket[hashkey].new = addNode;
		lhm->header->after = lhm->header->before = addNode;
		lhm->size ++;
		addNode->before = addNode->after = lhm->header;

		return;

	}

	addtoLinkList(lhm, addNode);
	addtoBucket(lhm, addNode);
	lhm-> size ++;

	return;

}


node_t* search(linkedHashMap_t* lhm, int key){
	int hashkey = lhm->p(key, lhm->capacity);
	node_t* node = lhm-> bucket[hashkey].new;
	while(node && node->key != key){

		node = node -> next;
	}

	if(node == NULL){
		printf("This key: %d doesn't exist in the linkedhaspmap.\n", key);
		return node; //At this time node is equal to null.
	}

	return node;
}


node_t* previousNode(bucket_t* bucket, node_t* node){
	if(bucket == NULL || node ==NULL){
		return NULL;

	}
	node_t* iterator = bucket->new;

	while(iterator->next->key != node-> key && iterator-> next!=NULL ){
		iterator = iterator-> next;
	}

	if(!(iterator->next)){

		return NULL;
	}

	return iterator;
}


void deleteNodeFromBucket(linkedHashMap_t* lhm,node_t* node){
	int key = node->key;
	int hashkey = lhm->p(key, lhm-> capacity);
	node_t* newerNode = lhm->bucket[hashkey].new;
	node_t* olderNode = lhm->bucket[hashkey].old;

	if(lhm-> size == 0){
		return;
	}

	//only one node in this bucket
	if(node == newerNode && node ==olderNode){

		newerNode = olderNode = NULL;
		
		return;

	}

	if(node == newerNode && node != olderNode){
		newerNode = olderNode;
		if(olderNode-> next){
		olderNode = olderNode-> next;}
		return;
	}

	if(node != newerNode && node == olderNode){
		olderNode = olderNode-> next;
		newerNode->next = olderNode;
		return;
	}

	node_t* BefDel = previousNode(&(lhm->bucket[hashkey]), node);
	node_t* afterDel = node->next;
	
	BefDel-> next = afterDel;

	return;

}

void deleteNodefromLHM(linkedHashMap_t* lhm, int key){

	int hashkey = lhm->p(key, lhm-> capacity);
	if(lhm-> size == 0){
		printf("The lhm is already empty, you cannot delete the node.\n");
		return;
	}

	//delete from the linked list
	node_t* delNode = search(lhm, key);

	if(delNode == NULL){
		return;
	}
	if(delNode == lhm->header->after){
		lhm->header->after = delNode->after;
		delNode->after->before = lhm->header;


	} 

	else if(delNode == lhm->header->before){

		lhm-> header -> before = delNode -> before;
		delNode -> before-> after = lhm-> header;

	}

	else{

		delNode -> before -> after = delNode -> after;
		delNode -> after -> before = delNode -> before;
	}


	deleteNodeFromBucket(lhm, delNode);

	lhm-> size --;
	free(delNode);
	return;

}




node_t* getfirst(linkedHashMap_t* lhm){

	node_t* firstnode = lhm->header->after;

	if(firstnode == NULL){
		printf("This linkedhaspmap is empty.\n");
		return firstnode; //At this time firstnode is empty
	}

	return firstnode;

}

node_t* getlast(linkedHashMap_t* lhm){

	node_t* lastnode =  lhm->header->before;

	if(lastnode == NULL){
		printf("This linkedhaspmap is empty.\n");
		return lastnode; //At this time lastnode is empty
	}

	return lastnode;
}

int getValue(linkedHashMap_t* lhm, int key){

	node_t* node = search(lhm, key);
	if(node == NULL){
		return NULL;
	}
	int value = node-> value;
	return value;
}


void updateValue(linkedHashMap_t* lhm, int key, int value){

	node_t* node = search(lhm, key);
	if(node == NULL){
		return;
	}
	node-> value = value;
	return;
}

void printLHM(linkedHashMap_t* lhm){
	node_t* iterator = lhm->header->after;
	for(int i=0; i<lhm->size; i++){

		printf("{ key:%d, value:%d, hashkey:%d } \n", iterator->key, iterator->value, lhm->p(iterator->key, lhm-> capacity));
		iterator = iterator-> after;
	}

	return;
}

void printBucket(bucket_t* bucket, int hashkey){

	node_t* iterator = bucket ->new;

	if(iterator ==NULL){
		printf("This bucket with hashkey: %d, is unoccupied\n", hashkey);
		return;
	}

	printf("This bucket with hashkey %d contains these nodes :\n", hashkey);
	while(iterator){
		printf("{ key:%d, value:%d, hashkey:%d } \n", iterator->key, iterator->value, hashkey);
		iterator = iterator-> next;

}
}

void swap(linkedHashMap_t* lhm, int key1, int key2){

	int hashkey1 = lhm-> p(key1, lhm->capacity);
	int hashkey2 = lhm-> p(key2, lhm->capacity);

	node_t* node1 = search(lhm, key1);
	node_t* node2 = search(lhm, key2);

	if(node1 == NULL  || node2 ==  NULL){
		return;
	}

	node_t* beforeNode1 = node1-> before;
	node_t* afterNode1 = node1-> after;
	node_t* beforeNode2 = node2 -> before;
	node_t* afterNode2 = node2-> after;

	beforeNode1-> after = node2;
	afterNode1-> before = node2;
	beforeNode2 -> after = node1;
	afterNode2 -> before = node2;

	node1 -> before = beforeNode2;
	node1 -> after = afterNode2;

	node2-> before = beforeNode1;
	node2 -> after = afterNode1;

	return;


}


linkedHashMap_t* sortWithValue(linkedHashMap_t* lhm){


	for(int i =0; i< lhm->size-1; i++){
		node_t* iterator = lhm -> header-> after;

	for(int j =0; j< lhm-> size-i; j++){
		if(iterator->value > iterator-> after-> value){
			swap(lhm, iterator-> key, iterator-> after-> key);
		}
		iterator = iterator-> next;


	}
}
return NULL;
}

int main(){
	linkedHashMap_t* lhm = makeLinkedHashMap(16, 0.75);
	addtoLHM(lhm, 1, 2);
	addtoLHM(lhm, 2, 3);
	addtoLHM(lhm, 3, 5);
	addtoLHM(lhm, 8, 1);
	addtoLHM(lhm, 17, 5);
	printLHM(lhm);
	printBucket(&lhm->bucket[1], 1);
	deleteNodefromLHM(lhm, 2);
	deleteNodefromLHM(lhm, 1);
	deleteNodefromLHM(lhm, 4);
	printf("\n");
	printLHM(lhm);

	printBucket(&lhm->bucket[1], 1);
	printf("%d\n", lhm->size);
	deleteLHM(lhm);

	return 0;
}
