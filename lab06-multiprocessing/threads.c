// Implement your part 2 solution here
// gcc -lpthread threads.c -o threads
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 64

int colors[64][64*3];
pthread_mutex_t muteX1 = PTHREAD_MUTEX_INITIALIZER;

void* paint(void* vargp){
        pthread_mutex_lock(&muteX1);
	int* row_p = (int*) vargp; 
	int row = *row_p;
	for(int i=0; i<64;i++){
	colors[row][i*3] = rand() % 255 ; 
	colors[row][i*3+1] =rand() % 255 ;  
	colors[row][i*3+2] =rand() % 255 ; 
	}
	pthread_mutex_unlock(&muteX1);
	return NULL;
}

void save(){
	FILE* fp = fopen("paint.ppm", "w+");
	fputs("P3\n", fp);
	fputs("64 64\n", fp);
	fputs("255\n", fp);
	for(int i = 0; i < 64; i++){
	for(int j = 0; j < 64*3; j++){
	fprintf(fp, "%d",colors[i][j]);
	fputs(" ", fp);
}
	fputs("\n", fp);
}	
	fclose(fp);
}

int main(){
pthread_t tids[NTHREADS];


for(int i=0; i< NTHREADS; ++i){
	void* row =&i;  
	pthread_create(&tids[i], NULL, paint, row);

}

for(int i=0; i< NTHREADS; ++i){
	pthread_join(tids[i], NULL);

}

save();

printf("finshed on the thread. /n");

return 0;
}
