#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>

/*
SERGIO ALMAZO CATAÑO
ANDRÉS IBARRA PAEZ
MANUEL SIERRA POSSO

matriz utilizada en archivo matriz.txt
4
4
85 72 65 45 
55 48 35 25
42 38 28 20
35 30 22 15
2 2 1 1
2 1 1 0
1 1 0 0
1 0 0 0
1 1 0 -1
1 0 -1 -1
0 -1 -1 -1 
-1 -1 -1 -1


./parcial2
4 4
Matriz N
	85.0	72.0	65.0	45.0
	55.0	48.0	35.0	25.0
	42.0	38.0	28.0	20.0
	35.0	30.0	22.0	15.0

Matriz C
	2.0	2.0	1.0	1.0
	2.0	1.0	1.0	0.0
	1.0	1.0	0.0	0.0
	1.0	0.0	0.0	0.0

Matriz P
	1.0	1.0	0.0	-1.0
	1.0	0.0	-1.0	-1.0
	0.0	-1.0	-1.0	-1.0
	-1.0	-1.0	-1.0	-1.0
MatrizR
	0.0	0.0	0.3	1.1
	0.0	0.5	1.3	3.0
	0.6	1.2	2.9	3.2
	1.3	2.8	3.1	3.4
MatrizS
	15.3 13.0 5.2 1.8
	9.9	3.8	1.4	0.5
	3.4	1.5	0.6	0.4
	1.4	0.6	0.4	0.3
Matriz A
	0.0	0.0	0.0	0.0
	0.0	0.0	0.0	0.0
	0.0	0.0	0.0	0.0
	0.0	0.0	0.0	1.0

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

int main(int argc, char *argv){
    double **matrizN, **matrizC, **matrizP;
    double **matrizR, **matrizS, **matrizA;
    int fil, col;
    FILE *ar; 
    ar = fopen("matriz.txt", "r");

    fscanf(ar, "%d", &fil);
    fscanf(ar, "%d", &col);
    printf("%d %d\n", fil, col);
    
    size_t sizematrizN = sizeof_dm(fil, col, sizeof(double));
    size_t sizematrizC = sizeof_dm(fil, col, sizeof(double));
    size_t sizematrizP = sizeof_dm(fil, col, sizeof(double));
    
    int shmidN = shmget(IPC_PRIVATE, sizematrizN, IPC_CREAT |0666);
    matrizN = shmat(shmidN, NULL, 0);
    create_index((void*)matrizN, fil, col, sizeof(double));


    int shmidC = shmget(IPC_PRIVATE, sizematrizC, IPC_CREAT |0666);
    matrizC = shmat(shmidC, NULL, 0);
    create_index((void*)matrizC, fil, col, sizeof(double));


    int shmidP = shmget(IPC_PRIVATE, sizematrizP, IPC_CREAT |0666);
    matrizP = shmat(shmidP, NULL, 0);
    create_index((void*)matrizP, fil, col,sizeof(double));



    size_t sizematrizR = sizeof_dm(fil, col, sizeof(double));
    int shmidR = shmget(IPC_PRIVATE, sizematrizR, IPC_CREAT |0666);
    matrizR = shmat(shmidR, NULL, 0);
    create_index((void*)matrizR, fil, col, sizeof(double));
    
    size_t sizematrizS = sizeof_dm(fil, col, sizeof(double));
    int shmidS = shmget(IPC_PRIVATE, sizematrizS, IPC_CREAT |0666);
    matrizS = shmat(shmidS, NULL, 0);
    create_index((void*)matrizS, fil, col, sizeof(double));

    size_t sizematrizA = sizeof_dm(fil, col, sizeof(double));
    int shmidA = shmget(IPC_PRIVATE, sizematrizA, IPC_CREAT |0666);
    matrizA = shmat(shmidA, NULL, 0);
    create_index((void*)matrizA, fil, col, sizeof(double));



    //matriz de niveles "N"
    printf("Matriz N\n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            fscanf(ar, "%2le", &matrizN[i][j]);
            printf("\t%.1f", matrizN[i][j]);
        }
        printf("\n");
    }
         printf("\n");
    //matriz de calidad "C"
    printf("Matriz C\n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            fscanf(ar, "%2le", &matrizC[i][j]);
            printf("\t%.1f", matrizC[i][j]);
        }
        printf("\n");
    }
     printf("\n");
    //matriz de prediccion "P" 
    printf("Matriz P\n");
    for(int i=0; i<fil; i++){
        for(int j=0; j<col; j++){
            fscanf(ar, "%2le", &matrizP[i][j]);
            printf("\t%.1f", matrizP[i][j]);
        }
        printf("\n");
    }

    fclose(ar);//cierro archivo

    for(int i=0; i<2; i++){
        if(!fork()){    
                switch(i){
                        case 0:
                               //hijo 1
                            printf("MatrizR\n");
                            for(int i=0; i<fil; i++){
                                for(int j=0; j<col; j++){
                                    matrizR[i][j] = ((100-matrizN[i][j])*(2-matrizC[i][j])*(1-matrizP[i][j]))/100;
                                    printf("\t%.1f", matrizR[i][j]);
                                }
                                printf("\n");
                             }
                         
                            exit(1);


                         case 1:
                              //hijo 2
                            printf("MatrizS\n");
                            for(int i=0; i<fil; i++){
                                for(int j=0; j<col; j++){
                                    matrizS[i][j] = ((2*matrizN[i][j])*(matrizC[i][j]+1)*(matrizP[i][j]+2))/100;
                                    printf("\t%.1f", matrizS[i][j]);
                                }
                                printf("\n");
                             }
                          
                            exit(1);

                        }
            }
    }
    for(int i=0; i<2; i++){
        wait(NULL);    
    }

    for(int i=0; i<fil; i++){
        for(int j=0; j<col; j++){
                if(matrizR[i][j] >1.5 && matrizS[i][j] <0.3){
                        matrizA[i][j] = 2; 
                   } 
                else if(matrizR[i][j] >1.2 && matrizS[i][j] <0.4){
                        matrizA[i][j] = 1; 
                   } 
                else{
                        matrizA[i][j] =0;                    
                    }
           }    
    }
    
        printf("Matriz A\n");
     for(int i=0; i<fil; i++){
          for(int j=0; j<col; j++){
             printf("\t%.1f", matrizA[i][j]);
           }
           printf("\n");
      }
   
shmdt(matrizN);
shmdt(matrizC);
shmdt(matrizP);
shmdt(matrizR);
shmdt(matrizS);
shmdt(matrizA);
shmctl(shmidN, IPC_RMID, NULL);
shmctl(shmidC, IPC_RMID, NULL);
shmctl(shmidP, IPC_RMID, NULL);
shmctl(shmidR, IPC_RMID, NULL);
shmctl(shmidS, IPC_RMID, NULL);
shmctl(shmidA, IPC_RMID, NULL);

}


