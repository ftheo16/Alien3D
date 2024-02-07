#include "../include/creature.h"
#include "../include/include.h"

//tableau aliens
extern Creature* tableau_creature;
extern Carre *Objects[4]; 
extern Point DG,DD,AG,AD;

//permet de retourne le tableau alien
Creature* obtenirTableauCreature() {
    return tableau_creature;
}

//mise a jour des enfants aliens
void mettreAJourAlienEnfant(Creature* creature, int indice){
    if(indice < 0){
        return;
    }

    for(int i=0; i<nombreAliens;i++){
        if(creature[i].enfant == 1 && i != indice){
            creature[i].enfant = 0;
        }
    }
}

int verificationjoueurAlien(Cote * cote){
    int boolean = 0;
    Cote *box = (Cote*)malloc(sizeof(Cote));

    box->p1.x = DG.x;
    box->p1.y = DG.y;
    box->p2.x = DD.x;
    box->p2.y = DD.y;
    boolean = intersection(*cote,*box);
    if(boolean == 1){
        free(box);
        return 1;
    }
    box->p1.x = DD.x;
    box->p1.y = DD.y;
    box->p2.x = AD.x;
    box->p2.y = AD.y;
    boolean = intersection(*cote,*box);
    if(boolean == 1){
        free(box);
        return 1;
    }
    box->p1.x = AD.x;
    box->p1.y = AD.y;
    box->p2.x = AG.x;
    box->p2.y = AG.y;
    boolean = intersection(*cote,*box);
    if(boolean == 1){
        free(box);
        return 1;
    }
    box->p1.x = AG.x;
    box->p1.y = AG.y;
    box->p2.x = DG.x;
    box->p2.y = DG.y;
    boolean = intersection(*cote,*box);
    if(boolean == 1){
        free(box);
        return 1;
    }
    return 0;
}


int verificationMurAlien(Cote *cote){
    Cote *mur1 = (Cote*)malloc(sizeof(Cote));

    if(mur1 == NULL ){
        printf("erreur d'allocation mémoire pour le segmant mur\n");
        exit(EXIT_FAILURE);
    }

    mur1->p1.x = 93;
    mur1->p1.y = 93;
    mur1->p2.x = 93;
    mur1->p2.y = -93;

    if( intersection(*cote,*mur1)){
        free(mur1);
        return 1;
    }
    
    mur1->p1.x = 93;
    mur1->p1.y = -93;
    mur1->p2.x = -93;
    mur1->p2.y = -93;

    if( intersection(*cote,*mur1)){
        free(mur1);
        return 1;
    }

    mur1->p1.x = -93;
    mur1->p1.y = -93;
    mur1->p2.x = -93;
    mur1->p2.y = 93;

    if( intersection(*cote,*mur1)){
        free(mur1);
        return 1;
    }

    mur1->p1.x = -93;
    mur1->p1.y = 93;
    mur1->p2.x = 93;
    mur1->p2.y = 93;

    if( intersection(*cote,*mur1)){
        free(mur1);
        return 1;
    }
    free(mur1);
    return 0;
}

int verificationColisionAlien(Cote *devant){
    //verifie la collision entre un segment et tout les obstacles de la carte

        int indice = 0;
        while(Objects[indice] != NULL){
            //verification des 4 cotés de l'obstacle
            if( intersection(*devant, Objects[indice]->C1) == 1)
                return 1;

            if( intersection(*devant, Objects[indice]->C2) == 1)
                return 1;
                    
            if( intersection(*devant, Objects[indice]->C3) == 1)
                return 1;
                    
            if( intersection(*devant, Objects[indice]->C4) == 1)
                return 1; 

            indice++;  
        }
   // }
    return 0;
}

int collisionAlien(int i, Cote *cote){
    Cote *box = (Cote*)malloc(sizeof(Cote));
    for(int indice=0;indice<nombreAliens;indice++){

        if( i != indice){
            //verification avec les 4 cotées de la hitbox des aliennes
            box->p1.x = tableau_creature[indice].pos_x-1;
            box->p1.y = tableau_creature[indice].pos_z-1;
            box->p2.x = tableau_creature[indice].pos_x+3;
            box->p2.y = tableau_creature[indice].pos_z-1;

            if(intersection(*cote,*box)==1){
                free(box);
                return 1;
            }

            box->p1.x = tableau_creature[indice].pos_x+3;
            box->p1.y = tableau_creature[indice].pos_z-1;
            box->p2.x = tableau_creature[indice].pos_x+3;
            box->p2.y = tableau_creature[indice].pos_z+3;

            if(intersection(*cote,*box)==1){
                free(box);
                return 1;
            }

            box->p1.x = tableau_creature[indice].pos_x+3;
            box->p1.y = tableau_creature[indice].pos_z+3;
            box->p2.x = tableau_creature[indice].pos_x-1;
            box->p2.y = tableau_creature[indice].pos_z+3;

            if(intersection(*cote,*box)==1){
                free(box);
                return 1;
            }

            box->p1.x = tableau_creature[indice].pos_x-1;
            box->p1.y = tableau_creature[indice].pos_z+3;
            box->p2.x = tableau_creature[indice].pos_x-1;
            box->p2.y = tableau_creature[indice].pos_z-1;

            if(intersection(*cote,*box)==1){
                free(box);
                return 1;
            }
        }
    }
    return 0;
}


