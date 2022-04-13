#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H


#include "../utilities/memwatch.h"
#include "czytacz.h"

#include <stdlib.h>
#include <stdio.h>

void calculate_path(char *filename, int x1, int x2, int y1, int y2);

void free_memory( struct Graph *graph);

#endif