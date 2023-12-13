#ifndef __LISTE__
#define __LISTE__
#include <stdio.h>
#include <stdlib.h>
// Dimensions de la grille en nombre de cases (origine en haut a gauche) :
#define COLONNES 12
#define LIGNES 18

// Les deux camps :
#define ABEILLE 'A'
#define FRELON 'F'

// Les types d'unites :
#define REINE 'r'
#define OUVRIERE 'o'
#define ESCADRON 'e'
#define GUERRIERE 'g'
#define FRELONS 'f'
#define RUCHE 'R'
#define NID 'N'

// Pour la recolte de pollen
#define RECOLTE 'p'

// Les temps necessaires a la production :
#define TREINEA 8
#define TREINEF 8
#define TOUVRIERE 2
#define TGUERRIERE 4
#define TESCADRON 6
#define TFRELON 5
#define TRECOLTE 4

// Les couts necessaires a la production :
#define CREINEA 7
#define CREINEF 8
#define COUVRIERE 3
#define CGUERRIERE 5
#define CESCADRON 6
#define CFRELON 3
#define CRUCHE 10
#define CNID 10

// La force des unites
#define FREINE 6
#define FOUVRIERE 1
#define FGUERRIERE 5
#define FESCADRON 12
#define FFRELON 8

// La structure Unite :
typedef struct unite {
char camp; // ABEILLE ou FRELON
char type; // RUCHE, NID, REINE, OUVRIERE, GUERRIERE, ESCADRON ou FRELON
int force; // la force de l'unite
int posx, posy; // position actuelle sur la grille
int destx, desty; // destination (negatif si immobile)
char production; // production d'une ruche ou d'un nid et RECOLTE pour la recolte de pollen
int temps; // nombres de tours total pour cette production
int toursrestant; // tours restant pour cette production
struct unite *usuiv, *uprec; // liste des unites affiliees a une ruche ou un nid
struct unite *colsuiv, *colprec; // liste des autres ruches ou nids (colonies) du même camp
struct unite *vsuiv, *vprec; // liste des autres unites sur la meme case
} Unite, *UListe;

// La structure Case :
typedef struct {
Unite *colonie; // S'il y a une ruche ou un nid sur la case
UListe occupant; // les autres occupants de la case
} Case;

// La structure Grille :
typedef struct {
Case plateau[LIGNES][COLONNES];
UListe abeille, frelon;
int tour; // Numero du tour
int ressourcesAbeille, ressourcesFrelon;
} Grille;

/**
 * @brief alloue l'unite
 * 
 * @param camp 
 * @param type 
 * @param force
 * @return Unite* 
 */
Unite* alloueCellule(char camp, char type);

/**
 * @brief initialise la liste en debut de partie
 * 
 * @param camp 
 * @return UListe 
 */
UListe initListe(char camp);

/**
 * @brief insere en tête de la liste
 * 
 * @param l 
 * @param reine
 * @param camp
 * @param type 
 * @return int 
 */
int inserer(UListe* l, UListe* reine, char camp, char type);

/**
 * @brief extrais de la liste unite(u), colonie(c), ou combat(f) au coordonnées posX et posY
 * 
 * @param l 
 * @param unite 
 * @param posX 
 * @param posY 
 * @return UListe 
 */
UListe extraitCellule(UListe* l, char unite, int posX, int posY);

/**
 * @brief libere les liste unite, colonie, et combat
 * 
 * @param l 
 */
void libereListe(UListe* l);

#endif
