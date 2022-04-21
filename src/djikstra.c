#include "djikstra.h"
#include "czytacz.h"

struct Queue{
	int *vertices;
	int start;
	int end;
};

extern int debug_flag;

int size;

void swap_i(int *a, int *b) // zamienia inty
{
  int temp = *b;
  *b = *a;
  *a = temp;
}

int get_lowest( double *array, struct Queue *queue) // poszukiwanie najbliższego nieodwiedzonego wierzchołka
{
	double smallest = array[queue->end];
	int smallest_ind = queue->end;
	for( int i = queue->end; i < queue->start; i++)
	{
		if( array[queue->vertices[i]] < smallest)
		{
			smallest_ind = i;
			smallest = array[queue->vertices[i]];
		}
	}
	int temp = queue->vertices[smallest_ind];
	queue->vertices[smallest_ind] = queue->vertices[queue->end];
	queue->vertices[queue->end] = temp;
	return queue->vertices[queue->end];
}

void free_memory( struct Graph *graph)
{
	int s = getwxk();
	
	for(int i = 0; i < s; i++)
	{
		struct node *current;
		struct node *next;
		current = graph->head[i];
		while( current != NULL)
		{	
			next = current->next;
			free(current);
			current = next;
		}
	}
}

void add_to_q( struct Queue *queue, int vertex) // dodawanie do kolejki
{
    queue->vertices[queue->start] = vertex;
    queue->start++;
}

int del_from_q( struct Queue *queue, int vertex) // usuwanie z kolejki
{
    //if( debug_flag == 1)
        //printf("Usunięto wierzchołek: %i \n", queue->vertices[queue->end]);
    //int temp = queue->vertices[vertex];
	//queue->vertices[vertex] = queue->vertices[queue->end];
	//queue->vertices[queue->end] = temp;
	queue->end++;

}

void calculate_path(char *filename, int x1, int x2, int y1, int y2)
{
	int tee = 0;
    printf("Obliczanie drogi z punktu:(%i;%i) do (%i;%i) w pliku %s.\n", x1, y1, x2, y2, filename);
    FILE *in = fopen( filename, "r");
    if( in == NULL)
    {
        fprintf(stderr, "Błąd, nie moge odczytać pliku lub nazwa pliku jest błędna.\n");
        exit(2);
    }
    
    struct edge *edges = readfromfile(in);

    int l = getl();
    int wxk = getwxk();
    struct Graph *graph = createGraph( edges, wxk, l);
	
	int wiersze = getwiersze(), kolumny = getkolumny();
    int p1 =  x1 + wiersze * y1; //pierwszy punkt bez współrzędnych
    int p2 =  x2 + wiersze * y2; //drugi punkt bez współrzędnych

    if( p1 < 0 || p1 > wxk || p2 < 0 || p2 > wxk)
    {
        fprintf( stderr, "Zły wierzchołek do pomiaru odległośći.\n");
        exit(6);
    }

	struct Queue queue;
	queue.vertices = malloc( wxk * sizeof(int));
	queue.start = 0;
	queue.end = 0;

	int size = wxk;
    //początek algorytmu
    double *droga = malloc( wxk * sizeof(double)); // tablica odlgegłości do poszczególnych wierzchołków
    short int *visited = malloc( wxk * sizeof(short int)); // tablica odwiedzonych wierzchołków
    for( int i = 0; i < wxk; i++)
    {
        if( i != p1)
        	droga[i] = __INT_MAX__; // wszystkie wierzchołki mają na początku nieskończoną odległość
        else
			droga[p1] = 0; // pierwszy wierzchołek do szuakania ma odległość 0
        visited[i] = 0; // żaden wierzchołek nieodwiedzony
    }
	add_to_q( &queue, p1);
	visited[p1] = 1;

    while(queue.end != wxk) // dopóki nie przeszuka wszystkich wierzchołków
    {
        int vertex = get_lowest( droga, &queue ); // wierzchołek z którego liczymy drogi do sąsiadujących wierzchołków - najbliższy od ostatniego i nieodwiedzony do tej pory
    		//if( debug_flag == 1)
				//printf("Element %i, wartość %lf\n", vertex, droga[vertex]); // do debugowania
        struct node *tmp = graph->head[vertex]; // tymczasowy wierzchołek z którego szukamy odległości
        while( tmp != NULL) // przeszukujemy wszystkich sąsiadów w tej pętli
        {
			//printf("%i: %.2lf -> %i: %.2lf\n", vertex, droga[vertex], tmp->dest, droga[tmp->dest]);
			if( visited[tmp->dest] == 0 )
			{
			//printf("Dodano wierzchołek %i droga %lf \n", tmp->dest, droga[tmp->dest]);
				add_to_q( &queue, tmp->dest);
				visited[tmp->dest] = 1;
			}
            	if( droga[tmp->dest] > droga[vertex] + tmp->weight)
            	{
            	    droga[tmp->dest] = droga[vertex] + tmp->weight;
            	}
				//printf("Droga do %i - %lf\n", tmp->dest, droga[tmp->dest]);
			
            tmp = tmp->next;
        }
		//size--; // zmiejszamy żeby pętla kiedyś się zakończyła

		del_from_q( &queue, vertex);

		//for( int i = queue.end; i < queue.start; i++)
		//{
		//	printf("%i ", queue.vertices[i]);
		//}
		//printf("\n");
    }
    printf("Droga do (%i;%i) - %i wynosi %lf. \n", x2, y2, p2, droga[p2]);
	
	/*
	if( debug_flag == 1)
	{
		for(int i = 0; i < wxk; i++)
		{
			printf("%i: %.2lf\n", i, droga[i]);
		}	
	}
	*/
	FILE *out = fopen( "data/por.txt", "w");
	for(int i = 0; i < wxk; i++)
		{
			fprintf( out, "%i: %.2lf\n", i, droga[i]);
		}
	//zwalnianie pamięci
    free(visited);
    free(droga);
    free_memory( graph);
    free(graph->head);
    free(graph);
	free(queue.vertices);
}