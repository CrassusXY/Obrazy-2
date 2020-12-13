#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "funkcje.h"


int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
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
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }

//zwalnianie jesli juz jakas jest
//alokacja!

  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

/*Funkcja zapisujaca tabele do pliku PGM*/
int zapisz(FILE *plik_wy,int obraz_pgm[][MAX],int *wymx, int *wymy, int szarosci) {
  int i, j;

  if (plik_wy==NULL){
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku.\n");
    return(0);
  }

  fprintf(plik_wy,"P2\n"); /*Zapisuje migidzne "P2"*/

  fprintf(plik_wy,"%d %d %d ",*wymx,*wymy,szarosci); /*Zapisuje parametry obrazu*/

  for(i=0;i<*wymy;i++){
    for(j=0;j<*wymx;j++){
      fprintf(plik_wy,"%d ",obraz_pgm[i][j]); /*Wypisuje wartosci tabeli*/
      fprintf(plik_wy,"\n");
    }
  }

  return 0; /*Zapisz zakonczone sukcesem*/
}

/*Funkcja czysczaca*/
void czysc(){
  system("clear");
}

/*Funkcja wyswietlajaca plik tymczasowy*/
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

/*Funkcja tworzaca negatyw*/
int negatyw(int obraz_pgm[][MAX], int *wymx, int *wymy, int szarosci) {
  int i, j;

  for(i=0; i<*wymy; i++){
    for(j=0; j<*wymx; j++){
      obraz_pgm[i][j] = szarosci - obraz_pgm [i][j]; /*Zmieniam wartosci elementow tablicy na znajdujace sie po przecinwej stronie skali szarosci*/
    }
  }
  return 0;
}

/*Fukcja wykonujaca progowanie*/
int progowanie(int obraz_pgm[][MAX], int *wymx, int *wymy, int szarosci, int *wartosc) {
    int i, j;

      for (i=0; i<*wymy; i++){
        for (j=0; j<*wymx; j++){
          if(obraz_pgm[i][j]<=(szarosci**wartosc/100)){ /*Sprawdzam czy element tabeli jest mniejszy badz rowny od progu*/
            obraz_pgm[i][j]=0; /*Jesli tak, to przypisuje mu wartosc 0*/
          }
          else{
            obraz_pgm[i][j]=szarosci; /*Jesli nie, to przypisuje mu maksymalna wartosc szarosci*/
          }
        }
      }
    return 0;
  }

/*Funkjca tworzaca kontur obrazu*/
int konturowanie(int obraz_pgm[][MAX], int *wymx, int *wymy, int szarosci) {
  int i, j;

  for(i=0; i<*wymy; i++){
    for(j=0; j<*wymx; j++){
      if(i+1==*wymy){ /*Specjalny przypadek zapobiegajacy wczytaniu elementu nienalezacego do tablicy poza wymy*/
        obraz_pgm[i][j] = abs(obraz_pgm[i][j+1]-obraz_pgm[i][j]);
      }
      if(j+1==*wymx){ /*Specjalny przypadek zapobiegajacy wczytaniu elementu nienalezacego do tablicy poza wymx*/
        obraz_pgm[i][j] = abs(obraz_pgm[i+1][j]-obraz_pgm[i][j]);
      }
      else{ /*Pozostale przypadki*/
        obraz_pgm[i][j] = (abs(obraz_pgm[i+1][j]-obraz_pgm[i][j])+abs(obraz_pgm[i][j+1]-obraz_pgm[i][j]));
      }
    }
  }
  return 0;
}

/*Funkcja rozmywajaca obraz*/
int rozmycie(int obraz_pgm[][MAX], int tablica_pomocnicza[][MAX], int *wymx, int *wymy, int szarosci, int*promien) {
  int i,j;

  for(i=0; i<*wymy; i++){
    for(j=0; j<*wymx; j++){ 
      tablica_pomocnicza[i][j]=obraz_pgm[i][j]; /*Przypisuje do elementow tablicy pomocniczej wartosci odpowiadajacych elementow tablicy zawierajacej obraz*/
    }
  }

  if(*promien==1){ /*Przypadek, kiedy promien rozmycia wynosi 1*/
    for(i=0; i<*wymy; i++){
      for(j=0; j<*wymx; j++){
        if(j==0){ /*Przypadek poczatku wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j]+tablica_pomocnicza[i][j+1])/2;
        }
        if(j+1==*wymx){ /*Przypadek konca wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j-1]+tablica_pomocnicza[i][j])/2;
        }
        else{ /*Normalny przypadek. obliczam srednia z trzech sasiadujacych elementow tablicy pomocniczej i przypisuje ja do tablicy zawierajacej obraz*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j-1]+tablica_pomocnicza[i][j]+tablica_pomocnicza[i][j+1])/3;
        }
      }
    }
  }

  if(*promien==2){ /*Przypadek, kiedy promien rozmycia wynosi 2*/
    for(i=0; i<*wymy; i++){
      for(j=0; j<*wymx; j++){
        if(j==0){ /*Pierwszy przypadek poczatku wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j]+tablica_pomocnicza[i][j+1]+tablica_pomocnicza[i][j+2])/3;
        }
        if(j==1){ /*Drugi przypadek poczatku wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j-1]+tablica_pomocnicza[i][j]+tablica_pomocnicza[i][j+1]+tablica_pomocnicza[i][j+2])/4;
        }
        if(j+1==*wymx){ /*Pierwszy przypadek konca wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j-2]+tablica_pomocnicza[i][j-1]+tablica_pomocnicza[i][j])/3;
        }
        if(j+2==*wymx){ /*Drugi przypadek konca wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j-2]+tablica_pomocnicza[i][j-1]+tablica_pomocnicza[i][j]+tablica_pomocnicza[i][j+1])/4;
        }
        else{ /*Normalny przypadek. obliczam srednia z pieciu sasiadujacych elementow tablicy pomocniczej i przypisuje ja do tablicy zawierajacej obraz*/
          obraz_pgm[i][j]=(tablica_pomocnicza[i][j-2]+tablica_pomocnicza[i][j-1]+tablica_pomocnicza[i][j]+tablica_pomocnicza[i][j+1]+tablica_pomocnicza[i][j+2])/5;
        }
      }
    }
  }
  return 0;
}