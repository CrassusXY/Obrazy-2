#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "funkcje.h"



int main() {
  int obraz[MAX][MAX]; /*Tablica do ktorej zostanie wczytany obraz*/
  int wymx,wymy,odcieni; /*Paremetry obrazu. Jego wymiary i skala szarosci*/
  int odczytano = 0; /*int pomagajacy w sprawdzeniu, czy wczytano poprawnie obraz do tablicy*/
  FILE *plik;
  char nazwa[100]; /*char pomagajacy przy operacji zapisywania i wczytywania*/
  int opcja; /*int uzywany przy wyborze opcji w menu*/
  int poziom; /*int z poziomem w operacji progowania*/
  int promien; /*int z promieniem w operacji rozmycia*/
  int tablica[MAX][MAX]; /*Tablica pomocnicza przy operacji rozmywania*/

  while (opcja!=8) /*Menu*/
  {
  printf("    Menu:\n");
  printf("1 - Wczytaj\n");
  printf("2 - Zapisz\n");
  printf("3 - Wyswietl\n");
  printf("4 - Negatyw\n");
  printf("5 - Progowanie\n"); 
  printf("6 - Konturowanie\n");
  printf("7 - Rozmycie\n");  
  printf("8 - Zakoncz\n");
  printf("\nTwój wybór:");
  scanf("%d", &opcja);
  printf("\n");

  switch (opcja)
    {
    case 1: /*Opcja wywolujaca wczytania pliku*/
      printf("Podaj nazwe pliku:\n");
      scanf("%s",nazwa); /*Pobieram nazwe pliku do wczytania*/
      plik=fopen(nazwa,"r"); /*Otwieram ten plik w trybie do czytania*/
      if (plik != NULL) { /*Sprawdzam, czy plik jest prawidlowy*/
        odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni); /*Wywoluje funkcje czytaj oraz przypisuje jej wynik, do odczytano*/
        fclose(plik); /*Zamykam plik*/
        czysc(); /*Czyszczenie*/
        printf("Plik odczytany poprawnie\n\n");
      }
      else{ /*Sytuacja, gdy plik nie jest poprawny*/
        czysc(); 
        printf("Plik nie odczytany poprawnie\n\n");
      }
      break;

    case 2:
      if(odczytano != 0){ /*Sprawdzam, czy jest wczytany plik*/
        printf("Podaj pod jaka nazwa mam zapisac plik:\n"); /*Sytacja, gdy plik jest wczytany*/
        scanf("%s",nazwa); /*Wczytuje nazwe pod jaka zapisac plik*/
        plik=fopen(nazwa,"w"); /*Otwieram plik do trybie zapisu*/
        zapisz(plik,obraz,&wymx,&wymy,odcieni); /*Wywoluje funkcje zapisz*/
        fclose(plik); /*Zamykam plik*/
        czysc();
        printf("Zapisano\n\n");
      }
      else
      {
        czysc(); /*Sytacja, gdy plik nie jest wczytany*/
        printf("Brak pliku do zapisania\n\n");
      }  
      break;

    case 3:
      if (odczytano != 0){ /*Sprawdzam, czy jest wczytany plik*/
        plik=fopen("tmp.pgm","w"); /*Otwieram plik tymczasowy do zapisu*/
        zapisz(plik,obraz,&wymx,&wymy,odcieni); /*Zapisuje go*/
        fclose(plik); /*zamykam go*/
        wyswietl("tmp.pgm"); /*Wywoluje funcje zapisz*/
        czysc();
        printf("Obraz wyswietlony poprawnie\n\n");
      }
      else{ /*Sytuacja, gdy plik nie jest wczytany*/
        czysc();
        printf("Brak pliku do wyswietlenia\n\n");
      }
      break;

    case 4:
      if (odczytano != 0){ /*Sprawdzam, czy jest wczytany plik*/
        negatyw(obraz,&wymx,&wymy,odcieni);
        czysc();
        printf("Negatyw wykonany poprawnie\n\n");
      }
      else{ /*Sytuacja, gdy plik nie jest wczytany*/
        czysc();
        printf("Brak pliku do operacji negatywu\n\n");
      }
      break;

    case 5:
      if(odczytano != 0){ /*Sprawdzam, czy jest wczytany plik*/
        printf("Podaj poziom progowania: ");
        scanf("%d",&poziom); /*Wczytuje poziom od jakiego ma byc progowanie*/
        if(poziom>=0||poziom<=100){ /*Sprawdzam, czy poziom progowania jest poprawny*/
        progowanie(obraz,&wymx,&wymy,odcieni,&poziom); /*Wywoluje operacje progowania*/
        czysc();
        printf("Progowanie wykonane poprawnie\n\n");
        }
        else{ /*Sytuacja, gdy uzytkownik podal niewlasciwy poziom progowania*/
          czysc();
          printf("Bledny poziom progowania.\n\n");
        }
      }
      else{ /*Sytuacja, gdy plik nie jest wczytany*/
        czysc();
        printf("Brak pliku do progowania\n\n");
      }
      break;

    case 6:
      if (odczytano != 0){ /*Sprawdzam, czy jest wczytany plik*/
        konturowanie(obraz,&wymx,&wymy,odcieni); /*Wywoluje operacje konturowania*/
        czysc();
        printf("Konturowanie wykonane poprawnie\n\n");
      }
      else{ /*Sytuacja, gdy plik nie jest wczytany*/
        czysc();
        printf("Brak pliku do konturowania\n\n");
      }
      break;

    case 7:
      if (odczytano != 0){ /*Sprawdzam, czy jest wczytany plik*/
        printf("Podaj promien rozmycia(1 lub 2): ");
        scanf("%d",&promien); /*Wczytuje promien rozmycia*/
        if(promien == 1 || promien == 2){ /*Sprawdzam promien rozmycia*/
          rozmycie(obraz,tablica,&wymx,&wymy,odcieni,&promien); /*Wywoluje operacje rozmycia*/
          czysc();
          printf("Konturowanie wykonane poprawnie\n\n");
        }
        else{ /*Sytaucja. gdy uzytkownik podal bledny promien*/
          czysc();
          printf("Bledny promien\n\n");
        }
      }
      else{ /*Sytuacja, gdy plik nie jest wczytany*/
        czysc();
        printf("Brak pliku do rozmycia\n\n");
      }
      break;

    case 8: /*Opcja konczaca dzialanie programu*/
      czysc();
      printf ("Program zakonczyl dzialanie\n\n");
      break;
    
    default: /*Ostrzezenie o wybraniu opcji spoza zdefiniowanej w menu*/
      czysc(); 
      printf("Nie ma takiej pozycji w menu\n\n");
      break;
    }
  }
}
