//NOM prénom étudiant 1 :
//NOM prénom étudiant 2 :

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonctions d'affichage utilisant la SDL
#include "towerdefend.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listeChainee.h"



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    TListePlayer l;
    initListe(&l);
    Tunite u1 = {
        .nom  = tourAir,
        .cibleAttaquable = air,
        .maposition = air,
        .pointsDeVie = 300,
        .vitesseAttaque = 2.1,
        .degats = 20,
        .portee = 3,
        .vitessedeplacement = 0.7,
        .posX = 2,
        .posY = 3,
        .peutAttaquer = 0
    };
    Tunite u2 = {
        .nom  = tourSol,
        .cibleAttaquable = solEtAir,
        .maposition = sol,
        .pointsDeVie = 234,
        .vitesseAttaque = 2.1,
        .degats = 25,
        .portee = 8,
        .vitessedeplacement = 0.7,
        .posX = 2,
        .posY = 2,
        .peutAttaquer = 1
    };
    Tunite u3 = {
        .nom  = gargouille,
        .cibleAttaquable = solEtAir,
        .maposition = sol,
        .pointsDeVie = 150,
        .vitesseAttaque = 2.1,
        .degats = 25,
        .portee = 8,
        .vitessedeplacement = 0.7,
        .posX = 2,
        .posY = 2,
        .peutAttaquer = 1
    };
    l = AjoutEnTete(l,u1);
    l = AjoutEnTete(l,u2);
    l = AjoutEnTete(l,u3);
    printf("Avant suppression\n");
    printf("\n");
    afficheTListePlayer(l);
    printf("Apres suppression\n");
    printf("\n");
    l = supprimerUniteListe(l,u3);
    afficheTListePlayer(l);
    return 0;
}
