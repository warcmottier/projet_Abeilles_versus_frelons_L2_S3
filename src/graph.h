#ifndef __GRAPH__
#define __GRAPH__
#include "MLV/MLV_all.h"
#include "liste.h"
#include "fichier.h"

/**
 * @brief affiche le plateaux de jeux
 * 
 * @param plateau
 */
void affichePlateaux(Grille plateau);

/**
 * @brief affiche le menue des reine et renvoie en char l'action voulue et modifie x et y si l'uniter se deplace 
 * et retourne l'action voulue
 * 
 * @param x 
 * @param y
 * @param posX
 * @param posY
 * @param ressource
 * @param camp
 * @param colonie
 * @return char 
 */
char menueReine(int* x, int* y, int posX, int posY, int ressource, char camp, UListe colonie);

/**
 * @brief affiche le menue des guerriere escadron et frelon et renvoie en char l'action voulue et modifie x et y si l'uniter se deplace 
 * et retourne l'action voulue
 * 
 * @param x 
 * @param y 
 * @param posX
 * @param posY
 * @param type
 * @param ressource
 * @param camp
 * @return char 
 */
char menueGEF(int* x, int* y, int posX, int posY, char type, int ressource, char camp);


/**
 * @brief affiche le menue des ouvirere et renvoie en char l'action voulue et modifie x et y si l'uniter se deplace
 * et retourne l'action voulue
 * 
 * @param x 
 * @param y 
 * @param posX
 * @param posY
 * @param ressource
 * @return char 
 */
char menueOuvriere(int* x, int* y, int posX, int posY, int ressource);

/**
 * @brief affiche le menue ds nid des frolon et retourne l'action voulue
 * 
 * @param posX 
 * @param posY 
 * @param ressource 
 * @return char 
 */
char menueNid(int posX, int posY, int ressource);

/**
 * @brief affiche le menue des Ruche et retourne l'action voulue
 * 
 * @param posX 
 * @param posY 
 * @param ressource 
 * @return char 
 */
char menueRuche(int posX, int posY, int ressource);

/**
 * @brief propose au joueur si il veut sauvegarder si oui il sauvegarde
 * 
 * @param camp 
 * @param plateau
 * @param nom
 */
void menueSauv(char camp, Grille plateau, char* nom);

/**
 * @brief propose au joueur de quitter si il le shouhaite
 * 
 * @param camp 
 * @return char 
 */
char quit(char camp);

#endif
