#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generator.h"

void create_graph(int x, int y, char *plik, double range_begin, double range_end)
{
    printf("Tworzenie grafu o wymiarach %ix%i, z wagami krawędzi w zakresie <%.2lf;%.2lf> i zapis do pliku %s.\n", x, y, range_begin, range_end, plik);
}