#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listeDouble.h"

//initListe ne fait pas de malloc, juste une initialisation à NULL du pointeur de liste
void initListe(T_liste *l){
*l=NULL;
}

bool listeVide( T_liste l){
    return (l==NULL);
}

void afficheListeV1( T_liste l){
    if(l == NULL){
        printf("La liste est vide\n");
        return;
    }
    T_cellule* ptr = l;
    while(ptr != NULL){
        printf("%d%s",*(ptr->pdata),ptr->suiv == NULL ? "" : "->");
        ptr = ptr->suiv;
    }
    printf("\n");
}

T_liste ajoutEnTete(T_liste l,int mydata){
    T_cellule* cell = (T_cellule*) malloc(sizeof(T_cellule));
    int* newdata = (int*) malloc(sizeof(int));
    if(l == NULL){
        cell->prec = NULL;
        cell->suiv = l;
        cell->pdata = newdata;
        *(cell->pdata) = mydata;
        l = cell;
        return l;
    }
    cell->prec = NULL;
    cell->suiv = l;
    cell->pdata = newdata;
    *(cell->pdata) = mydata;
    l->prec = cell;
    l = cell;
    return l;
}

T_liste ajoutEnFin(T_liste l,int mydata){
    T_cellule* cell = (T_cellule*) malloc(sizeof(T_cellule));
    int* newdata = (int*) malloc(sizeof(int));
    if(l == NULL){
        return l = ajoutEnTete(l,mydata);
    }
    T_cellule* ptr = l;
    while(ptr->suiv != NULL){
        ptr = ptr->suiv;
    }
    cell->prec = ptr;
    cell->suiv = NULL;
    cell->pdata = newdata;
    *(cell->pdata) = mydata;
    ptr->suiv = cell;
    return l;
}

T_liste ajoutEnN(T_liste l, int pos, int mydata){
    if(l == NULL){
        printf("Erreur : index hors de la liste\n");
        return NULL;
    }
    if(pos == 0){
        return l = ajoutEnTete(l,mydata);
    }
    T_cellule* ptr = l;
    for(int i = 0; i < pos; i++){
        ptr = ptr->suiv;
        if(ptr == NULL){
            printf("Erreur : index hors de la liste\n");
            return NULL;
        }
    }
    T_cellule* cell = (T_cellule*) malloc(sizeof(T_cellule));
    int* newdata = (int*) malloc(sizeof(int));
    T_cellule* temp = ptr->prec;
    temp->suiv = cell;
    cell->prec = temp;
    cell->suiv = ptr;
    cell->pdata = newdata;
    *(cell->pdata) = mydata;
    ptr->prec = cell;
    return l;
}

T_liste suppEnTete(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    if(l->suiv == NULL){
        free(l);
        l = NULL;
        return l;
    }
    T_cellule* temp = l->suiv;
    free(l);
    l = temp;
    temp->prec = NULL;
    return l;
}

T_liste suppEnFin(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    if(l->suiv == NULL){
        return l = suppEnTete(l);
    }
    T_cellule* ptr = l;
    while(ptr->suiv != NULL){
        ptr = ptr->suiv;
    }
    T_cellule* temp = ptr->prec;
    temp->suiv = NULL;
    free(ptr);
    return l;
}

T_liste suppEnN(T_liste l, int pos){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    if(pos == 0){
        return l = suppEnTete(l);
    }
    T_cellule* ptr = l;
    for(int i = 0; i < pos; i++){
        ptr = ptr->suiv;
        if(ptr == NULL){
            printf("Erreur : index hors de la liste\n");
            return NULL;
        }
    }
    if(ptr->suiv == NULL){
        return l = suppEnFin(l);
    }
    T_cellule* temp1 = ptr->prec;
    T_cellule* temp2 = ptr->suiv;
    temp1->suiv = temp2;
    temp2->prec = temp1;
    free(ptr);
    return l;
}

T_liste getptrFirstCell(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    if(l->prec == NULL){
        return l;
    }
    T_cellule* ptr = l;
    while(ptr->prec != NULL){
        ptr = ptr->prec;
    }
    return ptr;
}

T_liste getptrLastCell(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    if(l->suiv == NULL){
        return l;
    }
    T_cellule* ptr = l;
    while(ptr->suiv != NULL){
        ptr = ptr->suiv;
    }
    return ptr;
}

