#ifndef __GAME__
#define __GAME__
#include "unite.h"
#include "fichier.h"
#include "graph.h"

/**
 * @brief fais le combat avant de deplacer l'uniter et retourne 1 si l'unite est vivante 0 sinon
 * 
 * @param cases 
 * @param unite
 * @param plateau
 * @return int
 */
int combat(Case* cases, UListe* unite, Grille* plateau);

/**
 * @brief initialise la structure Grille
 * 
 * @param plateau 
 */
void initGrille(Grille* plateau);


/**
 * @brief effectue le tour des abeille
 * 
 * @param plateau 
 */
void tourAbeille(Grille* plateau);

/**
 * @brief effectue le tour des frelon
 * 
 * @param plateau 
 */
void tourFrelon(Grille* plateau);

#endif
