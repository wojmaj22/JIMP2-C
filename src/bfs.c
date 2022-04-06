#include "bfs.h"

int add_to_queue()
{

}

int del_from_queue()
{

}

void check_graph( char *plik)
{
    FILE *in = fopen( plik, "r");
    if( in == NULL)
    {
        fprintf(stderr, "Nie znalazłem lub nie moge otworzyć pliku do odczytu.\n");
        exit(1);
    }
    int x_size, y_size;
    fscanf( in, "%i", &x_size);
    fscanf( in, "%i", &y_size);
    vertex queue1;
    vertex queue2;
    adjacency_list *adj_list = malloc( x_size * y_size * sizeof(adjacency_list));
    printf("Wczytano graf o wymiarach: %ix%i, miejsce zajęte: %li.\n", x_size,y_size, x_size * y_size * sizeof(adjacency_list)); 
    printf("Sprawdzanie spójności grafu z pliku %s.\n", plik);
}