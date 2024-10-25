#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

typedef struct{
	int x;
	int  y;
	int cont;
	DatosShm *ptr;
	ptr->sgte = NULL;
}DatosShm;

unsigned int sizeof_dm(int filas, int colum, size_t sizeElement){
	
	size_t size;
	size = filas * sizeof(void*); //indexSize
	size += (colum * filas * sizeElement); //data size
	return size;
}

void create_index(void **m, int filas, int colum, size_t sizeElement){

	size_t sizeFilas = colum * sizeElement;
	m[0] = m + filas;
	for(int i = 1; i<filas; i++){
		m[i] = (m[i-1]+sizeFilas);
	}
}




int main(void){
	DatosShm *pr1;
	DatosShm *pr2;
	DatosShm *pr3;
	DatosShm *pr4;
	FILE *ar; 
	ar = fopen("matriz.txt", "r");
	int fil, col, shmid, shmpr1,shmpr2,shmpr3,shmpr4;
	fscanf(ar, "%d", &fil);	
	fscanf(ar, "%d", &col);
	printf("%d, %d\n", fil, col);
	
	int **matriz;
	size_t sizeMatriz = sizeof_dm(fil, col, sizeof(int));
	shmid = shmget(IPC_PRIVATE, sizeMatriz, IPC_CREAT | 0666);
	matriz = shmat(shmid, NULL, 0);
	create_index((void*)matriz, fil, col, sizeof(int));
	
	
	
	
	
	shmpr1 = shmget(IPC_PRIVATE, sizeof(DatosShm)*(fil*col), IPC_CREAT | 0666);
	pr1 = shmat(shmpr1, NULL, 0);
	
	shmpr2 = shmget(IPC_PRIVATE, sizeof(DatosShm)*(fil*col), IPC_CREAT | 0666);
	pr2 = shmat(shmpr2, NULL, 0);
	
	shmpr3 = shmget(IPC_PRIVATE, sizeof(DatosShm)*(fil*col), IPC_CREAT | 0666);
	pr3 = shmat(shmpr3, NULL, 0);
	
	shmpr4 = shmget(IPC_PRIVATE, sizeof(DatosShm)*(fil*col), IPC_CREAT | 0666);
	pr4 = shmat(shmpr4, NULL, 0);
	
	
	
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			fscanf(ar, "%1d", &matriz[i][j]);
			printf("\t%d", matriz[i][j]);
		}
		printf("\n");
	}
	
	
	for(int i=0; i<4; i++){
		if(!fork()){
			switch(i){
			
				case 0: //hijo 1
					for(int i=0; i<fil/2;i++){
						for(int j=0; j<col/2; j++){
							for(ptr; ; k++){
								if(matriz[i][j]==1){
									pr1[k].x = i;
									pr1[k].y = j;
									pr1[k].cont=+1;
								}	
							}
							
							
						}
					}
				
					
				
					exit(1);
				case 1: //hijo 2
				for(int i=fil/2; i<fil;i++){
						for(int j=0; j<col/2; j++){
							for(int k=0; k<sizeof(pr2); k++){
								if(matriz[i][j]==1){
									pr2[k].x = i;
									pr2[k].y = j;
									pr2[k].cont=+1;
								}	
							}
							
						}
					}
					
					exit(1);
				case 2: //hijo 3
					for(int i=0; i<fil/2;i++){
						for(int j=col/2; j<col; j++){
							for(int k=0; k<sizeof(pr3); k++){
								if(matriz[i][j]==1){
									pr3[k].x = i;
									pr3[k].y = j;
									pr3[k].cont=+1;
								}	
							}
							
						}
					}
					
					exit(1);
				case 3: //hijo 4
					for(int i=fil/2; i<fil;i++){
						for(int j=col/2; j<col; j++){
							for(int k=0; k<sizeof(pr4); k++){
								if(matriz[i][j]==1){
									pr4[k].x = i;
									pr4[k].y = j;
									pr4[k].cont=+1;
								}	
							}
							
						}
					}
					exit(1);
			
			}
		
			break;
		}
	}
	
	
	
	for(int i=0; i<4; i++){wait(NULL);}
	
	printf("Hijo 1\n");
	for(int i=0; i<pr1[i].cont; i++){
		printf("Filas %d columnas %d\n", pr1[i].x, pr1[i].y);
	}
	 
	printf("Hijo 2\n");
		for(int i=0; i<pr2[i].cont; i++){
			printf("Filas %d columnas %d\n", pr2[i].x, pr2[i].y);
	}
	
		
	
	
	printf("Hijo 3\n");
	for(int i=0; i<pr3->cont; i++){
		printf("Filas %d columnas %d\n", pr3[i].x, pr3[i].y);
	}
	printf("Hijo 4\n");
	for(int i=0; i<pr4->cont; i++){
		printf("Filas %d columnas %d\n", pr4[i].x, pr4[i].y);
	}	
		
}
