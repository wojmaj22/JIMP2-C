#ifndef _CZYTACZ_H_
#define _CZYTACZ_H_

#include "../utilities/memwatch.h"

struct node {
	int dest;
        double	weight;
	struct node* next;
};

struct edge {
	int src, dest;
      	double	weight;
};

struct Graph
{
        struct node** head;
};

struct Graph* createGraph( struct edge edges[], int wxk, int l );

void printGraph( struct Graph* graph, int wxk );

struct edge *readfromfile( FILE *in );

int getwxk();
int getl();

#endif
