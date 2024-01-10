#include "unite.h"


/**
 * @brief insere l'unite dans la 3eme liste chaine dans l'ordre des combat 
 * 
 * @param cases 
 * @param unite 
 */
void insererOrdre(Case* cases, UListe* unite){
    UListe debut = cases->occupant;

    if(cases->occupant == NULL){
        cases->occupant = *unite;
        cases->occupant->vsuiv = NULL;
        cases->occupant->vprec = NULL;
        return;
    }

    if((*unite)->camp == ABEILLE){
        
        //si l'unite est un escadron
        if((*unite)->type == ESCADRON){
            cases->occupant->vprec = *unite;
            (*unite)->vsuiv = cases->occupant;
            cases->occupant = *unite;
            return;
        }
        
        for(; cases->occupant->vsuiv != NULL && cases->occupant->type != ESCADRON; cases->occupant = cases->occupant->vsuiv);
        
        //si l'unite est une guerriere
        if((*unite)->type == GUERRIERE){

            if(cases->occupant->vsuiv == NULL){
                cases->occupant->vsuiv = *unite;
                (*unite)->vprec = cases->occupant;
            }

            else{
                (*unite)->vprec = cases->occupant->vprec;
                cases->occupant->vprec = *unite;
                (*unite)->vsuiv = cases->occupant;
                (*unite)->vprec->vsuiv = *unite;
            }

            cases->occupant = debut;
            return;
        }

        for(; cases->occupant->vsuiv != NULL && cases->occupant->type != GUERRIERE; cases->occupant = cases->occupant->vsuiv);

        //si l'unite est une reine

        if((*unite)->type == REINE){
            if(cases->occupant->vsuiv == NULL){
                cases->occupant->vsuiv = *unite;
                (*unite)->vprec = cases->occupant;
            }

            else{
                (*unite)->vprec = cases->occupant->vprec;
                cases->occupant->vprec = *unite;
                (*unite)->vsuiv = cases->occupant;
                (*unite)->vprec->vsuiv = *unite;
            }

            cases->occupant = debut;
            return;
        }

        for(; cases->occupant->vsuiv != NULL && cases->occupant->type != REINE; cases->occupant = cases->occupant->vsuiv);

        //si l'unite est une ouvriere

        if(cases->occupant->vsuiv == NULL){
            cases->occupant->vsuiv = *unite;
            (*unite)->vprec = cases->occupant;
        }

        else{
            (*unite)->vprec = cases->occupant->vprec;
            cases->occupant->vprec = *unite;
            (*unite)->vsuiv = cases->occupant;
            (*unite)->vprec->vsuiv = *unite;
        }
    }

    else{

        //si l'unite est un frelon
        if((*unite)->type == FRELONS){
            cases->occupant->vprec = *unite;
            (*unite)->vsuiv = cases->occupant;
            cases->occupant = *unite;
            return;
        }

        for(; cases->occupant->vsuiv != NULL && cases->occupant->type != FRELONS; cases->occupant = cases->occupant->vsuiv);

        //si l'unite est une reine

        if(cases->occupant->vsuiv == NULL){
            cases->occupant->vsuiv = *unite;
            (*unite)->vprec = cases->occupant;
        }

        else{
            (*unite)->vprec = cases->occupant->vprec;
            cases->occupant->vprec = *unite;
            (*unite)->vsuiv = cases->occupant;
            (*unite)->vprec->vsuiv = *unite;
        }
    }

    cases->occupant = debut;
}

void rechainerCaseActuelle(Case* casesActuelle, UListe *unite){
    UListe debut = casesActuelle->occupant;

    
    if(casesActuelle->occupant->vsuiv == NULL && casesActuelle->occupant->vprec == NULL){
        casesActuelle->occupant = NULL;
        return;
    }

    for(; casesActuelle->occupant != *unite; casesActuelle->occupant = casesActuelle->occupant->vsuiv);

    if(casesActuelle->occupant->vprec == NULL){
        casesActuelle->occupant = (*unite)->vsuiv;
        casesActuelle->occupant->vprec = NULL;
    }
    
    else if(casesActuelle->occupant->vsuiv == NULL){
        casesActuelle->occupant = (*unite)->vprec;
        casesActuelle->occupant->vsuiv = NULL;
        casesActuelle->occupant = debut;
    }

    else{
        casesActuelle->occupant->vprec->vsuiv = (*unite)->vsuiv;
        casesActuelle->occupant->vsuiv->vprec = (*unite)->vprec;
        casesActuelle->occupant = debut;
    }

    (*unite)->vprec = NULL;
    (*unite)->vsuiv = NULL;
}

int deplacement(UListe* unite, Case* casesFuture, Case* casesActuelle){
    // si la case est NULL on deplace l'unite dans la cas

    if( casesFuture->colonie == NULL && casesFuture->occupant == NULL){
        if(casesActuelle != NULL)
            rechainerCaseActuelle(casesActuelle, unite);

        (*unite)->posx = (*unite)->destx;
        (*unite)->posy = (*unite)->desty;
        (*unite)->destx = -1;
        (*unite)->desty = -1;

        casesFuture->occupant = *unite;
        casesFuture->occupant->vprec = NULL;
        casesFuture->occupant->vsuiv = NULL;

        return 1;
    }


    // si la case est pas vide et il y a deja une unite d'un autre camp sur la case on ne l'avance pas et on gerra le combat plus tard dans la boucle principale
    if((casesFuture->occupant != NULL && casesFuture->occupant->camp != (*unite)->camp) || (casesFuture->colonie != NULL && casesFuture->colonie->camp != (*unite)->camp)){
        return 0;
    }
    

    //on bouge l'unite sur la case deja occuper et on fais un chainage sur la 3eme liste chaine
    if(casesActuelle != NULL)
        rechainerCaseActuelle(casesActuelle, unite);
    
    (*unite)->posx = (*unite)->destx;
    (*unite)->posy = (*unite)->desty;
    (*unite)->destx = -1;
    (*unite)->desty = -1;
    
    insererOrdre(casesFuture, unite);

    return 1;
}

void fonderCol(Case* cases, UListe* unite){
    UListe ruche, debut = cases->occupant, reine;
    //on trouve la ruche de la liste des unite dans laquelle on se trouve
    
    for(; cases->occupant->type != RUCHE && cases->occupant->type != NID; cases->occupant = cases->occupant->uprec);

    ruche = cases->occupant;

    cases->occupant = debut;

    //on extrait l'unite qui va fonder une colonie
    reine = extraitCellule(unite);

    inserer(&ruche, &reine, cases->occupant->camp, ruche->type, cases->occupant->posx, cases->occupant->posy);

    //la nouvelle ruche se trouve sur la case dans la quelle elle se trouve
    cases->colonie = reine->uprec;
    //printf("%p\n", reine->uprec);
    
}