#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
Contenido del archivo.txt

5
3 1 4 2 5

*/
int turnoidx =0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int NumHilos;


typedef struct{
	int *VecOrdenes;
	int idx;
}HiloArgs;
void *ImprimirOrden(void*args);

int main(){

	


	FILE *ar;
	ar = fopen("archivo.txt", "r");
	fscanf(ar, "%d", &NumHilos);
	printf("%d\n",NumHilos);
	
	int VecOrdenes[NumHilos];
	
	//contiene los ordenes de impresion [3][2][1][4]
	for(int j=0; j<NumHilos; j++){
		fscanf(ar,"%1d", &VecOrdenes[j]);
		printf("[%d]", VecOrdenes[j]);
	}
	printf("\n");
	
	pthread_t *Hilos = NULL;
	
	//contiene los id de los hilos segun su orden de creación.
	Hilos = (pthread_t*)calloc(NumHilos, sizeof(pthread_t));
	
	for(int i=0; i<NumHilos; i++){
		HiloArgs *args = (HiloArgs*)malloc(sizeof(HiloArgs)); // Asigna memoria a args
   	 	args->VecOrdenes = VecOrdenes;
    	args->idx = i + 1;  // Los hilos se numeran desde 1
    	pthread_create(&Hilos[i], NULL, ImprimirOrden, (void*)args);
	}
	
	for(int i=0; i<NumHilos; i++){
		pthread_join(Hilos[i], NULL);
	}
	
	
	free(Hilos);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
	

}

void *ImprimirOrden(void *args){
	//casteo de datos

	
	HiloArgs *hiloArgs = (HiloArgs*)args;
    int *VecOrdenes = hiloArgs->VecOrdenes;
    int idx = hiloArgs->idx;
	
	pthread_mutex_lock(&mutex);
	while(idx != VecOrdenes[turnoidx]){
		pthread_cond_wait(&cond, &mutex);
	}
	//seccion critica
	printf("Hilo [%d]\n",idx);
	turnoidx+=1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}



