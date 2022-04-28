//Wojciech Majchrzak, Dawid Stereńczak

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "../utilities/memwatch.h"

#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#include "bfs.h"
#include "djikstra.h"
#include "generator.h"
#include "czytacz.h"

int debug_flag = DEBUG; // więcej informacji do debugowania

char *instrukcja = " Instrukcja programu %s służącego do rysowania grafów: \n" // instrukcja programu
" Możliwe argumenty wywołania programu to:\n"
"Argumenty ogólne:\n"
" -m <tryb> - wybór działania programu: \"generate\" - generowanie grafu, \"check\" - sprawdzenie spójności, \"path\" - obliczanie ścieżki \n"
" -f <nazwa_pliku> - plik do zapisu/odczytu grafu\n"
" -h wyświetlenie pomocy\n"
"Argumenty dla trybu \"generate\":\n"
" -s <szerokość x wysokość> - wymiary grafu\n"
" -n <ilość_podziałów> - ile razy graf ma zostać podzielony\n"
" -r <przedział> - przedział wag krawędzi generowanego grafu <początek-koniec>\n"
"Argumenty dla trybu \"path\":\n"
" -a <punkt> - pierwszy punkt do liczenia odległości format - <x;y>\n"
" -b <punkt> - drugi punkt do liczenia odległości <x;y\n";

int main ( int argc, char **argv)
{
    //zmienne
    int opt; // do getopta
    char *filename = NULL, *dim_tmp = NULL;
    char *point1_tmp = NULL, *point2_tmp = NULL, *range_tmp = NULL;; // do wczytywania argumetów getoptem
    char tmp[20], tmp2[10], tmp3[18], tmp4[9], tmp5[14], tmp6[14], tmp7[14]; // stringi do przekształcenia wczytywanych argumentów
    char *p = NULL; // jak wyżej
    int x_dim = 100, y_dim = 100;//domyślne wymiary grafu
    int amount = 0; // domyślna ilość podzialeń grafu
    int x1=0,  y1=0; // współrzędne pierwszego punktu do liczenia odległości
    int x2=0, y2=0;  // współrzędne drugiego punktu do liczenia odległości
    double range_begin = 0, range_end = 10; // zakres wag krawędzi grafu
    int mode = 0; // tryb programu: 0 - generate, 1 - check, 2 - path

    // wczytywanie argumentów getoptem
    while ((opt = getopt (argc, argv, "gcpf:s:n:r:a:b:h")) != -1) 
    {
        switch (opt) 
        {
        case 'g':
            mode = 0;
            break;
        case 'c':
            mode = 1;
            break;
        case 'p':
            mode = 2;
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
    if ( filename == NULL) // sprawdzenie czy wpisano nazwę pliku do zapisu/odczytu
    {
        filename = "data/graf.txt";
    } 

    if ( dim_tmp != NULL) // określenie z argumentów wymiarów generowanego grafu
    {
        p = strchr( dim_tmp, 120);
        int spacer = p - dim_tmp;
        strncpy( tmp,dim_tmp, spacer);
        x_dim = atoi(tmp);
        strncpy( tmp2, dim_tmp+spacer+1, strlen(dim_tmp) - spacer);
        y_dim = atoi(tmp2);
        if( x_dim * y_dim > 100000000 )
        {
            fprintf( stderr, "%s: Podano zbyt duże wymiary grafu. \n", argv[0]);
            return 1;
        }
    }
    
    if ( range_tmp != NULL) // określenie zakresu wag krawędzi w generowanym grafie
    {
        p = strchr( range_tmp, 45);
        int spacer = p - range_tmp;
        strncpy( tmp3, range_tmp, spacer);
        range_begin = atof(tmp3);
        strncpy( tmp4, range_tmp+spacer+1, strlen(range_tmp) - spacer);
        range_end = atof(tmp4);
        if( range_begin > range_end ) // tutaj zmiana - wagi od 0 do 100 inaczej mogą nie działać przy dużych grafach( przepełnienie intów)
        {
            fprintf( stderr, "%s: Źle wpisano zakres wag krawędzi grafu. \n", argv[0]);
            return 5;
        }
        if( range_begin > 100 )
        {
            fprintf( stderr, "%s: Zakres wag krawędzi wychodzi poza dopuszczony limit. \n", argv[0]);
            return 5;
        }
        if( range_end > 100 )
        {
            fprintf( stderr, "%s: Zakres wag krawędzi wychodzi poza dopuszczony limit. \n", argv[0]);
            return 5;
        }
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

    //dodatkowe informacje o wczytanych argumentach w programie
    if (debug_flag == 1)
    {
        printf("Informacje dodatkowe: \n");
        printf("Tryb: %i \n", mode);
        printf("Wczytany zakres: %i x %i.\n", x_dim, y_dim);
        printf("Plik do czytania/zapisu: %s \n", filename);
        printf("Zakres generowania: %lf ; %lf \n", range_begin, range_end);
        printf("Wybrane punkty: (%i,%i) oraz (%i,%i) \n", x1, y1, x2, y2);
    }

    //wybór trybu pracy programu    
    if ( mode == 0)
    {
        create_graph( x_dim, y_dim, filename, range_begin, range_end, amount);
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