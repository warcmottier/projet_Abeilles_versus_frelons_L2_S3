#include "liste.h"

Unite* alloueCellule(char camp, char type){
  Unite* ruche = malloc(sizeof(Unite));

  if (!ruche) {
    return NULL;
  }

  switch(type){
    case 'r':
      ruche->force = FREINE;
      break;

    case 'o':
      ruche->force = FOUVRIERE;
      break;

    case 'e':
      ruche->force = FESCADRON;
      break;

    case 'g':
      ruche->force = FGUERRIERE;
      break;

    case 'f':
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
  UListe l, debut, tmp;


  if(camp == ABEILLE){
    // la tete
    l = alloueCellule(camp, 0);

    if(!l)
      return NULL;

    debut = l;    
    
    //la premiere ruche
    tmp = alloueCellule(camp, RUCHE);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;
    
    l->posx = 0;
    l->posy = 0;

    //la premiere reine
    tmp = alloueCellule(camp, REINE);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;
    
    l->posx = 2;
    l->posy = 0;
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
    l->posy = 1;
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

    l->posx = 1;
    l->posy = 0;
    l->force = FGUERRIERE;

    l = debut;
  }

  else{
    //la tete
    l = alloueCellule(camp, 0);

    if(!l){
      return l;
    }

    debut = l;

    //le premier nid
    tmp = alloueCellule(camp, NID);

    if(!tmp){
      return NULL;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;

    l->posx = 11;
    l->posy = 17;

    //la premiere reine
    tmp = alloueCellule(camp, REINE);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;
    l = l->usuiv;

    l->posx = 11;
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

    l->posx = 10;
    l->posy = 17;
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
    l->posy = 16;
    l->force = FFRELON;

    l = debut;

  }
  
  return l;
}


int inserer(UListe* l, UListe* reine, char camp, char type, int x, int y){
  UListe tmp, debut;

  tmp = alloueCellule(camp, type);  
  
  if(!tmp)
    return 0; 
  
  tmp->posx = x;
  tmp->posy = y;
  debut = *l; 
  
  if((*l)->type != RUCHE || (*l)->type != NID){
    *l = (*l)->usuiv;
  } 
  
  
  if(type != RUCHE){
  
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
  
  else{
  
    for(; (*l)->colsuiv != NULL; *l = (*l)->colsuiv); 
  
    tmp->colprec = *l;
    (*l)->colsuiv = tmp;

    *l = (*l)->colsuiv;

    (*reine)->uprec = *l;
    (*reine)->usuiv = NULL;
    (*l)->usuiv = *reine;
  } 
  
  *l = debut; 
  
  return 1;
}

/**
 * @brief supprime la colonie dont l'adresse de la ruche ou du nid est l
 * 
 * @param l 
 */
void suprimeColonie(UListe* l){
  UListe tmp;
  
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

  if((*l)->colprec == NULL){
    *l = (*l)->uprec;
    (*l)->usuiv = tmp->colsuiv;
    
  }
  else{
    
    *l = tmp->colprec;
    
    (*l)->colsuiv = tmp->colsuiv;
    
    if(tmp->colsuiv != NULL)
      tmp->colsuiv->colprec = *l;

  }

  free(tmp);

}

void suprimeCellule(UListe* l){
  UListe tmp;
  // si il faut supprimer une ruche ou un nid on supprime toute la colonie
  if((*l)->type == RUCHE || (*l)->type == NID)
    suprimeColonie(l);
  
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

  //effacer la tete de la structure
  if((*l)->type == 0){
    tmp = *l;
    *l = (*l)->usuiv;
    (*l)->uprec = NULL;
    free(tmp);
  }
  
  // aller a la dernier colonie;
  libereListe(&(*l)->colsuiv);

  
  for(; (*l)->usuiv != NULL; *l = (*l)->usuiv);//printf("coucou\n");

  //effacer un a un les cellule de la colonie a effacer
  while((*l)->uprec != NULL){
    tmp = *l;
    *l = (*l)->uprec;
    free(tmp);
  }

  free(*l);
}
