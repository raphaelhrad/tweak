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
    // Test fonction combat
    Tunite* gargouilleTest = creeGargouille(3,6);
    Tunite* tourRoiTest = creeTourRoi(3,7);
    Tunite* tourSolTest = creeTourSol(2,5);
    TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
    initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
    TListePlayer listeRoi;
    initListe(&listeRoi);
    jeu[3][6] = gargouilleTest;
    jeu[3][7] = tourRoiTest;
    jeu[2][5] = tourSolTest;
    listeRoi = AjoutEnTeteV2(listeRoi,tourRoiTest);
    listeRoi = AjoutEnTeteV2(listeRoi,tourSolTest);
    combat(gargouilleTest,&listeRoi,jeu);
    tourRoiDetruite(listeRoi);
    return 0;
}
