#include "djikstra.h"
#include "czytacz.h"

int size = 0;

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

void print_array( double *array, int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("%lf, \n", array[i]);
	}
}

double get_lowest_ind( double *array, int size)
{
	int i;
	double lowest = __INT_MAX__;
	double lowest_ind;
	for( i = 1; i < size; i++)
	{
		if (array[i] < lowest)
		{
			lowest = array[i];
			lowest_ind = i;
		}
	}
	return lowest_ind;
}

void calculate_path(char *filename, int x1, int x2, int y1, int y2)
{
    printf("Obliczanie drogi z punktu:(%i;%i) do (%i;%i) w pliku %s.\n", x1, y1, x2, y2, filename);
    FILE *in = fopen( filename, "r");
    if( in == NULL)
    {
        fprintf(stderr, "Błąd, nie moge odczytać pliku lub plik jest błędny.\n");
        exit(2); // dać odpowiedni kod błędu
    }
    
    struct edge *edges = readfromfile(in);

    int l = getl();
    int wxk = getwxk();
    struct Graph *graph = createGraph( edges, wxk, l);
	
	int wiersze = getwiersze(), kolumny = getkolumny();
    int p1 =  x1 + wiersze * y1; //pierwszy punkt bez współrzędnych
    int p2 =  x2 + wiersze * y2; //drugi punkt bez współrzędnych

    double *droga = malloc( wxk * sizeof(double));
    for( int i = 0; i < wxk; i++)
    {
        if( i != p1)
        	droga[i] = __INT_MAX__;
        else
			droga[i] = 0;
		size++;
    }
	qsort( droga, wxk, sizeof(double), cmpfunc);
	int counter = 0;
    while(size != 0) // oblicza tylko drogę od 0, dodać kolejkę priorytetową
    {
        int u = counter;
		printf("Element %i, wartość %lf\n", u, droga[u]);
        struct node *tmp = graph->head[u];
        while( tmp != NULL)
        {
            if( droga[tmp->dest] > droga[u] + tmp->weight)
            {
                droga[tmp->dest] = droga[u] + tmp->weight;
            }
            tmp = tmp->next;
        }
		size--;
		counter++;
    }
    printf("Droga do (%i;%i) wynosi %lf. \n", x2, y2, droga[p2]);

    free(droga);
	free(edges);
    for( int i = 0; i < wxk; i++ )
		free( graph->head[i] );
    free(graph->head);
    free(graph);
}