#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h> // Para medir tiempos de ejecucion

// a). Implementacion del caso a.
void ProductoMatricesA(int row1, int col2, int n, float a[row1][n], float b[n][col2], int print)
{
    float c[row1][col2];
    int i, j, k;
    memset(c, 0.0, sizeof(c));

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            for (k=0; k<n; k++)
            {
                c[i][j] += (a[i][k]*b[k][j]);
            }
        }
    }

    if (print == 1)
    {
        // imprimiendo
        for (i=0; i<row1; i++)
        {
            for (j=0; j<col2; j++)
            {
                printf("\t%.1f", c[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

// b). Implementacion del caso b.
void ProductoMatricesB(int row1, int col2, int n, float a[row1][n], float b[n][col2], int print)
{
    float c[row1][col2];
    int i, j, k;
    memset(c, 0.0, sizeof(c));

    for (i=0; i<n; i++)
    {
        for (k=0; k<n; k++)
        {
            for (j=0; j<n; j++)
            {
                c[i][j] += (a[i][k]*b[k][j]);
            }
        }
    }

    if (print == 1)
    {
        // imprimiendo
        for (i=0; i<row1; i++)
        {
            for (j=0; j<col2; j++)
            {
                printf("\t%.1f", c[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

// c). Implementacion del caso c.
void ProductoMatricesC(int row1, int col2, int n, float a[row1][n], float b[n][col2], int print)
{
    float c[row1][col2];
    int i, j, k;
    memset(c, 0.0, sizeof(c));

    for (k=0; k<n; k++)
    {
        for (i=0; i<n; i++)
        {
            for (j=0; j<n; j++)
            {
                c[i][j] += (a[i][k]*b[k][j]);
            }
        }
    }

    if (print == 1)
    {
        // imprimiendo
        for (i=0; i<row1; i++)
        {
            for (j=0; j<col2; j++)
            {
                printf("\t%.1f", c[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}


void main()
{
    int iteraciones, jumps;  // dada por el usuario

    printf("Ingrese las iteraciones a hacer para los productos de matrices y el intervalo : ");
    scanf("%d %d", &iteraciones, &jumps);

    // variables para almacenar los tiempos de ejecucion de cada funcion
    float tiempoCasoA=0.0, tiempoCasoB=0.0, tiempoCasoC=0.0;

    // matriz 'a' de prueba
    float a[4][4] = {
        {1.0, 2.0, 3.0, 4.0},
        {4.0, 5.0, 6.0, 7.0},
        {7.0, 8.0, 9.0, 10.0},
        {10.0, 11.0, 12.0, 13.0}
    };

    // matriz 'b' de prueba
    float b[4][4] = {
        {1.0, 2.0, 3.0, 4.0},
        {4.0, 5.0, 6.0, 7.0},
        {7.0, 8.0, 9.0, 10.0},
        {10.0, 11.0, 12.0, 13.0}
    };

    printf("\nResultado del producto para el caso a.:\n\n");
    ProductoMatricesA(4, 4, 4, a, b, 1);

    printf("\nResultado del producto para el caso b.:\n\n");
    ProductoMatricesB(4, 4, 4, a, b, 1);

    printf("\nResultado del producto para el caso c.:\n\n");
    ProductoMatricesC(4, 4, 4, a, b, 1);

    printf("\nCalculando tiempos...\n");

    FILE *matrixRunTimeData;
    matrixRunTimeData = fopen("ejecucionMatrices.txt", "w");

    for (int iters=jumps; iters<iteraciones; iters+=jumps)
    {
        clock_t inicioCasoA = clock();
        for (int j=0; j<iters; j++)
        {
            ProductoMatricesA(4, 4, 4, a, b, 0);
        }
        clock_t finCasoA = clock();
        tiempoCasoA = (float) (finCasoA - inicioCasoA) / CLOCKS_PER_SEC;


        clock_t inicioCasoB = clock();
        for (int j=0; j<iters; j++)
        {
            ProductoMatricesB(4, 4, 4, a, b, 0);
        }
        clock_t finCasoB = clock();
        tiempoCasoB = (float) (finCasoB - inicioCasoB) / CLOCKS_PER_SEC;


        clock_t inicioCasoC = clock();
        for (int j=0; j<iters; j++)
        {
            ProductoMatricesC(4, 4, 4, a, b, 0);
        }
        clock_t finCasoC = clock();
        tiempoCasoC = (float) (finCasoC - inicioCasoC) / CLOCKS_PER_SEC;

        fprintf(matrixRunTimeData, "%d %.4f %.4f %.4f\n", iters, tiempoCasoA, tiempoCasoB, tiempoCasoC);
    }

    fclose(matrixRunTimeData);

    printf("Calculos hechos! revisar el archivo 'ejecucionMatrices.txt' para ver los resultados.\n\n");
}