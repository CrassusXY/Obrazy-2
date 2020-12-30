#ifndef struktura_h
#define struktura_h

#define MAX 999           /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

typedef struct{
int wymx, wymy, szarosci;
int obraz_pgm[MAX][MAX];
} struktura_obraz;

#endif