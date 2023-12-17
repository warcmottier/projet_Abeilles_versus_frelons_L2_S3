#include "abeille.h"

void deplacement(UListe* unite, UListe* cases){
    UListe debut = *cases;
    
    if( *cases == NULL){
        (*unite)->posx = (*unite)->destx;
        (*unite)->posy = (*unite)->desty;
        (*unite)->destx = -1;
        (*unite)->desty = -1;

        *cases = *unite;
        (*cases)->vprec = NULL;
        (*cases)->vsuiv = NULL;
        
        return;
    }
    
    for(; (*cases)->vsuiv != NULL && (*unite)->type != (*cases)->type; *cases = (*cases)->vsuiv);

    if((*cases)->vsuiv == NULL){
        (*unite)->vprec = (*cases);
        (*cases)->vsuiv = *unite;
        return;
    }

    (*unite)->vsuiv = (*cases)->vsuiv;
    (*cases)->vsuiv->vprec = *unite;
    (*unite)->vprec = (*cases);
    (*cases)->vsuiv = *unite;

    (*cases) = debut;

    (*unite)->posx = (*unite)->destx;
    (*unite)->posy = (*unite)->desty;
}

void fonderCol(Case* cases){
    UListe ruche, debut = cases->occupant;

    for(; cases->occupant->type != RUCHE; cases->occupant = cases->occupant->uprec);

    ruche = cases->occupant;

    cases->occupant = debut;

    cases->occupant = extraitCellule(&cases->occupant);

    inserer(&ruche, &cases->occupant, ABEILLE, RUCHE, cases->occupant->posx, cases->occupant->posy);

    cases->colonie = cases->occupant->uprec;
    
}