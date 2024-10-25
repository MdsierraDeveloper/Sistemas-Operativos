#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
	
	char *buffer;
	FILE *archi = fopen("minas.txt", "r");
	
	int filas, columnas;
	if(fscanf(archi," %d %d", &filas, &columnas)!=2){
		fclose(archi);
	}
	printf("%d %d\n", filas, columnas);
	
	
	int **archivo = (int **)malloc(filas * sizeof(int *));
	for(int i = 0; i<filas; i++){
		archivo[i] = (int *)malloc(columnas * sizeof(int*));
	}
	
	for(int i =0; i<filas; i++){
		for(int j =0; j<columnas; j++){
			fscanf(archi, "%1d", &archivo[i][j]);
		}
	}
	fclose(archi);
	

	
	int fd[4][2];
	for(int i =0; i<4;i++){
		if(pipe(fd[i])==-1){
			printf("ERROR CREACION DE TUB");
			exit(1);
		}
	}
	
	
	//escritura 1
	//lectura 0
	
	//cerramos automaticamente las de escritura de todas las tub
	for(int i=0; i<4; i++){
		close(fd[i][1]);
	}	
	
	//hijo 1
	read(fd[0][0], buffer, sizeof(buffer));
	close(fd[0][0]);
	printf("HIJO 1 -> %d\n", buffer);
	
	
	//hijo 2
	read(fd[1][0], buffer, sizeof(buffer));
	close(fd[1][0]);
	printf("HIJO 2 -> %d\n", buffer);
	
	
	//hijo 3
	read(fd[2][0], buffer, sizeof(buffer));
	close(fd[2][0]);
	printf("HIJO 3 -> %d\n", buffer);
	
	
	//hijo 4
	read(fd[3][0], buffer, sizeof(buffer));
	close(fd[3][0]);
	printf("HIJO 4 -> %d\n", buffer);
		
	//de aca pa arriba es el padre
	
	for(int i =0; i<4; i++){
		if(!fork()){
			switch(i){
				case 0: //hijo 1
									
					//configuracion tuberias
					for(int i=0; i<4; i++){
							close(fd[i][0]);
							if(i != 0){
								close(fd[i][1]);
							}
					}
					
					//primer cuadrante
					for(int i=0; i<filas/2;i++ ){
						for(int j = 0; j<columnas/2; j++){
	
							//if(i>=0 || i<=filas){
								//if(j>=0 || j<=columnas){
								
									if(archivo[i][j]==1){
	

										for(k=i+1; k<=; i++){
											for(j+1; j<j-1; j++){
											
												if(archivo[i][j]==2){
													break;
												};
											}
										}
										
										write(fd[0][1], &buffer, sizeof(buffer));
										close(fd[0][1]);
										
										
										
									}
									
								
							
									
							
							
							
						}
					}
					
					
					

					exit(1);
				case 1: //hijo 2
				
				
					//configuracion tuberias
					for(int i=0; i<4; i++){
						if(i != 1){
							close(fd[i][0]);
						}
					}
					
					//segundo cuadrante
					for(int i=filas/2; i<filas;i++ ){
						for(int j =0 ; j<columnas/2; j++){
							if(1>=0 || i<=filas){
								if(j>=0 || j<=columnas){
									if(archivo[i][j]==1){
										buffer = archivo[i][j];
										for(i+1; i< i-1; i++){
											for(j+1; j<j-1; j++){
												if(archivo[i][j]==2){
													write(fd[1][1], &buffer, sizeof(buffer));
													close(fd[1][1]);
												};
											}
										}
										
										
										
									}
									
								}
							
							}		
							
							
							
						}
					}
					
					
					
					
					
					exit(1);
				case 2: //hijo 3
				
					//configuracion tuberias
					for(int i=0; i<4; i++){
						if(i != 2){
							close(fd[i][0]);
						}
					}
					
					//tercer cuadrante
					for(int i=0; i<filas/2;i++ ){
						for(int j =columnas/2 ; j<0; j++){
							if(1>=0 || i<=filas){
								if(j>=0 || j<=columnas){
									if(archivo[i][j]==1){
										buffer = archivo[i][j];
										for(i+1; i< i-1; i++){
											for(j+1; j<j-1; j++){
												if(archivo[i][j]==2){
													write(fd[2][1], &buffer, sizeof(buffer));
													close(fd[2][1]);
												};
											}
										}
										
										
										
									}
									
								}
							
							}		
							
							
							
						}
					}
				
					
					
					exit(1);
				case 3: //hijo 4
					//tercer cuadrante
					for(int i=0; i<filas/2;i++ ){
						for(int j =columnas/2 ; j<0; j++){
							if(1>=0 || i<=filas){
								if(j>=0 || j<=columnas){
									if(archivo[i][j]==1){
										buffer = archivo[i][j];
										for(i+1; i< i-1; i++){
											for(j+1; j<j-1; j++){
												if(archivo[i][j]==2){						
													write(fd[3][1], &buffer, sizeof(buffer));
													close(fd[3][1]);
												};
											}
										}
										
										
										
									}
									
								}
							
							}		
							
							
							
						}
					}
				
				
					
					
					exit(1);
			}
		
			break;		
		}
	}
	//de aca pa abajo es el padre
	



}
