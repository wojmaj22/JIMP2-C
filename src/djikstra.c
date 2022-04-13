#include "djikstra.h"
#include "czytacz.h"

extern int debug_flag;

double get_lowest_not_visited( double *array, short int *visited, int size) // poszukiwanie najbliższego nieodwiedzonego wierzchołka
{
	int i;
	double lowest = __INT_MAX__;
	double lowest_ind;
	for( i = 1; i < size; i++)
	{
		if (array[i] < lowest)
		{
            if(visited[i] == 0)
            {
			    lowest = array[i];
			    lowest_ind = i;
            }
        }
	}
return lowest_ind;
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

void calculate_path(char *filename, int x1, int x2, int y1, int y2)
{
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
    int size = 0;

    if( p1 < 0 || p1 > wxk || p2 < 0 || p2 > wxk)
    {
        fprintf( stderr, "Zły wierzchołek do pomiaru odległośći.\n");
        exit(6);
    }

    double *droga = malloc( wxk * sizeof(double)); // tablica odlgegłości do poszczególnych wierzchołków
    short int *visited = malloc( wxk * sizeof(short int)); // tablica odwiedzonych wierzchołków
    for( int i = 0; i < wxk; i++)
    {
        if( i != p1)
        	droga[i] = __INT_MAX__; // wszystkie wierzchołki mają na początku nieskończoną odległość
        else
			droga[p1] = 0; // pierwszy wierzchołek do szuakania ma odległość 0
        visited[i] = 0; // żaden wierzchołek nieodwiedzony
		size++; // ilość wierzchołków razem
    }
    while(size != 0) // dopóki nie przeszuka wszystkich wierzchołków
    {
        int vertex = get_lowest_not_visited( droga, visited, wxk); // wierzchołek z którego liczymy drogi do sąsiadujących wierzchołków - najbliższy od ostatniego i nieodwiedzony do tej pory
        if( debug_flag == 1)
		    printf("Element %i, wartość %lf\n", vertex, droga[vertex]); // do debugowania
        struct node *tmp = graph->head[vertex]; // tymczasowy wierzchołek z którego szukamy odległości
        while( tmp != NULL) // przeszukujemy wszystkich sąsiadów w tej pętli
        {
            if( droga[tmp->dest] > droga[vertex] + tmp->weight)
            {
                droga[tmp->dest] = droga[vertex] + tmp->weight;
            }
            tmp = tmp->next;
        }
        visited[vertex] = 1; // wierzchołek oznaczamy jako odwiedzony
		size--; // zmiejszamy żeby pętla kiedyś się zakończyła 
    }
    printf("Droga do (%i;%i) - %i wynosi %lf. \n", x2, y2, p2, droga[p2]);

    free(visited); // zwalnianie pamięci
    free(droga);
    free_memory( graph);
    free(graph->head);
    free(graph);
}