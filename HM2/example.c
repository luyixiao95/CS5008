#include <stdio.h>


void foo(int a[], int len){

	a[0] = 2;
	printf("%d\n",  a[0]);
}

int main(){

	int b[3] = {1, 2, 3};
	foo(b, 3);
	printf("%d\n", b[0]);
}
