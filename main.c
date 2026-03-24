//NOM prénom étudiant 1 :
//NOM prénom étudiant 2 :

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonctions d'affichage utilisant la SDL
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listeChainee.h"



/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    TplateauJeu test = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
    initPlateauAvecNULL(test,LARGEURJEU,HAUTEURJEU);
    Tunite u1 = {
        .nom  = tourRoi,
        .cibleAttaquable = solEtAir,
        .maposition = sol,
        .pointsDeVie = 300,
        .vitesseAttaque = 2.1,
        .degats = 20,
        .portee = 3,
        .vitessedeplacement = 0.7,
        .posX = 5,
        .posY = 5,
        .peutAttaquer = 0
    };
    Tunite u2 = {
        .nom  = tourSol,
        .cibleAttaquable = sol,
        .maposition = sol,
        .pointsDeVie = 234,
        .vitesseAttaque = 2.1,
        .degats = 25,
        .portee = 2,
        .vitessedeplacement = 0.7,
        .posX = 2,
        .posY = 1,
        .peutAttaquer = 1
    };
    Tunite u3 = {
        .nom  = archer,
        .cibleAttaquable = solEtAir,
        .maposition = sol,
        .pointsDeVie = 150,
        .vitesseAttaque = 2.1,
        .degats = 25,
        .portee = 8,
        .vitessedeplacement = 0.7,
        .posX = 4,
        .posY = 0,
        .peutAttaquer = 1
    };
    test[2][1] = &u2;
    test[4][0] = &u3;
    test[5][5] = &u1;
    TListePlayer listeportee = quiEstAPortee(test,&u2);
    afficheTListePlayer(listeportee);
    return 0;
}
