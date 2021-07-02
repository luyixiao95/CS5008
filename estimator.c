// Luyi Xiao
//CS 5008 lab 3


#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//Create an Estimator struct that has several fields of assembly instructors,
//Also instr for total Instruction and cyc for Cycle.
typedef struct Esti{
int add;
int sub;
int mul;
int div;
int mov;
int lea;
int push;
int pop;
int ret;
int instr;
int cyc;

}Esti_t ;

//Create a new empty Estimator that in the heap memory
Esti_t* makeEsti(){

	Esti_t* newEsti = (Esti_t*)malloc(sizeof(Esti_t));
	
	newEsti->add = 0;
	newEsti->sub = 0;
	newEsti->mul = 0;
	newEsti->div = 0;
	newEsti->mov = 0;
	newEsti->lea = 0;
	newEsti->push = 0;
	newEsti->pop = 0;
	newEsti->ret = 0;
	newEsti->instr = 0;
	newEsti->cyc = 0;


	return newEsti;
} 

//count the number of every fields in the file 
void analyseEst( FILE* input, Esti_t* esti){

	while(!feof(input)){
		char line[1024];
		fgets(line, 1024, input);
		int len = strlen(line);
	 	for(int i = 0; i< len -3; i++ ){
	 		char add[] = "add";
	 		char sub[] = "sub";
	 		char mul[] = "mul";
	 		char div[] = "div";
	 		char mov[] = "mov";
	 		char lea[] = "lea";
	 		char push[] = "push";
	 		char pop[]  = "pop";
	 		char ret[] = "ret";

			if( line[i] == add[0] && line[i+1]== add[1] && line[i+2]== add[2]){  
	 			esti->add ++;
	 			}
			else if (line[i] == sub[0] && line[i+1]== sub[1] && line[i+2]== sub[2])	{
				esti->sub ++;
			}	
			else if (line[i] == mul[0] && line[i+1]== mul[1] && line[i+2]== mul[2]) {
				esti->mul ++;
			}
			else if (line[i] == div[0] && line[i+1]== div[1] && line[i+2]== div[2]) {
				esti->div ++;
			}
			else if (line[i] == mov[0] && line[i+1]== mov[1] && line[i+2]== mov[2]) {
				esti->mov ++;
			}
			else if (line[i] == lea[0] && line[i+1]== lea[1] && line[i+2]== lea[2]) {
				esti->lea ++;
			}
			else if (line[i] == push[0] && line[i+1]== push[1] && line[i+2]== push[2] && line[i+3] == push[3]){
				esti->push ++;
			}
			else if (line[i] == pop[0] && line[i+1]== pop[1] && line[i+2]== pop[2]) {
				esti->pop ++;
			}
			else if (line[i] == ret[0] && line[i+1]== ret[1] && line[i+2]== ret[2]) {
				esti->ret ++;
			}
		 
	}

}
}

//print the field if exists

void print(Esti_t* esti){
	if(esti->add){
		printf("add %d\n", esti->add);
	}
	if(esti->sub){
		printf("sub %d\n", esti->sub);
	}
	if(esti->mul){
		printf("mul %d\n", esti->mul);
	}
	if(esti->div){
		printf("div %d\n", esti->div);
	}
	if(esti->mov){
		printf("mov %d\n", esti->mov);
	}
	if(esti->lea){
		printf("lea %d\n", esti->lea);
	}
	if(esti->push){
		printf("push %d\n", esti->push);
	}
	if(esti->pop){
		printf("pop %d\n", esti->pop);
	}
	if(esti->ret){
		printf("ret %d\n", esti->ret);
	}

	printf("\n\n");
	printf("Total Instructions = %d\n", esti->instr);
	printf("Total Cycles = %d\n", esti->cyc);	
}

//count the inst and cyc field of an exstimator
void countEst(Esti_t* esti){
	esti->instr = esti->add + esti->sub + esti->mul + esti->div + esti->mov + esti->lea + esti->push + esti->pop + esti->ret;
	esti->cyc = esti->add + esti->sub + esti->mul *3 + esti->div * 24 + esti->mov + esti->lea * 3 + esti->push + esti->pop + esti->ret;
}

//main function
int main (int argc, char **argv){

	FILE* file = fopen(argv[1], "r");
	Esti_t* Estimator = makeEsti();
	analyseEst(file, Estimator);
	countEst(Estimator);
	print(Estimator);
	fclose(file);

	free(Estimator);


	return 0;

}
