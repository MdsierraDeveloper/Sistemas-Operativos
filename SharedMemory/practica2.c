#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <stdlib.h>

typedef struct{
	int x;
	int y;
}DatoCoordenada;

typedef struct{
	int **matriz;
	int nCoordenadas;
	DatoCoordenada *datoC;
}DataShm;

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

int celdas(int **matriz,int filas, int cols, int i, int j){
	int bandera = 0;
	int data;
	
	if(i-1>=0 && j-1>=0){
		data = matriz[i-1][j-1];
		if(data==2){
			bandera = 1;
		}
	}
	if(i-1>=0){
		data = matriz[i-1][j];
		if(data==2){
			bandera = 1;
		}
	}
	if(i-1>=0 && j+1<cols){
		data = matriz[i-1][j+1];
		if(data==2){
			bandera = 1;
		}
	}
	if(j-1>=0 && i+1<filas){
		data = matriz[j-1][i+1];
		if(data==2){
			bandera = 1;
		}
	}
	if(j-1>=0){
		data = matriz[i][j-1];
		if(data==2){
			bandera = 1;
		}
	}
	if(j+1<cols){
		data = matriz[i][j+1];
		if(data==2){
			bandera = 1;
		}
	}
	if(i+1<filas){
		data = matriz[i+1][j];
		if(data==2){
			bandera = 1;
		}
	}
	if(i+1<filas && j+1<cols){
		data = matriz[i+1][j+1];
		if(data==2){
			bandera = 1;
		}
	}
	
	return bandera;
}

int main(){
	int fil, col;
	FILE *ar; 
	ar = fopen("matriz.txt", "r");
	fscanf(ar, "%d", &fil);
	fscanf(ar, "%d", &col);
	int id;
	DataShm *dataShm;
	
	int shmid = shmget(IPC_PRIVATE, sizeof(DataShm)*4,0666);
	dataShm = (DataShm*)shmat(shmid, NULL, 0);
	
	
	
	for(int k=0;k<4;k++){
		dataShm[k].matriz = (int **)malloc(fil * sizeof(int *));
		dataShm[k].datoC = (DatoCoordenada *)malloc(fil*col * sizeof(DatoCoordenada));
		for (int i = 0; i < fil; i++) {
		    dataShm[k].matriz[i] = (int *)malloc(col * sizeof(int));
		}
	}		
    
    for(int k=0;k<4;k++){
    	for(int i=0; i<fil; i++){
			for(int j=0; j<col; j++){
				fscanf(ar, "%1d", &dataShm[k].matriz[i][j]);
				printf(" [%d] ", dataShm[k].matriz[i][j]);
			}
			printf("\n");
		}	
		fseek(ar,0,SEEK_SET);
		printf("\n");
    }
	
	//creacion de hijos	
	
	for(id =0; id<4; id++){
		if(!fork()){
			break;
		}
	}
	
	if(id==4){
		for(int i=0;i<4;i++){
			wait(NULL);
		}
		
		for(int i=0;i<4;i++){
			printf("El proceso [%d]\n",i);
			for(int j=0;j<dataShm[i].nCoordenadas;j++){
				printf("La coordenada [%d,%d]\n",dataShm[i].datoC->x,dataShm[i].datoC->y);
			}
		}
		
	}else{
		switch(id){
			//hijo 1
			case 0:
				int c1=0;
				for(int i =0; i < fil/2; i++){
					for(int j =0; j<col/2; j++){
						if(dataShm[0].matriz[i][j] == 1){
							if(celdas(&dataShm[0].matriz[i][j],fil,col,i,j)==1){
								dataShm[0].datoC->x = i; 
								dataShm[0].datoC->y = j;
								c1++;
							}
						}
					}
				}
				dataShm[0].nCoordenadas = c;
			exit(1);
			
			//hijo 2
			case 1:
				int c2=0;
				for(int i =fil/2; i <fil ; i++){
					for(int j =0; j<col/2; j++){
						if(dataShm[1].matriz[i][j] == 1){
							if(celdas(dataShm[1].matriz[i][j],fil,col,i,j)==1){
								dataShm[1].datoC->x = i; 
								dataShm[1].datoC->y = j;
								c2++;
							}
						}
					}
				}
				dataShm[1].nCoordenadas = c;
			exit(1);
			
			//hijo 3
			case 2:
				int c3=0;
				for(int i =0; i < fil/2; i++){
					for(int j =col/2; j<col; j++){
						if(dataShm[2].matriz[i][j] == 1){
							if(celdas(dataShm[2].matriz[i][j],fil,col,i,j)==1){
								dataShm[2].datoC->x = i; 
								dataShm[2].datoC->y = j;
								c3++;
							}
						
						}
					}
				}
				dataShm[2].nCoordenadas = c;
			exit(1);
			
			//hijo 4
			case 3:
				int c4=0;
				for(int i =fila/2; i < fil; i++){
					for(int j =col/2; j<col; j++){
						if(dataShm[3].matriz[i][j] == 1){
							if(celdas(dataShm[3].matriz[i][j],fil,col,i,j)==1){
								dataShm[3].datoC->x = i; 
								dataShm[3].datoC->y = j;
								c4++;
							}
						}
					}
				}
				dataShm[3].nCoordenadas = c;
			exit(1);
		}
	}	
	return 0;
}


