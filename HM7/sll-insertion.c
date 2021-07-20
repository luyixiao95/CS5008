#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//sll.h is a header file for SLL created in HM3
#include "sll.h"

//swap function is to swap two data in certain nodes.
void swap(slist_t* sll, node_t* node1, node_t* node2){

	int buffer = node1-> data;
	node1-> data = node2 -> data;
	node2 -> data = buffer;
}

//insertionSort to insert the sort by insertion sort method
void insertionSort(slist_t* sll, unsigned int size){

	for(int i = 1; i < size; i++){

		for(int j = i; j > 0; j--){
			node_t* node1 = search(sll, j-1);
			node_t* node2 = node1-> next;
			if(node2->data < node1-> data){
				swap(sll, node1, node2);
			}
		}
	}
}


int main(){
slist_t* sll = makeSLL();
push_frontS(sll, 4);
push_frontS(sll, 6);
push_frontS(sll, 5);
push_frontS(sll, 7);
push_frontS(sll, 8);

printSLL(sll);
insertionSort(sll, 5);
printSLL(sll);
freeSLL(sll);

return 0;


}