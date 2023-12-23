#include "unite.h"

int deplacement(UListe* unite, UListe* cases){
    UListe debut = *cases;
    
    // si la case est NULL on deplace l'unite dans la case
    if( *cases == NULL){
        (*unite)->posx = (*unite)->destx;
        (*unite)->posy = (*unite)->desty;
        (*unite)->destx = -1;
        (*unite)->desty = -1;

        *cases = *unite;
        (*cases)->vprec = NULL;
        (*cases)->vsuiv = NULL;
        
        return 1;
    }

    // si la case est pas vide et il y a deja une unite d'un autre camp sur la case on ne l'avance pas et on gerra le combat plus tard dans la boucle principale
    if((*cases)->camp != (*unite)->camp){
        return 0;
    }
    
    //on bouge l'unite sur la case deja occuper et on fais un chainage sur la 3eme liste chaine
    for(; (*cases)->vsuiv != NULL && (*unite)->type != (*cases)->type; *cases = (*cases)->vsuiv);

    if((*cases)->vsuiv == NULL){
        (*unite)->vprec = (*cases);
        (*cases)->vsuiv = *unite;
        return 1;
    }

    (*unite)->vsuiv = (*cases)->vsuiv;
    (*cases)->vsuiv->vprec = *unite;
    (*unite)->vprec = (*cases);
    (*cases)->vsuiv = *unite;

    (*cases) = debut;

    (*unite)->posx = (*unite)->destx;
    (*unite)->posy = (*unite)->desty;

    return 1;
}

void fonderCol(Case* cases){
    UListe ruche, debut = cases->occupant;

    //on trouve la ruche de la liste des unite dans laquelle on se trouve
    for(; cases->occupant->type != RUCHE; cases->occupant = cases->occupant->uprec);

    ruche = cases->occupant;

    cases->occupant = debut;

    //on extrait l'unite qui va fonder une colonie
    cases->occupant = extraitCellule(&cases->occupant);

    inserer(&ruche, &cases->occupant, cases->occupant->camp, ruche->type, cases->occupant->posx, cases->occupant->posy);

    //la nouvelle ruche se trouve sur la case dans la quelle elle se trouve
    cases->colonie = cases->occupant->uprec;
    
}