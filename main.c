/* Auteur : MBUMA MONA Nathan
 * création : 29/01/2019
 * modification : 02/03/2019*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define LONGUEUR 1200
#define LARGEUR 700
#include "affichage.h"

/* fonction    : matchs
 * paramteres  : le joueur gagnant et les 2 joueurs .
 * retour      : rien
 * description : incremente un joueur selon le nombre de victoire */ 
void matchs(Jouer joueur_gagnant, int* joueur1, int* joueur2);

/* fonction    : jouer_le jeu
 * paramteres  : la hauteur , la largeur , le nombre de partie et un fichier
 * retour      : rien
 * description : cette fonction fait appel à toutes les fonctions précedentes 
 * avec un algorithme simple tant que le joueur n'a pas mangé le chocolat on relance */ 
void joueur_le_jeu(int hauteur,int largeur,int nb_partie,FILE *fichier);


int main(void){
	int hauteur = 0;
	int largeur = 0;
	int nb_partie = 0;
	char *nom;
	MLV_Image *image;
	MLV_Font* font = NULL;
    FILE *fichier = NULL;
    FILE *fichier2 = NULL;
    int retour;
    MLV_create_window("CHOMP", "CHOMP",LONGUEUR,LARGEUR);
    
    font = MLV_load_font( "src/Garuda-Oblique.ttf" , 35 );
	retour = afficher_menu();
	
	switch(retour){
		case 1 :
			MLV_clear_window(MLV_COLOR_BLACK);
			fichier = fopen("fichier" , "w");
			joueur_le_jeu(hauteur,largeur,nb_partie,fichier);
			break;
		case 2 :
			MLV_clear_window(MLV_COLOR_BLACK);
			image = MLV_load_image("src/f.jpg");
			MLV_resize_image_with_proportions(image, LONGUEUR, LARGEUR);
			MLV_draw_image(image, 0, 0);
			MLV_actualise_window();
			/* on demande le nom du fichier*/
			MLV_wait_input_box_with_font(
			10,70,
			400,90,
			MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
			"Le nom du fichier : ",
			&nom,font);
			
			fichier2 = fopen(nom,"rw");
			if(fichier2 == NULL){
				MLV_draw_filled_rectangle(LONGUEUR/2-100, LARGEUR/2-50, 450, 50, MLV_COLOR_WHITE);
				MLV_draw_text_with_font(LONGUEUR/2-95 , LARGEUR/2-50 ,"Fichier inexistant au revoir !!!", font, MLV_COLOR_RED);
				MLV_actualise_window();
				MLV_wait_seconds( 5 );
				MLV_free_window();
				return 0;
				
			}
				
			recupere_info(fichier2,&hauteur,&largeur,&nb_partie);
			
			joueur_le_jeu(hauteur,largeur,nb_partie,fichier2);
			
			
			break;
		
		
	}
    
            
    return 0;  
        
}

void matchs(Jouer joueur_gagnant, int* joueur1, int* joueur2){
	if (joueur_gagnant == JOUEUR1)
		*joueur1 = *joueur1 + 1;
	else
		*joueur2 = *joueur2 + 1;
}

void joueur_le_jeu(int hauteur,int largeur,int nb_partie,FILE *fichier){
	int joueur1 = 0;
	int joueur2 = 0;
	int epais;
	int i = 0;
	Position pos;
	Jouer joueur_gagnant;
	Coup c;
	MLV_Font* font = MLV_load_font( "src/Garuda-Oblique.ttf" , 35 );
	if(hauteur == 0 && largeur == 0)
		nb_partie = dimension_et_nb_parties(&hauteur, &largeur,fichier);
	do{
		pos.table = creer_tablette(hauteur, largeur,fichier);
		pos.tour = JOUEUR1;
		MLV_wait_seconds( 1 );
		MLV_clear_window(MLV_COLOR_BLACK);
		MLV_draw_adapted_text_box_with_font(LONGUEUR/2-100, LARGEUR/2-50,"PARTIE %d/%d",font,9,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER, i+1, nb_partie);
		MLV_actualise_window();
		MLV_wait_seconds( 2 );
		MLV_clear_window(MLV_COLOR_BLACK);
		while(!(est_jeu_termine(&pos, &joueur_gagnant))){
			MLV_clear_window(MLV_COLOR_BLACK);
			afficher_position(&pos, hauteur, largeur,&epais);
			MLV_actualise_window();
			c = lire_coup(&pos,epais, hauteur, largeur,fichier);
			if(c.x != -1)
				jouer_coup(&pos, &c, hauteur, largeur);
		}
		MLV_clear_window(MLV_COLOR_BLACK);
		MLV_draw_adapted_text_box_with_font(240, 150,"PARTIE TERMINEE",font,9,MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER);
		if (joueur_gagnant == JOUEUR1)
			MLV_draw_text_with_font(200, 250,"Partie %d remporté par le JOUEUR 1",font,MLV_COLOR_GREEN, i+1);
		else
			MLV_draw_text_with_font(200, 250,"Partie %d remporté par le JOUEUR 2",font,MLV_COLOR_GREEN, i+1);
		MLV_actualise_window();
		MLV_wait_seconds( 3 );
		matchs(joueur_gagnant, &joueur1, &joueur2);
		free(pos.table.tab);
		i++;
	}while(i < nb_partie);
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_adapted_text_box_with_font(230, 150,"MATCH TERMINE %d - %d",font,9, MLV_COLOR_RED,MLV_COLOR_GREEN, MLV_COLOR_BLACK,MLV_TEXT_CENTER, joueur1, joueur2);
	if (joueur1 > joueur2)
		MLV_draw_text_with_font(205, 250,"Match remporté par le JOUEUR 1 !",font,MLV_COLOR_GREEN);

	
	else if (joueur1 < joueur2)
		MLV_draw_text_with_font(205, 250,"Match remporté par le JOUEUR 2 !",font,MLV_COLOR_GREEN,font);
	
	
	else
		MLV_draw_text_with_font(210, 250,"Pas de vainqueur MATCH NUL !",font,MLV_COLOR_GREEN,font);
	MLV_actualise_window();
	MLV_wait_seconds( 10 );
	
}
