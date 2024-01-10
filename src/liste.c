#include "liste.h"

Unite* alloueCellule(char camp, char type){
  Unite* ruche = malloc(sizeof(Unite));

  if (!ruche) {
    return NULL;
  }

  switch(type){
    case REINE:
      ruche->force = FREINE;
      break;

    case OUVRIERE:
      ruche->force = FOUVRIERE;
      break;

    case ESCADRON:
      ruche->force = FESCADRON;
      break;

    case GUERRIERE:
      ruche->force = FGUERRIERE;
      break;

    case FRELONS:
      ruche->force = FFRELON;
      break;

    default :
      ruche->force = 0;
      break;
  }

  ruche->camp = camp; 
  ruche->type = type;
  ruche->posx = -1;
  ruche->posy = -1;
  ruche->destx = -1;
  ruche->desty = -1;
  ruche->production = 0;
  ruche->temps = 0;
  ruche->toursrestant = 0;

  ruche->uprec = NULL;
  ruche->usuiv = NULL;
  ruche->vprec = NULL;
  ruche->vsuiv = NULL;
  ruche->colprec = NULL;
  ruche->colsuiv = NULL;

  return ruche;
}

UListe initListe(char camp){
  UListe l = NULL, debut = NULL, tmp;


  if(camp == ABEILLE){
    
    //la premiere ruche
    tmp = alloueCellule(camp, RUCHE);

    if(!tmp){
      l = debut;
      return l;
    }

    l = tmp;
    l->posx = 0;
    l->posy = 0;

    debut = l;

    //la premiere reine
    tmp = alloueCellule(camp, REINE);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;
    
    l->posx = 1;
    l->posy = 1;
    l->force = FREINE;

    //la premiere ouvriere
    tmp = alloueCellule(camp, OUVRIERE);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;

    l->posx = 1;
    l->posy = 0;
    l->force = FOUVRIERE;

    //la premiere guerriere
    tmp = alloueCellule(camp, GUERRIERE);

    if(!tmp){
      l = debut;
      return l;
    }


    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;

    l->posx = 0;
    l->posy = 1;
    l->force = FGUERRIERE;

    l = debut;
  }

  else{

    //le premier nid
    tmp = alloueCellule(camp, NID);

    if(!tmp){
      return NULL;
    }

    l = tmp;

    l->posx = 11;
    l->posy = 17;

    debut = l;

    //la premiere reine
    tmp = alloueCellule(camp, REINE);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;

    l->posx = 10;
    l->posy = 16;
    l->force = FREINE;

    //premier frelon
    tmp = alloueCellule(camp, FRELONS);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;

    l->posx = 11;
    l->posy = 16;
    l->force = FFRELON;
    
    //deuxieme frelon
    tmp = alloueCellule(camp, FRELONS);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;

    l->posx = 10;
    l->posy = 17;
    l->force = FFRELON;

    l = debut;

  }
  
  return l;
}


UListe inserer(UListe* l, UListe* reine, char camp, char type, int x, int y){
  UListe tmp, debut;

  tmp = alloueCellule(camp, type);

  if(!tmp)
    return NULL; 
  
  tmp->destx = x;
  tmp->desty = y;
  debut = *l;

  // si la cellule n'est pas une ruche on l'insere avec les autre cellule de sont type
  if(type != RUCHE && type != NID){
  
    for(; (*l)->type != type && (*l)->usuiv != NULL; *l = (*l)->usuiv); 
  
    if((*l)->usuiv == NULL){
      tmp->uprec = *l;
      (*l)->usuiv = tmp;
    } 
  
    else{
      tmp->usuiv = (*l)->usuiv;
      (*l)->usuiv->uprec = tmp;
      tmp->uprec = *l;
      (*l)->usuiv = tmp;
    }
  } 
  
  //si c'est une ruche ou un nid on cree une nouvelle colonie avec sa reine
  else{

    tmp->posx = x;
    tmp->posy = y;
    tmp->destx = -1;
    tmp->desty = -1;

    if(*l == NULL){
      *l = tmp;
      return tmp;
    }

    for(; (*l)->colsuiv != NULL; *l = (*l)->colsuiv); 
  
    tmp->colprec = *l;
    (*l)->colsuiv = tmp;
    *l = (*l)->colsuiv;
    
    if(reine != NULL){
      (*reine)->uprec = *l;
      (*reine)->usuiv = NULL;
      (*l)->usuiv = *reine;
    }

  } 
  
  *l = debut;
  
  return tmp;
}

/**
 * @brief supprime la colonie dont l'adresse de la ruche ou du nid est l
 * 
 * @param l
 * @return int
 */
int suprimeColonie(UListe* l){
  UListe tmp;
  int fin = 0;
  
  //allez au fon de la colonie que l'on veut effacer
  for(; (*l)->usuiv != NULL; *l = (*l)->usuiv);

  //effacer un a un les cellule de la colonie a effacer
  while((*l)->type != RUCHE && (*l)->type != NID){
    tmp = *l;
    *l = (*l)->uprec;
    free(tmp);
  }

  //effacer la ruche ou le nid de la colonie
  tmp = *l;

  if((*l)->colprec == NULL && (*l)->colsuiv == NULL){
    *l = NULL;
    fin = 1;
  }

  else if((*l)->colprec == NULL){
    *l = tmp->colsuiv;
    (*l)->colprec = NULL;
  }
  
  else{
    
    *l = tmp->colprec;
    
    (*l)->colsuiv = tmp->colsuiv;
    
    if(tmp->colsuiv != NULL){
      tmp->colsuiv->colprec = *l;
    }

  }

  tmp->colprec = NULL;
  tmp->colsuiv = NULL;

  free(tmp);

  return fin;

}

int suprimeCellule(UListe* l){
  UListe tmp;
  int fin = 0;
  // si il faut supprimer une ruche ou un nid on supprime toute la colonie
  if((*l)->type == RUCHE || (*l)->type == NID){
    fin = suprimeColonie(l);
  }
  
  else{
    tmp = *l;
    
    //si on est a la fin de la liste
    if((*l)->usuiv == NULL){
      *l = (*l)->uprec;
      (*l)->usuiv = NULL;
    }

    else{
      (*l) = (*l)->uprec;
      (*l)->usuiv = tmp->usuiv;
      tmp->usuiv->uprec = *l;
    }
      
    free(tmp);
  }

  return fin;
}

UListe extraitCellule(UListe* l){
  UListe tmp;
    tmp = *l;
  
    //si on est a la fin de la liste
    if((*l)->usuiv == NULL){
      *l = (*l)->uprec;
      (*l)->usuiv = NULL;
    }

    else{
      (*l) = (*l)->uprec;
      (*l)->usuiv = tmp->usuiv;
      tmp->usuiv->uprec = *l;
    }

    tmp->uprec = NULL;
    tmp->usuiv= NULL;
      
    return tmp;
}

void libereListe(UListe* l){
  UListe tmp;
  
  if(*l == NULL)
    return;
  
  // aller a la dernier colonie;
  libereListe(&(*l)->colsuiv);

  // aller a la fin de la colonie
  for(; (*l)->usuiv != NULL; *l = (*l)->usuiv);

  //effacer un a un les cellule de la colonie a effacer
  while((*l)->uprec != NULL){
    tmp = *l;
    *l = (*l)->uprec;
    free(tmp);
  }

  free(*l);
}
