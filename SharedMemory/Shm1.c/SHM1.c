#include <stdlib.h> 
#include <stdio.h> 
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

/*
Suma de indices de matrices i*i

Compilacion 
gcc SHM1.c -o salida.out

Ejecucion 
./salida.out archivo.txt

*/

unsigned int sizeof_dm(int filas, int colum, size_t sizeElement){
	size_t size;
	size = filas * sizeof(void*);
	size += (colum * filas * sizeElement);
	return size; 
}

void create_index(void **m, int filas, int colum, size_t sizeElement){
	size_t sizeFilas = colum * sizeElement;
	m[0]  = m + filas;
	for(int i= 1; i<filas; i++){
		m[i] = (m[i-1] + sizeFilas);
	}
}

int main(int argc, char **argv){
	
	char *ar; 
	ar = argv[1];
	
	FILE *file;
	file = fopen(ar, "r"); //File Open
	
//	[Structs][enteros][strings][loquesea]

	int **matriz1, **matriz2, **matrizR; 
	int fil, col;
	
	fscanf(file, "%d", &fil);
	fscanf(file, "%d", &col); 
	printf("Filas %d, Columnas %d\n", fil, col);
	
	size_t sizeMatriz = sizeof_dm(fil, col, sizeof(int));
	int shmid = shmget(IPC_PRIVATE, sizeMatriz, IPC_CREAT | 0600 );
	
	
	matriz1 = shmat(shmid, NULL, 0); 
	create_index((void*)matriz1, fil, col, sizeof(int));
	
	matriz2 = shmat(shmid, NULL, 0); 
	create_index((void*)matriz2, fil, col, sizeof(int));
	
	matrizR = shmat(shmid, NULL, 0); 
	create_index((void*)matrizR, fil, col, sizeof(int));

	printf("matriz 1\n");	
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			fscanf(file, "%1d", &matriz1[i][j]);
			printf(" %d ", matriz1[i][j]);
		}
		printf("\n");
	}
	
	printf("matriz 2\n");
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			fscanf(file, "%1d", &matriz2[i][j]);
			printf(" %d ", matriz2[i][j]);
		}
		printf("\n");
	}
	
	
	
	for(int i =0; i<1; i++){ // i < nhijos
		if(!fork()){
			switch(i){
				case 0: //hijo 1
					if(!fork()){ //sub hijo 1.1
						if(!fork()){ //sub hijo 1.1.1
							for(int i=0; i<fil; i++){
								for(int j=0; j<col; j++){
								matrizR[i][j] = matriz1[i][j]+matriz2[i][j];
								}
							}
						}	
					}
					exit(1);

			}	
		
		}
	
	}
	
	for(int i=0; i<10; i++){ // i < nhijos
		wait(NULL);
	}
	
	
	
	
	printf("matriz R\n");
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			printf(" %d ", matrizR[i][j]);
		}
		printf("\n");
	}
	
	
	
	shmdt(matriz1);
	shmdt(matriz2);
	shmdt(matrizR);
	shmctl(shmid, IPC_RMID, NULL);

	return EXIT_SUCCESS;
	
}











