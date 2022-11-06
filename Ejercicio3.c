#include<stdio.h>
#include<math.h>
#include<time.h>  // para medir el tiempo

unsigned long long factorial(int number)
{
    unsigned long long result = 1;

    for (int n = 1; n <= number; n++)
    {
        result *= n;
    }

    return result;
}

void SumatoriaSinTaylor(float angulo, int N, int intervalo, int iteraciones)
{
    double s_total = 0.0, s_parcial = 0.0;
    float x = angulo*M_PI/180;

    for (int iters = 0; iters < iteraciones; iters++)
    {
        // se hace la particion
        int i = 0;
        for (int limite = intervalo; limite <= N; limite += intervalo)
        {
            while (i < limite)
            {
                s_parcial += pow(-1, i)*( pow(x, 2*i+1)/factorial(2*i+1) );
                i++;
            }
            s_total += s_parcial;
            s_parcial = 0.0;
        }
    }
}

void main()
{
    float angulo;
    int N, iteraciones, jumps;

    printf("\nSumatoria tipo serie de taylor de sin(x) :\n");
    printf("escriba el angulo, cantidad de términos, iteraciones e intervalo entre iteraciones :\n");
    scanf("%f %d %d %d", &angulo, &N, &iteraciones, &jumps);
    printf("\nrealizando calculos...");

    // conjunto de intervalos para agrupar terminos de la serie
    int agrupaciones[6] = {2, 3, 4, 5, 6, 10};

    float tiempo;  // para almacenar cada tiempo

    FILE *serieSegmentada;
    serieSegmentada = fopen("comparativa_serie_segmentada.txt", "w");

    for (int iters=jumps; iters<iteraciones; iters+=jumps)
    {
        fprintf(serieSegmentada, "%d", iters);
        for (int intervalo=0; intervalo<6; intervalo++)
        {
            clock_t begin = clock();
            SumatoriaSinTaylor(angulo, N, agrupaciones[intervalo], iters);
            clock_t end = clock();
            tiempo = (float) (end - begin) / CLOCKS_PER_SEC;

            fprintf(serieSegmentada, " %.5f", tiempo);
        }
        fprintf(serieSegmentada, "\n");
    }

    fclose(serieSegmentada);
    printf("\nCalculos hechos! revise el archivo 'comparativa_serie_segmentada.txt' para mas informacion.\n\n");
}