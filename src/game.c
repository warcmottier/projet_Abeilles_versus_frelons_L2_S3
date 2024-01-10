#include "game.h"

/**
 * @brief retire des case les uniote qui vons etre effacer
 * 
 * @param col
 */
void supprimeCasesColonie(UListe* col, Grille* plateau){
    UListe debut = *col;
    
    for(; *col != NULL; *col = (*col)->usuiv){
        if((*col)->type == RUCHE || (*col)->type == NID){
            continue;
        }
        rechainerCaseActuelle(&plateau->plateau[(*col)->posx][(*col)->posy], col);
    }
    *col = debut;
}

int combat(Case* cases, UListe* unite, Grille* plateau){
    UListe courant, debut = cases->occupant, ruche = cases->colonie;
    int fin = 0;
    
    // on regarde si il y a des occupant

    if(cases->occupant != NULL){
        
        while(cases->occupant != NULL){

            // on sauvegarde l'unite qui va combatre et on avance dans case occuper pour que se soit plus simple a gere en cas de defaire
            courant = cases->occupant;  
            cases->occupant = cases->occupant->vsuiv;

            if(courant->force * (rand() % 10 + 1) > (*unite)->force * (rand() % 10 + 1)){
                
                
                //on met a jour les ressource frelon si c'est une abeille qui perd
                if((*unite)->camp == ABEILLE){

                    switch ((*unite)->type){
                    case ESCADRON:
                        plateau->ressourcesFrelon += 6;
                        break;
                    
                    case GUERRIERE:
                        plateau->ressourcesFrelon += 5;
                        break;
                    
                    case REINE:
                        plateau->ressourcesFrelon += 7;
                        break;
                    
                    case OUVRIERE:
                        plateau->ressourcesFrelon += 3;
                    
                    default:
                        break;
                    }
                }
                
                suprimeCellule(unite);
                cases->occupant = debut;
                return 0;
            }

            else{
                if(cases->occupant != NULL)
                    cases->occupant->vprec = NULL;

                //on met a jour les ressource frelon si c'est une abeille qui perd
                if(courant->camp == ABEILLE){

                    switch ((*unite)->type){
                    case ESCADRON:
                        plateau->ressourcesFrelon += 6;
                        break;
                    
                    case GUERRIERE:
                        plateau->ressourcesFrelon += 5;
                        break;
                    
                    case REINE:
                        plateau->ressourcesFrelon += 7;
                        break;
                    
                    case OUVRIERE:
                        plateau->ressourcesFrelon += 3;
                    
                    default:
                        break;
                    }

                }
                
                suprimeCellule(&courant);
                debut = cases->occupant;
            }
        }
    }

    //on regarde si il y a un nid ou une ruche et on la supprime
    if(cases->colonie != NULL){

        if(cases->colonie->camp == ABEILLE){
            ruche = ruche->usuiv;
            
            for(; ruche != NULL; ruche = ruche->usuiv){
                switch (ruche->type){
                    case ESCADRON:
                        plateau->ressourcesFrelon += 6;
                        break;
                    
                    case GUERRIERE:
                        plateau->ressourcesFrelon += 5;
                        break;
                    
                    case REINE:
                        plateau->ressourcesFrelon += 7;
                        break;
                    
                    case OUVRIERE:
                        plateau->ressourcesFrelon += 3;
                    
                    default:
                        break;
                    }
            }

        }
        

        supprimeCasesColonie(&cases->colonie, plateau);

        plateau->abeille = cases->colonie->colsuiv;

        fin  = suprimeCellule(&cases->colonie);
        cases->colonie = NULL;

        
    }

    deplacement(unite, cases, &plateau->plateau[(*unite)->posy][(*unite)->posx]);

    //si c'est uune reine frelon elle transforme la ruche en un nid de frelon
    if((*unite)->camp == FRELON && (*unite)->type == REINE){
        fonderCol(cases, unite);
    }

    return fin;

}

