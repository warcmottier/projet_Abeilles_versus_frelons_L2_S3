#ifndef __UNITE__
#define __UNITE__
#include "liste.h"

/**
 * @brief vérifie si il y a deja des occupant sur la case si oui alors il fais le chainage necessaire et fait bouger l'unite a la case voulue
 * 
 * @param unite 
 * @param casesFuture
 * @param casesActuelle
 * @return int
 */
int deplacement(UListe* unite, Case* casesFuture, Case* casesActuelle);

/**
 * @brief la reine fonde une colonie et la met dans la case ou elle se trouve
 *  
 * @param cases
 * @param reine
 */
void fonderCol(Case* cases, UListe* reine);

/**
 * @brief rechaine la case actuelle ou unite va disparaitre
 * 
 * @param casesActuelle 
 * @param unite 
 */
void rechainerCaseActuelle(Case* casesActuelle, UListe *unite);

#endif
