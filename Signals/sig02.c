#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <signal.h>

void showtree(){
	char command[50];
	sprintf(command, "pstree -lp %d", getpid());
	system(command);

}

void handler(int s){}
void Kill(pid_t pid, int s){ usleep(100); kill(pid, s);}

int main(int argc, char **argv){
	pid_t pids[3],child, root = getpid();	
	int idx;
	signal(SIGUSR1, handler);
	for(idx=0; idx <3; idx++){
		pids[idx] = fork();
		if(pids[idx]==0){
			if(idx ==1)child = fork();
			break;		
		}
		
	}
	if(root == getpid()){
		usleep(100);
		showtree();
		printf("procesos %d\n", getpid());
		kill(pids[2], SIGUSR1);
		pause();
		printf("procesos %d\n", getpid());
	
	}
	else{
		pause();
		printf("proceso: %d\n", getpid());
		if(idx == 1){
			if(child){
				Kill(child, SIGUSR1);
				pause();
				printf("proceso %d\n",getpid());
				Kill(pids[idx-1], SIGUSR1);
			}else{
				Kill(getppid(), SIGUSR1);
			}	
		}else{
			if(idx == 0) Kill(getppid(), SIGUSR1);
			else Kill(pids[idx-1], SIGUSR1);
		}
	}

	return EXIT_SUCCESS;
}
