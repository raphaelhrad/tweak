#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "listeChainee.h"
#include "towerdefend.h"


//typedef Tunite* ** TplateauJeu;

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
}

TListePlayer initRoi(){
    TListePlayer ListeRoi;
    ListeRoi = NULL;
    return ListeRoi;
}

TListePlayer initHorde(){
    TListePlayer ListeHorde;
    ListeHorde = NULL;
    return ListeHorde;
}

/*
void ecritCheminVersleHaut  : permet d'initilaiser le tab chemin de distance cases (avec des coord x y) dans une direction, à partir d'un point x y donné

int **chemin  : tab de coordonnées x y du chemin
int *ichemin  : indice de la case du chemin d'où on part
int *xdepart, int *ydepart : valeur en x y de départ pouri la premiere case
int distance  : distance sur laquelle on va écrire des coordonnées dans le tab chemin
int *distanceMaxRestante : securité pour ne pas sortir de la plage d'indice de chemin
*/
void ecritCheminVersleHaut(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int y;
        for (y=*ydepart;y>*ydepart-distance;y--){
            chemin[*ichemin][X]= *xdepart;
            chemin[*ichemin][Y]= y;
            (*ichemin)++;
        }
        *ydepart=y;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaDroite(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x<*xdepart+distance;x++){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}
void ecritCheminVerslaGauche(int **chemin, int *ichemin, int *xdepart, int *ydepart, int distance, int *distanceMaxRestante){
    if ((*distanceMaxRestante - distance)>=0){
        int x;
        for (x=*xdepart;x>*xdepart-distance;x--){
            chemin[*ichemin][X]= x;
            chemin[*ichemin][Y]= *ydepart;
            (*ichemin)++;
        }
        *xdepart=x;
    }
    else printf("erreur longueur chemin\n");
}

int **initChemin(){
    int **chemin = (int**)malloc(sizeof(int*)*NBCOORDPARCOURS);

    for (int j=0;j<NBCOORDPARCOURS;j++){
        chemin[j] = (int*)malloc(sizeof(int)*2);  //2 cases :indice 0 pour la coord en X, indice 1 pour la coord en Y
    }

    int ydepart = 18;  //et non 19
    int xdepart = 5;  //5 = milieu de la fenetre de 11 de largeur (0-10)
    int i = 0;  //parcourt les i cases du chemin
    int distanceMaxRestante = NBCOORDPARCOURS;

    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 5, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVerslaDroite(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);
    ecritCheminVerslaGauche(chemin, &i, &xdepart, &ydepart, 4, &distanceMaxRestante);
    ecritCheminVersleHaut(chemin, &i, &xdepart, &ydepart, 3, &distanceMaxRestante);

    return chemin;  //tab2D contenant des pointeurs
}

void afficheCoordonneesParcours(int **chemin, int nbcoord){
    printf("Liste coordonnees: ");
    for (int i=0; i<nbcoord; i++){
        printf("(%d, %d)",chemin[i][X], chemin[i][Y]);
    }
    printf("\nfin liste coordonnées\n");
}

void freeChemin(int **tab){
    for (int j=0;j<NBCOORDPARCOURS;j++){
        free(tab[j]);  //libere chaque case, qui est un tableau de 2 cases
    }
    free(tab);
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"s", "a", "r", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
                // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}


/*
à vérifier derniereCaseChemin(int** chemin){
    à utiliser pour la création de la tour du roi
}
*/

//Combat

bool tourRoiDetruite(TListePlayer playerRoi){
 //récupérer le roi dans la liste
 //s'il a été supprimé : true
 //sinon : false
}

int CoordValideEnX(int calculCoord){
    if(calculCoord < 0){ return 0; }
    if(calculCoord > LARGEURJEU - 1){ return LARGEURJEU - 1; }
    return calculCoord;
}

int CoordValideEnY(int calculCoord){
    if(calculCoord < 0){ return 0; }
    if(calculCoord > HAUTEURJEU - 1){ return HAUTEURJEU - 1; }
    return calculCoord;
}



bool peutAttaquer(Tunite* UniteAttaquante, Tunite* UniteCible){
    if(UniteAttaquante == NULL || UniteCible == NULL){
        return false;
    }
    if(UniteAttaquante->nom == chevalier || UniteAttaquante->nom == archer || UniteAttaquante->nom == dragon || UniteAttaquante->nom == gargouille){
        if(UniteCible->nom == tourRoi){
            return true;
        }
        else{
            return false;
        }
    }
    else if(UniteAttaquante->nom == tourRoi){
        if(UniteCible->nom == tourAir || UniteCible->nom == tourSol){
            return false;
        }
        else{
            return true;
        }
    }
    else if(UniteAttaquante->nom == tourAir){
        if(UniteCible->maposition == air && UniteCible->nom != tourAir){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if(UniteCible->maposition == sol && UniteCible->nom != tourSol && UniteCible->nom != tourRoi){
            return true;
        }
        else{
            return false;
        }
    }
}

TListePlayer quiEstAPortee(TplateauJeu jeu, Tunite *UniteAttaquante){
    TListePlayer listePortee;
    initListe(&listePortee);
    //Calcul coordonnées
    int posxD = CoordValideEnX(UniteAttaquante->posX - UniteAttaquante->portee);
    int posyD = CoordValideEnY(UniteAttaquante->posY - UniteAttaquante->portee);
    int posxF = CoordValideEnX(UniteAttaquante->posX + UniteAttaquante->portee);
    int posyF = CoordValideEnY(UniteAttaquante->posY + UniteAttaquante->portee);
    printf("coordD = (%d,%d), coordF = (%d,%d)\n",posxD,posyD,posxF,posyF); // A garder pour les tests
    //Parcours du tableau pour chercher les unités à portée
    /* - si l'unite fait partie de la horde alors que l'unité attaquante est de la horde on l'ignore
       - si l'unite est une tour du roi alors on l'ignore
       - Toutes les cibles ne sont pas attaquables, bien vérifier que l'unite attaquante peut attaquer l'unité à portée
    */
    for(int largeur = posxD ; largeur <= posxF; largeur++){
        for(int hauteur = posyD; hauteur <= posyF; hauteur++){
            Tunite* UniteCible = jeu[largeur][hauteur];
            if(largeur == UniteAttaquante->posX && hauteur == UniteAttaquante->posY){ //Peut-être mieux de dire de ne pas attaquer la case ou se trouve l'unité attaquante
                continue;
            }
            if(peutAttaquer(UniteAttaquante,UniteCible)){
                listePortee = AjoutEnTete(listePortee,*UniteCible);
            }
        }
    }
    //Tri de la liste selon le nombre de points de vie
    tri_selection_liste(listePortee,comparaisonPDVAinfB);
    return listePortee;
}


bool comparaisonPDVAinfB(Tunite UniteA, Tunite UniteB){
    return UniteA.pointsDeVie < UniteB.pointsDeVie;
}

bool comparaisonUniteAegaleB(Tunite UniteA, Tunite UniteB){
    return (UniteA.nom == UniteB.nom)
        && (UniteA.cibleAttaquable == UniteB.cibleAttaquable)
        && (UniteA.maposition == UniteB.maposition)
        && (UniteA.pointsDeVie == UniteB.pointsDeVie)
        && (UniteA.vitesseAttaque == UniteB.vitesseAttaque)
        && (UniteA.degats == UniteB.degats)
        && (UniteA.portee == UniteB.portee)
        && (UniteA.vitessedeplacement == UniteB.vitessedeplacement)
        && (UniteA.posX == UniteB.posX)
        && (UniteA.posY == UniteB.posY)
        && (UniteA.peutAttaquer == UniteB.peutAttaquer) ;
}

Tunite* premierElementTListePlayer(TListePlayer listeUnites){
    return listeUnites->pdata;
}

void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite, TplateauJeu jeu){
    //Si PDV inf ou égal 0, alors suppression dans liste player et sur plateau
    //Si Tunite est dernière unité de joueur, alors liste = NULL
}

void combat(SDL_Surface *surface, Tunite *UniteAttaquante, Tunite *UniteCible){
    //Soustraction des dégats sur UniteCible
    //Attaque de UniteAttaquante soustraite à PV d'UniteCible
    //Si 0 ou moins PDV : supprimerUnite
}

//Déplacement
/*
(à vérifier) prochaineCaseChemin(Tplateau jeu, int** chemin, Tunite* Unite){
    //vérifier la validité des coordonnées données
    //donc si la case suivante n'est pas prise
    //si prise : renvoie les mêmes coordonnées
    //sinon : prochaine case chemin
}
*/

void modifierPositionUnite(Tunite *Unite, int posx, int posy){
 //modifier posx et posy
}

void modifierPositionPlateau(TplateauJeu jeu, int posx, int posy){
    //placer le pointeur de l'unité sur la nouvelle case
}


void avancerUnite(Tunite* Unite, TplateauJeu jeu, int** chemin){
    //prochaineCaseChemin
    //modifierPositionUnite/modifierPositionPlateau
}

void ajouterUnite(TListePlayer *player, Tunite *nouvelleUnite){
    //ajouter à la fin de notre liste player cette nouvelle unité
    //si NULL : aucune
}

/* à faire en dernier car algorithme
à vérifier positionCreationUniteRoi(){
}
*/

//Création

void creationUniteAleatoireRoi(){
    //15-50% de proba
    //si la proba est bonne alors:
        //0,1,2
        //creerTour...
}

void creationUniteAleatoireHorde(){
    //5-60% de proba
    //position pour horde au même endroit : début chemin : premiere valeur liste chemin
    //si la proba est bonne alors:
        //0,1,2...
        //creer...
}

//Valeurs des unités
Tunite *creeTourSol(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourSol;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 120;
    nouv->portee = 5;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeTourAir(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourAir;
    nouv->cibleAttaquable = air;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 180;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = sol;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 900;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->peutAttaquer = 1;
    //nouv->cible = NULL;
    return nouv;
}

// Affichage des Tunites pour vérifier que ça fonctionne bien

char* TuniteDuJeuToString(TuniteDuJeu t){
    char* resultat;
    switch((int) t){
        case 0 :
            resultat = "tourSol";
            break;
        case 1 :
            resultat = "tourAir";
            break;
        case 2 :
            resultat = "tourRoi";
            break;
        case 3 :
            resultat = "archer";
            break;
        case 4 :
            resultat = "chevalier";
            break;
        case 5 :
            resultat = "dragon";
            break;
        case 6 :
            resultat = "gargouille";
            break;
        default :
            resultat = "inconnu";
            break;
    }
    return resultat;
}

char* TcibleToString(Tcible c){
    char* resultat;
    switch((int) c){
        case 0 :
            resultat = "sol";
            break;
        case 1 :
            resultat = "solEtAir";
            break;
        case 2 :
            resultat = "air";
            break;
        default :
            resultat = "inconnu";
            break;
    }
    return resultat;
}

void printUnite(Tunite u){
    printf("nom : %s ; cibleAttaquable : %s ; maposition : %s ; pointsDeVie: %d ; vitesseAttaque : %f ; degats : %d ; portee : %d ; vitessedeplacement : %f ; posX : %d ; posY : %d ; peutAttaquer : %d\n",
           TuniteDuJeuToString(u.nom),TcibleToString(u.cibleAttaquable),TcibleToString(u.maposition),u.pointsDeVie,u.vitesseAttaque,u.degats,u.portee,u.vitessedeplacement,u.posX,u.posY,u.peutAttaquer);
}

void afficheTListePlayer(TListePlayer l){
    if(listeVide(l)){
        printf("Erreur afficheTListePlayer : la liste est vide\n");
        return;
    }
    TListePlayer ptr = l;
    while(!listeVide(ptr)){
        printUnite(*ptr->pdata);
        printf("\n");
        ptr = ptr->suiv;
    }
}
