/* Auteur : MBUMA MONA Nathan
 * création : 29/01/2019
 * modification : 02/03/2019*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define LONGUEUR 1200
#define LARGEUR 700
#include <MLV/MLV_all.h>

#define M 16
#define N 8



typedef enum{
    
    JOUEUR1,
    JOUEUR2
    
}Jouer;


typedef struct{
    int ** tab;
    
}Tablette;


typedef struct{
    Tablette table;
    Jouer tour;
    
    
}Position;



typedef struct{
    int x;
    int y;
}Coup;


/* fonction    : creer_tablette
 * parametres  : la hauteur ,largeur et le fichier
 * retour      : une tablette de chocolat
 * description : elle cree un tableau de type Tablette de taille
 * 				 largeur x hauteur et écrit la hauteur et
 * 				 la largeur  dans le fihier			  */
Tablette creer_tablette(int hauteur ,int largeur,FILE *fichier);

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

/* fonction    : afficher_position
 * parametres  : une position pos , hauteur,largeur et un pointeur sur epais 
 * retour      : rien
 * description : affiche une position en utilisant la bibliothèque graphique .*/

void afficher_position(Position *pos,int hauteur,int largeur,int *epais);

/* fonction    : lire_coup
 * parametres  : un pointeur sur une position , une  epaisseur , une  hauteur ,une largeur et un fichier
 * retour      : un Coup 
 * description : elle atteint  un clic de l’utilisateur sur la tablette de chocolat dans la fenêtre graphique
				 calcule et renvoie le coup spécifié par l’utilisateur. Si l’utilisateur ne clique pas sur
				 la tablette, ou bien clique sur un carré de chocolat déjà mangé, la fonction ne fait
				 rien et attend de traiter le prochain clic.*/
Coup lire_coup(Position *pos,int epais,int hauteur,int largeur,FILE *fichier);

/*fonction    : dimension_et_nb_parties
 *parametres   : un pointeur sur une  hauteur, un pointeur sur une largeur et un fichier
 *retour      : un entier
 *description : cette fonction génère des  boites de dialogue et récupère les éléments pour modifier
 les pointeurs qui sont passés en parametre et renvoie le nombre de partie*/
 
int dimension_et_nb_parties(int* hauteur, int* largeur,FILE *fichier);

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

/* fonction    : jouer_le jeu
 * paramteres  : la hauteur , la largeur , le nombre de partie et un fichier
 * retour      : rien
 * description : cette fonction fait appel à toutes les fonctions précedentes 
 * avec un algorithme simple tant que le joueur n'a pas mangé le chocolat on relance */ 
void joueur_le_jeu(int hauteur,int largeur,int nb_partie,FILE *fichier);

/* fonction    : matchs
 * paramteres  : le joueur gagnant et les 2 joueurs .
 * retour      : rien
 * description : incremente un joueur selon le nombre de victoire */ 
void matchs(Jouer joueur_gagnant, int* joueur1, int* joueur2);


/* fonction    : recupere_info
 * paramteres  : un fichier , la hauteur , la largeur et le nombre de partie 
 * retour      : un entier
 * description : modifie les parametres avec les éléments du fichier */ 
int recupere_info(FILE * fichier ,int *hauteur,int *largeur,int *nb_partie);

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



int recupere_info(FILE * fichier ,int *hauteur,int *largeur,int *nb_partie){
	int c;
	c =fscanf(fichier,"%d", nb_partie);
	
	c =fscanf(fichier , "%d", largeur);
	
	c = fscanf(fichier , "%d", hauteur);
	return c;
}
	
	
void matchs(Jouer joueur_gagnant, int* joueur1, int* joueur2){
	if (joueur_gagnant == JOUEUR1)
		*joueur1 = *joueur1 + 1;
	else
		*joueur2 = *joueur2 + 1;
}
	

