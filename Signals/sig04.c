#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc,**argv ){

	pid_t *pids, root=getpid(), child;
	
	int nchild = atoi(argv[1]),idx;

	pids = (pid_t*)malloc(sizeof(pid_t)*nchild);
	signal(SIGUSR1, manejador);
	for(idx=0; idx<nchild; idx++){
		pids[idx]=fork();
		if(!pids[idx]){
			if(idx==0 ||idx==nchild-1){
				child = fork();
				break;
			}
		}	
	}

	if(root){
		pause();
		printf("proceso %d", getpid());


	}else{
		pause();

	
	}

	
}
