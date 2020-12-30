#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "funkcje.h"
#include "struktura.h"


/*Funkcja tworzaca negatyw*/
int negatyw(struktura_obraz *obraz) {
  int i, j;

  for(i=0; i<(obraz->wymy); i++){
    for(j=0; j<(obraz->wymx); j++){
      obraz->obraz_pgm[i][j] = obraz->szarosci - obraz->obraz_pgm [i][j]; /*Zmieniam wartosci elementow tablicy na znajdujace sie po przecinwej stronie skali szarosci*/
    }
  }
  return 0;
}

/*Fukcja wykonujaca progowanie*/
int progowanie(struktura_obraz *obraz, int *wartosc) {
    int i, j;

      for (i=0; i<obraz->wymy; i++){
        for (j=0; j<obraz->wymx; j++){
          if(obraz->obraz_pgm[i][j]<=(obraz->szarosci**wartosc/100)){ /*Sprawdzam czy element tabeli jest mniejszy badz rowny od progu*/
            obraz->obraz_pgm[i][j]=0; /*Jesli tak, to przypisuje mu wartosc 0*/
          }
          else{
            obraz->obraz_pgm[i][j]=obraz->szarosci; /*Jesli nie, to przypisuje mu maksymalna wartosc szarosci*/
          }
        }
      }
    return 0;
  }

/*Funkjca tworzaca kontur obrazu*/
int konturowanie(struktura_obraz *obraz) {
  int i, j;

  for(i=0; i<obraz->wymy; i++){
    for(j=0; j<obraz->wymx; j++){
      if(i+1==obraz->wymy){ /*Specjalny przypadek zapobiegajacy wczytaniu elementu nienalezacego do tablicy poza wymy*/
        obraz->obraz_pgm[i][j] = abs(obraz->obraz_pgm[i][j+1]-obraz->obraz_pgm[i][j]);
      }
      if(j+1==obraz->wymx){ /*Specjalny przypadek zapobiegajacy wczytaniu elementu nienalezacego do tablicy poza wymx*/
        obraz->obraz_pgm[i][j] = abs(obraz->obraz_pgm[i+1][j]-obraz->obraz_pgm[i][j]);
      }
      else{ /*Pozostale przypadki*/
        obraz->obraz_pgm[i][j] = (abs(obraz->obraz_pgm[i+1][j]-obraz->obraz_pgm[i][j])+abs(obraz->obraz_pgm[i][j+1]-obraz->obraz_pgm[i][j]));
      }
    }
  }
  return 0;
}

/*Funkcja rozmywajaca obraz*/
int rozmycie(struktura_obraz *obraz) {
  int i,j;
  struktura_obraz obraz_pomocniczy;

  for(i=0; i<obraz->wymy; i++){
    for(j=0; j<obraz->wymx; j++){ 
      obraz_pomocniczy.obraz_pgm[i][j]=obraz->obraz_pgm[i][j]; /*Przypisuje do elementow tablicy pomocniczej wartosci odpowiadajacych elementow tablicy zawierajacej obraz*/
    }
  }

  for(i=0; i<obraz->wymy; i++){
    for(j=0; j<obraz->wymx; j++){
      if(j==0){ /*Przypadek poczatku wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
        obraz->obraz_pgm[i][j]=(obraz_pomocniczy.obraz_pgm[i][j]+obraz_pomocniczy.obraz_pgm[i][j+1])/2;
      }
      if(j+1==obraz->wymx){ /*Przypadek konca wiersza, zapobiegajacy pobraniu nieistniejacych wartosci*/
        obraz->obraz_pgm[i][j]=(obraz_pomocniczy.obraz_pgm[i][j-1]+obraz_pomocniczy.obraz_pgm[i][j])/2;
      }
      else{ /*Normalny przypadek. obliczam srednia z trzech sasiadujacych elementow tablicy pomocniczej i przypisuje ja do tablicy zawierajacej obraz*/
        obraz->obraz_pgm[i][j]=(obraz_pomocniczy.obraz_pgm[i][j-1]+obraz_pomocniczy.obraz_pgm[i][j]+obraz_pomocniczy.obraz_pgm[i][j+1])/3;
      }
    }
  }
  return 0;
}