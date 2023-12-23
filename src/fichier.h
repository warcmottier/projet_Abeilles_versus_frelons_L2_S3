#ifndef __FICHIER__
#define __FICHIER__
#include "unite.h"

/**
 * @brief ouvre le fichier de sauvegarde et si il existe pas il le crée
 * 
 * @param nom 
 * @return FILE* 
 */
FILE* ouvreFichier(char* nom);

/**
 * @brief charge la sauvegarde
 * 
 * @param f 
 */
void charger(FILE* f);

/**
 * @brief sauvegarde la partie (a ajouter les argument que l'on aura besoin dans le prototype)
 * 
 * @param f 
 */
void sauvegarder(FILE* f);

#endif
