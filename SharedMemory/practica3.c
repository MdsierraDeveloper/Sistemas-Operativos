#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>
/*
Un hijo proceso encuentra las minas y el 
padre imprime las posiciones.

gcc practica3.c -o practica3
./practica3


Out:

Mina #1 x:0, y:2
Mina #2 x:0, y:6
Mina #3 x:0, y:8
Mina #4 x:2, y:0
Mina #5 x:2, y:1
Mina #6 x:2, y:2
Mina #7 x:2, y:8
Mina #8 x:3, y:8

matriz.txt
4
10
0010021010
0200000020
1110000210
0020000210

*/
typedef struct{
	int x; //filas
	int y;//columnas

}Datos;


int main(void){
	int  **matriz,fil,col; 
	int countMinas=0;
	Datos *st;
	FILE *ar;
	ar = fopen("matriz.txt", "r");
	
	//toma los datos del archivo
	fscanf(ar, "%d", &fil);
	fscanf(ar, "%d", &col);
	
	//reserva espacio en memoria dinamica para la matriz
	matriz = (int**)malloc(fil*sizeof(int));
	for(int i=0; i<fil; i++){
		matriz[i] = (int*)malloc(col*sizeof(int));
	}
	
	//ingresa los datos y imprime la matriz
	for(int i=0; i<fil;i++){
		for(int j=0; j<col; j++){
			fscanf(ar, "%1d", &matriz[i][j]);
			printf("\t%d" ,matriz[i][j]);
		}
		printf("\n");
	}
	
	//contar las minas
	for(int i=0; i<fil;i++){
			for(int j=0; j<col; j++){
				if(matriz[i][j]==1){
					countMinas+=1;
				}
			}
	}
	
	printf("Total Minas: %d \n", countMinas);
	
	int shmid = shmget(IPC_PRIVATE, sizeof(int)*countMinas, 0666);
	st = shmat(shmid, NULL, 0);
	
	
	//hijo
	if(!fork()){
			int k=0;//posiciones del vector
			for(int i=0; i<fil;i++){
				for(int j=0; j<col; j++){
						if(matriz[i][j]==1){
							st[k].x =i;
							st[k].y=j;		
							k++;			
						}
				}
			
			}
		
		exit(1);
	}
	
	wait(NULL);
	
	
	for(int k=0; k<countMinas; k++){
		printf("Mina #%d\t", k+1);
		printf("x:%d, y:%d\n", st[k].x, st[k].y);
	}
	shmdt(st); //desacoplar
	shmctl(shmid, IPC_RMID, NULL);//Borrar segmento de datos
	
}
