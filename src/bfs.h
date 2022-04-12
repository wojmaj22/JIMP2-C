#ifndef _BFS_H
#define _BFS_H

#include <stdlib.h>
#include <stdio.h>
#include "../utilities/memwatch.h"

struct FIFO { // kolejka FIFO
    int *vertices;
    int front;
    int end;
};

void add_to_queue( struct FIFO *queue, int vertex);

int del_from_queue( struct FIFO *queue);

void check_graph( char *plik);

#endif