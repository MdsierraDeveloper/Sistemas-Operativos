#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*
Implementar un programa que cree N hilos, donde cada hijo debe imprimir su mensaje en un orden
en especifico definido en un archivo de entrada.

Requisitos: 
1. Los hilos deben crearse en orden numerico(1,2,3,4,5).
2. La impresión debe seguir el orden del archivo.
3. Cada hilo debe esperar su turno para imprimir.

----
El mutex serializa la secuencia de instrucciones, sin orden, pero solo ejecuta 1 hilo 
a la vez. No sirve para eso.

Una barrera, Decir a los hilos, nadie sigue hasta que todos estén una instruccion antes 
de la barrera. no sirve para eso.

Se podria resolver por turnos.
while(turno != idx){
	SI
	turno++;
} 
Este enfoque sirve pero es ineficiente.

Variables de condición.
Es una herramienta de ejecucion que permite sincronizar dado una condicion arbitraria.

if(!condicion){
	Condicion_wait(&c) //no cumple la condicion, entra a una cola
	}else{
		SI
		condicion_change();
		cond_signal(&c);
	}

Declarando variable de condición.
pthread_cont_t c = PTHREAD_COND_INITIALIZER

Condicion de espera por condicion
pthread_cond_wait(&c, &m);

Condicion brodcast para despertar todos los hilos
pthread_cond_broadcast(&c);

Condicion de señalizacion de 1 hilo.
pthread_cond_signal(&c);

condicion de destruccion de hilo.
pthread_cond_destroy(&c);

*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *ImprimirDato(void* arg){
	int dato = (int*)arg;
	
	
	
	
}

int main(void){
	FILE *r;
	int cantHilos;


	
	r = fopen("archivo.txt", "r");
	fscanf(r, "%d", &cantHilos);
	printf("%d\n", cantHilos);
	
	int *vectPos[cantHilos];
	pthread_t *hilos[cantHilos];
	
	for(int i=0; i<cantHilos; i++){
		fscanf(r, "%1d", &vectPos[i]);
		printf("%d\t", vectPos[i]);
	}
	//Ingresando los hilos al vector de hilos
	for(int j=0; j<cantHilos; j++){
		
		pthread_create(&hilos[i], NULL, ImprimirDato, (void*)j);
	}
	
	
	
	
	return EXIT_SUCCESS;
}
