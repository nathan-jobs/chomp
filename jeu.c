/* Auteur : MBUMA MONA Nathan
 * création : 29/01/2019
 * modification : 02/03/2019*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define LONGUEUR 1200
#define LARGEUR 700
#include <MLV/MLV_all.h>
#include "jeu.h"


void manger(Tablette *t , Coup coups, int hauteur , int largeur){
    int i, j;
  
	for(i = coups.x ; i < hauteur ; i++){
		for(j = coups.y ; j < largeur ; j++)
			t->tab[i][j] = 0;			
       }
}
    
         
int est_legal(Position *pos , Coup *coups){
    int x = coups->x;
    int y = coups->y;
    if(pos->table.tab[x][y] == 1)
        return 1;
    return 0;
    
    
}
        

int est_jeu_termine(Position *pos , Jouer *joueur_gagnant){
    if(pos->table.tab[0][0] == 0){
        if(pos->tour == JOUEUR1)
            *joueur_gagnant = JOUEUR1;
        else
            *joueur_gagnant = JOUEUR2;
        
        return 1;
        
    }
    
    return 0;
    
}

void jouer_coup(Position *pos , Coup *coups, int hauteur, int largeur){
    if(est_legal(pos,coups)){
        
        manger(&(pos->table) ,*coups,hauteur,largeur);
        if(pos->tour == JOUEUR1)
            pos->tour = JOUEUR2;
        else
            pos->tour = JOUEUR1;
        }
   
    
}

Coup lire_coup(Position *pos,int epais,int hauteur,int largeur,FILE *fichier){
	Coup coups;
	
	int souris_x ,souris_y;
	do{
		MLV_wait_mouse(&souris_x, &souris_y);
	}while(!((10 <= souris_x && souris_x < 10 + hauteur * (epais + 1)) && (17 <= souris_y && souris_y < 17 + largeur * (epais + 1))));
	souris_x = (souris_x -10)/ epais;
	souris_y = (souris_y - 17)/ epais;
	
	if(souris_x >= hauteur )
		souris_x = hauteur -1;
	if(souris_y >= largeur )
		souris_y = largeur -1;
	if(pos->table.tab[souris_x][souris_y] == 1){
		coups.x = souris_x;
		coups.y = souris_y;
		fprintf(fichier,"\n%d\n",coups.x);
		fprintf(fichier,"\n%d",coups.y);
		return coups;
	}
	coups.x = -1;
	coups.y = -1;
	
	return coups;
	
    
}
