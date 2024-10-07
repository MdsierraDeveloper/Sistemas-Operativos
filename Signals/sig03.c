#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void Manejador(int sig){
	if(sig == SIGUSR1){
		printf("Signal USR1\n");
	}
	
	if (sig == SIGINT){
		printf("signal de interrupcion");
		usleep(1000000);
	}

}



int main(){
	

	
	signal(SIGUSR1, Manejador);
	signal(SIGINT, Manejador);			
 

	while(1){
		printf("Esperando una signall\n");	
		usleep(1000000);
	}
		return 0;

	
}
