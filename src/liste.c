#include "liste.h"

Unite* alloueCellule(char camp, char type,int x,int y){
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

  ruche->camp = camp; ruche->type = type;

  ruche->posx = x; ruche->posy = y;

  ruche->uprec = NULL;
  ruche->usuiv = NULL;
  ruche->vprec = NULL;
  ruche->vsuiv = NULL;
  ruche->colprec = NULL;
  ruche->colsuiv = NULL;

  return ruche;
}

int rechercheDispo(UListe l, int* x, int* y){
  UListe depart = l;
  for (int i = -1; i< 2; i++){
    for (int j = -1; j< 2; j++){
      
      do{

        if (l->posx != *x+i && l->posy != *y+j){
          *x = *x+i; *y= *y+j;
          return 1;
        }

        l = (*l).usuiv;
        
      } while(l != depart);
    
    } 
  }
  return 0;
}

int insereEnTete(UListe* l, char camp, char type, char unite, int x, int y){
  int x_val = x; int y_val = y;

  /*if (rechercheDispo(*l,&x_val,&y_val) == 0){
    return 0;
  }*/

  UListe tete = alloueCellule(camp, type, x_val, y_val);

  if(!tete){
    return 0;
  }

  if(*l == NULL){
    *l = tete;
    return 1;
  }
  

  if(unite == 'u'){
    tete->usuiv = *l;
    (*l)->uprec = tete;
  
    *l = tete;
  }

  if(unite == 'c'){
    tete->colsuiv = *l;
    (*l)->colprec = tete;
    *l = tete;
  }

  return 1;
}

UListe extraitCellule(UListe* l, char unite, int posX, int posY){
  

}

void libereListe(UListe* l){
  
}
