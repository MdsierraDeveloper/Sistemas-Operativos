#include <stdio.h>
#include <stdlib.h>

int **crearmat(int filas, int colum);
int borrarmat(int matriz, int filas, int colum);

int main(){

	int fil;
	int col;
	FILE *ar; 
	ar = fopen("matriz.txt", "r");
	
	fscanf(ar, "%d", &fil);
	fscanf(ar, "%d", &col);
	

	
	int **matriz = crearmat(fil, col);
	
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
		
			fscanf(ar, "%1d", &matriz[i][j]);	
			
			printf("\t%d", matriz[i][j]);
		}
		printf("\n");
	}
	
	
	return 0;
}


int ** crearmat(int filas, int columnas){
	int **matriz = (int **)malloc(filas*sizeof(int*));
	for(int i=0; i<filas; i++){
		matriz[i] = malloc(columnas*sizeof(int));
	}
	return matriz;
}
