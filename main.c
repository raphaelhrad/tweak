//NOM prénom étudiant 1 :
//NOM prénom étudiant 2 :

#include "SDL.h"
#include "maSDL.h"    //bibliothèque avec des fonctions d'affichage utilisant la SDL
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "towerdefend.h"
#include "listeChainee.h"

/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    // Initialisation de l'aléatoire pour les générations
    srand(time(NULL));

    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "Appuyez sur ECHAP pour quitter, S/C ET D/V les gerer les sauvegardes",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);
    SDL_Surface* pSpriteTourSol = SDL_LoadBMP("./data/TourSol.bmp");
    SDL_Surface* pSpriteTourAir = SDL_LoadBMP("./data/TourAir.bmp");
    SDL_Surface* pSpriteTourRoi = SDL_LoadBMP("./data/TourRoi.bmp");
    SDL_Surface* pSpriteArcher = SDL_LoadBMP("./data/Archer.bmp");
    SDL_Surface* pSpriteChevalier = SDL_LoadBMP("./data/Chevalier.bmp");
    SDL_Surface* pSpriteDragon = SDL_LoadBMP("./data/Dragon.bmp");
    SDL_Surface* pSpriteGargouille = SDL_LoadBMP("./data/Gargouille.bmp");
    SDL_Surface* pSpriteEau = SDL_LoadBMP("./data/Eau.bmp");
    SDL_Surface* pSpriteHerbe = SDL_LoadBMP("./data/Herbe.bmp");
    SDL_Surface* pSpritePont = SDL_LoadBMP("./data/Pont.bmp");
    SDL_Surface* pSpriteTerre = SDL_LoadBMP("./data/Terre.bmp");

    SDL_Surface* TabSprite[11]={pSpriteTourSol,pSpriteTourAir,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteEau,pSpriteHerbe,pSpritePont,pSpriteTerre};

    int** tabParcours=initChemin();

    if ( pSpriteTourSol )
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        maj_fenetre(pWindow);

        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^
        message("Welcome in TowerDfend","Ceci est un point de depart pour votre future interface de votre jeu TowerDefend");
        message("et fin","ECHAP->quitter, S/C ET D/V les gerer les sauvegardes");

        /**********************************************************************/
        /* DEFINISSEZ/INITIALISER ICI VOS VARIABLES              */

        TListePlayer listeHorde = initHorde();
        TListePlayer listeRoi = initRoi();

        // Ajout de la Tour du Roi initiale à la fin du chemin
        // (tabParcours[NBCOORDPARCOURS-1] est la dernière case du chemin)
        Tunite* roiInitial = creeTourRoi(tabParcours[NBCOORDPARCOURS-1][X], tabParcours[NBCOORDPARCOURS-1][Y]);
        // Dans towerdefend.c, vous avez ajouté ajouterUnite(&listeRoi, roiInitial)
        listeRoi = AjoutEnTete(listeRoi, roiInitial);

        /* FIN de vos variables                                               */
        /**********************************************************************/

        // boucle principale du jeu
        int cont = 1;
        while ( cont != 0 ){
                SDL_PumpEvents(); //do events
                efface_fenetre(pWinSurf);

                /***********************************************************************/
                /* */
                //APPELEZ ICI VOS FONCTIONS QUI FONT EVOLUER LE JEU

                // On vide le plateau virtuel pour le reconstruire
                initPlateauAvecNULL(jeu, LARGEURJEU, HAUTEURJEU);

                positionnePlayerOnPlateau(listeHorde, jeu);
                positionnePlayerOnPlateau(listeRoi, jeu);

                // Création de nouvelles unités
                creationUniteAleatoireHorde(&listeHorde, tabParcours);
                creationUniteAleatoireRoi(&listeRoi, tabParcours, jeu);

                // Déplacement horde
                TListePlayer ptrHorde = listeHorde;
                while(!listeVide(ptrHorde)){
                    avancerUnite(ptrHorde->pdata, jeu, tabParcours);
                    ptrHorde = ptrHorde->suiv;
                }

                TListePlayer cur = listeRoi;
                while (cur != NULL) {
                    cur->pdata->peutAttaquer = 1;
                    cur = cur->suiv;
                }

                cur = listeHorde;
                while (cur != NULL) {
                    cur->pdata->peutAttaquer = 1;
                    cur = cur->suiv;
                }

                TListePlayer ptrRoi = listeRoi;
                while (ptrRoi != NULL) {
                    combat(pWinSurf, ptrRoi->pdata, &listeHorde, jeu);
                    ptrRoi = ptrRoi->suiv;
                }

                ptrHorde = listeHorde;
                while (ptrHorde != NULL){
                    combat(pWinSurf, ptrHorde->pdata, &listeRoi, jeu);
                    ptrHorde = ptrHorde->suiv;
                }

                //Fin de la partie
                if(tourRoiDetruite(listeRoi)) {
                    cont = 0;
                    message("Fin de la partie","La tour du Roi est detruite ! Fin de la partie.\n");
                }

                /* FIN DE VOS APPELS                                                   */
                /***********************************************************************/

                //affichage du jeu à chaque tour (avec les nouvelles positions)
                prepareAllSpriteDuJeu(jeu,tabParcours,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                maj_fenetre(pWindow);
                SDL_Delay(1000);  // Régler le délai


                //LECTURE DE CERTAINES TOUCHES POUR LANCER LES RESTAURATIONS ET SAUVEGARDES
                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                if ( pKeyStates[SDL_SCANCODE_V] ){
                        // CHARGER SÉQUENTIEL (TEXTE)
                        //chargerPartieSequentiel(&listeRoi, &listeHorde, "partieseq.tds");
                        printf("Chargement sequentiel...\n");
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){
                        // CHARGER BINAIRE
                        //chargerPartieBinaire(&listeRoi, &listeHorde, "partiebin.tdb");
                        printf("Chargement binaire...\n");
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){
                        // SAUVEGARDER SÉQUENTIEL (TEXTE)
                        //sauvegarderPartieSequentiel(listeRoi, listeHorde);
                        printf("Sauvegarde sequentielle effectuee !\n");
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_S] ){
                        // SAUVEGARDER BINAIRE
                        //sauvegarderPartieBinaire(listeRoi, listeHorde, "partiebin.tdb");
                        printf("Sauvegarde binaire effectuee !\n");
                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){
                        cont = 0;  //sortie de la boucle
                }

        }
        //fin boucle du jeu

        SDL_FreeSurface(pSpriteTourSol);
        SDL_FreeSurface(pSpriteTourAir);
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteEau);
        SDL_FreeSurface(pSpriteHerbe);
        SDL_FreeSurface(pSpritePont);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    freeChemin(tabParcours);
    return 0;
}
