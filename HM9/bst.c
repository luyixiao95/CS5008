#include <stdio.h>
#include <stdlib.h>

typedef struct bstnode
{
	int data;
	struct bstnode* leftChild;
	struct bstnode* rightChild;
	
}bstnode_t;

typedef struct bst
{unsigned int size;
	bstnode_t* root;
	
}bst_t;
//node_create to create a new node with data and allocate the memory 
bstnode_t* node_create(int data){

	bstnode_t* node = (bstnode_t*) malloc(sizeof(bstnode_t));
	node->data = data;
	node->leftChild = NULL;
	node-> rightChild = NULL;

	return node;

}

//bst_create is to create a new binary search tree and allocate its memory.
bst_t* bst_create(){

	bst_t* bst = (bst_t*)malloc(sizeof(bst_t));
	bst -> root = NULL;
	bst -> size = 0;
	return bst;
}

//bst_empty is to see if the bst is empty of not
//@return 0 if it is empty, return 1 if it is not empty.

int bst_empty(bst_t* t){
	if(t->root == NULL){
		return 0;
	}
	return 1;

}

//addHelper function is the helper function for add function.
//Using recursive method to compare and add till the base case.
void addHelper(bst_t* t, bstnode_t* node, int item){

	if(node->data > item){
		if(node->leftChild == NULL){
			bstnode_t* newNode = node_create(item);
			node -> leftChild = newNode;
			t-> size ++;
			return;
		}
		else{
		addHelper(t, node->leftChild, item);
	}
	}

	else{
		if(node->rightChild == NULL){
			bstnode_t* newNode = node_create(item);
			node -> rightChild = newNode;
			t-> size ++;
			return;
		}


		else{

		addHelper(t, node->rightChild, item);

	}

}
}

//bst_add function is to add a new item into the tree. 
int bst_add(bst_t* t, int item){
	if(t == NULL){
		return 0;
	}

	if(t-> size == 0){
		bstnode_t* node = node_create(item);
		t-> root = node;
		t-> size = 1;
		return 1;
	}

	addHelper(t, t->root, item);

	return 1;

}

//printHelper function is a helper function to the bst_print function.

//It used recursive method to firstly printHelper the right node, then print the node itself and then printHelper the right node.

//And the basecase is the node is null.
void printHelper(bstnode_t* node){

	if(node ==NULL){
		return;
	}


	printHelper(node->leftChild);
	printf("%d ", node->data);
	printHelper(node->rightChild);

}

//bst_print function is to print the tree in ascending order. 

void bst_print(bst_t* t){

	printHelper(t-> root);
	printf("\n");

}

//sumHelper function is the helper function for bst_sum.

int sumHelper(bst_t* t, bstnode_t* node){

	int sum = node->data;
	if(node-> leftChild != NULL){
	sum += sumHelper(t, node->leftChild);}
	if(node->rightChild != NULL){
	sum += sumHelper(t, node-> rightChild);}

	return sum;


}
//bst_sum function sum all the elements together.
int bst_sum(bst_t* t){
	int sum = sumHelper(t, t->root);
	return sum;
}
//if the value can find in the tree , return 1
//if the value cannot find, return 0;
int bst_find(bst_t* t, int value){
	bstnode_t* node = t->root;
	while(node!=NULL){

		if(node->data > value){
			node = node->leftChild;
		}
		else if(node->data < value){
			node = node-> rightChild;
		}
		else{
			return 1;
		}

	}

	return 0;

}

//return the size of the tree.
unsigned int bst_size(bst_t* t){

	return t->size;
}

//freeHelper is to free the node of the tree from bottom to peak, using recursive way.
void freeHelper(bstnode_t* node){

	if(node!=NULL){
		freeHelper(node->rightChild);
		freeHelper(node->leftChild);
		free(node);
	}
}

//bst_free is to free the treenode and the tree itself.
void bst_free(bst_t* t){
	if(t->size !=0){
	freeHelper(t->root);}
	free(t);
}


//unitTest to test the bst_add, bst_sum, bst_find and bst_free.
int unitTest(){

	int result;

	bst_t* tree = bst_create();
	for(int i=0; i< 100 ; i++){

		bst_add(tree, i);
	}

	int size = bst_size(tree);
	int find = bst_find(tree, 50);
	int sum = bst_sum(tree);
	bst_free(tree);

	if(size == 100 && find == 1 && sum == 4950){
		return 1;
	}

	return 0 ; 
}
int main(){

	bst_t* tree = bst_create();
	bst_add(tree, 1);
	bst_add(tree, 2);
	bst_add(tree, -1);

	bst_add(tree, 3);
	bst_add(tree, -5);
	bst_add(tree, 9);
	bst_add(tree, 10);
	bst_add(tree, 8);
	bst_print(tree);


	bst_free(tree);

	int test = unitTest();
	printf("The unitTest result is: %d\n", test);
	return 0;
}