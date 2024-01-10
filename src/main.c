#include "game.h"
#include <time.h>

int main(int argc, char* argv[]){
    Grille plateau;
    int alea;
    char camp, quitter = 0;

    if(argc < 2){
        printf(" il manque un fichier de sauvegarde\n");
        return 0;
    }

    srand(time(NULL));

    camp = charger(argv[1], &plateau);
    

    if(camp == 0)
        initGrille(&plateau);

    MLV_create_window("", "", 1000, 1080);

    while (plateau.abeille != NULL && plateau.frelon != NULL){
        alea = rand() % 2;

        if(camp == ABEILLE){
            menueSauv(ABEILLE, plateau, argv[1]);
            quitter = quit(ABEILLE);
            if(quitter == 'q')
                break;

            tourAbeille(&plateau);
            tourFrelon(&plateau);
            camp = 0;
        }

        if(camp == FRELON){
            menueSauv(FRELON, plateau, argv[1]);
            quitter = quit(FRELON);
            if(quitter == 'q')
                break;

            tourFrelon(&plateau);
            tourAbeille(&plateau);
            camp = 0;
        }

        if(alea == 0 || camp == ABEILLE){
            menueSauv(ABEILLE, plateau, argv[1]);
            quitter = quit(ABEILLE);
            if(quitter == 'q')
                break;

            tourAbeille(&plateau);
            
            if(plateau.abeille == NULL)
                break;
            
            tourFrelon(&plateau);
        }

        else{
            menueSauv(FRELON, plateau, argv[1]);
            quitter = quit(FRELON);
            if(quitter == 'q')
                break;
            
            tourFrelon(&plateau);

            if(plateau.frelon == NULL)
                break;

            tourAbeille(&plateau);
        }

        plateau.tour++;
    }
    
    MLV_free_window();

    if(plateau.abeille == NULL)
        printf("les frelon on gagner\n");
    else if(plateau.frelon == NULL)
        printf("les abeille on gagner\n");

    libereListe(&plateau.abeille);
    libereListe(&plateau.frelon);
    
    return 0;
}
