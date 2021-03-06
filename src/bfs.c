#include "bfs.h"
#include "czytacz.h"
#include "djikstra.h"

extern int debug_flag;

void add_to_queue( struct FIFO *queue, int vertex) // dodawanie do kolejki
{
    queue->vertices[queue->front] = vertex;
    queue->front++;
}

int del_from_queue( struct FIFO *queue) // usuwanie z kolejki
{
    if( debug_flag == 1)
        printf("Usunięto wierzchołek: %i \n", queue->vertices[queue->end]);
    int tmp = queue->vertices[queue->end];
    queue->vertices[queue->end] = -1;
    queue->end++;
return tmp;
}

void check_graph( char *plik) // Algorytm BFS
{
    printf("Sprawdzanie spójności grafu z pliku %s.\n", plik);
    FILE *in = fopen( plik, "r");
    if( in == NULL)
    {
        fprintf(stderr, "Błąd, nie moge odczytać pliku lub nazwa pliku jest błędna.\n");
        exit(2);
    }

    struct edge *edges = readfromfile(in);

    int l = getl();
    int wxk = getwxk();
    struct Graph *graph = createGraph( edges, wxk, l);

    struct FIFO queue; // kolejka FIFO
    short int *visited = malloc ( wxk * sizeof (int));
    for( int i = 0; i < wxk; i++)
    {
        visited[i] = 0;
    }
    queue.vertices = (int *) malloc( wxk * sizeof(int) );
    queue.front = 0;
    queue.end = 0;
    
    add_to_queue( &queue, 0); // dodanie zerowego wierzchołka do kolejki
    if( debug_flag == 1)
        printf("Dodano wierzchołek 0 do kolejki.\n");
    visited[0] = 1;
    while( queue.front != queue.end) // sprawdzanie kolejnych wierzchołków
    {
        int current_vertex = del_from_queue( &queue);

        struct node *tmp = graph->head[current_vertex];
        while( tmp != NULL)
        {
            int adjVertex = tmp->dest;

            if( visited[adjVertex] == 0)
            {
                if( debug_flag == 1)
                    printf("Dodano wierzchołek %i do kolejki.\n", adjVertex);
                visited[adjVertex] = 1;
                add_to_queue( &queue, adjVertex);
            }
            tmp = tmp->next;
        }
    }
    int test = 0;
    if( queue.front == getwxk())
        printf("Graf jest spójny.\n");
    else
        printf("Graf nie jest spójny.\n");
    /*
    for( int i = 0; i < wxk; i++)
    {
        if( visited[i] == 0)
        {
            if(debug_flag == 1)
                printf("Nie odwiedzono wierzchołka %i\n", i);
            printf("Graf nie jest spójny.\n");
            test = 1;
            break;
        }
    }
    if ( test == 0)
        printf("Graf jest spójny.\n");
    */
    free(queue.vertices); // czyszczenie pamięci
    free(visited);
    free_memory( graph);
	free( graph->head);
	free( graph);
}