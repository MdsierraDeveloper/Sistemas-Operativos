#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void print_tree(){
	char cmd[500] = {""};
	sprintf(cmd, "pstree -lp %d", getpid());
	system(cmd);
}

int main(int argc, char **argv){
	int s_idx, idx, p_idx;//id para hijos
	
	pid_t root = getpid();
	
	pid_t c_v[3];
	
	//primeros 3 hijos
	for(p_idx=0; p_idx<3; p_idx++){
		if((c_v[p_idx] = fork())==0){
			if(p_idx==1){
				for(idx =0; idx<2; idx++){
					if(fork()){
						break;
					}	
				}
				
				if(idx==2){
					for(s_idx =0; s_idx <2; s_idx++){
						if(!fork()){break;}
					}
				}
			}
			
			break;
		}
	}
	
	
	//si root == getpid(); es el padre
	if(root == getpid())
	{	

		printf("padre %d\n", getpid());
		usleep(100000);
		print_tree();
		for(int i = 0; i< 3; i++){wait(NULL);}		
		
	}else{//sino son los hijos

	printf("soy hijo %d, padre %d\n",getpid(), getppid());	
		usleep(20000);
		

	}
	
	
	
	
	
	return EXIT_SUCCESS;
}
