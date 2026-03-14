#ifndef TRILISTE_H_INCLUDED
#define TRILISTE_H_INCLUDED

#include <stdbool.h>
#include <time.h>
#include "listeDouble.h"

void tri_selection(int *tableau, int taille);
T_liste listeRandN(int n);
int* listeVersTab(T_liste l, int n);
void afficherTab(int *tab, int n);
int* listeVersTabFree(T_liste l, int n);
T_liste tabVersListe(int *tab, int n);
T_liste triListe(T_liste l, int n);
void chronometrerTriN(int n);
void tri_selection_liste(T_liste l);

#endif
