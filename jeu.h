/* Auteur : MBUMA MONA Nathan
 * création : 01/03/2019
 * modification : 02/03/2019*/
 
#ifndef __jeu__
#define __jeu__

#include "creation.h"

typedef enum{
    
    JOUEUR1,
    JOUEUR2
    
}Jouer;


typedef struct{
    Tablette table;
    Jouer tour;
    
    
}Position;



typedef struct{
    int x;
    int y;
}Coup;



/* fonction    : manger
 * parametres  : un pointeur sur une tablette , une position (x ,y) et la taille de la grille
 * retour      : rien
 *description  : elle  modifie la tablette t de sorte à manger le carré de chocolat en position (x,y)
ainsi que tous ceux qui sont en dessous de lui et à sa droite.*/

void manger(Tablette *t ,Coup coups, int hauteur , int largeur);


/* fonction    : est_legal
 * parametres  : (tableau et joueur) et un coup 
 * retour      : un entier 
 * description : elle renvoie 1 si le deplacement est possible 0 sinon
 * Un coup dans une position donnée est légal s’il ordonne de manger un carré de
chocolat qui existe encore. */

int est_legal(Position *pos , Coup *coups);


/* fonction    : et_jeu_termine
 * parametres  : une position pos et un joueur 
 * retour      : un entier
 * description : elle renvoie 1 si la partie est terminée sinon  0 
 * La partie est terminée lorsque le carré de chocolat empoisonné vient d’être mangé.
Dans ce cas, c’est le joueur qui vient de jouer qui a perdu et l’autre qui a gagné.*/

int est_jeu_termine(Position *pos , Jouer * joueur_gagant);


/* fonction    : jouer_coup
 * parametres  : une position et un coup 
 * retour      : rien
 * description : elle modifie la position    qui joue le coup coup dans la position pos. 
 * Il ne faut pas oublier de modifier le
champ qui contient le joueur dont c’est le tour de jouer.*/


void jouer_coup(Position *pos , Coup *coups, int hauteur , int largeur);


/* fonction    : lire_coup
 * parametres  : un pointeur sur une position , une  epaisseur , une  hauteur ,une largeur et un fichier
 * retour      : un Coup 
 * description : elle atteint  un clic de l’utilisateur sur la tablette de chocolat dans la fenêtre graphique
				 calcule et renvoie le coup spécifié par l’utilisateur. Si l’utilisateur ne clique pas sur
				 la tablette, ou bien clique sur un carré de chocolat déjà mangé, la fonction ne fait
				 rien et attend de traiter le prochain clic.*/
Coup lire_coup(Position *pos,int epais,int hauteur,int largeur,FILE *fichier);


#endif
