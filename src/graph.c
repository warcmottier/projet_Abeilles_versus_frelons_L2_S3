#include "graph.h"

void legende(){
    MLV_draw_text(810, 650, "Legende :", MLV_COLOR_WHITE);
    MLV_draw_text(810, 665, "R = ruche cout = %d", MLV_COLOR_WHITE, CRUCHE);
    MLV_draw_text(810, 680, "N = nid cout = %d", MLV_COLOR_WHITE, CNID);
    MLV_draw_text(810, 695, "rA = reine abeille cout = %d", MLV_COLOR_WHITE, CREINEA);
    MLV_draw_text(810, 710, "rF = reine frelon cout = %d", MLV_COLOR_WHITE, CREINEF);
    MLV_draw_text(810, 725, "o = ouvriere cout = %d", MLV_COLOR_WHITE, COUVRIERE);
    MLV_draw_text(810, 740, "e = escadron cout = %d", MLV_COLOR_WHITE, CESCADRON);
    MLV_draw_text(810, 755, "g = guerriere cout = %d", MLV_COLOR_WHITE, CGUERRIERE);
    MLV_draw_text(810, 770, "f = frelon cout = %d", MLV_COLOR_WHITE, CFRELON);
    
}

void afficheCase(Case cases, int x, int y){
    int reineA = 0, escadron = 0, guerriere = 0, ouvriere = 0, frelon = 0, reineF = 0;


    for(; cases.occupant != NULL; cases.occupant = cases.occupant->vsuiv){

        if(cases.occupant->camp == ABEILLE && cases.occupant->type == REINE)
            reineA++;
        
        if(cases.occupant->camp == FRELON && cases.occupant->type == REINE)
            reineF++;
        
        switch (cases.occupant->type){
            case ESCADRON:
                escadron++;
                break;
        
            case GUERRIERE:
                guerriere++;
                break;
            
            case OUVRIERE:
                ouvriere++;
                break;
            
            case FRELONS:
                frelon++;
                break;
        
            default:
                break;
        }
    }

    if(reineA > 0){
        MLV_draw_text_box(x, y, 30, 20, "rA*%d", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, reineA);
    }

    if(reineF > 0){
        MLV_draw_text_box(x + 30, y, 30, 20, "rF*%d", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, reineF);
    }

    if(ouvriere > 0){
        MLV_draw_text_box(x, y +20, 20, 20, "o*%d", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, ouvriere);
    }

    if(cases.colonie != NULL && cases.colonie->type == RUCHE){
        MLV_draw_text_box(x + 20, y + 20, 20, 20, "R", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    }

    if(cases.colonie != NULL && cases.colonie->type == NID){
        MLV_draw_text_box(x + 20, y + 20, 20, 20, "N", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    }

    if(frelon > 0){
        MLV_draw_text_box(x + 40, y + 20, 20, 20, "f*%d", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, frelon);
    }

    if(guerriere > 0){
        MLV_draw_text_box(x, y + 40, 30, 20, "g*%d", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, guerriere);
    }

    if(escadron > 0){
        MLV_draw_text_box(x + 30, y + 40, 30, 20, "e*%d", 5, MLV_COLOR_BLUE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, escadron);
    }
}

void affichePlateaux(Grille plateau){
    int x = 0, y = 0;

    MLV_clear_window(MLV_COLOR_BLACK);

    for(int i = 0; i < LIGNES; i++){
        for(int j = 0; j < COLONNES; j++){
            MLV_draw_rectangle(x, y, 60, 60, MLV_COLOR_PURPLE);
            afficheCase(plateau.plateau[i][j], x, y);
            x += 60;
        }
        x = 0;
        y += 60;
    }

    legende();

    MLV_actualise_window();
}


char menueReine(int* x, int* y, int posX, int posY, int ressource, char camp, UListe colonie){
    char c = '\n';
    int clickX, clickY;

    MLV_draw_text_box(860, 100, 100, 50, "passer", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    switch (camp){
        case ABEILLE:
            MLV_draw_text_box(760, 100, 100, 50, "fonder colonie", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
                MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

            MLV_draw_text(790, 500, "vous jouez les abeilles", MLV_COLOR_WHITE);
            break;
    
        case FRELON:
            MLV_draw_text_box(760, 100, 100, 50, "fonder colonie\n(%d)", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
                MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, CNID, CNID);

            MLV_draw_text(800, 500, "vous jouez les frelon", MLV_COLOR_WHITE);
            break;
    
        default:
            break;
    }

    MLV_draw_text(720, 530, "vous jouer une reine en position (%d %d)", MLV_COLOR_WHITE, posX, posY);
    MLV_draw_text(790, 560, "vous avez %d ressource", MLV_COLOR_WHITE, ressource);

    MLV_actualise_window();


    while(c == '\n'){
        MLV_wait_mouse(&clickX, &clickY);

        if(clickX > 760 && clickX < 860 && clickY < 150 && clickY > 100 && colonie == NULL && (ressource >= CRUCHE || ressource >= CNID))
            c = 'f';
        
        else if(clickX > 860 && clickX < 960 && clickY < 150 && clickY > 100)
            c = 0;
        
        else if(clickX > 0 && clickX < 720 && clickY > 0 && clickY < 1080){
            *x = clickX / 60;
            *y = clickY / 60;

            if(abs(*x - posX) < 2 && abs(*y - posY) < 2){
                c = 0;
            }

        }
    }

    MLV_actualise_window();

    return c;
}

char menueGEF(int* x, int* y, int posX, int posY, char type, int ressource, char camp){
    char c = '\n';
    int clickX, clickY;

    MLV_draw_text_box(760, 100, 100, 50, "passer", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    switch (camp){
        case ABEILLE:
            MLV_draw_text(790, 500, "vous jouez les abeilles", MLV_COLOR_WHITE);
            break;
    
        case FRELON:
            MLV_draw_text(790, 500, "vous jouez les frelon", MLV_COLOR_WHITE);
            break;
    
        default:
            break;
    }
    switch (type){

        case ESCADRON:
            MLV_draw_text(720, 530, "vous jouer une escadron en position (%d %d)", MLV_COLOR_WHITE, posX, posY);
            break;
    
        case GUERRIERE:
            MLV_draw_text(718, 530, "vous jouer une guerriere en position (%d %d)", MLV_COLOR_WHITE, posX, posY);
            break;
    
        case FRELONS:
            MLV_draw_text(720, 530, "vous jouer un frelon en position (%d %d)", MLV_COLOR_WHITE, posX, posY);
            break;
    
        default:
            break;
    }

    MLV_draw_text(790, 560, "vous avez %d ressource", MLV_COLOR_WHITE, ressource);

    MLV_actualise_window();

    while(c == '\n'){
        MLV_wait_mouse(&clickX, &clickY);

        if(clickX > 760 && clickX < 860 && clickY < 150 && clickY > 100)
            c = 0;
        
        else if(clickX > 0 && clickX < 720 && clickY > 0 && clickY < 1080){
            *x = clickX / 60;
            *y = clickY / 60;

            if(abs(*x - posX) < 2 && abs(*y - posY) < 2){
                c = 0;
            }
        }
    }

    return c;
}

char menueOuvriere(int* x, int* y, int posX, int posY, int ressource){
    char c = '\n';
    int clickX, clickY;

    MLV_draw_text_box(760, 100, 100, 50, "recolter pollen", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text_box(860, 100, 100, 50, "passer", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text(790, 500, "vous jouez les abeilles", MLV_COLOR_WHITE);    
    MLV_draw_text(720, 530, "vous jouer une ouvriere en position (%d %d)", MLV_COLOR_WHITE, posX, posY);
    MLV_draw_text(790, 560, "vous avez %d ressource", MLV_COLOR_WHITE, ressource);

    MLV_actualise_window();

    while(c == '\n'){
        MLV_wait_mouse(&clickX, &clickY);

        if(clickX > 760 && clickX < 860 && clickY < 150 && clickY > 100)
            c = 'r';
        
        else if(clickX > 860 && clickX < 960 && clickY < 150 && clickY > 100)
            c = 0;
        
        else if(clickX > 0 && clickX < 720 && clickY > 0 && clickY < 1080){
            *x = clickX / 60;
            *y = clickY / 60;
            
            if(abs(*x - posX) < 2 && abs(*y - posY) < 2){
                c = 0;
            }
        }
    }


    return c;
}

char menueNid(int posX, int posY, int ressource){
    char c = '\n';
    int clickX, clickY;

    MLV_draw_text_box(760, 100, 100, 50, "passer", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text_box(860, 100, 100, 50, "cree frelon", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text_box(760, 150, 100, 50, "cree reine", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text(790, 500, "vous jouez les frelon", MLV_COLOR_WHITE);
    MLV_draw_text(740, 530, "vous jouer un nid en position (%d %d)", MLV_COLOR_WHITE, posX, posY);
    MLV_draw_text(790, 560, "vous avez %d ressource", MLV_COLOR_WHITE, ressource);

    MLV_actualise_window();

    while(c == '\n'){
        MLV_wait_mouse(&clickX, &clickY);

        if(clickX > 760 && clickX < 860 && clickY < 150 && clickY > 100)
            c = 0;
        
        else if(clickX > 860 && clickX < 960 && clickY < 150 && clickY > 100)
            c = 'f';
        
        else if(clickX > 760 && clickX < 860 && clickY < 200 && clickY > 150 && ressource >= CREINEF){
            c = 'r';
        }
    }

    return c;
}

char menueRuche(int posX, int posY, int ressource){
    char c = '\n';
    int clickX, clickY;

    MLV_draw_text_box(760, 100, 100, 50, "passer", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text_box(860, 100, 100, 50, "cree ouvriere", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text_box(760, 150, 100, 50, "cree reine", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text_box(860, 150, 100, 50, "cree escadron", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    
    MLV_draw_text_box(760, 200, 100, 50, "cree guerriere", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_draw_text(790, 500, "vous jouez les abeilles", MLV_COLOR_WHITE);
    MLV_draw_text(740, 530, "vous jouer une ruche en position (%d %d)", MLV_COLOR_WHITE, posX, posY);
    MLV_draw_text(790, 560, "vous avez %d ressource", MLV_COLOR_WHITE, ressource);

    MLV_actualise_window();

    while(c == '\n'){
        MLV_wait_mouse(&clickX, &clickY);

        if(clickX > 760 && clickX < 860 && clickY < 150 && clickY > 100)
            c = 0;
        
        else if(clickX > 860 && clickX < 960 && clickY < 150 && clickY > 100)
            c = 'o';
        
        else if(clickX > 760 && clickX < 860 && clickY < 200  && clickY > 150 && ressource >= COUVRIERE)
            c = 'r';
        
        else if(clickX > 860 && clickX < 960 && clickY < 200 && clickY > 150 && ressource >= CREINEA){
            c = 'e';
        }

        else if(clickX > 760 && clickX < 860 && clickY < 250 && clickY > 200 && ressource >= CESCADRON){
            c = 'g';
        }
    }
    
    return c;
}

void menueSauv(char camp, Grille plateau, char * nom){
    int x = 0, y = 0, ok1, ok2;
    char c = '\n';

    MLV_clear_window(MLV_COLOR_BLACK);

    if(camp == ABEILLE){
        MLV_draw_text(400, 580, "abeille voulez vous sauvegarder", MLV_COLOR_WHITE);   
    }

    else{
        MLV_draw_text(400, 580, "frelon voulez vous sauvegarder", MLV_COLOR_WHITE); 
    }

    MLV_draw_text_box(350, 600, 100, 50, "oui", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    
    MLV_draw_text_box(550, 600, 100, 50, "non", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_actualise_window();
    
    do{
        MLV_wait_mouse(&x, &y);
        ok1 = (x > 350 && x < 450 && y > 600 && y < 650);
        ok2 = (x > 550 && x < 650 && y > 600 && y < 650);

        if(ok1){
            sauvegarder(nom, plateau, camp);
            c = 0;
        }

        else if(ok2){
            c = 0;
        }

    }while(c == '\n');

}

char quit(char camp){
    int x, y, ok1, ok2;
    char c;

    MLV_clear_window(MLV_COLOR_BLACK);

    if(camp == ABEILLE){
        MLV_draw_text(400, 580, "abeille voulez vous quitter", MLV_COLOR_WHITE);   
    }

    else{
        MLV_draw_text(400, 580, "frelon voulez vous quitter", MLV_COLOR_WHITE); 
    }

    MLV_draw_text_box(350, 600, 100, 50, "oui", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    
    MLV_draw_text_box(550, 600, 100, 50, "non", 5, MLV_COLOR_PURPLE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, 
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_actualise_window();
    
    do{
        MLV_wait_mouse(&x, &y);
        ok1 = (x > 350 && x < 450 && y > 600 && y < 650);
        ok2 = (x > 550 && x < 650 && y > 600 && y < 650);

        if(ok1){
            c = 'q';
        }

        else if(ok2){
            c = 0;
        }

    }while(c == '\n');

    return c;
}
