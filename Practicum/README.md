# Writing Exercises

## 1. introduction of this week's project.

In this week's tough work, I have implemented the linkedhashmap by C. LinkedHashMap is the data structure used to store the key-value pairs like HashMap but it guarantees the order of insertion(unlike the HashMap). So the elements are stored in the order of their insertion. In my works, I considered linkedhashmap as a organic mixture of an array of buckets, and every bucket can be seen as a singly linked list, which can store the nodes with the same hashkey one by one, and also these nodes are linked together in order via a doubly linked list with a header. We also implemented some basic functions used in the linkedhashmap. Below is the brief introduction about these functions:

**MakeNode** function is to actually create a new node that will be linked to the linkedhashmap(AKA LHM in this file as well as the code part), and it inputs the key and value of the node, and returns the node itself.

**makeLinkedHashmap** function create a new LHM with certain capacity and loadfactor, in this function. the threshold field is used to test if the size is too crowd, if the answer is true, it will resize the LHM by resize function that defined later in the file. Header is to trace the beginning and end of the LHM.

**deleteLHM** function is to destroy a certain LHM and free the memory in the heap.

**resize** function to resize the LHM to capacity twice as before.

**addtoLHM** function is to add a new node with the key and value parameter to the certain LHM parameter. It needs to refer to two functions, **addtoBucket** and **addtoLinkedList**, which are adding this node to the two parts of the LHM.

**search** function is to search if there is a node with the key parameter in the LHM.

**deleteNodefromLHM** is to delete a certain node with the key parameter in the LHM, it used the **deleteNodefromBucket** function and this is to delete the node from the function. 

**getfirst** is just to get the first node of the LHM.

**getlast** is just to the get the last node of the LHM.

**updateValue** is to change a value of a certain key parameter to a given one in the LHM.

**printLHM** is to print the nodes(key and value) in the LHM in place.

## 2. Complexity

Access: 1

Search: 1

insert: 1 if resize, n

delete: 1 if resize, n

sort: in this one n^2





