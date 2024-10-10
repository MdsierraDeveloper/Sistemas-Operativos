#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main(){
	
	int fd[2];
	pipe(fd);
	char buffer[10];
	int tam;
	if(!fork()){
		//es el hijo
		close(fd[0]);
		printf("\n Soy el hijo %d, mi padre %d\n", getpid(), getppid());
		printf("Voy a enviar un mensaje al padre por una tuberia\n");
		write(fd[1], "abcde", 5);
		printf("Mensaje enviado....\n");						 		
		close(fd[1]);
		printf(".....................\n");
		
	}else{
		//es el padre
		
		close(fd[1]);
		usleep(1000000);
		printf("\nSoy el padre %d\n", getpid());
		printf("Recibiendo mensaje\n");
		tam = read(fd[0], buffer, sizeof(buffer));
		close(fd[0]);
		printf("Mensaje recibido> %s\n", buffer);
	
	}
	


	return EXIT_SUCCESS;
}
