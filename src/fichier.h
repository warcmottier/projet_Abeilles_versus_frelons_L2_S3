#ifndef __FICHIER__
#define __FICHIER__
#include "unite.h"

/**
 * @brief charge la sauvegarde et renvoie le prochain joueur
 * 
 * @param nom
 * @param g
 * @return char
 */
char charger(char* nom,Grille * g);

/**
 * @brief sauvegarde la partie
 * 
 * @param nom
 * @param g
 * @param camp
 */
void sauvegarder(char* nom, Grille g, char camp);

#endif
