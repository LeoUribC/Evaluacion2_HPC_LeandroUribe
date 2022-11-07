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

// el parametro segmentSize de momento sera 2048x512
void PromedioPixeles(long int segmentSize, int partialX[], int partialY[], int partialZ[])
{
    /*de momento sera el nuevo tamaño considerando una
    particion de 4 segmentos de imagen*/
    int newSize = 256*64;
    float Xaverage[newSize], Yaverage[newSize], Zaverage[newSize];
    float average = 0.0;
    int intensityBlock[64];  // bloque de 64 intensidades

    /*se calculan los promedios de cada bloque de 64 (8x8) intensidades*/
    int z_i = 0, z_index = 0, bloque;
    for (bloque = 64; bloque < segmentSize; bloque += 64)
    {
        for (int i=0; i<64; i++)
        {
            // array 'slicing' de partialZ a 64 elementos
            intensityBlock[i] = partialZ[z_i];
            z_i++;
        }
        // promedio de cada bloque de 64 intensidades
        average = Promedio(intensityBlock, 64);
        Zaverage[z_index] = average;  // para aprovechar el iterador bloque
        z_index++;
    }

    /*el tamaño de y_index va a cambiar. De momento es 64*/
    int x_index = 0, y_index = 0;
    for (int y_value = 1; y_value <= 64; y_value++)
    {
        for (int x_value = 1; x_value <= 256; x_value++)
        {
            Xaverage[x_index] = x_value;
            Yaverage[y_index] = y_value;
            x_index++; y_index++;
        }
    }

    // prueba para escribir el resultado en un archivo .txt
    FILE *image_segment;
    image_segment = fopen("segmento_prueba.txt", "w");

    for (int pixel = 0; pixel < newSize; pixel++)
    {
        fprintf(image_segment, "%d %d %.3f\n", Xaverage[pixel], Yaverage[pixel], Zaverage[pixel]);
    }

    fclose(image_segment);
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