#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct datos{
	int **matriz;
	int fil;
	int col;
	int ResultadodiagonalPrincipal;
	int ResultadoColumnas;
};

void *FuncionSumarDiagonalPrincipal(void *arg);




int main(int argc, char *argv[]){
	pthread_t idHiloCol;
	pthread_t idHilofil;

	char *arn = argv[1];
	int fil;
	int col;
	int **matriz;
	FILE *ar;
	ar = fopen(arn, "r");
	fscanf(ar,"%d", &fil);
	fscanf(ar,"%d", &col);
	printf("filas: %d, Columnas %d\n", fil, col);
	
	//reserva espacio en memoria dinamica para la matriz
	matriz = (int**)malloc(fil*sizeof(int));
	for(int i=0; i<fil; i++){
		matriz[i] = (int*)malloc(col*sizeof(int));
	}
	
	//leer matriz
	for(int i=0; i<fil; i++){
		for(int j=0; j<col; j++){
			fscanf(ar, "%d",&matriz[i][j]);
			printf("[%d]\t",matriz[i][j]);
		}
		printf("\n");
	}
	

	struct datos* dato;
	dato = (struct datos*)malloc(sizeof(struct datos));
	
	dato->matriz = matriz;
	dato->fil = fil;
	dato->col = col;
	
	pthread_create(&idHiloCol, NULL,FuncionSumarDiagonalPrincipal, (void *)dato);
	pthread_join(idHiloCol,NULL);
	
	printf("El resultado de la suma de las columnas: %d\n",dato->ResultadodiagonalPrincipal);
	
	
	
}

void *FuncionSumarDiagonalPrincipal(void *arg){
	struct datos* dato = (struct datos*)arg;
	int **matriz = dato->matriz;
	int col =0;
	int fil =dato->fil;
	int suma=0;
	for(int i=0; i<fil;i++){
		suma +=matriz[i][col];
		col++;
	}
	dato->ResultadodiagonalPrincipal = suma;
	
	free(matriz);
	pthread_exit(0);
}
