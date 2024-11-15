#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* funcion_hilo1( void* arg);	


int main(){
	pthread_t pid; //identificadores de los hilos
	int *dato;
	dato = malloc(sizeof(int));
	*dato = 10;
	
	
	pthread_create(&pid, NULL, funcion_hilo1, dato);//se crea el hilo secundario
	//se muestra el hilo principal
	printf("Hilo principal {%lu}\t, dato a enviar {%d}\n", pthread_self(), *dato);	
	//funcion para esperar a el hilo secundario
	pthread_join(pid, NULL);
	
	free(dato); //libera memoria
	return EXIT_SUCCESS;

}

void* funcion_hilo1( void* arg){
	int *parametro =(int*)arg;
	printf("hilo secundario [%lu]\t, dato recibido [%d]\n",pthread_self(), *parametro );
	pthread_exit(0);

}	
