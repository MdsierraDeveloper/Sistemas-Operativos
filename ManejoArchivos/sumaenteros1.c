#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Manejo de archivos para sumar enteros creando 2 subprocesos con la llamada al sistema FORK.
*/
int main(){

	//archivo de prueba, cambiar
	FILE *ar;
	ar = fopen("test3.in", "r");
	//ar = fopen("test2.in", "r");
	//ar = fopen("test1.in", "r");
	
	
	//Se pueden compartir punteros a archivos, estos son copiados por los hijos en el stack segment
	FILE *arh;
	arh = fopen("exit.txt", "a");
	
	long cant; //variable para guardar la cantidad de datos en el archivo
	
	//leemos y mostramos la cantidad
	fscanf(ar, "%d", &cant);
	printf("%d\n", cant);
	
	//asignamos memoria dinamica a un vector, este es copiado por los hijos, hasta 
	//cuando ya tiene los datos dentro.
	int *vec = (int *)malloc(cant*sizeof(int));
		
	//recorremos el archivo y insertamos cada dato en nuestro vector dinamico.
	for(int i=0; i<cant; i++){
		fscanf(ar, "%d", &vec[i]);
		//printf("%d\n", vec[i]);
	}
	printf("valores Guardados correctamente por el padre\n");
	
	
	//creacion de hijos, todo codigo que este por fuera de este ciclo es codigo ejecutado por el padre.
	for(int i=0; i<2; i++){
	//forma mas intuitiva de crear los sub procesos.
		if(!fork()){
		
			switch(i){
				case 0://hijo 1
					printf("Hijo 1.\n");
					long a=0; //variable a guardar el valor total de la suma de recorrido 			del for
					for(int i=0; i<cant/2; i++){
						a += vec[i];
					}
					printf("De 0 hasta %d es: %ld\n", cant/2, a);
					
					fprintf(arh,"%ld\n", a); //guardamos el dato en un archivo ya creado
					
					
					exit(1);//llamada al sistema para terminar el subproceso
					
				case 1://hijo 2 el hijo 2 hace exactamente lo mismo que el hijo 1
				
					printf("Hijo 2.\n");
					long c=0;
					for(int i=cant/2+1; i<cant; i++){
						c += vec[i];
					}
					printf("De %d hasta %d es: %ld\n", (cant/2)+1, cant, c);
																 
					fprintf(arh,"%ld\n", c);
					
					exit(1);		
			}
		}
	}
	
	
	
	
	for(int i=0; i<2; i++){wait(NULL);} //ciclo for para esperar  a que todos los subprocesos terminen
	usleep(100000);
	
	long sum1, sum2;
	
	//abrimos desde el padre en modo lectura para sumar lo que los hijos colocaron
	FILE *arp;
	arp = fopen("exit.txt", "r");
	
	fscanf(arp, "%d", &sum1);
	fscanf(arp, "%d", &sum2);
	
	long total = sum1+sum2;
	printf("El resultado final es: %ld", total);
	
	remove("exit.txt");
	

}
