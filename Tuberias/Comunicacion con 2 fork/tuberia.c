#include <stdlib.h> //manejo dinamico de memoria
#include <stdio.h> // para manejo de archivos
#include <unistd.h> // pipe, fork etc
#include <string.h>
#include <sys/wait.h>


int main(int argc, char **argv){
	/*
	
	Compilacion y ejecucion
	
	gcc tuberia.c
	
	./a.out archivo1.txt archivo2.txt
	
	Un proceso padre crea 2 hijos que leen 2 archivos y usan la comunicacion de tuberias
	para intercalar mensajes de los diferentes archivos.
	
	*/	

	char *archivo1, *archivo2;
	// [a.out 0]["arhivo1.txt 1"]["archivo2.txt 2"]
	archivo1 = argv[1];
	archivo2 = argv[2];
	
	printf("Archivos: %s %s\n", archivo1, archivo2);
	
	FILE *ar1;
	ar1 = fopen(archivo1, "r");
	
	
	FILE *ar2; 
	ar2 = fopen(archivo2, "r");
	
	char buffer[100];
	/*fscanf(ar1, "%s", buffer);
	printf("%s", buffer);
	*/
	
	int fd1[2];
	pipe(fd1);
	
	int fd2[2];
	pipe(fd2);
	
	/*
	0 : lectura
	1 : escritura
	*/	
	
	
	//creacion de hijos
	for(int i=0; i<2; i++){
		if(!fork()){
			switch(i){
				case 0: //hijo 1
					    close(fd1[0]);
					    
				 	while((fscanf(ar1, "%s", buffer)) != EOF){ //END OF FILE
					    write(fd1[1], buffer, sizeof(buffer));				 	
				 	}    
				 	
					    close(fd1[1]);
					    
					    exit(1);
			
				case 1: //hijo 2
					close(fd2[0]);
					
					while((fscanf(ar2, "%s", buffer) != EOF)){
						write(fd2[1], buffer, sizeof(buffer));
					}
					
					close(fd2[1]);
					
					exit(1);
			
			}
		}
	
	}
	//dentro de este for solo actuan los hijos
	
	
	for(int i=0; i<2; i++){
		wait(NULL);
	}
	
	close(fd1[1]); //cerramos escritura tub 1
	close(fd2[1]); //cerramos escritura tub 1
	
	while(1){
		int n1 = read(fd1[0], buffer, sizeof(buffer));
		if(n1>0){
		printf("hijo 1 -> %s\n", buffer);
			}
			
		int n2 = read(fd2[0], buffer, sizeof(buffer));
		if(n2 > 0){
			printf("hijo 2 -> %s\n", buffer);
			}
		if(n1 < 0 && n2 < 0){
			break;
		}

	}
	
	
	
	close(fd1[0]);
	close(fd2[0]);
	
	
	
	fclose(ar1);
	fclose(ar1);
	
	return EXIT_SUCCESS;

}


