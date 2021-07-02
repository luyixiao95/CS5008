// Compile with clang lottery.c -o lottery
//
// Run with: ./lottery
//
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// This function is external to our
// code, but will be found by the linker
extern int TopSecretGenerateRandomNumber();

int main(){

	srand(time(NULL));
	
	int number1 = 0;	
	int number2 = 0;	
	int number3 = 0;	
	int number4 = 0;	

	printf("And the winning numbers are...\n");
	number1 = TopSecretGenerateRandomNumber();
	printf("%d\n",number1);
	fflush(stdout);
	//sleep(500);

	number2 = TopSecretGenerateRandomNumber();
	printf("%d\n",number2);
	fflush(stdout);
	//sleep(500);

	number3 = TopSecretGenerateRandomNumber();
	printf("%d\n",number3);
	fflush(stdout);
	//sleep(500);

	number4 = TopSecretGenerateRandomNumber();
	printf("%d\n",number4);
	fflush(stdout);
	//sleep(500);

	printf("%d %d %d %d...who would have guessed!\n",number1,number2,number3,number4);
	return 0;

}
