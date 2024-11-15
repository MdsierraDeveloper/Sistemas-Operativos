#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct dato{
	int id;	
};

void *functionHilos(void *);
void error(char *);
int NumHilos;
int *orden = NULL;
int cont = 0;
pthread_cond_t vcond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
	pthread_t *tid = NULL; //almacenar los identificadores
	struct dato *data = NULL; //instancia del struct
	
	FILE *ar;
	ar = fopen("archivo.txt", "r");

	fscanf(ar, "%d", &NumHilos);

	orden = (int*)calloc(NumHilos, sizeof(int));//da espacio en memoria al orden

	for(int i=0; i<NumHilos; i++){
		fscanf(ar, "%1d", &orden[i]);
		printf("%d", orden[i]);
	}
	
	tid = (pthread_t *)calloc(NumHilos,sizeof(pthread_t));

	for(int j=1; j<NumHilos; j++){
		data = (struct dato *)malloc(sizeof(struct dato));
		if(!data) error("No hay Suficiente memoria");
		data->id = j;
		pthread_create(&tid[j],NULL, functionHilos,  (void *)&data);
	}

	for(int i=0; i<NumHilos; i++){
		pthread_join(tid[i], NULL);
	}

	free(tid);
	free(data);
	free(orden);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&vcond);

	return 0;

}

void *functionHilos(void *id){
	int mid = ((struct dato*)id)->id;
	pthread_mutex_lock(&mutex);
	while(mid!=orden[cont]){
		pthread_cond_wait(&vcond, &mutex);
	}
	//seccion critica
	printf("Soy hilo %d\n", mid );
	cont = cont +1;

	pthread_cond_broadcast(&vcond);
	pthread_mutex_unlock(&mutex);
	pthread_exit(0);

}

void error(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
