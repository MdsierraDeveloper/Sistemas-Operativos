#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
/*
COMPILACION en LINUX POSIX
gcc reforestacion.c 

EJECUCION
./a.out archivo.txt


Contenido archivo.txt
10

10

10

1 2 2 0 1 0 1 2 0 1

0 2 2 1 0 0 1 1 0 1

1 2 1 2 0 0 1 0 1 1

2 2 0 0 1 0 2 1 2 1

0 2 1 0 2 1 0 1 1 0

1 1 2 0 1 1 2 1 1 1

0 2 0 2 1 2 0 1 0 1

1 2 1 1 0 2 1 0 0 0

0 1 1 2 1 0 1 2 2 1

2 1 1 0 1 2 0 0 2 0


*/


int **matrizInicial;
int fil;
int col;
int anios;

void *funcionDeforestar(void *args){
	printf("\nHijoDeforestar\n");
	
	for(int i=0; i<anios; i++){
		//printf("\nReforestar en el año %d\n", i);
		for(int i=0; i<fil; i++){
			for(int j=0; j<col; j++){
				//zona critica 
				
				//printf("%d\t", matrizInicial[i][j]);
				if(matrizInicial[i][j] == 1){
					int contdef=0;
					for(int m = i-1; m<=i+1; m++){
						for(int n = j-1; n<=j+1;n++){
							if(m>=0 && m<fil && n>=0 && n<col){
								if(m!=i || n!=j){
									if(matrizInicial[m][n] == 0){
										contdef+=1;
									}								
								}

							}
							
						}
					}
					if(contdef>=4){
						pthread_mutex_lock(&mutex);
						matrizInicial[i][j] =0;
					}
					
				
				}
				
				pthread_mutex_unlock(&mutex);
				

			}
			//printf("\n");
		}
		//barreras
		pthread_barrier_wait(&barrier);
	
	}
	
	
}


void *funcionRecuperar(void *args){
	printf("\nHijoRecuperar\n");
	for(int i=0; i<anios; i++){
		//printf("\nRecuperar en el año %d\n", i);
		for(int i=0; i<fil; i++){
			for(int j=0; j<col; j++){
				//zona critica inicio
				
				if(matrizInicial[i][j] == 0){
					int contdef=0;
					for(int m = i-1; m<=i+1; m++){
						for(int n = j-1; n<=j+1;n++){
							if(m>=0 && m<fil && n>=0 && n<col){
								if(m!=i || n!=j){
									if(matrizInicial[m][n] == 2 || matrizInicial[m][n] == 1){
										contdef+=1;
									}
								}
								
							}
							
						}
					}
					if(contdef>=5){
					pthread_mutex_lock(&mutex);
						matrizInicial[i][j] =2;
					}
					
				
				}
			
				
			//	printf("%d\t", matrizInicial[i][j]);
				
				pthread_mutex_unlock(&mutex);

			}
			//printf("\n");
		}
		//barreras
		pthread_barrier_wait(&barrier);
	}
}




int main(int argc, char *argv[]){
	pthread_barrier_init(&barrier, NULL, 2);
	
	char *archivo = argv[1];
	printf("%s\n", archivo);
	
	
	FILE * ar; 
	ar = fopen(archivo, "r");

	fscanf(ar, "%d", &anios);
	fscanf(ar, "%d", &fil);
	fscanf(ar, "%d",&col);
	printf("años: %d, filas: %d, col: %d\n", anios, fil, col);
	
	
	
	matrizInicial = (int**)malloc(fil * sizeof(int*));
	for(int i=0; i<fil; i++){
		matrizInicial[i] = (int*)malloc(col*sizeof(int));
	}
	
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			fscanf(ar, "%1d",&matrizInicial[i][j]);
			printf("%d\t", matrizInicial[i][j]);
		}
		printf("\n");
	}
	
	pthread_t Hilo1;
	pthread_t Hilo2;
	//hilo 1
	pthread_create(&Hilo1, NULL,funcionDeforestar, NULL);
	//hilo2
	pthread_create(&Hilo2, NULL,funcionRecuperar, NULL);
	
	pthread_join(Hilo1, NULL);
	pthread_join(Hilo2, NULL);
	
	//usleep(10*1000000);
	
	printf("\nDespues de %d Anios\n", anios);
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			printf("%d\t", matrizInicial[i][j]);
		}
		printf("\n");
	}
	
	pthread_barrier_destroy(&barrier);
	return EXIT_SUCCESS;
}
