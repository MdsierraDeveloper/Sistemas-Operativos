#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
IMPLEMENTA UN PROGRAMA QUE CREE DOS HILOS: UNO PRODUCTOR Y UNO CONSUMIDOR.
EL PRODUCTOR DEBE GENERAR NUMEROS ENTEROS Y ALMACENARLO EN UNA COSA DE TAMAÑO FIJO.
EL CONSUMIDOR DEBE LEER LOS NUMEROS DE LA COLA Y MOSTRARLOS EN PANTALLA
*/
int *vec;
void *FuncionWrite(void *vec){
}
void *FuncionRead(void *vec){

}

int main(void){
	
	pthread_t idhp;//creación de hilo productor
	pthread_t idhc;//Creación de hilo de consumidor

	
	pthread_create(&idhp, NULL, FuncionWrite, vec); 
	pthread_create(&idhc, NULL,FuncionRead, vec);
	
	

}
