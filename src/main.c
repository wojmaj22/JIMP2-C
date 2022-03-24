#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "bfs.h"
#include "djikstra.h"
#include "generator.h"

char *instrukcja = "Instrukcja programu %s służącego do rysowania grafów: \n" // do aktualizacji
"Możliwe argumenty wywołania programu to:\n"
" -x <liczba całkowita> - wymiar pionowy grafu\n"
" -y <liczba całkowita> - wymiar poziomy grafu\n"
"[-n <liczba całkowita> - podział grafu na ilość podgrafów\n";

void check_graph( char *plik)
{
    printf("Sprawdzanie spójności grafu z pliku %s.\n", plik);
}
void calculate_path( char *plik, int x1, int x2, int y1, int y2)
{
    printf("Obliczanie długości ścieżki pomiędzy węzłami: (%i,%i) oraz (%i,%i) w pliku %s.\n", x1, y1, x2, y2, plik);
}

int main ( int argc, char **argv)
{
    //zmienne
    int opt; // do getopta
    char *mode_tmp = NULL, *filename = NULL, *dim_tmp = NULL;
    char *point1_tmp = NULL, *point2_tmp = NULL, *range_tmp = NULL;; // do wczytywania argumetów getoptem
    char tmp[14], tmp2[7], tmp3[18], tmp4[9], tmp5[14], tmp6[14], tmp7[14], tmp8[14]; // stringi do przeksztąłcenia wczytywanych argumentów
    char *p = NULL; // jak wyżej
    int x_dim = 100, y_dim = 100;//domyślne wymiary grafu
    int amount = 1; // domyślny podział grafu
    int x1=0,  y1=0; // współrzędne pierwszego punktu do liczenia odległości
    int x2=0, y2=0;  // współrzędne drugiego punktu do liczenia odległości
    double range_begin = 0, range_end = 10; // zakres wag krawędzi grafu
    int mode = 0; // tryb programu: 0 - generate, 1 - check, 2 - path

    // wczytywanie argumentów getoptem
    while ((opt = getopt (argc, argv, "m:f:s:n:r:a:b:h")) != -1) 
    {
        switch (opt) 
        {
        case 'm':
            mode_tmp = optarg;
            break;
        case 'f':
            filename = optarg;
            break;
        case 's':
            dim_tmp = optarg;;
          break;
        case 'n':
            amount = atoi (optarg);
            break;
        case 'r':
            range_tmp = optarg;
            break;
        case 'a':
            point1_tmp = optarg;
            break;
        case 'b':
            point2_tmp = optarg;
            break;
        case 'h':
            printf ( instrukcja, argv[0]);
            return 0;
        default:                   
            fprintf ( stderr, instrukcja, argv[0]);
            exit (EXIT_FAILURE);
        }   
    }

    // obróbka wczytanych argumetów i sprawdzenie ich
    if ( mode_tmp == NULL)
    {
        mode = 0;
    }
    else if ( strcmp( mode_tmp, "generate") == 0)
    {
        mode = 0;
    }
    else if( strcmp( mode_tmp, "check") == 0)
    {
        mode = 1;
    }
    else if( strcmp( mode_tmp, "path") == 0)
    {
        mode = 2;
    }
    else
    {
        fprintf( stderr, "%s: Błędny tryb programu.\n", argv[0]);
    }

    if ( filename == NULL) // sprawdzenie czy wpisano nazwę pliku do zapisu/odczytu
    {
        filename = "graf.txt";
    } 

    if ( dim_tmp != NULL) // określenie z argumentów wymiarów generowanego grafu
    {
        p = strchr( dim_tmp, 120);
        int spacer = p - dim_tmp;
        strncpy( tmp,dim_tmp, spacer);
        x_dim = atoi(tmp);
        strncpy( tmp2, dim_tmp+spacer+1, sizeof(dim_tmp) - spacer);
        y_dim = atoi(tmp2);

    }
    
    if ( range_tmp != NULL) // określenie zakresu wag krawędzi w generowanym grafie - to nie działa dla liczb niecałkowitych
    {
        p = strchr( range_tmp, 45);
        int spacer = p - range_tmp;
        strncpy( tmp3, range_tmp, spacer);
        range_begin = atof(tmp3);
        strncpy( tmp4, range_tmp+spacer+1, strlen(range_tmp) - spacer);
        range_end = atof(tmp4);
    }

    if ( point1_tmp != NULL) // pierwszy punkt do pomiaru odległości
    {
        p = strchr( point1_tmp, 44);
        int spacer = p - point1_tmp;
        strncpy( tmp5, point1_tmp, spacer);
        x1 = atof(tmp5);
        strncpy( tmp6, point1_tmp+spacer+1, sizeof(point1_tmp) - spacer);
        y1 = atof(tmp6);
    }

    if ( point2_tmp != NULL) // drugi punkt do pomiaru odległośći
    {
        p = strchr( point2_tmp, 44);
        int spacer = p - point2_tmp;
        strncpy( tmp7, point2_tmp, spacer);
        x2 = atof(tmp7);
        strncpy( tmp7, point2_tmp+spacer+1, sizeof(point2_tmp) - spacer);
        y2 = atof(tmp7);
    }

    if ( mode == 0)
    {
        create_graph( x_dim, y_dim, filename, range_begin, range_end);
    }
    else if( mode  == 1)
    {
        check_graph( filename);
    }
    else if( mode == 2)
    {
        calculate_path( filename, x1, x2, y1, y2);
    }

return 0;
}