#ifndef __UNITE__
#define __UNITE__
#include "liste.h"

/**
 * @brief vérifie si il y a deja des occupant sur la case si oui alors il fais le chainage necessaire et fait bouger l'unite a la case voulue
 * 
 * @param unite 
 * @param cases
 * @return int
 */
int deplacement(UListe* unite, UListe* cases);

/**
 * @brief la reine fonde une colonie et la met dans la case ou elle se trouve
 *  
 * @param cases 
 */
void fonderCol(Case* cases);

#endif
