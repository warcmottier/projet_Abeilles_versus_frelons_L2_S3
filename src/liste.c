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

    //la premiere escadron
    tmp = alloueCellule(camp, ESCADRON);

    if(!tmp){
      l = debut;
      return l;
    }

    l->usuiv = tmp;
    tmp->uprec = l;

    l = l->usuiv;

    l->posx = 0;
    l->posy = 1;
    l->force = FESCADRON;

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

    l = debut;
  }
  
  return l;
}

/* marche pas

int rechercheDispo(UListe l, int* x, int* y){
  for (int i = -1; i< 2; i++){
    for (int j = -1; j< 2; j++){
      
      do{

        if (l->posx != *x+i && l->posy != *y+j){
          *x = *x+i; *y= *y+j;
          return 1;
        }

        l = (*l).usuiv;
        
      } while(l != NULL);
    
    } 
  }
  return 0;
}
*/

int inserer(UListe* l, UListe* reine, char camp, char type){
  UListe tmp, debut;
  int x, y; 

  tmp = alloueCellule(camp, type);  
  
  if(!tmp)
    return 0; 
  
  debut = *l; 
  
  if((*l)->type != RUCHE || (*l)->type != NID){
    *l = (*l)->usuiv;
  } 
  
  
  if(type != RUCHE){

    x = (*l)->posx;
    y = (*l)->posy;

    //trouver la case vide la plus proche possible de la ruche (a du mal)
  
    for(; (*l)->type != type && (*l)->usuiv != NULL; *l = (*l)->usuiv); 
  
    if((*l)->usuiv == NULL){
      tmp->uprec = *l;
      (*l)->usuiv = tmp;
    } 
  
    else{
      tmp->usuiv = (*l)->usuiv;
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