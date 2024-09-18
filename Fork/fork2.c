#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(void)
{

	pid_t pidchild = fork();
	switch(pidchild)
	{
		case -1: 
			perror("ErrorFork");
			exit(EXIT_FAILURE);
		case 0:
			printf("proceso hijo: pid=%d y ppid=%d\n ", getpid(), getppid());
			break;
		default:
			printf("Proceso padre: pid=%d y ppid=%d\n", getpid(), getppid());
			wait(NULL);
	}
	return EXIT_SUCCESS;

}
