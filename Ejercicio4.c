#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<mpi.h>

float Promedio(int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
  
    return (float) sum / n;
}

void PromedioPixeles(long int segmentSize, int partialX[], int partialY[], int partialZ[])
{
    /*de momento sera el nuevo tamaño considerando una
    particion de 4 segmentos de imagen*/
    int newSize = 256*64;
    float Xaverage[newSize], Yaverage[2], Zaverage[2];

    int i = 0, bloque;
    for (bloque=64; bloque<segmentSize; bloque+=64)
    {
        while (i < bloque)
        {

            i++;
        }
    }
}

// metodo elegido para particionar el dominio : horizontal
int main(int argc, char *argv[])
{
    int err;
    unsigned long int originalImageSize = 2048*2048;
    int Number_of_Processes, task;
    int x[originalImageSize], y[originalImageSize], intensity[originalImageSize];

    err = MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &Number_of_Processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &task);

    FILE *originalImageData;
    originalImageData = fopen("imagen_0001.pix", "r");

    // task 0 es el encargado de leer y escribir
    if (task == 0)
    {
        // lee los datos
        for (int pixel = 0; pixel < originalImageSize; pixel++)
        {
            fscanf(originalImageData, "%d. %d.  %d.\n", &x[pixel], &y[pixel], &intensity[pixel]);
        }
    }

    fclose(originalImageData);



    for (int i=0; i<Number_of_Processes; i++)
    {
        if (i == task)
        {

        }
    }
}