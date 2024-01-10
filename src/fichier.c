#include "fichier.h"

void GrilleVide(Grille* g){
    g->abeille = NULL;
    g->frelon = NULL;
    g->ressourcesAbeille = 0;
    g->ressourcesFrelon = 0;
    g->tour = 0;
    
    for(int i = 0; i < LIGNES; i++){
        for(int j = 0; j < COLONNES; j++){
            g->plateau[i][j].colonie = 0;
            g->plateau[i][j].occupant = 0;
        }
    }
}

char charger(char* nom, Grille * g){
    FILE * sesame;
    UListe new;
    char camp, type, prod, joueur;
    int ressource1, ressource2, x, y, toureres;

    GrilleVide(g);
  
    sesame = fopen(nom,"r");
    if (sesame == NULL){
        //la sauvegarde n'existe pas
        return 0;
    }

    g->abeille = NULL;
    g->frelon = NULL;

    fscanf(sesame, "%c %d %d\n", &camp, &ressource1, &ressource2);

    joueur = camp;

    if(camp == ABEILLE){
        g->ressourcesAbeille = ressource1;
        g->ressourcesFrelon = ressource2;
    }

    else{
        g->ressourcesFrelon = ressource1;
        g->ressourcesAbeille = ressource2;
    }

    while( fscanf(sesame, "%c %c %d %d %c %d\n", &camp, &type, &x, &y, &prod, &toureres) != EOF){

        if(camp == ABEILLE){
            new = inserer(&g->abeille, NULL, camp, type, x, y);
        }

        else{
            new = inserer(&g->frelon, NULL, camp, type, x, y);
        }

        new->posx = x;
        new->posy = y;

        new->production = prod;
        new->toursrestant = toureres;

        switch(prod){
            case REINE:
                new->temps = TREINEA;
                break;

            case OUVRIERE:
                new->temps = TOUVRIERE;
                break;

            case ESCADRON:
                new->temps = TESCADRON;
                break;

            case GUERRIERE:
                new->temps = TGUERRIERE;
                break;

            case FRELONS:
                new->temps = TFRELON;
                break;
            
            case RECOLTE:
                new->temps = TRECOLTE;

            default :
                break;
        }

        
        if(g->abeille != NULL && g->abeille->colsuiv != NULL){
            g->abeille = g->abeille->colsuiv;
        }

        if(g->frelon != NULL && g->frelon->colsuiv != NULL)
            g->frelon = g->frelon->colsuiv;
        

        if(type != RUCHE && type != NID)
            deplacement(&new, &g->plateau[new->posy][new->posx], NULL);
        
        else
            g->plateau[new->posy][new->posx].colonie = new;
    }

    for(; g->abeille->colprec != NULL; g->abeille = g->abeille->colprec);
    for(; g->frelon->colprec != NULL; g->frelon = g->frelon->colprec);

    fclose(sesame);
    
    return joueur;
}

void sauvegarder(char* nom, Grille g,char camp){
    FILE * sesame;
    UListe ruche;
    int ressource_joueur,ressource_ennemi;

    // ouverture en w car cela évite les problèmes si le fichier n'existe pas
    sesame = fopen(nom,"w");
    if(!sesame)
        return;

    //switch pour avoir un seul fprintf
    switch (camp){

        case ABEILLE:
            ressource_joueur = g.ressourcesAbeille;
            ressource_ennemi = g.ressourcesFrelon;
        case FRELON:
            ressource_joueur = g.ressourcesFrelon;
            ressource_ennemi = g.ressourcesAbeille;        
    }
    
    fprintf(sesame, "%c %d %d\n",camp,ressource_joueur,ressource_ennemi);
    
    //parcours des unités pour les abeilles
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
