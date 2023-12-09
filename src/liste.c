#include "liste.h"

Unite* alloueCellule(char camp, char type,int x,int y){
  Unite* ruche = malloc(sizeof(Unite));
  if (!ruche) {
    return NULL;
  }
  int force;
  switch(type){
    case 'r':
      force = FREINE;
      break;
    case 'o':
      force = FOUVRIERE;
      break;
    case 'e':
      force = FESCADRON;
      break;
    case 'g':
      force = FGUERRIERE;
      break;
    case 'f':
      force = FFRELON;
      break;
    default :
      force = 0;
      break;
  }
  (*ruche).camp = camp; (*ruche).type = type; (*roche).force = force;
  (*ruche).x = x; (*ruche).y = y;
  return ruche;
}

int rechercheDispo(UListe l, int* x, int* y){
  for (int i = -1; i< 2; i++){
    for (int j = -1; j< 2; j++){
      Uliste* depart = &l;
      do{
        if (l.x != x+i && l.y != y+j){
          *x = x+i; *y= y+j;
          return 1;
        }
        l = (*l).usuiv;
      } while(&l != depart)
    }
  }
  return 0;
}

int insereEnTete(UListe* l, char type, int x, int y){
  int x_val = x; int y_val = y;
  if (rechercheDispo(l,&x_val,&y_val) != 0){
    Unite* tete = alloueCellule((**l).camp,type,x_val,y_val);
  }
  if(!tete){
    return 0;
  }
  (**tete).uprec = (**l).uprec; (**tete).colprec = (**l).colprec;
  (**l).uprec = *tete; (**l).colprec = *tete;
  (**tete).usuiv = *l; (**tete).colsuiv = *l;
  return 1;
}

int suprimeCellule(UListe* l, char type, int posX, int posY){
  
}

void libereListe(UListe* l){
  
}
