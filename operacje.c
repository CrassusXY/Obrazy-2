#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "operacje.h"
#include "struktura.h"

/*Wczytaj*/
int czytaj(FILE *plik_we, struktura_obraz *obraz) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d", &obraz->wymx, &obraz->wymy, &obraz->szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }

//zwalnianie jesli juz jakas jest
//alokacja!

  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz->obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return obraz->wymx*obraz->wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

/*Zapisz*/
int zapisz(FILE *plik_wy, struktura_obraz *obraz) {
  int i, j;

  if (plik_wy==NULL){
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku.\n");
    return(0);
  }

  fprintf(plik_wy,"P2\n"); /*Zapisuje migidzne "P2"*/

  fprintf(plik_wy,"%d %d %d ",obraz->wymx,obraz->wymy,obraz->szarosci); /*Zapisuje parametry obrazu*/

  for(i=0;i<obraz->wymy;i++){
    for(j=0;j<obraz->wymx;j++){
      fprintf(plik_wy,"%d ",obraz->obraz_pgm[i][j]); /*Wypisuje wartosci tabeli*/
      fprintf(plik_wy,"\n");
    }
  }

  return 0; /*Zapisz zakonczone sukcesem*/
}

void czysc(){
  system("clear");
}

/*Wyswietl*/
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}