void initGrille(Grille* plateau){
    UListe debut;
    
    for(int i = 0; i < LIGNES; i++){
        for(int j = 0; j < COLONNES; j++){
            plateau->plateau[i][j].colonie = NULL;
            plateau->plateau[i][j].occupant = NULL;
        }
    }

    plateau->tour = 0;
    plateau->ressourcesAbeille = 20;
    plateau->ressourcesFrelon = 20;
    plateau->abeille = initListe(ABEILLE);
    plateau->frelon = initListe(FRELON);

    debut = plateau->abeille;
    plateau->plateau[0][0].colonie = plateau->abeille;
    plateau->abeille = plateau->abeille->usuiv;

    for(; plateau->abeille != NULL; plateau->abeille = plateau->abeille->usuiv){
        plateau->plateau[plateau->abeille->posy][plateau->abeille->posx].occupant = plateau->abeille;
    }

    plateau->abeille = debut;

    debut = plateau->frelon;
    plateau->plateau[17][11].colonie = plateau->frelon;
    plateau->frelon = plateau->frelon->usuiv;

    for(; plateau->frelon != NULL; plateau->frelon = plateau->frelon->usuiv){
        plateau->plateau[plateau->frelon->posy][plateau->frelon->posx].occupant = plateau->frelon;
    }

    plateau->frelon = debut;
}

