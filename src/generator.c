#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generator.h"

extern int debug_flag;

void cut_graph(int x, int y,short int **tab_x, short int **tab_y)
{
		int tmp2;
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
		tab_x[vertex / x][vertex % x] = -1;
		tab_y[vertex / x][vertex % x] = -1;
		do
		{
			tab_x[vertex / x][vertex % x] = -1;
		    tab_y[vertex / x][vertex % x] = -1;
			if (tmp % 3 == 0)
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
			else if (tmp % 3 == 1)
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
			if(tmp % 3 == 2)
			{
				tmp2 = rand() % 4;
				if( tmp2 == 0)
				{
					vertex++;
				}
				else if( tmp2 == 1)
				{
					vertex+=x;
				}
				else if( tmp2 == 2)
				{
					vertex--;
				}
				else
				{
					vertex-=x;
				}
			}
			tab_x[vertex / x][vertex % x] = -1;
			tab_y[vertex / x][vertex % x] = -1;
			tmp++;
		} while (vertex != w2);
		tab_x[vertex / x][vertex % x] = -1;
		tab_y[vertex / x][vertex % x] = -1;
}

void create_graph(int x, int y, char *plik, double range_begin, double range_end, int amount)
{

    printf("Tworzenie grafu o wymiarach %ix%i, dzielonego %i-razy, z wagami krawędzi w zakresie <%.2lf;%.2lf> i zapis do pliku %s.\n", x, y, amount, range_begin, range_end, plik);
    FILE *out = fopen( plik, "w");
	if ( out == NULL)
	{
		fprintf(stderr, "Błąd, nie moge odczytać pliku lub nazwa pliku jest błędna.\n");
        exit(2);
    }
    srand(time(NULL));
    int counter = 0;
   
    if(amount == 0) // wypisywanie bez dzielenia
    {
        fprintf( out, "%i %i\n", x, y);
        while ( counter < x*y)
        {
            if( counter % x != x-1)
                fprintf( out, "%i :%lf  ", counter + 1, range_begin + ((rand() / (double)RAND_MAX) * (range_end - range_begin)));
            if( counter < (x*y - x))
                fprintf( out, "%i :%lf  ", counter + x, range_begin + ((rand() / (double)RAND_MAX) * (range_end - range_begin)));
            fprintf(out, "\n");
            counter++;
        }

        fclose(out);
        exit(0);
    }

	//wypisywanie z dzieleniem grafu
    int wiersze_x = y, wiersze_y = y;
	int kolumny_x = x, kolumny_y = x;

    short int **tab_x = malloc ( wiersze_x * sizeof(short int*));
	for( int i = 0; i < wiersze_x; i++)
	{
		tab_x[i] = malloc( kolumny_x * sizeof(short int));
        for( int j = 0; j < kolumny_x; j++)
        {
            tab_x[i][j] = 0;
        }
	}

    short int **tab_y = malloc ( wiersze_y * sizeof(short int*));
	for( int i = 0; i < wiersze_y; i++)
	{
		tab_y[i] = malloc( kolumny_y * sizeof(short int));
        for( int j = 0; j < kolumny_y; j++)
        {
            tab_y[i][j] = 0;
        }
	}

    for(int i = 0; i < amount; i++)
    {
        cut_graph( x, y, tab_x, tab_y);
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
					if (j != x - 1 && tab_x[ i/2][ j] != -1)
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
					if (tab_y[ i/2][ j] != -1)
						printf("|  ");
					else
						printf("   ");
				}
				printf("\n");
			}
			tmp2++;
		}
	}

    fprintf( out, "%i %i\n", x, y); // wypisywanie podzielonego grafu
        while ( counter < x*y)
        {
            if( counter % x != x-1)
                if(tab_x[counter/x][counter%x] != -1)
                    fprintf( out, "%i :%lf  ", counter + 1, range_begin + ((rand() / (double)RAND_MAX) * (range_end - range_begin)));
            if( counter < (x*y - x))
                if(tab_y[counter/x][counter%x] != -1)
                    fprintf( out, "%i :%lf  ", counter + x, range_begin + ((rand() / (double)RAND_MAX) * (range_end - range_begin)));
            fprintf(out, "\n");
            counter++;
        }
    for ( int i = 0; i < wiersze_x; i++) // zwalnianie pamięci itd
	{
		free(tab_x[i]);
	}
	for ( int i = 0; i < kolumny_y; i++)
	{
		free(tab_y[i]);
	}
    free(tab_x);
    free(tab_y);
    fclose(out);
}