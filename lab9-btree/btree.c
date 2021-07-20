#include <stdio.h>
#include <stdlib.h>

#define childSize 4
//define the node struct: contains the size of the node, 
//an int array keys(with size 4) and a node array (with size 5)
typedef struct node
{
	int size;
	int keys[childSize];
	struct node* children[childSize+1];

	
}node_t;

//tree contains the root value and the numNudes.
typedef struct tree{

	node_t* root;
	int numNodes;
} tree_t;

//makeNodea new node with data in it.
node_t* makeNode(int data){

	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	newNode -> size = 1;
	newNode-> keys[0] = data;


	for(int i = 0; i < childSize + 1; i++){
		newNode->children[i] = NULL;

	}
	return newNode;
}
//maketree to make a new tree with the first element in the 
//root is the data
tree_t* maketree(int data){
	tree_t* newTree = (tree_t*) malloc(sizeof(tree_t));
	newTree-> root = makeNode(data);
	newTree-> numNodes = 1;

	return newTree;
}

//swap is the helper function for insertion sort.
void swap(int* a, int* b){
	int buffer = *b;
	*b = *a;
	*a = buffer;
}

//insertion sort
void sort(int* array, unsigned int size){

 	for(int i = 1 ; i < size; i ++){
 		for(int j = i; j > 0; j --){

 			if(array[j] < array[j-1] ){

 				swap(&array[j], &array[j-1]);
 			
 			}
 		}

 	}
 }

 //find index is to find the index of an element in the node 
 //and return the index.
int findIndex(int a, node_t* node){
	int i = 0;
	while(a > node->keys[i] && i < node->size){
		i++;
	}


	return i;
	
}

//add and sort data to a new node
void addtoNode(node_t* node, int data){

	node->keys[node->size] = data;
	node->size ++;
	sort(node->keys, node->size);
	return;

}

//helper function for insert.
void insertHelper(tree_t* tree, int data, node_t* node){
	//firstly get the index of the new data in the node array
	int index = findIndex(data, node);

	//base case 1: if the aiming node is still not full,
	//add the data to the array and adjust the array
	if(node->size<childSize){
		addtoNode(node, data);
		return;
	}
	//base case 2: if the array is full and the node pointer with 
	//index is null, create one new node with data and link it with
	//the former node array.
	if(node->size == childSize && node->children[index]==NULL){
		node_t* newNode = makeNode(data);
		node->children[index] = newNode;
		tree -> numNodes ++;
		return;
	}
	//in other ways just using recursive method, now the node* is the 
	//node* at index of the original node* array
	insertHelper(tree, data, node->children[index]);
}

//insert function to insert a datam to the tree.
void insert(tree_t* tree, int data){


	insertHelper(tree, data, tree->root);

	return ;

}

//print node
void printNode(node_t* node){
	for(int i =0; i< node->size; i++){

		printf("%d ", node->keys[i]);
	}
	printf("\n");

	return;
}


int main(){
	//make a new tree, and the elements in the root are 0, 10, 20, 30
	tree_t* tree = maketree(0);
	insert(tree, 10);
	insert(tree, 20);
	insert(tree, 30);

	//randomly add a 21 in it
	insert(tree, 21);

	//insert these four data to let the children[0] contains these data
	insert(tree, -10);
	insert(tree, -8);
	insert(tree, -4);
	insert(tree, -2);

	//check the recursive part with the level 2 data.
	insert(tree, -11);

	//children[1] data of the root
	insert(tree, 2);
	insert(tree, 5);
	insert(tree, 8);
	insert(tree, 9);

	//children[2] data (also check for sorting)
	insert(tree, 11);
	insert(tree, 17);
	insert(tree, 15);
	insert(tree, 12);

	//children[3] data (with 21)
	insert(tree, 23);
	insert(tree, 25);
	insert(tree, 27);

	//children[4] data
	insert(tree, 35);
	insert(tree, 37);
	insert(tree, 40);
	insert(tree, 41);

	//check recursive and children[0][0]data
	insert(tree, -13);
	insert(tree, -15);
	insert(tree, -17);

	printf("root: ");
	printNode(tree->root);
	for(int i =0; i<5; i++){
	printf("level 1 branch %d:    ", i);
	printNode(tree->root->children[i]);}

	printf("level 2 branch 0: (Test recursion)");
	printNode(tree->root->children[0]->children[0]);
	free(tree->root->children[0]->children[0]);

	for(int i =0; i<5; i++){
	free(tree->root->children[i]);}
	free(tree->root);
	free(tree);

	return 1;


}

