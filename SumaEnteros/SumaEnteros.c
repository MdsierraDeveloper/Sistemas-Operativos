#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


void Ordernar(int *array, int ini, int fn)
{
    int izq, der, piv,  aux;
    izq = ini;
    der = fn;
    piv = array[(int)((izq+der)/2)];
    do
    {
        while (array[izq] < piv && izq<fn)
        {
            izq++;
        }
        while (array[der] > piv && der>ini)
        {
            der--;
        }      
        if(izq <= der)
        {
            aux =array[izq];
            array[izq] = array[der];
            array[der] =aux;
            izq++;
            der--;
        }
    } while (izq <= der);
    
    if (ini <= der)
    {
        Ordernar(array, ini, der);
    }
    if (fn > izq)
    {
        Ordernar(array,izq,fn);
    }
}
double mediana(int *array, int size)
{
     if (size % 2 == 0) {
        return (array[size / 2 - 1] + array[size / 2]) / 2.0;
        
    } else {
        
        return array[size / 2];
    }
}
double Varianza(int *array, double media, int n)
{
    double vari =0.0;
    for (int i = 0; i < n; i++)
    {
        double diff = array[i] - media;
        vari += diff * diff;
    }
    return vari /= n;
}
double DesvEstandar(int *array, double media, int n)
{
    double devstandar = Varianza(array, media, n);
    return sqrt(devstandar);
}



struct timespec start, end;
int main(int argc, char const *argv[])
{
    //lectura
    double elapsed1;
    clock_gettime(CLOCK_REALTIME, &start);

    FILE *file;
    file = fopen(argv[1], "r");                     // para mandarle argumentos por medio de la terminal en el primer argv en la posicion 1.
    if(file == NULL)
    {
        printf("EROR AL ARBRIR");
        exit(1);
    }
    int size;                                       //tamano del array
    int *array = NULL;                               //inicializa el array como puntero
    fscanf(file, "%d", &size);                          //guarda el tamano en size del primer dato del archivo, la funcion  es file scanf

    array = (int*)malloc(size*sizeof(int));       //reserva de memoria de tamano size y lo multiplica por el sizeof(int) el tamano de un entero es 8bytes

    clock_gettime(CLOCK_REALTIME, &end);
    elapsed1 = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec)/1e9);
    printf("TIempo de lectura :");
    printf("%.8lf\n", elapsed1);

    //almacenamiento de archivo en memoria
    for (int i = 0; i < size; i++)
    {
         fscanf(file, "%d", &array[i]);     //funcion fscaf que recibe el archivo, el tipo de dato y lo guarda en la instancia &array[] en la posicion i
    }
    
    double elapsed2;
    clock_gettime(CLOCK_REALTIME, &start);
    
    long int sum =0;                                //variable donde se guarda la suma
    for (int i = 0; i < size; i++)                  // ciclo de recorrido
    {
        sum += array[i];                            //va anadiendo  a la suma el dato que esta en array[i]
    }

    clock_gettime(CLOCK_REALTIME, &end);
    elapsed2 = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec)/1e9);

    printf("\nSUMA : %ld\n", sum);
    
    printf("\nTiempo Suma : %.8lf\n", elapsed2);
    
    //ordenar
    double time_sort;
    clock_gettime(CLOCK_REALTIME, &start);

    Ordernar(array,0,size-1);

    clock_gettime(CLOCK_REALTIME, &end);
    time_sort = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec)/1e9);
    printf("\nTIEMPO ORDENAR: %.8lf\n", time_sort);

    //MEDIANA
    double medianaR = mediana(array, size);
    printf("\nLa Mediana es: %.2lf\n",medianaR );
    
    //Media
    int media = sum/size;
    printf("\nMEDIA : %ld\n", media);

    //Varianza
   // float varianzaR = ;
    double varian = Varianza(array, media, size);
    printf("\nLa varianza es: %.2lf\n", varian);

    //desviacion estandar es la raiz cuadrada de la varianza
    double desviEstandar = DesvEstandar(array, media, size);
    printf("\nDesviacion estandar : %.2lf\n", desviEstandar);

    //numeros repetidos
    
   

    fclose(file);
    free(array);
    return 0;
}

