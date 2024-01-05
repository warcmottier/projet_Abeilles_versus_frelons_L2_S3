#include "fichier.h"

UListe inserer_charg(UListe* l, UListe* reine, char camp, char type, int x, int y){
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
  
    for(; (*l)->colsuiv != NULL; *l = (*l)->colsuiv); 
  
    tmp->colprec = *l;
    (*l)->colsuiv = tmp;

    *l = (*l)->colsuiv;

    (*reine)->uprec = *l;
    (*reine)->usuiv = NULL;
    (*l)->usuiv = *reine;
  } 
  
  *l = debut;
  
  return tmp;
}

char charger(char* nom, Grille * g){
  FILE * sesame;
  char joueur,camp,type,prod;
  int tank,nb_ligne = 0,compteur_char = 0,x,y,tours_restant,taille_int1 = 0,taille_int2=0,tmp;
  sesame = fopen(*nom,"r");
  if (sesame == NULL){
    //la sauvegarde n'existe pas
    return NULL;
  } else {
    while((tank = fgetc(sesame))!=EOF){
        //pour savoir sur quel caractère de la ligne nous sommes
        if (tank == '\n'){
            compteur_char = 0;
            nb_ligne ++;
        } else {
            compteur_char ++;
        }
        //si on est sur la première ligne
        if (nb_ligne == 0){
            if (tank != ' '){
                if (compteur_char == 1){
                    joueur = tank;
                }
                if (compteur_char == 3){
                    do{
                        if (taille_int1>0){
                            tmp = tmp*10 + tank-'0';
                            taille_int1++;
                        } else {
                            tmp = tank - '0';
                            taille_int1++;
                        } 
                        tank = fgetc(sesame);
                        compteur_char++;
                    } while (tank!= ' ' || tank != '\n');
                }
                switch (joueur){
                    case ABEILLE :
                        (*g).ressourcesAbeille = tmp;
                        break;
                    case FRELON :
                        (*g).ressourcesFrelon = tmp;
                        break;   
                }
                if (compteur_char == 5+taille_int1+1){//la position du chiffre précédent, la taille du chiffre et un espace
                    taille_int1 = 0;
                    do{
                        if (taille_int2>0){
                            tmp = tmp*10 + tank-'0';
                            taille_int2++;
                        } else {
                            tmp = tank - '0';
                            taille_int2++;
                        } 
                        tank = fgetc(sesame);
                        compteur_char++;
                    } while (tank!= ' ' || tank != '\n');
                } 
                switch (joueur){
                    case ABEILLE :
                        (*g).ressourcesFrelon = tmp;    
                    case FRELON :
                        (*g).ressourcesAbeille = tmp;
                }
            }
        } else { //le reste du fichier de sauvegarde
            if (compteur_char == 0 && nb_ligne > 2){
                switch (camp){
                    case ABEILLE:
                        if(inserer(&(*g).abeille,NULL,camp,type,x,y) == NULL){
                            fprintf(stderr,"plus de mémoire");
                            return NULL;
                        } else {
                            (*g).abeille;
                        }
                    case FRELON:
                        if(inserer(&(*g).frelon,NULL,camp,type,x,y) == NULL){
                            fprintf(stderr,"plus de mémoire");
                            return NULL;
                        }
                }
            } else if (compteur_char == 1){
                camp = tank;
            } else if (compteur_char == 3){
                type = tank;
            } else if (compteur_char == 5){
                do{
                    if (taille_int1>0){
                        tmp = tmp*10 + tank-'0';
                        taille_int1++;
                    } else {
                        tmp = tank - '0';
                        taille_int1++;
                    } 
                    tank = fgetc(sesame);
                    compteur_char++;
                } while (tank!= ' ' || tank != '\n');
                x = tmp;
            } else if (compteur_char == 5 + taille_int1 + 1) {
                do{
                    if (taille_int2>0){
                        tmp = tmp*10 + tank-'0';
                        taille_int2++;
                    } else {
                        tmp = tank - '0';
                        taille_int2++;
                    } 
                    tank = fgetc(sesame);
                    compteur_char++;
                } while (tank!= ' ' || tank != '\n');
                y = tmp;
            } else if (compteur_char == 5 +taille_int1 + 1 +taille_int2 +1){
                prod = tank;
            } else if (compteur_char == 5 + taille_int1 + 1 + taille_int2 +3){
                taille_int1 = 0;
                do{
                    if (taille_int1>0){
                        tmp = tmp*10 + tank-'0';
                    } else {
                        tmp = tank - '0';
                        taille_int1++;
                    } 
                    tank = fgetc(sesame);
                    compteur_char++;
                } while (tank!= ' ' || tank != '\n');
                tours_restant = tmp;
            }
                
            switch(compteur_char){
                case 1:
                    camp = tank;
                case 3:
                    type = tank;
                case 5:
                    x = tank-'0';
                case 7:
                    y = tank-'0';
                case 9:
                    prod = tank;
                case 11:
                    tours_restant = tank-'0';
            }
        }
    }
    
  }
  fclose(sesame);
}

void sauvegarder(char* nom, Grille g,char camp){
    FILE * sesame;
    // ouverture en w car cela évite les problèmes si le fichier n'existe pas
    sesame = fopen(nom,"w");
    int ressource_joueur,ressource_ennemi;
    //switch pour avoir un seul fprintf
    switch (camp)
    {
    case ABEILLE:
        ressource_joueur = g.ressourcesAbeille;
        ressource_ennemi = g.ressourcesFrelon;
    case FRELON:
        ressource_joueur = g.ressourcesFrelon;
        ressource_ennemi = g.ressourcesAbeille;        
    }
    fprintf(sesame, "%s %d %d\n",camp,ressource_joueur,ressource_ennemi);
    //parcours des unités pour les abeilles
    UListe ruche;
    for(; g.abeille != NULL; g.abeille = g.abeille->colsuiv){
        ruche = g.abeille;
        for(;g.abeille != NULL; g.abeille = g.abeille->usuiv){
            fprintf(sesame,"%c %c %d %d %c %d\n",g.abeille->camp,g.abeille->type,g.abeille->posx,g.abeille->posy,g.abeille->production,g.abeille->toursrestant);
        }
        g.abeille = ruche;
    }
    //parcours des unités pour les frelons
    for(; g.frelon != NULL; g.frelon = g.frelon->colsuiv){
        ruche = g.frelon;
        for(;g.frelon != NULL; g.frelon = g.frelon->usuiv){
            fprintf(sesame,"%c %c %d %d %c %d\n",g.frelon->camp,g.frelon->type,g.frelon->posx,g.frelon->posy,g.frelon->production,g.frelon->toursrestant);
        }
        g.frelon = ruche;
    }
    fclose(sesame);
}
