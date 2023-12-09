#include "liste.h"

Unite* alloueCellule(char camp, char type){
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
  return ruche;
}

int insereEnTete(UListe* l, char type){
  Unite* tete = alloueCellule((**l).camp,type);
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
