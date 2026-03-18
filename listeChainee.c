#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "listeChainee.h"

void initListe(TListePlayer* l){
    *l=NULL;
}

bool listeVide(TListePlayer l){
    return TListePlayer == NULL;
}

TListePlayer AjoutEnTete(TListePlayer l, Tunite data){
    T_cell* newcell = (T_cell*) malloc(sizeof(T_cell));
    Tunite* newdata = (Tunite*) malloc(sizeof(Tunite));
    if(listeVide(l)){
        newcell->suiv = NULL;
        newcell->pdata = newdata;
        *newcell->pdata = data;
        l = newcell;
        return l;
    }
    TListePlayer temp = l->suiv;
    newcell->suiv = temp;
    newcell->pdata = newdata;
    *newcell->pdata = data;
    l = newcell;
    return l;
}

TListePlayer supprimerUniteListe(TListePlayer l, Tunite unite){
    if(listeVide(l)){
        printf("Erreur supprimerUniteListe : la liste est vide\n");
        return NULL;
    }
    if(comparaisonUniteAegaleB(*l->pdata,unite)){
        TListePlayer temp = l;
        l = l->suiv;
        free(temp->pdata);
        free(temp);
        return l;
    }
    TListePlayer ptr = l;
    while(!listeVide(ptr->suiv)){
        TListePlayer nextcell = ptr->suiv;
        if(comparaisonUniteAegaleB(*nextcell->pdata,unite)){
            ptr->suiv = nextcell->suiv;
            free(nextcell->pdata);
            free(nextcell);
            return l;
        }
        ptr = ptr->suiv;
    }
    return l;
}

void tri_selection_liste(TListePlayer l, bool (*fcomp)(Tunite a, Tunite b)){
    TListePlayer i = l;
    while(i != NULL){
        TListePlayer cell_min = i;
        TListePlayer j = i->suiv;
        while(j != NULL){
            if(fcomp(*j->pdata,*cell_min->pdata)){
                cell_min = j;
            }
            j = j->suiv;
        }
        Tunite* temp = i->pdata;
        i->pdata = cell_min->pdata;
        cell_min->pdata = temp;
        i = i->suiv;
    }
}
