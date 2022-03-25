#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generator.h"

void create_graph(int x, int y, char *plik, double range_begin, double range_end)
{
    printf("Tworzenie grafu o wymiarach %ix%i, z wagami krawędzi w zakresie <%.2lf;%.2lf> i zapis do pliku %s.\n", x, y, range_begin, range_end, plik);

    int counter = 0;

    FILE *out = fopen( plik, "w");

    srand(time(NULL));
    
    fprintf( out, "%i %i\n", x,y);
    for ( int i = 0; i < x; i++)
    {
        for( int j = 0; j < y; j++)
        {
            if ( j != y-1 )
                fprintf( out, "%i :%lf  ", counter+1, range_begin + ((rand() / (double) RAND_MAX) * (range_end - range_begin))); // połączenie w lewo
            if ( i != x-1 )
                fprintf( out, "%i :%lf", counter+x, range_begin + ((rand() / (double) RAND_MAX) * (range_end - range_begin))); // połączenie w dół
            counter++;
            fprintf( out, "\n");
        }
    }
}