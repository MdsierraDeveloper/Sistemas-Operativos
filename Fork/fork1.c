#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void fork1()
{
	int x = 1;
	pid_t p = fork();
	if(fork()<0)
	{
		perror("fork fail");
		exit(1);
	}
	else if (p==0)
	{
		printf("child has x = %d\n", ++x);
	}
	else
	{
		printf("padre has x = %d\n",--x);
	}
}

void forkthreesons()
{
	//Does'nt work
	pid_t h = fork();
	for(int i =0; i<3; i++)
	{
		h = fork();
		if(h==0)
		{
			if(i==1||i==2)
			{
				h = fork();
				break;
				printf("CHILD %d\n",i);
			}
		}
	}
		
	
}

void fork2()
{
	//obviusly work
	fork();
	printf("Hola mundo");
}

void forkShowSons()
{	
	//pid
	//getpid -> pid from the father
	//getppid -> pid from the son
	
	pid_t pid; // sys/type.h
	pid = fork(); //unisted.h
	
	// pid > 0 -> is the father
	// pid == 0 -> is the son
	
	if(pid > 0)
	{
		printf("Soy el padre con pid %d y creare otro proceso\n", getpid());
		fork();
	}else{
		printf("Soy el proceso hijo con pid %d y soy hijo de %d \n", getpid(), getppid());
	}

}

int main()
{
	forkShowSons();
	return 0;
}

