#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
//#include<mpi.h>  // este .c no implementa paralelizacion

float Promedio(float a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
  
    return (float) sum / n;
}

// el parametro segmentSize de momento sera 2048x512
void PromedioPixeles(int segmentSize, float partialX[], float partialY[], float partialZ[])
{
    /*de momento sera el nuevo tamaño considerando una
    particion de 4 segmentos de imagen*/
    int newSize = 256*64;
    float *Xaverage, *Yaverage, *Zaverage;

    Xaverage = (float *) malloc( newSize*sizeof(float) );
    Yaverage = (float *) malloc( newSize*sizeof(float) );
    Zaverage = (float *) malloc( newSize*sizeof(float) );

    float average = 0.0;
    float intensityBlock[64];  // bloque de 64 intensidades

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

    /*el tamaño de y_index va a cambiar. De momento es 64
    y todo el segmento comienza en x = y = 0*/
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
        fprintf(image_segment, "%.3f %.3f %.3f\n", Xaverage[pixel], Yaverage[pixel], Zaverage[pixel]);
    }

    fclose(image_segment);
}


// metodo elegido para particionar el dominio : horizontal
void main()
{
    int originalImageSize = 2048*2048; // por probar
    float *x, *y, *intensity;
    //int Number_of_Processes, task;

    x = (float *) malloc( originalImageSize*sizeof(float) );
    y = (float *) malloc( originalImageSize*sizeof(float) );
    intensity = (float *) malloc( originalImageSize*sizeof(float) );

    FILE *originalImageData;
    originalImageData = fopen("imagen_0001.pix", "r");

    // lee los datos
    for (int pixel = 0; pixel < originalImageSize; pixel++)
    {
        fscanf(originalImageData, "%f %f %f\n", &x[pixel], &y[pixel], &intensity[pixel]);
    }

    fclose(originalImageData);

    int segmentSize = 2048*512;  // para probar el primer segmento de imgen
    float *partialX, *partialY, *partialZ;
    partialX = (float *) malloc( segmentSize*sizeof(float) );
    partialY = (float *) malloc( segmentSize*sizeof(float) );
    partialZ = (float *) malloc( segmentSize*sizeof(float) );

    // se llenan valores parciales para la prueba
    for (int pix = 0; pix < segmentSize; pix++)
    {
        partialX[pix] = x[pix];
        partialY[pix] = y[pix];
        partialZ[pix] = intensity[pix];
    }

    printf("\ncalculando...");
    PromedioPixeles(segmentSize, partialX, partialY, partialZ);
    printf("\nListo! revise los resultados.\n");

/*
    for (int i=0; i<Number_of_Processes; i++)
    {
        if (i == task)
        {

        }
    }*/
}