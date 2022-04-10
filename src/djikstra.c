#include "djikstra.h"
#include "czytacz.h"

int size = 0;

void swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

// Function to heapify the tree
void heapify(int array[], int size, int i) {
  if (size == 1) {
    printf("Single element in the heap");
  } else {
    // Find the largest among root, left child and right child
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < size && array[l] > array[largest])
      largest = l;
    if (r < size && array[r] > array[largest])
      largest = r;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&array[i], &array[largest]);
      heapify(array, size, largest);
    }
  }
}

// Function to insert an element into the tree
void insert(int array[], int newNum) {
  if (size == 0) {
    array[0] = newNum;
    size += 1;
  } else {
    array[size] = newNum;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(array, size, i);
    }
  }
}

// Function to delete an element from the tree
void deleteRoot(int array[], int num) {
  int i;
  for (i = 0; i < size; i++) {
    if (num == array[i])
      break;
  }

  swap(&array[i], &array[size - 1]);
  size -= 1;
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(array, size, i);
  }
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
    
    int wiersze = getwiersze(), kolumny = getkolumny();
    
    struct edge *edges = readfromfile(in);

    int l = getl();
    int wxk = getwxk();
    struct Graph *graph = createGraph( edges, wxk, l);

    int p1 =  x1 + wiersze * y1; //pierwszy punkt bez współrzędnych
    int p2 =  x2 + wiersze * y2; //drugi punkt bez współrzędnych

    double *droga = malloc( wxk * sizeof(double));
    int *priority_queue = malloc( wxk * sizeof(int));
    short int *odwiedzone = malloc( wxk * sizeof(double));
    for( int i = 0; i < wxk; i++)
    {
        droga[i] = __INT_MAX__;
        odwiedzone[i] = 0;
        insert(priority_queue, i);
    }
    droga[p1] = 0;
    
    while(size != 0)
    {
        int u = priority_queue[size-1];
        struct node *tmp = graph->head[u];
        while( tmp->next != NULL)
        {
            if( droga[tmp->dest] > droga[u] + tmp->weight)
            {
                droga[tmp->dest] = droga[u] + tmp->weight;
            }
            tmp = tmp->next;
        }
        deleteRoot( priority_queue, priority_queue[size-1]);
    }

    printf("Droga do (%i;%i wynosi %lf. \n", x2, y2, droga[p2]);
    
    free(droga);
}