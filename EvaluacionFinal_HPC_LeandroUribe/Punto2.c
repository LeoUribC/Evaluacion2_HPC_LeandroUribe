#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<mpi.h>

// se ingresan dos particulas, cada una son listas de 3 elementos referentes a su posicion
double distanciaEntreParticulas(float P1[], float P2[])
{
    double result = sqrt( pow((P1[0] - P2[0]), 2) + pow((P1[1] - P2[1]), 2) + pow((P1[2] - P2[2]), 2) );
    return result;
}

// aproximaxion serial
void main()
{
    FILE *info_particulas;
    info_particulas = fopen("particulas.dat", "r");

    double *posiciones_x, *posiciones_y, *posiciones_z;
    posiciones_x = (float *) malloc( 100000*sizeof(double) );
    posiciones_y = (float *) malloc( 100000*sizeof(double) );
    posiciones_z = (float *) malloc( 100000*sizeof(double) );

    for (int i = 0; i<100001; i++)
    {
        fscanf("%.8f %.8f %.8f", &posiciones_x[i], &posiciones_y[i], &posiciones_z[i]);
    }

    fclose(info_particulas);

    // creacion del archivo de distancias acumuladas para cada particula
    FILE *distancias;
    distancias = fopen("distancias.txt", "w");
    
    double distanciaAcumulada = 0.0;
    double particula1[3], particula2[3];
    for (int i=0; i<100001; i++)
    {
        particula1[0] = posiciones_x[i];
        particula1[1] = posiciones_y[i];
        particula1[2] = posiciones_z[i];
        for (int j=0; j<100001; j++)
        {
            particula2[0] = posiciones_x[j];
            particula2[1] = posiciones_y[j];
            particula2[2] = posiciones_z[j];
            distanciaAcumulada += distanciaEntreParticulas(particula1, particula2);
        }
        fprintf(distancias, "%.8f\n", distanciaAcumulada);
        distanciaAcumulada = 0.0;
    }
    
    fclose(distancias);
}