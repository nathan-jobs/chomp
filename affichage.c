/* Auteur : MBUMA MONA Nathan
 * création : 01/03/2019
 * modification : 02/03/2019*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define LONGUEUR 1200
#define LARGEUR 700
#include "affichage.h"

void afficher_position(Position *pos,int hauteur,int largeur,int *epais){
    Tablette tmp = pos->table;
	int i, j;
	int longueur = 0, larg = 0;
	MLV_Font* font = NULL;
	if(largeur > 50 || hauteur > 50)
		*epais = 8;
	
	else
		if(largeur > 38)
			*epais = 13 ;
		
		else
			*epais = 22;
	
	
	
	font = MLV_load_font( "src/Garuda-Oblique.ttf" , 25 );
	
	for(i = 0 ; i < hauteur ; i++){
		larg = 0;
		for(j = 0 ; j < largeur ; j++){
			if (tmp.tab[i][j] == 1){
				MLV_draw_filled_rectangle(10 + longueur, 17 + larg, *epais, *epais, MLV_COLOR_BROWN);
				
				
				larg = larg + *epais+1;
			}
		}
		
		longueur = longueur + *epais+1;
	}
	MLV_draw_filled_circle(10 + *epais / 2, 17 + *epais / 2, 3, MLV_COLOR_BLACK);
	if (pos->tour == JOUEUR1){
		
		MLV_draw_text_with_font(1000, 600  ,"JOUEUR 1",font, MLV_COLOR_YELLOW);
		
	}
	else{
		MLV_draw_text_with_font(1000, 600  ,"JOUEUR 2",font, MLV_COLOR_YELLOW);
		
	}
}


MLV_Color fabriqueCouleur(void){
	return MLV_rgba(255, 255, 255, 100);
}

int afficher_menu(void){
	MLV_Event event;
	int i = 1;
	int x, y;
	MLV_Image *image;
	MLV_Font* font = MLV_load_font( "src/Garuda-Oblique.ttf" , 35 );
	image = MLV_load_image("src/f.jpg");
	MLV_resize_image_with_proportions(image, LONGUEUR, LARGEUR);
	MLV_draw_image(image, 0, 0);
	MLV_actualise_window();
	MLV_draw_filled_rectangle(400, 215, 450, 50, fabriqueCouleur() );
	MLV_draw_text_with_font(490, 210,"JOUER", font, MLV_COLOR_GREEN);
	MLV_draw_filled_rectangle(400,275, 450, 50, fabriqueCouleur() );
	MLV_draw_text_with_font(420, 270,"CHARGER UNE PARTIE", font, MLV_COLOR_GREEN);
	MLV_draw_filled_rectangle(400, 333, 450, 50, fabriqueCouleur() );
	MLV_draw_text_with_font(490, 326,"QUITTER", font, MLV_COLOR_GREEN);
	
	MLV_actualise_window();
	do{
		event = MLV_get_event(
			NULL,NULL,NULL,
			NULL, NULL,
			&x,&y,NULL,
			NULL
		);
		if(event == MLV_MOUSE_BUTTON ){
			
			if((x>400 && y> 215) && (x<850 && y>210) &&  (x> 400 && y< 275) && (x<850 && y< 275))
				return 1;
			else if((x>400 && y> 275) && (x<850 && y> 260) &&  (x> 400 && y< 333) && (x<850 && y<333 ))
				return 2;
			else if((x>400 && y> 333) && (x<850 && y>320) &&  (x> 400 && y< 390) && (x<850 && y< 390))
			{
				MLV_clear_window(MLV_COLOR_BLACK);
				MLV_draw_filled_rectangle(LONGUEUR/2-100, LARGEUR/2-50, 250, 50, MLV_COLOR_WHITE);
				MLV_draw_text_with_font(LONGUEUR/2-85 , LARGEUR/2-50 ,"Au revoir  !!!", font, MLV_COLOR_RED);
				MLV_actualise_window();
				MLV_wait_seconds(5);
				MLV_free_window();
				exit(EXIT_FAILURE);
			}
		}
	}while(i);
	MLV_free_font( font );
	return 0;
}


