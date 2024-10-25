//Suponga que tiene tres procesos, que saquen la secuencia ABC
//con una variable turno global
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h> 

int main() {
//  int shm_size = sizeof(int);
    int shmid;
    int *turno;

    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR); //crea el espacio en memoria compartida
    
    turno = (int*)shmat(shmid, 0,0); //adjunto un puntero al espacio de memoria creado en shmid
    
    *turno =1;
    
    int idx;
    for(idx=0;idx<3; idx++){
    	if(!fork()){
    		while(*turno!=idx+1){
    			usleep(100);
    			}
    		
    	if(idx==0){//es el padre
    		printf("A");
    	
    	}else if(idx==1){//es el primer hijo
    		printf("B");
    	
    	}else if(idx==2){// es el nieto
    		printf("C");
    	}
    	
    	*turno = idx +2;
    	exit(0);
    	}
    	
    }
    
    for(int i =0; i<idx; i++){
    	wait(NULL);
    }
    
    
    shmdt(turno);
    shmctl(shmid, IPC_RMID, NULL );
    
    
	return 0;    
    
}