int lancerCollisionAlien(float x, float z,int indice){
    int boolean=0;
    Cote *box = (Cote*)malloc(sizeof(Cote));
    box->p1.x = x-1;
    box->p1.y = z-1;
    box->p2.x = x+3;
    box->p2.y = z-1;
    
    boolean = collisionAlien(indice,box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationColisionAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationMurAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
     boolean = verificationjoueurAlien(box);
        if(boolean == 1 ){
        free(box);
        return 1;
    }

    box->p1.x = x+3;
    box->p1.y = z-1;
    box->p2.x = x+3;
    box->p2.y = z+3;
    boolean = collisionAlien(indice,box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationColisionAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationMurAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
     boolean = verificationjoueurAlien(box);
        if(boolean == 1 ){
        free(box);
        return 1;
    }

    box->p1.x = x+3;
    box->p1.y = z+3;
    box->p2.x = x-1;
    box->p2.y = z+3;
    boolean = collisionAlien(indice,box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationColisionAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationMurAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationjoueurAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }

    box->p1.x = x-1;
    box->p1.y = z+3;
    box->p2.x = x-1;
    box->p2.y = z-1;   
    boolean = collisionAlien(indice,box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationColisionAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationMurAlien(box);
    if(boolean == 1 ){
        free(box);
        return 1;
    }
    boolean = verificationjoueurAlien(box);
        if(boolean == 1 ){
        free(box);
        return 1;
    }
    return 0;

}

//retourne l'indice de l'alien le plus proche (il faut donner l'indice de l'alien chercheur en parametre)
int trouverCreaturePlusProche(Creature* creature, int indexCreature) {
    float distMin = INFINITY;
    int indexCible = -1;

    for (int i = 0; i < nombreAliens; i++) {
        if (i != indexCreature && creature[i].etat == 1 && creature[indexCreature].etat == 1) {
            float dist = sqrtf(powf(creature[i].pos_x - creature[indexCreature].pos_x, 2) + powf(creature[i].pos_z - creature[indexCreature].pos_z, 2));
            if (dist < distMin) {
                distMin = dist;
                indexCible = i;
            }
        }
    }
    return indexCible;
}

//permet de faire déplacer un alien
void deplacerCreature(Creature* creature, float distanceDeplacement) {
    int bool = 0;
    Point *tmp= (Point*)malloc(sizeof(Point));
    if(tmp == NULL){
        printf("erreur d'allocation mémoire pour le Point tmp\n");
        exit(EXIT_FAILURE);
    }

    //pour chaque alien
    for (int i = 0; i < nombreAliens; i++) {
        tmp->x = creature[i].pos_x;
        tmp->y = creature[i].pos_y;
        //x et y du nouveau deplacement
        float deplacementX = ((float)rand() / RAND_MAX) * (2 * distanceDeplacement) - distanceDeplacement;
        float deplacementZ = ((float)rand() / RAND_MAX) * (2 * distanceDeplacement) - distanceDeplacement;


        //créature en mode recherche
        if(creature[i].etat == 1){

            //index de la creature la plus proche de la creature actuelle
            int indexCible = trouverCreaturePlusProche(creature, i);
            //s'il une cible est LOCALISÉE JE REPETE LOCALISÉE
            if(indexCible != -1){
                float cibleX = creature[indexCible].pos_x;
                float cibleZ = creature[indexCible].pos_z;
                float deplacementX = cibleX - creature[i].pos_x;
                float deplacementZ = cibleZ - creature[i].pos_z;
                //racine carré float -> sqrtf
                float magnitude = sqrtf(deplacementX * deplacementX + deplacementZ * deplacementZ);

                //normaliser le vecteur de déplacement
                if (magnitude > 0) {
                    deplacementX /= magnitude;
                    deplacementZ /= magnitude;
                }

                
                tmp->x += deplacementX * distanceDeplacement;
                tmp->y += deplacementZ * distanceDeplacement;

                bool = lancerCollisionAlien(tmp->x,tmp->y,i);
                //printf("%d\n",bool);

                //peut se deplacer
                if( bool == 0){
                    
                    //changement du vecteur déplacement
                    creature[i].deplacement.x = deplacementX;
                    creature[i].deplacement.z = deplacementZ;

                    creature[i].pos_x += creature[i].deplacement.x * distanceDeplacement;
                    creature[i].pos_z += creature[i].deplacement.z * distanceDeplacement;
                     if(creature[i].pos_x > 93){
                    creature[i].pos_x = 92;
                }
                if(creature[i].pos_x < -93){
                    creature[i].pos_x = -92;
                }
                if(creature[i].pos_z > 93){
                    creature[i].pos_z = 92;
                }
                if(creature[i].pos_z < -93){
                    creature[i].pos_z = -92;
                }
                }
            }else{

                tmp->x += deplacementX * distanceDeplacement;
                tmp->y += deplacementZ * distanceDeplacement;

                bool = lancerCollisionAlien(tmp->x,tmp->y,i);
                
               
                if(bool == 0){
                    //changement du vecteur deplacement
                    creature[i].deplacement.x = deplacementX;
                    creature[i].deplacement.z = deplacementZ;

                    creature[i].pos_x += creature[i].deplacement.x * distanceDeplacement;
                    creature[i].pos_z += creature[i].deplacement.z * distanceDeplacement;

                     if(creature[i].pos_x > 93){
                    creature[i].pos_x = 92;
                }
                if(creature[i].pos_x < -93){
                    creature[i].pos_x = -92;
                }
                if(creature[i].pos_z > 93){
                    creature[i].pos_z = 92;
                }
                if(creature[i].pos_z < -93){
                    creature[i].pos_z = -92;
                }
                }
            }

            //vérifier si la créature est dans la zone d'une autre créature en état 1 et mettre à jour son état
            for (int j = 0; j < nombreAliens; j++) {
                if (i != j && creature[j].etat == 1) {
                    float distance = sqrtf(powf(creature[i].pos_x - creature[j].pos_x, 2) + powf(creature[i].pos_z - creature[j].pos_z, 2));
                    float rayonZone = 7;

                    //un enfant, je repete UN ENFANT!!!!
                    if (distance <= rayonZone) {

                        //les aliens passent en mode non recherche
                        creature[i].etat = 0;
                        creature[j].etat = 0;


                        Vecteur* deplacement = (Vecteur*)malloc(sizeof(Vecteur));
                        deplacement->x = 1;
                        deplacement->y = 0;
                        deplacement->z = 0;
                        tableau_creature[nombreAliens].deplacement = *deplacement;               
                        tableau_creature[nombreAliens].pos_x = creature[i].pos_x;   
                        tableau_creature[nombreAliens].pos_y = creature[i].pos_y; 
                        tableau_creature[nombreAliens].pos_z = creature[i].pos_z;
                        tableau_creature[nombreAliens].etat = 0;  
                        tableau_creature[nombreAliens].enfant = 1;

                        //mise a jour des aliens enfant
                        mettreAJourAlienEnfant(tableau_creature,nombreAliens);

                        //on augmente le nombre d'aliens
                        nombreAliens++;
                        break;
                    }
                }
            }
        }else{
                tmp->x += deplacementX * distanceDeplacement;
                tmp->y += deplacementZ * distanceDeplacement;
                
                bool = lancerCollisionAlien(tmp->x,tmp->y,i);
                
            if(bool == 0 && distanceDeplacement == 0.5){


                //changement de la position
                creature[i].pos_x += creature[i].deplacement.x;
                creature[i].pos_z += creature[i].deplacement.z;
                 if(creature[i].pos_x > 93){
                    creature[i].pos_x = 92;
                }
                if(creature[i].pos_x < -93){
                    creature[i].pos_x = -92;
                }
                if(creature[i].pos_z > 93){
                    creature[i].pos_z = 92;
                }
                if(creature[i].pos_z < -93){
                    creature[i].pos_z = -92;
                }
            }
            if(bool == 1 && distanceDeplacement == 0.5){


                if(rand()>0.5){
                    tmp->x = creature[i].deplacement.z;
                    tmp->y = -creature[i].deplacement.x;

                    creature[i].deplacement.x = tmp->x;
                    creature[i].deplacement.z = tmp->y;
                }else{
                    tmp->x = creature[i].deplacement.z;
                    tmp->y = creature[i].deplacement.x;

                    creature[i].deplacement.x = tmp->x;
                    creature[i].deplacement.z = tmp->y;
                }

                creature[i].pos_x += creature[i].deplacement.x;
                creature[i].pos_z += creature[i].deplacement.z;

                if(creature[i].pos_x > 93){
                    creature[i].pos_x = 92;
                }
                if(creature[i].pos_x < -93){
                    creature[i].pos_x = -92;
                }
                if(creature[i].pos_z > 93){
                    creature[i].pos_z = 92;
                }
                if(creature[i].pos_z < -93){
                    creature[i].pos_z = -92;
                }
            }
        }
    }
}

Creature* creerTableauCreature(int taille) {
    tableau_creature = (Creature*)malloc(sizeof(Creature) * taille);
    for (int i = 0; i < taille; i++) {
        Vecteur* deplacement = (Vecteur*)malloc(sizeof(Vecteur));
        deplacement->x = (rand()%(99+99))-99;
        deplacement->y = 0;
        deplacement->z = (rand()%(99+99))-99;
        *deplacement = normalisation(*deplacement);

        tableau_creature[i].pos_x = (rand() % 201) - 100;
        tableau_creature[i].pos_y = 0;
        tableau_creature[i].pos_z = (rand() % 201) - 100;

        tableau_creature[i].deplacement = *deplacement;

        tableau_creature[i].etat = 0;
        tableau_creature[i].enfant = 0;

    }
    return tableau_creature;
}

