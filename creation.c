/* Auteur : MBUMA MONA Nathan
 * création : 29/01/2019
 * modification : 02/03/2019*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "creation.h"


Tablette creer_tablette(int hauteur,int largeur,FILE * fichier){
    int i, j;
    Tablette choco;
    assert(hauteur > 1);
    assert(largeur > 1);
    fprintf(fichier,"%d",largeur);
    fprintf(fichier,"\n%d\n",hauteur);
    choco.tab = malloc(hauteur * sizeof(int*));
    if (NULL == choco.tab)
		exit(EXIT_FAILURE);
	
    for(i = 0 ; i < hauteur ; i++){
		choco.tab[i] = malloc(largeur * sizeof(int));
		if (NULL == choco.tab[i])
		
			exit(EXIT_FAILURE);
			
        for(j = 0 ; j < largeur ; j++)
            choco.tab[i][j] = 1;
            
    }
    
    return choco;
    
}

int recupere_info(FILE * fichier ,int *hauteur,int *largeur,int *nb_partie){
	int c;
	c =fscanf(fichier,"%d", nb_partie);
	
	c =fscanf(fichier , "%d", largeur);
	
	c = fscanf(fichier , "%d", hauteur);
	return c;
}



int dimension_et_nb_parties(int* hauteur, int* largeur,FILE *fichier){
	char* j1;
	char* j2;
	char* haut;
	char* larg;
	int nb_partie = 0;
	MLV_Image *image;
	MLV_Font* font = MLV_load_font( "src/Garuda-Oblique.ttf" , 25 );
	image = MLV_load_image("src/f.jpg");
	MLV_resize_image_with_proportions(image, LONGUEUR, LARGEUR);
	MLV_draw_image(image, 0, 0);
	MLV_actualise_window();
	MLV_draw_text_with_font(
		10, 10,
		"Veuillez entrer la hauteur (ENTRE 1 ET 100) et la largeur ENTRE 1 ET 75) du plateau désirée. ",font,
		MLV_COLOR_GREEN
	);
	MLV_actualise_window();
	do{
		MLV_wait_input_box_with_font(
			10,70,
			200,90,
			MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
			"HAUTEUR : ",
			&haut,font
		);
	}while(!(0 < atoi(haut) && atoi(haut) <= 100));
	*hauteur = atoi(haut);
	do{
		MLV_wait_input_box_with_font(
			10,70,
			200,90,
			MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
			"LARGEUR : ",
			&larg,font
		);
	}while(!(0 < atoi(larg) && atoi(larg) <= 75));
	*largeur = atoi(larg);
	MLV_clear_window(MLV_COLOR_BLACK);
	image = MLV_load_image("src/f.jpg");
	MLV_resize_image_with_proportions(image, LONGUEUR, LARGEUR);
	MLV_draw_image(image, 0, 0);
	MLV_actualise_window();
	MLV_draw_text_with_font(
		10, 10,
		"Veuillez chacun entrer le nombre de parties désiré. (10 MAX)",font,
		MLV_COLOR_GREEN
	);
	MLV_actualise_window();
	do{
		MLV_wait_input_box_with_font(
			10,70,
			200,90,
			MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
			"JOUEUR 1 : ",
			&j1,font
		);
	}while(!(0 < atoi(j1) && atoi(j1) <= 10));
	do{
		MLV_wait_input_box_with_font(
			10,70,
			200,90,
			MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
			"JOUEUR 2 : ",
			&j2,font
		);
	}while(!(0 < atoi(j2) && atoi(j2) <= 10));
	
	nb_partie = (atoi(j1) + atoi(j2))/2;
	fprintf(fichier,"%d\n",nb_partie);
	return nb_partie;
}
