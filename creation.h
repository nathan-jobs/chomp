/* Auteur : MBUMA MONA Nathan
 * création : 01/03/2019
 * modification : 02/03/2019*/
 
#ifndef __creation__
#define __creation__

#define LONGUEUR 1200
#define LARGEUR 700
 
 typedef struct{
    int ** tab;
    
}Tablette;


/* fonction    : creer_tablette
 * parametres  : la hauteur ,largeur et le fichier
 * retour      : une tablette de chocolat
 * description : elle cree un tableau de type Tablette de taille
 * 				 largeur x hauteur et écrit la hauteur et
 * 				 la largeur  dans le fihier			  */
 
Tablette creer_tablette(int hauteur ,int largeur,FILE *fichier);



/* fonction    : recupere_info
 * paramteres  : un fichier , la hauteur , la largeur et le nombre de partie 
 * retour      : un entier
 * description : modifie les parametres avec les éléments lu dans le fichier */ 
int recupere_info(FILE * fichier ,int *hauteur,int *largeur,int *nb_partie);



/*fonction    : dimension_et_nb_parties
 *parametres   : un pointeur sur une  hauteur, un pointeur sur une largeur et un fichier
 *retour      : un entier
 *description : cette fonction génère des  boites de dialogue et récupère les éléments pour modifier
 les pointeurs qui sont passés en parametre et renvoie le nombre de partie*/
 
int dimension_et_nb_parties(int* hauteur, int* largeur,FILE *fichier);

#endif
