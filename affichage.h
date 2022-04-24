/* Auteur : MBUMA MONA Nathan
 * création : 01/03/2019
 * modification : 02/03/2019*/

#ifndef __affichage__
#define __affichage__


#include "jeu.h"
#include <MLV/MLV_all.h>


/* fonction    : afficher_position
 * parametres  : une position pos , hauteur,largeur et un pointeur sur epais 
 * retour      : rien
 * description : affiche une position en utilisant la bibliothèque graphique .*/

void afficher_position(Position *pos,int hauteur,int largeur,int *epais);

/* fonction    : afficher_menu
 * parametre   : rien
 * retour      : un entier
 * description : cette fonction affiche le menu au debut du jeu elle
 * 1 si l'utilisateur decide de jouer , 2 pour charger une partie et 3 pour
 * quitter.*/
 
int afficher_menu(void);

/* fonction    : fabriqueCouleur
 * parametre   : rien
 * retour      : un code couleur de type MLV_color
 * description : cette fonction génère une couleur*/
MLV_Color fabriqueCouleur(void);

#endif