void tourAbeille(Grille* plateau){
    UListe debut = plateau->abeille, ruche, new;
    int x = -1, y = -1;
    char c;

    //on donne les ordre de toute les ruche

    affichePlateaux(*plateau);


    for(; plateau->abeille != NULL; plateau->abeille = plateau->abeille->colsuiv){
        ruche = plateau->abeille;

        affichePlateaux(*plateau);

        //fonction de choix d'ordre pour les ruche renvoi le type de l'uniter
        c = menueRuche(plateau->abeille->posx, plateau->abeille->posy, plateau->ressourcesAbeille);


        if(c != 0){
            switch (c){
                case 'e':
                    plateau->ressourcesAbeille -= CESCADRON;
                    plateau->abeille->production = ESCADRON;
                    plateau->abeille->temps = TESCADRON;
                    plateau->abeille->toursrestant = TESCADRON;
                    break;
                
                case 'g':
                    plateau->ressourcesAbeille -= CGUERRIERE;
                    plateau->abeille->production = GUERRIERE;
                    plateau->abeille->temps = TGUERRIERE;
                    plateau->abeille->toursrestant = TGUERRIERE;
                    break;
                
                case 'r':
                    plateau->ressourcesAbeille -= CREINEA;
                    plateau->abeille->production = REINE;
                    plateau->abeille->temps = TREINEA;
                    plateau->abeille->toursrestant = TREINEA;
                    break;
                
                case 'o':
                    plateau->ressourcesAbeille -= COUVRIERE;
                    plateau->abeille->production = OUVRIERE;
                    plateau->abeille->temps = TOUVRIERE;
                    plateau->abeille->toursrestant = TOUVRIERE;
                    break;
                
                default:
                    break;
            }
        }

        //on met a jour les production des ruche et on ajoute la nouvelle unite si besoin
        if(plateau->abeille->production != 0){
            plateau->abeille->toursrestant--;

            if(plateau->abeille->toursrestant == 0){
                new = inserer(&plateau->abeille, NULL, ABEILLE, plateau->abeille->production, plateau->abeille->posx, plateau->abeille->posy);

                deplacement(&new, &plateau->plateau[new->desty][new->destx], NULL);

                plateau->abeille->production = 0;
                plateau->abeille->temps = 0;
            }
        }
    }

    plateau->abeille = ruche;

    if(plateau->abeille->colprec == NULL && plateau->abeille->usuiv == NULL)
        return;

    //ordre de toute les unite
    for(; plateau->abeille != NULL; plateau->abeille = plateau->abeille->colprec){
        ruche = plateau->abeille;
        
        for(;plateau->abeille != NULL; plateau->abeille = plateau->abeille->usuiv){

            affichePlateaux(*plateau);

            switch (plateau->abeille->type){
            
                case ESCADRON:
                    //ordre de l'escadront
                    c = menueGEF(&x, &y, plateau->abeille->posx, plateau->abeille->posy, ESCADRON, plateau->ressourcesAbeille, ABEILLE);
                    
                    if(x != -1 && y != -1){
                        plateau->abeille->destx = x;
                        plateau->abeille->desty = y;

                        if(deplacement(&plateau->abeille, &plateau->plateau[y][x], &plateau->plateau[plateau->abeille->posy][plateau->abeille->posx]) == 0)
                            combat(&plateau->plateau[y][x], &plateau->abeille, plateau);
                        
                        x = -1;
                        y = -1;
                    }

                    break;
                
                case REINE:
                    // ordre de la reine
                    
                    c = menueReine(&x, &y, plateau->abeille->posx, plateau->abeille->posy, plateau->ressourcesAbeille, ABEILLE, plateau->plateau[plateau->abeille->posy][plateau->abeille->posx].colonie);

                    if(c == 'f'){
                        plateau->ressourcesAbeille -= CRUCHE;
                        fonderCol(&plateau->plateau[plateau->abeille->posy][plateau->abeille->posx], &plateau->abeille);
                    }

                    else if(x != -1 && y != -1){
                        plateau->abeille->destx = x;
                        plateau->abeille->desty = y;
                        
                        if(deplacement(&plateau->abeille, &plateau->plateau[y][x], &plateau->plateau[plateau->abeille->posy][plateau->abeille->posx]) == 0){
                            combat(&plateau->plateau[y][x], &plateau->abeille, plateau);
                        }
                        
                        x = -1;
                        y = -1;

                    }

                    break;
                
                case GUERRIERE:
                    // ordre des guerriere
                    c = menueGEF(&x, &y, plateau->abeille->posx, plateau->abeille->posy, GUERRIERE, plateau->ressourcesAbeille, ABEILLE);
                    
                    if(x != -1 && y != -1){
                        plateau->abeille->destx = x;
                        plateau->abeille->desty = y;
                        
                        if(deplacement(&plateau->abeille, &plateau->plateau[y][x], &plateau->plateau[plateau->abeille->posy][plateau->abeille->posx]) == 0)
                            combat(&plateau->plateau[y][x], &plateau->abeille, plateau);
                        
                        x = -1;
                        y = -1;
                    }

                    break;
                
                case OUVRIERE:
                    
                    // on regarde si l'ouvriere produit du pollen
                    if(plateau->abeille->production == RECOLTE){
                        plateau->ressourcesAbeille++;
                        plateau->abeille->toursrestant--;

                        if(plateau->abeille->toursrestant == 0){
                            plateau->abeille->production = 0;
                            plateau->abeille->temps = 0;
                            suprimeCellule(&plateau->abeille);
                        }

                        break;
                    }

                    // ordre ouvriere
                    c = menueOuvriere(&x, &y, plateau->abeille->posx, plateau->abeille->posy, plateau->ressourcesAbeille);

                    if(x != -1 && y != -1){
                        plateau->abeille->destx = x;
                        plateau->abeille->desty = y;      
                        if(deplacement(&plateau->abeille, &plateau->plateau[y][x], &plateau->plateau[plateau->abeille->posy][plateau->abeille->posx]) == 0)
                            combat(&plateau->plateau[y][x], &plateau->abeille, plateau);
                        
                        x = -1;
                        y = -1;
                    }

                    else if(c == 'r'){
                        plateau->abeille->production = RECOLTE;
                        plateau->abeille->temps = TRECOLTE;
                        plateau->abeille->toursrestant = TRECOLTE;
                    }

            
            default:
                break;
            }
            
        }

        plateau->abeille = ruche;
    }

    plateau->abeille = debut;

}


