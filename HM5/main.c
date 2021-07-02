#include "maxHeap.h"

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
	add(maxHeap, 5);
	printS(maxHeap);
	freeSlist(maxHeap);
	return 0;

}