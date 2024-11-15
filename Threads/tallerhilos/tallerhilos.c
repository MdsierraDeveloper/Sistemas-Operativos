#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
/*
Conteo de bases:
A: 2412 veces
T: 2516 veces
C: 2514 veces
G: 2558 veces

La secuencia 'TTGTAC' aparece 2 veces.
Posiciones de la secuencia: [1377, 7578]

Compilación
gcc tallerhilos.c -o tallerhilos

Ejecucion
./tallerhilos 1
*/

long int NumAdn;
int NumHilos;
char *adn;

struct datos{
	int A;
	int T;
	int C;
	int G;
};
struct datosBuscar{
	int fin;
	int inicio;
};
void *FuncionBuscar(void *arg);
void *FuncionContar(void *arg);
//end declaraciones globales

int main(int argc, char *argv[]){

	NumHilos = atoi(argv[1]);
	pthread_t idH1;
	pthread_t idHn[NumHilos];
	printf("Numero de hilos: %d\n", NumHilos);
	
	//manejo de archivo leer cant de adn
	FILE *ar;
	ar = fopen("adn1.in", "r");	
	fscanf(ar, "%d", &NumAdn);
	printf("numero de adn: %d\n", NumAdn);
	
	adn = (char *)malloc(NumAdn*sizeof(char));
	

	//leer toda la cadena de adn
	while(!feof(ar)){
		fscanf(ar, "%s", adn);
	}
	//printf("%s\n",adn);
	
	
	struct datos *argCont;
	argCont = (struct datos*)malloc(sizeof(struct datos));
	
	//hilo 1
	pthread_create(&idH1, NULL, FuncionContar, (void *)argCont);
	
	pthread_join(idH1, NULL);



	//N HILOS
	struct datosBuscar *datobuscar;
	datobuscar = (struct datosBuscar*)malloc(sizeof(struct datosBuscar)*NumHilos);
	
	for(int i=0; i<NumHilos; i++){
	
		//asignacion de segmento
		int segmento = NumAdn/NumHilos;
		//asignamos un sobrante para los numeros que su modulo es diferente a cero
		int sobrante = NumAdn%NumHilos;
		
		//asigno posiciones para cada hilo
		datobuscar[i].inicio = i*segmento;
		datobuscar[i].fin = (i+1)*segmento;
		
		//si es el ultimo hilo
		if(i==NumHilos-1){
			datobuscar[i].fin = NumAdn;
		}
	
	
		pthread_create(&idHn[i], NULL, FuncionBuscar, (void*)&datobuscar[i]);
	}
	
	for(int i=0; i<NumHilos; i++){
		pthread_join(idHn[i], NULL);
	}
	

	
	return EXIT_SUCCESS;

}//end main


void *FuncionBuscar(void *argbuscar){
	struct datosBuscar* argBuscar = (struct datosBuscar*)argbuscar;
	
	int inicio =argBuscar->inicio;
	int fin = argBuscar->fin;
	
	for(int i=inicio; i<fin-6;i++){
		if(strncmp(&adn[i], "TTGTAC", 6)==0){
			printf("Secuencia encontrada en %d\n", i);
		}
	}


}//end FuncionBuscar


void *FuncionContar(void *arg){
	struct datos* argcont = (struct datos*)arg;

	int A =0; int T = 0; int C=0;int G=0;
	for(int i=0; i<NumAdn;i++){
		switch(adn[i]){
			case 'A':
				A++;
				break;
			case 'T':
				T++;
				break;
			case 'C':
				C++;
				break;
			case 'G':
				G++;
				break;
		}
		
	}
	
	argcont->A=A;
	argcont->T=T;
	argcont->C=C;
	argcont->G=G;
	
	printf("A: %d\n T: %d\n C:%d\n G:%d\n ", argcont->A, argcont->T,argcont->C,argcont->G);
	free(argcont);
	pthread_exit(0);
	
}//end funcioncontar

