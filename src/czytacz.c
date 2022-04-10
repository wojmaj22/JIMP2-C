#include <stdio.h>
#include <stdlib.h>

#include "czytacz.h"

int l;
int wxk;
int wiersze;
int kolumny;

int getwiersze(){
	return wiersze;
}

int getkolumny(){
	return kolumny;
}

int getwxk() {
	return wxk;
}

int getl() {
	return l;
}

struct Graph* createGraph(struct edge edges[], int wxk, int l)
{

	// allocate memory for the graph data structure
	//struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	struct Graph* graph = malloc(sizeof *graph);
	graph->head = malloc( l * sizeof *(graph->head) );

	// initialize head pointer for all vertices
	for ( int i = 0; i < wxk; i++ ) {
		graph->head[i] = NULL;
	}

	// add edges to the directed graph one by one
	for ( int i = 0; i < l; i++ )
	{
		// get the source and destination vertex
		int src = edges[i].src;
		int dest = edges[i].dest;
		double weight = edges[i].weight;

		// allocate new node of adjacency list from `src` to `dest`
		struct node* newNode = malloc(sizeof *(newNode) );
		struct node* newNode2 = malloc( sizeof *(newNode2));
		newNode->dest = dest;
		newNode->weight = weight;

		newNode->next = NULL;
		if( graph->head[src] == NULL ) {
			graph->head[src] = newNode;
		} else {
			for( newNode2 = graph->head[src]; newNode2->next != NULL; newNode2 = newNode2->next )
				;
			newNode2->next = newNode;
		}
	}

	
	return graph;
}

// Function to print adjacency list representation of a graph
void printGraph( struct Graph* graph, int wxk ) {
	for ( int i = 0; i < wxk; i++ ) {
		// print the current vertex and all its neighbors
		struct node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			printf("%d -> %d (%lf)\t", i, ptr->dest, ptr->weight);
			ptr = ptr->next;
		}

		printf("\n");
	}
}


struct edge *readfromfile( FILE * in ) {
	int c; 
	//int 
	l = 0;

	//liczenie dwukropków w pliku, czyli krawędzi:
	while((c = fgetc(in)) != EOF) {
		if( c == ':')
			l++;
	}

	rewind(in); //ustawienie wskaźnika z powrotem na początek pliku

	//czytanie pierwszej linijki pliku ( wymiary grafu ):
	if( fscanf( in, "%d %d", &wiersze, &kolumny) != 2 ) {
		fclose(in);
		printf("Zła pierwsza linijka!\n");
		return NULL;
	}
	else {
		wxk = wiersze*kolumny;
		//printf("Bedzie %d wierzcholkow\n", wxk);
	}

	//struct edge edges[l];
	struct edge *edges = malloc( l * sizeof(*edges));

	char buf[1024];
	
	//czytanie pozostałych linii z pliku i zapisywanie do struktury edges
	int i = -1, j = -1;
	int tempd1, tempd2;
	double tempw1, tempw2;
	while( fgets( buf, 1024, in ) != NULL ) {
		if( sscanf( buf, "%d :%lf %d :%lf", &tempd1, &tempw1, &tempd2, &tempw2) == 4) {
					//&edges[i].dest, &edges[i].weight, &edges[i+1].dest, &edges[i+1].weight) == 4 ) {

			//ten dlugi if to ogolnie sprawdzanie czy ta krawedz juz wczesniej nie wystapila w pliku
			//( w sensie ze np 2->1 to powtorzenie polaczenia 1->2, ktore juz bylo )
			//( jeszcze do dodania dla 3 i 4 polaczen )
			//jesli sie nie powtarza to wrzuca polaczenie do edges, jesli sie powtarza to nie
			if( tempd1 > j ) {
				if( tempd2 > j ) { //oba sie nie powtarzaja
					edges[i].src = j;
					edges[i+1].src = j;
					edges[i].dest = tempd1;
					edges[i].weight = tempw1;
					edges[i+1].dest = tempd2;
					edges[i+1].weight = tempw2;
					i+=2;
					j++;
				} else { //czyli pierwszy jest ok, drugi nie
					struct edge *newedges = realloc(edges, (l-1)*sizeof *newedges);
					edges = newedges;
					edges[i].src = j;
					edges[i].dest = tempd1;
					edges[i].weight = tempw1;
					i++;
					j++;
					l--;
				}
			} else { //czyli tempd1 < j, czyli pierwszy jest zly
				if( tempd2 > j ) { //drugi ok
					struct edge *newedges = realloc(edges, (l-1)*sizeof *newedges);
					edges=newedges;
					edges[i].src = j;
					edges[i].dest = tempd2;
					edges[i].weight = tempw2;
					i++;
					j++;
					l--;
				} else { //oba nie ok
					struct edge *newedges = realloc(edges, (l-2)*sizeof *newedges);
					edges=newedges;
					l-=2;
					continue;
				}
			}
		} else if( sscanf( buf, "%d :%lf", &tempd1, &tempw1) == 2 ) { 
					//&edges[i].dest, &edges[i].weight ) == 2 ) {
			if( tempd1 > j ) { //nie powtarza sie
				edges[i].src = j;
				edges[i].dest = tempd1;
				edges[i].weight = tempw1;
				i++;
				j++;
			} else { //powtarza sie
				struct edge *newedges = realloc(edges, (l-1)*sizeof *newedges);
                                edges=newedges;
				l--;
				continue;
			} 
		} else {			//(do poprawy jeszcze)
			i++;
			j++;
		}
	}
		fclose(in);

	return edges;
}
/*	


	free( edges );
	for( int i = 0; i < wxk; i++ )
		free( graph->head[i] );

	free( graph->head );
	free( graph );

	return 0;
	}
*/
