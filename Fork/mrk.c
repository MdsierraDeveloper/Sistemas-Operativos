#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
int main(void){

	pid_t root = getpid();

	if(!fork()){
		printf("Soy el hijo\n");
		return 257;
	}

	int status = 0;

	if(root = getpid()){
		wait(&status);
		printf("el hijo termino con %d \n", status);
	}

	return 0;
}
