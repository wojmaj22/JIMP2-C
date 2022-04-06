#ifndef _BFS_H
#define _BFS_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Vertex{
    int vertex_number;
    struct Vertice *next;
} vertex;

typedef struct Adjacency_list {
    int vertex;
    int adjacent_vertices[2];
} adjacency_list;

int add_to_queue();

int del_from_queue();

void check_graph( char *plik);

#endif