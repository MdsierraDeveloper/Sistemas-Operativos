#include <stdlib.h> // para funciones de entrada y salida
#include <stdio.h> // exit_success y  exit_failure
#include <unistd.h> // fork(), getpid(), usleep() y pause()
#include <sys/wait.h> // para wait()
#include <signal.h> // para signal(), SIGUSR1, kill()

void sighandler(int sig);

int main(){
	
	pid_t *pidhijos=NULL;
	int nHijos, i=0, status;

	// funcion que guarda el estado anterior en la tabla de signals
	void (*oldstatus)(int);
	oldstatus = signal(SIGUSR1, sigstatus);
	if(oldstatus == SIG_ERR){
		perror("signal:");
		exit(EXIT_FAILURE);
	}

	printf("Digite los N procesos Hijos");
	scanf("%d", &nHijos);

	//apartamos memoria para los n hijos
	pidhijos = (pid_t *)malloc(nHijos * sizeof(pid_f));
	if(pidhijos == NULL){
		printf("No se aparto memoria");
		exit(1);
	}

	for(i=0; i<nHijos; i++){
		pidhijos[i] = fork();
		if(pidhijos[i]==0){
			break;
		}
	}

	if(i == nHijos){

	}




}

