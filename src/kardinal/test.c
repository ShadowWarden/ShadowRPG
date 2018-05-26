/* test.cpp
 * Testing libkardinal.so
 */
#include "kardinal.h"

int main(int argc, char ** argv){
	printf("Argv[1] = %s\n",argv[1]);
	int res = exec(argv[1],-1);
	return res;
}
