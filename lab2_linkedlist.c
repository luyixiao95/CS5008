//Luyi Xiao
//CS 5008
//May 20, 2021
//Linked_list


#include <stdio.h>
#include <stdlib.h>

typedef struct node{
struct node* next;
int years;
int wins;
}node_t;

//create a function to connect nodes
void connect_node(node_t* n1, node_t* n2){

        n1->next = n2;
 }


//Create a function to create nodes in the heap memory
node_t* create_node_malloc(int win_num, int year_num){

	node_t* node_malloc = malloc(sizeof(node_t));
	node_malloc -> years = year_num;
	node_malloc -> wins = win_num;

	return node_malloc;

}

// Create a function create_list to create the list of Red Sox's results from 2014 to 2018
node_t* create_list(){
        node_t* y2014 = create_node_malloc(71, 2014);
        node_t* y2015 = create_node_malloc(78, 2015);
        node_t* y2016 = create_node_malloc(93, 2016);
        node_t* y2017 = create_node_malloc(93, 2017);
        node_t* y2018 = create_node_malloc(108, 2018);

        connect_node(y2018, y2017);
        connect_node(y2017, y2016);
        connect_node(y2016, y2015);
        connect_node(y2015, y2014);
        y2014 -> next= NULL;
        return y2018;

}


//create a function to create a list

void print_list(node_t* node_p){
        while(node_p != NULL){
        printf("%d, %d wins\n", node_p->years, node_p->wins);
        node_p = node_p -> next;
        }

}

//free the heap memory

void free_list(node_t* node_p){ 
	while(node_p != NULL){
		free(node_p);
		node_p = node_p -> next;
	}
	
}

int main(){
        node_t* redSocks = create_list();
          print_list(redSocks);
          free_list(redSocks);
 
          return 0;
	 }

