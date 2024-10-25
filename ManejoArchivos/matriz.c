#include <stdio.h>

// pasar la matriz desde un archivo a el programa
// gcc matriz.c -o matriz
// ./matriz "matriz.txt"

int main(void){

	FILE *ar;
	ar = fopen("matriz.txt", "r");
	int fi;
	int col;
	
	
	fscanf(ar, "%d", &fi);
	fscanf(ar, "%d", &col);
	int matriz[fi][col];
	
	printf("Filas %d, Columnas %d\n", fi, col);
	
	for(int i=0; i<fi; i++){
		for(int j =0; j<col; j++){
			fscanf(ar, "%1d", &matriz[i][j]);	
		}
	
	}
	
	for(int i=0; i<fi; i++){
		for(int j =0; j<col; j++){
			printf("\t%1d", matriz[i][j]);
		}
		printf("\n");
	}	
	
	fclose(ar);
	return 0;
		
}
