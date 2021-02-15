/*Uwaga,
dla widnows trzeba zamienic komendy system("clear")
na system("cls"), aby to uczynic wystarczy w miejscach wskazanych
przez bledy w kompilatorze zakomentowac za pomoca "//" system("clear")
i odkomentowac system("cls"). Maciej Kawka*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//architektora koszyka
typedef struct koszyk {
  char *nazwa_artykulu;
  float cena_jednostkowa;
  int liczba_artykulow;

  struct koszyk *popr;
  struct koszyk *nast;
}koszyk;

koszyk *poczatek = NULL;
koszyk *koniec = NULL;

void pokarz_koszyk() {
  koszyk *i; float suma = 0;
  for (i = poczatek; i != NULL; i=i->nast){
    printf("%s, ", i->nazwa_artykulu);
    printf("cena: %.2f, ", i->cena_jednostkowa);
    printf("ilosc %d\n", i->liczba_artykulow);
    suma = suma + (i->cena_jednostkowa*i->liczba_artykulow);
  }
  printf("Nalerznosc: %.2f\n", suma);
}

int stworzKoszyk() {
  //tworzenie zmiennych pomocniczych
  koszyk *nowyArtykol;
  char bufor[30];
  char *nazwa;
  float cena;
  int liczba;
  liczba = 0;

  nazwa = (char*)malloc(sizeof(char)*(strlen(bufor)));//przydzielanie odpowiedniej ilosci pamieci

  //pobieranie pierwszego art od klienta
  system("clear");
  //system("cls") //dla windows
  printf("Wpisz nazwe art: ");
  scanf("%s", bufor);
  strcpy(nazwa, bufor);
  printf("Podaj cene %s: ", bufor);
  scanf("%f", &cena);
  printf("Podaj ile chesz dodac: ");
  scanf("%d", &liczba);

  //przydzielenie pamieci na pierwszy ele koszyku oraz wyzerowanie
  //wartosci ktore sa w nich
  nowyArtykol = (koszyk*)malloc(sizeof(koszyk));//przydzielenie pamieci na koszyk
  nowyArtykol->nast = NULL;
  nowyArtykol->popr = NULL;
  nowyArtykol->nazwa_artykulu = nazwa;
  nowyArtykol->cena_jednostkowa = cena;
  nowyArtykol->liczba_artykulow = liczba;

  if (poczatek == NULL) {
    nowyArtykol->nast = NULL;
    nowyArtykol->popr = NULL;
    poczatek = nowyArtykol;
    koniec = nowyArtykol;
  } else {
    nowyArtykol->nast = NULL;
    nowyArtykol->popr = koniec;
    koniec->nast = nowyArtykol;
    koniec = nowyArtykol;
  }
  printf("[*] Pomyslnie dodano twoj produkt\n");
  pokarz_koszyk();
  return 0;
}

void usuwanie_artykulu() {
  if (poczatek == NULL) {
    return;
  }
  printf("Wpisz nazwe artykulu ktory chcesz usunac: ");
  char bufor[30];
  scanf("%s", bufor);
  printf("\n Wpisz ile artylulow chcesz usunac: ");
  int ilosc;
  scanf("%d", &ilosc);

  koszyk *i;
  i = poczatek;
  while(i != NULL) {
    if (strcmp(bufor, i->nazwa_artykulu) == 0) {
      break;
    }
    i = i->nast;
  }
  if (i->liczba_artykulow > ilosc) {
    i->liczba_artykulow = i->liczba_artykulow - ilosc;
  } else {
    if (poczatek == i) {
      poczatek = i->nast;
    }
    if (koniec == i) {
      koniec = i->popr;
    }
    if (i->nast != NULL) {
      i->nast->popr = i->nast;
    }
    if (i->popr != NULL) {
      i->popr->nast = i->nast;
    }
    free(i);
    return;
  }
}

void zwalnianie_pamieci() {
  koszyk *i, *fre;

  while (i != NULL) {
    fre = i;
    i = i->nast;
    free(fre);
  }
}

int main() {
  system("clear");
  //system(cls); //dla windows

  int end = 1;
  while (end == 1) {
    printf("Zakupy on-line\n");
    printf("-----------------------\n");
    printf("[0] Wyjscie z programu\n");
    printf("[1] Dodaj do koszyka artykul\n");
    printf("[2] Usun z koszyka artykul\n");
    printf("[3] Zatwierdz koszyk\n");
    printf("-----------------------\n");
    printf("Wybrana komenda: ");
    int wybor, czypierwszy = 0;
    scanf("%d", &wybor);
    switch (wybor) {
      case 0:
        end = 0;
        break;
      case 1:
        stworzKoszyk();
        break;
      case 2:
        usuwanie_artykulu();
        printf("usuwam");
        break;
      case 3:
        printf("zatwierdzam\n");
        pokarz_koszyk();
        end = 0;
        zwalnianie_pamieci();
        printf("[*] Ukonczono zwalnianie pamieci");
        break;
    }
  }
}
