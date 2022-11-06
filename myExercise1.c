#include<stdio.h>
#include<math.h>
#include<time.h>  // para medir el tiempo

void OperacionOriginal(int iteraciones, float alpha, float x, float y)
{
    float t1, t2;

    for (int i=0; i<iteraciones; i++)
    {
        t1 = sin(alpha)*x + cos(alpha)*y;
        t2 = (-1)*cos(alpha)*x + sin(alpha)*y;
    }
}

void OperacionOptimizada(int iteraciones, float alpha, float x, float y)
{
    float s = sin(alpha), c = cos(alpha);
    float t1, t2;

    for (int i=0; i<iteraciones; i++)
    {
        t1 = s*x + c*y;
        t2 = (-1)*c*x + s*y;
    }
}


void main()
{
    int iteraciones, jumps;
    float alpha, x, y, tiempoOriginal, tiempoOptimizado;

    printf("ingrese numero de iteraciones y sus saltos, así como un ángulo en grados y dos valores 'x' y 'y' :\n");
    scanf("%d %d %f %f %f", &iteraciones, &jumps, &alpha, &x, &y);
    printf("\ncalculando operaciones...");

    alpha = alpha*M_PI/180;  // se convierte a radianes

    FILE *operaciones;
    operaciones = fopen("operacionesSinCos.txt", "w");

    for (int iters=jumps; iters<iteraciones; iters+=jumps)
    {
        clock_t originalBegin = clock();
        OperacionOriginal(iters, alpha, x, y);
        clock_t originalEnd = clock();
        tiempoOriginal = (float) (originalEnd - originalBegin) / CLOCKS_PER_SEC;

        clock_t optimizedBegin = clock();
        OperacionOptimizada(iters, alpha, x, y);
        clock_t optimizedEnd = clock();
        tiempoOptimizado = (float) (optimizedEnd - optimizedBegin) / CLOCKS_PER_SEC;

        fprintf(operaciones, "%d %.4f %.4f\n", iters, tiempoOriginal, tiempoOptimizado);
    }

    fclose(operaciones);

    printf("\nOperaciones listas! revise el archivo 'operacionesSinCos.txt' para ver los resultados.\n\n");
}