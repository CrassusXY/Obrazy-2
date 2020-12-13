#ifndef funkcje_h
#define funckje_h

#define MAX 999           /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

typedef struct{
int wym_x, wym_y, odcieni;
int obraz[MAX][MAX];
} t_obraz;

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci);

int zapisz(FILE *plik_wy,int obraz_pgm[][MAX],int *wymx, int *wymy, int szarosci);

void czysc();

void wyswietl(char *n_pliku);

int negatyw(int obraz_pgm[][MAX], int *wymx, int *wymy, int szarosci);

int progowanie(int obraz_pgm[][MAX], int *wymx, int *wymy, int szarosci, int *wartosc);

int konturowanie(int obraz_pgm[][MAX], int *wymx, int *wymy, int szarosci);

int rozmycie(int obraz_pgm[][MAX], int tablica_pomocnicza[][MAX], int *wymx, int *wymy, int szarosci, int*promien);

#endif