#include "struktura.h"

#ifndef operacje_h
#define operacje_h

int czytaj(FILE *plik_we, struktura_obraz *obraz);

int zapisz(FILE *plik_wy, struktura_obraz *obraz);

void czysc();

void wyswietl(char *n_pliku);

#endif