#include <stdio.h>
#include <math.h>
double power(double base, double n){
	double result = base;	
	while(n>1){
	result = result * base;
	n = n - 1;	
}
	return result;
}
int main(){
	double i = 1, r;
	while( i <=10){
	r= power(2, i);
	printf("%f\n", r);
	i++;
} 
return 0;
}