T_liste getptrNextCell(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    if(l->suiv == NULL){
        return NULL;
    }
    return l->suiv;
}

T_liste getptrPrevCell(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    if(l->prec == NULL){
        return NULL;
    }
    return l->prec;
}

int* getPtrData(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return NULL;
    }
    return l->pdata;
}

void swapPtrData(T_liste source, T_liste destination){
    if(source == NULL){
        printf("Erreur : le pointeur vers la source est nul\n");
        return;
    }
    if(destination == NULL){
        printf("Erreur : le pointeur vers la destination est nul\n");
        return;
    }
    T_cellule temp = *source;
    *source = *destination;
    *destination = temp;
}

int getNbreCell(T_liste l){
    T_cellule* ptr = l;
    int cpt = 0;
    while(ptr != NULL){
        cpt++;
        ptr = ptr->suiv;
    }
    return cpt;
}

int getSizeBytes(T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide\n");
        return -1;
    }
    T_cellule* ptr = l;
    int cptbyte = 0;
    while(ptr != NULL){
        cptbyte = cptbyte + ((int) sizeof(*ptr));
        ptr = ptr->suiv;
    }
    return cptbyte;
}

T_cellule* createCell(int data){
    T_cellule* cell = malloc(sizeof(T_cellule));
    int* ptrData = malloc(sizeof(int));
    *ptrData = data;
    cell->pdata = ptrData;
    cell->suiv = NULL;
    cell->prec = NULL;
    return cell;
}

T_liste createNewListeFromFusion(T_liste l1, T_liste l2){
    if(l1 == NULL){
        printf("Erreur : le pointeur l1 est nul");
        return NULL;
    }
    if(l2 == NULL){
        printf("Erreur : le pointeur l2 est nul");
        return NULL;
    }
    T_liste result;
    T_liste courant;
    initListe(&result);
    initListe(&courant);
    while(l1 != NULL){
        T_liste nouveau = createCell(*(l1->pdata));
        if(result == NULL){
            result = nouveau;
            courant = result;
        }
        else{
            courant->suiv = nouveau;
            nouveau->prec = courant;
            courant = nouveau;
        }
        l1 = l1->suiv;
    }
    while(l2 != NULL){
        T_liste nouveau = createCell(*(l2->pdata));
        courant->suiv = nouveau;
        nouveau->prec = courant;
        courant = nouveau;
        l2 = l2->suiv;
    }
    return result;
}

T_liste addBehind(T_liste debut, T_liste suite){
    if(debut == NULL){
        printf("Erreur : la liste debut est vide");
        return NULL;
    }
    if(suite == NULL){
        printf("Erreur : la liste suite est vide");
        return NULL;
    }
    T_cellule* ptrDbt = debut;
    T_cellule* ptrSte = suite;
    while(ptrDbt->suiv != NULL){
        ptrDbt = ptrDbt->suiv;
    }
    while(ptrSte != NULL){
        ajoutEnFin(ptrDbt,*(ptrSte->pdata));
        ptrSte = ptrSte->suiv;
        ptrDbt = ptrDbt->suiv;
    }
    return debut;
}

T_liste findCell(T_liste l, int data){
    if(l == NULL){
        printf("Erreur : la liste est vide");
        return NULL;
    }
    T_liste ptr = l;
    while(ptr != NULL){
        int valeur = *(ptr->pdata);
        if(valeur == data){
            return ptr;
        }
        ptr = ptr->suiv;
    }
    return NULL;
}

int getOccurences(T_liste l, int data){
    if(l == NULL){
        printf("Erreur : la liste vide");
        return -1;
    }
    int cpt = 0;
    T_cellule* ptr = l;
    while(ptr != NULL){
        int valeur = *(ptr->pdata);
        if(valeur == data){
            cpt++;
        }
        ptr = ptr->suiv;
    }
    return cpt;
}

void afficheListeV2( T_liste l){
    if(l == NULL){
        printf("Erreur : la liste est vide");
        return;
    }
    while(l != NULL){
        printf("%d%s",*(getPtrData(l)),l->suiv == NULL ? "" : "-->");
        l = getptrNextCell(l);
    }
    printf("\n");
}
