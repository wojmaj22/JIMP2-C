#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "generator.h"

void cut_graph(int x, int y,double **edges_tab_x, double **edges_tab_y, int debug_flag)
{
		int w1, w2;
 		int true = 0;
		while (true == 0) // losowanie pierwszego wierzchołka
		{
			w1 = rand() / (double)RAND_MAX * x * y;
			if (w1 < x || w1 >= (x * y - x) || w1 % x == 0 || w1 % x == x - 1)
				true = 1;
		}
		if( debug_flag == 1) 
			printf("Wybrany wierzchołek to: %i \n", w1);
		true = 0;
		if (w1 % x == 0) // losowanie drugiego wierzchołka na przeciwnym boku
		{
			while (true == 0)
			{
				w2 = rand() / (double)RAND_MAX * x * y;
				if (w2 % x == x - 1)
					true = 1;
			}
		} else if (w1 % x == x - 1)
		{
			while (true == 0)
			{
				w2 = rand() / (double)RAND_MAX * x * y;
				if (w2 % x == 0)
					true = 1;
			}
		} else if (w1 < x)
		{
			while (true == 0)
			{
				w2 = rand() / (double)RAND_MAX * x * y;
				if (w2 >= (x * y - x))
					true = 1;
			}
		} else if (w1 >= (x * y - x))
		{
			while (true == 0)
			{
				w2 = rand() / (double)RAND_MAX * x * y;
				if (w2 < x)
					true = 1;
			}
		}
		if( debug_flag == 1)
			printf("Wybrany wierzchołek to: %i \n", w2);

		int vertex = w1; // usuwanie krawędzi na drodze między wylosowanymi wierzchołkami
		int tmp = 0; // ruch w pionie lub poziomie
		edges_tab_x[vertex / x][vertex % x] = -1;
		edges_tab_y[vertex / x][vertex % x] = -1;
		do
		{
			edges_tab_x[vertex / x][vertex % x] = -1;
			edges_tab_y[vertex / x][vertex % x] = -1;
			if (tmp % 2 == 0)
			{
				if (vertex % x > w2 % x)
				{
					vertex--;
				}
				else if (vertex % x < w2 % x)
				{
					vertex++;
				}
			}
			else if (tmp % 2 == 1)
			{
				if ((vertex / x) > (w2 / x))
				{
					vertex = vertex - x;
				}
				else if ((vertex / x) < (w2 / x))
				{
					vertex = vertex + x;
				}
			}
			tmp++;
		} while (vertex != w2);
		edges_tab_x[vertex / x][vertex % x] = -1;
		edges_tab_y[vertex / x][vertex % x] = -1;
}

void create_graph(int x, int y, char *plik, double range_begin, double range_end, int amount, int debug_flag)
{
	printf("Tworzenie grafu o wymiarach %ix%i, dzielonego %i-razy, z wagami krawędzi w zakresie <%.2lf;%.2lf> i zapis do pliku %s.\n", x, y, amount, range_begin, range_end, plik);

	srand(time(NULL));

	int counter = 0;  // licznik wierzchołków
	int counter2 = 0; // drugi licznik

	int wiersze_x = y, wiersze_y = y;
	int kolumny_x = x, kolumny_y = x;

	double **edges_tab_x = malloc ( wiersze_x * sizeof(double*));
	double **edges_tab_y = malloc ( wiersze_y * sizeof(double*));

	for( int i = 0; i < wiersze_x; i++)
	{
		edges_tab_x[i] = malloc( kolumny_x * sizeof(double));
	}
	for( int i = 0; i < wiersze_y; i++)
	{
		edges_tab_y[i] = malloc( kolumny_y * sizeof(double));
	}

	for (int i = 0; i < wiersze_x; i++) // generowanie krawędzi poziomych
	{
		for (int j = 0; j < kolumny_x; j++)
		{
			edges_tab_x[i][j] = range_begin + ((rand() / (double)RAND_MAX) * (range_end - range_begin));
		}
	}

	for (int i = 0; i < wiersze_y; i++) // generowanie krawędzi pionowych
	{
		for (int j = 0; j < kolumny_y; j++)
		{
			edges_tab_y[i][j] = range_begin + ((rand() / (double)RAND_MAX) * (range_end - range_begin));
		}
	}

	FILE *out = fopen(plik, "w"); // plik do zapisu danych

	if (out == NULL) // test czy plik jest ok
	{
		fprintf(stderr, "Nie znalazłem lub nie moge otworzyć pliku do odczytu.\n");
		exit(1);
	}

	for (int i = 0; i < amount; i++) // cięcie grafu określoną ilość razy
	{
		cut_graph( x, y, edges_tab_x, edges_tab_y, debug_flag);
	}

	if (debug_flag == 1) // Drukowanie do zobaczenia podziału grafu na stdout - funkcja do debugownaia głównie
	{
		int tmp2 = 0;
		for (int i = 0; i < 2*y-1; i++)
		{
			if (tmp2 % 2 == 0)
			{
				for (int j = 0; j < x; j++)
				{
					printf("*");
					if (j != x - 1 && edges_tab_x[ i/2][ j] != -1)
						printf("--");
					else
						printf("  ");
				}
				printf("\n");
			}
			else if (tmp2 % 2 == 1)
			{
				for (int j = 0; j < x; j++)
				{
					if (edges_tab_y[ i/2][ j] != -1)
						printf("|  ");
					else
						printf("   ");
				}
				printf("\n");
			}
			tmp2++;
		}
	}

	fprintf(out, "%i %i\n", x, y);
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (j != y - 1)
				if (edges_tab_x[counter / x][counter2] != -1)
					fprintf(out, "%i :%lf  ", counter + 1, edges_tab_x[counter / x][counter2]); // połączenie w prawo
			if (i != x - 1)
				if (edges_tab_y[counter / x][counter2] != -1)
					fprintf(out, "%i :%lf", counter + x, edges_tab_y[counter / x][counter2]); // połączenie w dół
			counter++;
			fprintf(out, "\n");
		}
		counter2++;
	}
	for ( int i = 0; i < y; i++)
	{
		free(edges_tab_x[i]);
	}
	for ( int i = 0; i < y; i++)
	{
		free(edges_tab_y[i]);
	}
	fclose(out);
	free(edges_tab_x);
	free(edges_tab_y);
}