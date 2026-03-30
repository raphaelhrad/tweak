#ifndef LISTECHAINEE_H_INCLUDED
#define LISTECHAINEE_H_INCLUDED

#include "towerdefend.h"

void initListe(TListePlayer* l);
bool listeVide(TListePlayer l);
TListePlayer AjoutEnTete(TListePlayer l, Tunite data);
TListePlayer AjoutEnTeteV2(TListePlayer l, Tunite *data);
TListePlayer supprimerUniteListe(TListePlayer l, Tunite unite);
void tri_selection_liste(TListePlayer l, bool (*fcomp)(Tunite a, Tunite b));



#endif // LISTECHAINEE_H_INCLUDED
