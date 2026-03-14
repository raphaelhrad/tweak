#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "listeDouble.h"
#include "tri_liste.h"

//Tri sélection
void tri_selection(int *tab, int n){
    int temp;
    for (int i=0; i<n-1; i++){
        for (int j = i+1; j<n; j++){
            if (tab[i] > tab[j]){
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
}

//Q1
T_liste listeRandN(int n){
    T_liste l;
    initListe(&l);
    srand(time(NULL));
    for (int i = 0; i < n; i++){
         l = ajoutEnFin(l, rand()%100);
    }
    return l;
}

//Q2
int* listeVersTab(T_liste l, int n){
    int* tab = malloc(n * sizeof(int));

    T_cellule* ptr = l;
    for (int i = 0; i < n; i++){
        tab[i] = *(ptr->pdata);
        ptr = ptr->suiv;
    }
    return tab;
}

void afficherTab(int *tab, int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", tab[i]);
    }
}

//Q3
int* listeVersTabFree(T_liste l, int n){
    int* tab = malloc(n * sizeof(int));
    T_cellule* ptr = l;
    for (int i = 0; i < n; i++){
        tab[i] = *(ptr->pdata);
        free(ptr->pdata);
        ptr = ptr->suiv;
        free(l);
        l = ptr;
    }
    return tab;
}

//Q4
T_liste tabVersListe(int *tab, int n){
    T_liste l;
    initListe(&l);
    for (int i = 0; i < n; i++){
        l = ajoutEnFin(l, tab[i]);
    }
    return l;
}

//Q5
T_liste triListe(T_liste l, int n){
    int* tab = malloc(n * sizeof(int));
    tab = listeVersTabFree(l, n);
    tri_selection(tab, n);
    l = tabVersListe(tab, n);
    free(tab);
    return l;
}

//Q6
void chronometrerTriN(int n){
    T_liste l = listeRandN(n);
    time_t now = time(NULL);
    triListe(l, n);
    time_t apres = time(NULL);
    printf("Tri exécuté en %.2f seconde(s) pour %d entiers !", difftime(apres, now), n);
}

//Etape 3
void tri_selection_liste(T_liste l){
    for (T_liste ptr = getptrFirstCell(l); ptr != NULL; ptr = getptrNextCell(ptr)){ //premier parcours : valeur examinér
        printf("%d\n", *(ptr->pdata));
        for (T_liste ptr2 = getptrNextCell(ptr); ptr2 != NULL; ptr2 = getptrNextCell(ptr2)){
            if (*(ptr->pdata) > *(ptr2->pdata)){
                swapPtrData(ptr, ptr2);
            }
        }
    }
}
