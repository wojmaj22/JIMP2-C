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
		struct node* newNode = malloc( sizeof *(newNode) );
		struct node* newNode2;
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
		
		struct node* newNode3 = malloc( sizeof *(newNode3) );
                struct node* newNode4;
                newNode3->dest = src;
                newNode3->weight = weight;

                newNode3->next = NULL;
                if( graph->head[dest] == NULL ) {
                        graph->head[dest] = newNode3;
                } else {
                        for( newNode4 = graph->head[dest]; newNode4->next != NULL; newNode4 = newNode4->next )
                                ;
                        newNode4->next = newNode3;
                }

		//free(newNode);
		//free(newNode3);

	}
	free(edges);

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
	l = 0;
	
	while((c = fgetc(in)) != EOF) {
		if( c == '\n')
			l++;
	}

#ifdef DEBUG
	fprintf(stderr, "Linii bedzie %d\n", l);
#endif

	rewind(in);

	if( fscanf( in, "%d %d", &wiersze, &kolumny) != 2 ) {
		fclose(in);
		//printf("Zła pierwsza linijka!\n");
		return NULL;
	}
	//rewind(in);
	wxk = wiersze*kolumny;
	//printf("Bedzie %d wierzcholkow\n", wxk);

	//struct edge edges[l];
	struct edge *edges = malloc( l * sizeof(*edges) );

	char buf[1024];
	
	//czytanie pozostałych linii z pliku i zapisywanie do struktury edges
	int i = 0, j = -1;
	int tempd1, tempd2, tempd3, tempd4;
	double tempw1, tempw2, tempw3, tempw4;
	while( fgets( buf, sizeof(buf), in ) != NULL ) {
		if( buf[0] == '\n' ) {
		        l--;
			j++;	
			continue;
		} else if( sscanf( buf, "%d :%lf %d :%lf %d :%lf %d :%lf", &tempd1, &tempw1, &tempd2, &tempw2, &tempd3, &tempw3, &tempd4, &tempw4 ) == 8 ) {
			if( tempd1 > j && tempd2 > j ) {
				struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
                                edges[i+1].src = j;
                                edges[i].dest = tempd1;
                                edges[i].weight = tempw1;
                                edges[i+1].dest = tempd2;
                                edges[i+1].weight = tempw2;
                                i+=2;
                                j++;
                                l++;
			} else if( tempd1 > j && tempd3 > j ) {
				struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
                                edges[i+1].src = j;
                                edges[i].dest = tempd1;
                                edges[i].weight = tempw1;
                                edges[i+1].dest = tempd3;
                                edges[i+1].weight = tempw3;
                                i+=2;
                                j++;
                                l++;
			} else if( tempd1 > j && tempd4 > j ) {
				struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
                                edges[i+1].src = j;
                                edges[i].dest = tempd1;
                                edges[i].weight = tempw1;
                                edges[i+1].dest = tempd4;
                                edges[i+1].weight = tempw4;
                                i+=2;
                                j++;
                                l++;
			} else if( tempd2 > j && tempd3 > j ) {
				struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
                                edges[i+1].src = j;
                                edges[i].dest = tempd2;
                                edges[i].weight = tempw2;
                                edges[i+1].dest = tempd3;
                                edges[i+1].weight = tempw3;
                                i+=2;
                                j++;
                                l++;
			} else if( tempd2 > j && tempd4 > j ) {
				struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
                                edges[i+1].src = j;
                                edges[i].dest = tempd2;
                                edges[i].weight = tempw2;
                                edges[i+1].dest = tempd4;
                                edges[i+1].weight = tempw4;
                                i+=2;
                                j++;
                                l++;
			} else if( tempd3 > j && tempd4 > j ) {
				struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
                                edges[i+1].src = j;
                                edges[i].dest = tempd3;
                                edges[i].weight = tempw3;
                                edges[i+1].dest = tempd4;
                                edges[i+1].weight = tempw4;
                                i+=2;
                                j++;
                                l++;
			} else if( tempd1 > j ) {
				//struct edge *newedges = realloc( edges, (l-3)*sizeof *newedges );
				//edges = newedges;
				edges[i].src = j;
				edges[i].dest = tempd1;
				edges[i].weight = tempw1;
				i++;
				j++;
				//l-=3;
			} else if( tempd2 > j ) {
                                //struct edge *newedges = realloc( edges, (l-3)*sizeof *newedges );
                                //edges = newedges;
                                edges[i].src = j;
                                edges[i].dest = tempd2;
                                edges[i].weight = tempw2;
                                i++;
                                j++;
                                //l-=3;
                        } else if( tempd3 > j ) {
                                //struct edge *newedges = realloc( edges, (l-3)*sizeof *newedges );
                                //edges = newedges;
                                edges[i].src = j;
                                edges[i].dest = tempd3;
                                edges[i].weight = tempw3;
                                i++;
                                j++;
                                //l-=3;
                        }else if( tempd4 > j ) {
                                //struct edge *newedges = realloc( edges, (l-3)*sizeof *newedges );
                                //edges = newedges;
                                edges[i].src = j;
                                edges[i].dest = tempd4;
                                edges[i].weight = tempw4;
                                i++;
                                j++;
                                //l-=3;
                        }
		} else if( sscanf( buf, "%d :%lf %d :%lf %d :%lf", &tempd1, &tempw1, &tempd2, &tempw2, &tempd3, &tempw3) == 6) {
			if( tempd1 > j && tempd2 > j ) {
				struct edge *newedges = realloc( edges, (l+1) *sizeof *newedges );
				edges = newedges;
				edges[i].src = j;
				edges[i+1].src = j;
				edges[i].dest = tempd1;
				edges[i].weight = tempw1;
				edges[i+1].dest = tempd2;
				edges[i+1].weight = tempw2;
				i+=2;
				j++;
				l++;
			} else if( tempd1 > j && tempd3 > j ) {
                                struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
				edges[i+1].src = j;
                                edges[i].dest = tempd1;
                                edges[i].weight = tempw1;
				edges[i+1].dest = tempd3;
				edges[i+1].weight = tempw3;
                                i+=2;
                                j++;
                                l++;
                        } else if( tempd2 > j && tempd3 > j ) {
                                struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
                                edges = newedges;
                                edges[i].src = j;
				edges[i+1].src = j;
                                edges[i].dest = tempd2;
                                edges[i].weight = tempw2;
				edges[i+1].dest = tempd3;
				edges[i+1].weight = tempw3;
                                i+=2;
                                j++;
                                l++;
                        } else if( tempd1 > j ) {
                                //struct edge *newedges = realloc( edges, (l-2)*sizeof *newedges );
                                //edges = newedges;
                                edges[i].src = j;
                                edges[i].dest = tempd1;
                                edges[i].weight = tempw1;
                                i++;
                                j++;
                                //l-=2;
                        } else if( tempd2 > j ) {
                                //struct edge *newedges = realloc( edges, (l-2)*sizeof *newedges );
                                //edges = newedges;
                                edges[i].src = j;
                                edges[i].dest = tempd2;
                                edges[i].weight = tempw2;
                                i++;
                                j++;
                                //l-=2;
                        } else if( tempd3 > j ) {
                                edges[i].src = j;
                                edges[i].dest = tempd3;
                                edges[i].weight = tempw3;
                                i++;
                                j++;
                        }	
		} else if( sscanf( buf, "%d :%lf %d :%lf", &tempd1, &tempw1, &tempd2, &tempw2 ) == 4 ) {
			//printf("2 polaczenia\n");
			if( tempd1 > j ) {
				if( tempd2 > j ) { 
					struct edge *newedges = realloc( edges, (l+1)*sizeof *newedges );
					edges = newedges;

					edges[i].src = j;
					edges[i+1].src = j;
					edges[i].dest = tempd1;
					edges[i].weight = tempw1;
					edges[i+1].dest = tempd2;
					edges[i+1].weight = tempw2;
					i+=2;
					j++;
					l++;
				} else {
					edges[i].src = j;
					edges[i].dest = tempd1;
					edges[i].weight = tempw1;
					i++;
					j++;
				}
			} else { 
				if( tempd2 > j ) {
					edges[i].src = j;
					edges[i].dest = tempd2;
					edges[i].weight = tempw2;
					i++;
					j++;
				} else {
					struct edge *newedges = realloc( edges, (l-1)*sizeof *newedges );
					edges=newedges;
					l--;
					continue;
				}
			}
		}
		else if( sscanf( buf, "%d :%lf", &tempd1, &tempw1 ) == 2 ) {
			//printf("1 polaczenie\n");
			if( tempd1 > j ) { 
				edges[i].src = j;
				edges[i].dest = tempd1;
				edges[i].weight = tempw1;
				i++;
				j++;
			} else { 
				struct edge *newedges = realloc( edges, (l-1)*sizeof *newedges );
                                edges=newedges;
				l--;
				continue;
			}
		}	
		else {
			//fprintf(stderr, "Niewłaściwy format pliku!\n");
			return NULL;
		}
	}	
		fclose(in);
	//printf("l to %d\n", l);	
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