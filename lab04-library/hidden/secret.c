// This file is only here in case libsecret.so is not working for your architecture.
// Then compile it using the instructions in the readme.
//
// To be honest, this file is not super secret anyway...
//
#include <stdlib.h>

int TopSecretGenerateRandomNumber(){
	return rand() % 99;
}
