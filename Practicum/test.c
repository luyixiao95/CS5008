#include <stdio.h>
#include <stdlib.h>
#include "linkedHashMap.h"


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
	printf("\n");

	addtoLHM(lhm, 12, 5);
	addtoLHM(lhm, 18, 7);
	addtoLHM(lhm, 24, 13);
	addtoLHM(lhm, 25, 15);
	addtoLHM(lhm, 31, 11);
	addtoLHM(lhm, 35, 32);
	addtoLHM(lhm, 46, 12);
	addtoLHM(lhm, 56, 8);
	addtoLHM(lhm, 65, 11);
	swap(lhm, 17, 65);
	sortWithValue(lhm);
	
	printLHM(lhm);
	printf("\n");

	lhm = resize(lhm);
	addtoLHM(lhm, 33, 17);
	printLHM(lhm);
	
	printf("\n");
	printBucket(&lhm->bucket[1], 1);
	
	deleteLHM(lhm);

	return 0;
}
