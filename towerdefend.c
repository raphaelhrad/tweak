#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "maSDL.h"
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


/** !! A chaque tour on reconstruit le plateau de jeu, ainsi les fonctions ne modifie que l'unité et la liste du joueur, le plateau sera recrée grâce aux listes modifiées des deux joueurs !! */

//Combat

bool UniteRoiPresente(TListePlayer playerRoi){
    if(listeVide(playerRoi)){
        printf("Erreur UniteRoiPresente : La liste est vide\n");
        return false;
    }
    TListePlayer ptr = playerRoi;
    while(!listeVide(ptr)){
        Tunite *currentUnite = ptr->pdata;
        if(currentUnite->nom == tourRoi){
            return true;
        }
        ptr = ptr->suiv;
    }
    return false;
}

bool tourRoiDetruite(TListePlayer playerRoi){
    //récupérer le roi dans la liste
    //s'il a été supprimé : true
    //sinon : false
    if(UniteRoiPresente(playerRoi)){
        printf("Tour du Roi toujours presente\n");
        return false;
    }
    else{
        printf("Tour du Roi detruite\n");
        return true;
    }
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
    //Calcul coordonnées (il faudra changer le début et la fin en regardant le schéma dans le pdf)
    int posxD = CoordValideEnX(UniteAttaquante->posX - UniteAttaquante->portee);
    int posyD = CoordValideEnY(UniteAttaquante->posY - UniteAttaquante->portee);
    int posxF = CoordValideEnX(UniteAttaquante->posX + UniteAttaquante->portee);
    int posyF = CoordValideEnY(UniteAttaquante->posY + UniteAttaquante->portee);
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
                listePortee = AjoutEnTete(listePortee,UniteCible);
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

bool comparaisonUniteAegaleB(Tunite UniteA, Tunite UniteB){ // Il faut faire très attention avec l'utilisation de cette fonction car elle ne vérifie pas si les deux unités sont valides
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
    // Récupération des coordonnées de l'unité détruite
    int coordxUnite = UniteDetruite->posX, coordyUnite = UniteDetruite->posY;
    // Retirer le pointeur vers cette unité dans le plateau de jeu
    jeu[coordxUnite][coordyUnite] = NULL; // Vu qu'on reconstruit le plateau avec les listes des joueurs dans une autre fonction on a pas besoin de le faire ici
    //Retirer l'unité de la liste du joueur
    *player = supprimerUniteListe(*player,*UniteDetruite);
}


/** (C'est un commentaire de doc mais c'est super important que je le vois)
Attention, dans la fonction AjoutEnTete, je n'ajoute que des copies d'unités.
Or lorsqu'une modification a besoin de se transmettre sur l'ensemble des entités pointant l'unité en question,
toute unité ayant utilisée cette méthode ne pointe pas vers l'unité originale mais vers une copie. Dans cette fonction, les modification
effectuées sur les points de vies de l'unité cible n'était pas visible par listeplayer car dans listeUniteCible, c'est une copie de l'unité
originale donc aucun impact sur l'originale. C'est pourquoi j'ai crée la fonction AjoutEnTeteV2 qui prend un pointeur sur Tunite et non pas
un Tunite */
void combat(SDL_Surface *surface, Tunite *UniteAttaquante, TListePlayer *listeplayer, TplateauJeu jeu){ //Penser à supprimer cette partie
    //Attaque de UniteAttaquante soustraite à PV d'UniteCible
    //Soustraction des dégats sur UniteCible
    TListePlayer listeUniteCible = quiEstAPortee(jeu,UniteAttaquante);
    Tunite *UniteCible = premierElementTListePlayer(listeUniteCible);
    UniteCible->pointsDeVie = UniteCible->pointsDeVie - UniteAttaquante->degats;
    if(UniteCible->pointsDeVie <= 0){
        //Si 0 ou moins PDV : supprimerUnite
        supprimerUnite(listeplayer,UniteCible,jeu);
    }
    dessineAttaque(surface,UniteAttaquante,UniteCible);
}

//Déplacement

int ProchaineCaseChemin(int** chemin, Tunite* Unite){
    int indexCase = 0;
    bool indexTrouve = false;
    while(!indexTrouve && indexCase < NBCOORDPARCOURS){
        indexCase++;
        if(Unite->posX == chemin[indexCase][X] && Unite->posY == chemin[indexCase][Y]){
            indexTrouve = true;
        }
    }
    if(indexCase > 0 && indexCase < NBCOORDPARCOURS - 1){
        return indexCase + 1; //Case suivante du tableau chemin
    }
    if(indexCase == NBCOORDPARCOURS - 1){
        return indexCase; // C'est la dernière case donc on renvoie la même car il n'y a pas de case suivante
    }
    else{
        return indexCase; // Il faut faire de la gestion d'erreur
    }
}


void avancerUnite(Tunite* Unite, TplateauJeu jeu, int** chemin){
    int caseSuiv = ProchaineCaseChemin(chemin, Unite);
    int coordXCaseSuiv = chemin[caseSuiv][X], coordYCaseSuiv = chemin[caseSuiv][Y];
    if(jeu[coordXCaseSuiv][coordYCaseSuiv] == NULL){ // Si aucune autre unité de la horde se trouve sur la prochaine case alors on peut avancer l'unité
        Unite->posX = coordXCaseSuiv;
        Unite->posY = coordYCaseSuiv;
    } // Sinon on ne fait rien, elle reste là où elle est
}



//Création


void ajouterUnite(TListePlayer *player, Tunite *nouvelleUnite){
    AjoutEnTete(*player,nouvelleUnite);
}

int NbCaseCheminAPortee(int posX, int posY, int portee, int** chemin){
    int posxD = CoordValideEnX(posX - portee);
    int posyD = CoordValideEnY(posY - portee);
    int posxF = CoordValideEnX(posX + portee);
    int posyF = CoordValideEnY(posY + portee);
    int cpt = 0;
    for(int i = 0; i < NBCOORDPARCOURS; i++){
       if(posX == chemin[i][X] && posY == chemin[i][Y]){
            return -1; // C'est une case du chemin donc on l'évite
       }
       if((chemin[i][X] >= posxD && chemin[i][X] <= posxF) && (chemin[i][Y] >= posyD && chemin[i][Y] <= posyF)){
            cpt++;
       }
    }
    return cpt;
}

/*TListe EmplacementTourRoi(int largeur, int hauteur, int portee, int** chemin){
    TListe listeEmplacement = NULL;
    for(int i = 0; i < largeur; i++){
        for(int j = 0; j < hauteur; j++){
            int nbCase = NbCaseCheminAPortee(i,j,portee,chemin);
            if(nbCase > 0){
                // Tcoord* data = malloc(sizeof(Tcoord));
                // data->posX = i;
                // data->posY = j;
                // data->score_emplacement = nbCase;
                // listeEmplacement = AjoutEnTete(listeEmplacement,data);
            }
        }
    }
    return listeEmplacement;
}*/


void creationUniteAleatoireRoi(TListePlayer listeRoi, int** chemin){
    // Tour Sol : 40%, Tour Air : 40%, Aucune : 20%
    /* - Générer des coordonnées aléatoires
       - Vérifier la validité (il ne faut pas quelles représentes une case du chemin ou l'emplacement d'une autre tour)
       - Vérifier la logique (aucun intérêt si elle est placée à un endroit ou elle n'aura jamais la portée suffisante pour attaquer) */


}

void creationUniteAleatoireHorde(TListePlayer listeHorde, int** chemin){
    // Chevalier : 15%, Dragon : 20%, Archer : 20%, Gargouille : 25%, Aucune : 20%
    // Les unités de la horde apparaissent toujours au début du chemin
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

// Fonction permettant de reconstruire le plateau de jeu à chaque tour

void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu){
    //Si il n'y a eu aucun chagement de position alors on ne change rien
    //Si l'unité a changé de position (les coordonnées de l'unité ne correspondent plus au placement sur le plateau) alors on effectue les modifications nécessaires
    //Si une nouvelle unité apparaît alors on effectue les modifications nécessaires

}