void tourFrelon(Grille* plateau){
    UListe debut = plateau->frelon, ruche, new;
    int x = -1, y = -1;
    char c;

    //on donne les ordre de tout les nid

    affichePlateaux(*plateau);

    for(; plateau->frelon != NULL; plateau->frelon = plateau->frelon->colsuiv){
        ruche = plateau->frelon;

        //fonction d'ordre pour les nid renvoie le type de l'uniter
        c = menueNid(plateau->frelon->posx, plateau->frelon->posy, plateau->ressourcesFrelon);

        switch (c){
            case 'f':
                plateau->ressourcesFrelon -= CFRELON;
                plateau->frelon->production = FRELONS;
                plateau->frelon->temps = TFRELON;
                plateau->frelon->toursrestant = TFRELON;
                break;
        
            case 'r':
                plateau->ressourcesFrelon -= CREINEF;
                plateau->frelon->production = REINE;
                plateau->frelon->temps = TFRELON;
                plateau->frelon->toursrestant = TFRELON;
                break;
        }

        // on met a jour les production des nid et on ajouter une unite si besoin

        if(plateau->frelon->production != 0){
            plateau->frelon->toursrestant--;
            if(plateau->frelon->toursrestant == 0){
                new = inserer(&plateau->frelon, NULL, FRELON, plateau->frelon->production, plateau->frelon->posx, plateau->frelon->posy);

                deplacement(&new, &plateau->plateau[new->desty][new->destx], NULL);

                plateau->frelon->production = 0;
                plateau->frelon->temps = 0;
            }
        }

    }

    plateau->frelon = ruche;

    if(plateau->frelon->colprec == NULL && plateau->frelon->usuiv == NULL)
        return;

    //ordre de toute les unite
    for(; plateau->frelon != NULL; plateau->frelon = plateau->frelon->colprec){
        ruche = plateau->frelon;

        for(; plateau->frelon != NULL; plateau->frelon = plateau->frelon->usuiv){

            affichePlateaux(*plateau);

            switch (plateau->frelon->type){
            case FRELONS:
                //ordre des frelon

                c = menueGEF(&x, &y, plateau->frelon->posx, plateau->frelon->posy, FRELONS, plateau->ressourcesFrelon, FRELON);
                    
                if(x != -1 && y != -1){
                    plateau->frelon->destx = x;
                    plateau->frelon->desty = y;

                    if(deplacement(&plateau->frelon, &plateau->plateau[y][x], &plateau->plateau[plateau->frelon->posy][plateau->frelon->posx]) == 0){
                        if(combat(&plateau->plateau[y][x], &plateau->frelon, plateau) == 1){
                            plateau->abeille = NULL;
                            plateau->frelon = debut;
                            return;
                        }
                    }
                    
                    x = -1;
                    y = -1;
                }
                
                break;
            
            case REINE:
                //odre de la reine
                c = menueReine(&x, &y, plateau->frelon->posx, plateau->frelon->posy, plateau->ressourcesFrelon, FRELON, plateau->plateau[plateau->frelon->posx][plateau->frelon->posy].colonie);

                if(x != -1 && y != -1){
                    plateau->frelon->destx = x;
                    plateau->frelon->desty = y;
                    
                    if(deplacement(&plateau->frelon, &plateau->plateau[y][x], &plateau->plateau[plateau->frelon->posy][plateau->frelon->posx]) == 0)
                        if(combat(&plateau->plateau[y][x], &plateau->frelon, plateau) == 1){
                            plateau->abeille = NULL;
                            plateau->frelon = debut;
                            return;
                        }
                        
                    
                    x = -1;
                    y = -1;
                }

                else if(c == 'f'){
                    fonderCol(&plateau->plateau[plateau->frelon->posy][plateau->frelon->posx], &plateau->frelon);
                }
                
                break;
            
            default:
                break;
            }
        }

        plateau->frelon = ruche;
    }

    plateau->frelon = debut;

}
