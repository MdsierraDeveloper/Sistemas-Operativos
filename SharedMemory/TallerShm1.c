#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
/*
./Taller.out 3 3
{0.00}  {0.00}  {0.00} 
{3.00}  {4.00}  {5.00} 
{6.00}  {7.00}  {8.00} 

*/

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

void handler(int sig){}

int main(int argc, char **argv){
	
	double **matriz;
	int filas = atoi(argv[1]);
	int colum = atoi(argv[2]);
	
	pid_t dt;
	signal(SIGUSR1, handler);
	
	size_t sizeMatriz = sizeof_dm(filas, colum, sizeof(double));

	
	int shmid = shmget(IPC_PRIVATE, sizeMatriz, IPC_CREAT|0600);
	matriz = shmat(shmid, NULL, 0);
	create_index((void*)matriz, filas, colum, sizeof(double));

	if(!(dt = fork())){//padre
		usleep(10000);
		////accediendo a los elementos de la matriz para asignar valores
		for(int i = 0; i<filas; i++){
			for(int j=0; j<colum; j++){
				matriz[i][j] = (i * colum) +j; //asigna valor
			}
		}
		kill(dt, SIGUSR1);

	}else{//es el hijo
			
		pause();
		//imprimir los elementos de la matriz para verificar
		for(int i = 0; i<filas; i++){
			for(int j=0; j<colum; j++){
				printf("{%.2f} \t", matriz[i][j]);
			}
			printf("\n");
		}
	
	}
	
	
	
	shmdt(matriz);
	
	shmctl(shmid, IPC_RMID, NULL);
	return EXIT_SUCCESS;
	

}
