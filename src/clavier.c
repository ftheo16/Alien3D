#include "../include/include.h"
#include "../include/clavier.h"
//#include "../include/vecteur.h"
#include "../include/creature.h"

extern float zpos,xpos,ypos;
extern float zreg,xreg,yreg;

extern Vecteur direction;
extern Vecteur gauche;
extern Vecteur tete;

extern Creature* tableau_creature;

//mise a jour de l'affichage des aliens
extern int miseAJourAffichage;

extern Carre *Objects[4]; 
extern int indiceObject;
extern Point DG,DD,AG,AD;

extern int nombreAliens;

void MAJdirectionGauche(){
    //met à jour les vecteur et les normalisent
    direction.z = (zreg-zpos);
    direction.x = (xreg-xpos);
    direction = normalisation(direction);

    gauche.x = (direction.y*tete.z)-(direction.z*tete.y);
    gauche.y = (direction.z*tete.x)-(direction.x*tete.z);
    gauche.z = (direction.x*tete.y)-(direction.y*tete.x);
    gauche = normalisation(gauche);
}


void MAJboxJoueur(){
    //met à jour la hitbox du joueur
    //mise à jour du point Devant Gauche de la hitbox du personnage
    DG.x = (xpos+direction.x+gauche.x+direction.x+gauche.x+direction.x+gauche.x);
    DG.y = (zpos+direction.z+gauche.z+direction.z+gauche.z+direction.z+gauche.z);
            
    //mise à jour du point Devant Droite de la hitbox du personnage
    DD.x = (xpos+direction.x-gauche.x+direction.x-gauche.x+direction.x-gauche.x);
    DD.y = (zpos+direction.z-gauche.z+direction.z-gauche.z+direction.z-gauche.z);

    //mise à jour du point Arriere Gauche de la hitbox du personnage
    AG.x = (xpos-direction.x+gauche.x-direction.x+gauche.x-direction.x+gauche.x);
    AG.y = (zpos-direction.z+gauche.z-direction.z+gauche.z-direction.z+gauche.z);
        
    //mise à jour du point Arriere Droite de la hitbox du personnage
    AD.x = (xpos-direction.x-gauche.x-direction.x-gauche.x-direction.x-gauche.x);
    AD.y = (zpos-direction.z-gauche.z-direction.z-gauche.z-direction.z-gauche.z);
}

int verificationMur(Cote *cote){
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

int verificationColision(Cote *devant){
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

int verificationAlien(Cote *cote, int change){
    Cote *box = (Cote*)malloc(sizeof(Cote));

    if(box == NULL ){
        printf("erreur d'allocation mémoire pour le segmant mur\n");
        exit(EXIT_FAILURE);
    }

    for(int indice=0;indice<nombreAliens;indice++){
        //verification avec les 4 cotées de la hitbox des aliennes
        box->p1.x = tableau_creature[indice].pos_x-1;
        box->p1.y = tableau_creature[indice].pos_z-1;
        box->p2.x = tableau_creature[indice].pos_x+3;
        box->p2.y = tableau_creature[indice].pos_z-1;

        if(intersection(*cote,*box)==1){
            if(change && tableau_creature[indice].enfant == 0)
                tableau_creature[indice].etat = 1;
            free(box);
            return 1;
        }

        box->p1.x = tableau_creature[indice].pos_x+3;
        box->p1.y = tableau_creature[indice].pos_z-1;
        box->p2.x = tableau_creature[indice].pos_x+3;
        box->p2.y = tableau_creature[indice].pos_z+3;

        if(intersection(*cote,*box)==1){
            if(change && tableau_creature[indice].enfant == 0)
                tableau_creature[indice].etat = 1;
            free(box);
            return 1;
        }

        box->p1.x = tableau_creature[indice].pos_x+3;
        box->p1.y = tableau_creature[indice].pos_z+3;
        box->p2.x = tableau_creature[indice].pos_x-1;
        box->p2.y = tableau_creature[indice].pos_z+3;

        if(intersection(*cote,*box)==1){
            if(change && tableau_creature[indice].enfant == 0)
                tableau_creature[indice].etat = 1;
            free(box);
            return 1;
        }

        box->p1.x = tableau_creature[indice].pos_x-1;
        box->p1.y = tableau_creature[indice].pos_z+3;
        box->p2.x = tableau_creature[indice].pos_x-1;
        box->p2.y = tableau_creature[indice].pos_z-1;

        if(intersection(*cote,*box)==1){
            if(change && tableau_creature[indice].enfant == 0)
                tableau_creature[indice].etat = 1;
            free(box);
            return 1;
        }
    }
    return 0;
}


void GererClavier(unsigned char touche, int x, int y){
    int boolean = 0;
    float vecXx,vecXy,vecXz;
    float vecYx,vecYy,vecYz;
    float vecZx,vecZy,vecZz;
    float anglex;
    //on met pas ajour les aliens si on bouge
    miseAJourAffichage = 0;
    switch (touche){
        // Le joueur va à droite
        case TOUCHE_D:          
            MAJdirectionGauche();
            MAJboxJoueur();

            Cote *droite = (Cote*)malloc(sizeof(Cote));
            if(droite == NULL){
                printf("erreur d'allocation mémoire pour le segmant droite\n");
                exit(EXIT_FAILURE);
            }

            droite->p1 = DD;
            droite->p2 = AD;

            boolean = verificationColision(droite);
            if(boolean == 0){
                boolean = verificationMur(droite);
            }
            if(boolean == 0){
                boolean = verificationAlien(droite,0);
            }
            free(droite);

            if(boolean == 0){
                //si aucune collision dans cette direction on peut avancé
                xpos += gauche.x*VITESSE;
                zpos += gauche.z*VITESSE;
                xreg += gauche.x*VITESSE;
                zreg += gauche.z*VITESSE;        
            }    

            glutPostRedisplay();    
            break;

        //Le joueur va à gauche
        case TOUCHE_Q:
            MAJdirectionGauche();
            MAJboxJoueur();

            Cote *gauche1 = (Cote*)malloc(sizeof(Cote));
            if(gauche1 == NULL){
                printf("erreur d'allocation mémoire pour le segmant gauche\n");
                exit(EXIT_FAILURE);
            }

            gauche1->p1 = DG;
            gauche1->p2 = AG;

            boolean = verificationColision(gauche1);

            if(boolean == 0)
                boolean = verificationMur(gauche1);
            
            if(boolean == 0)
                boolean = verificationAlien(gauche1,0);
            
            free(gauche1);

            if(boolean == 0){
                xpos -= gauche.x*VITESSE;
                zpos -= gauche.z*VITESSE;
                xreg -= gauche.x*VITESSE;
                zreg -= gauche.z*VITESSE;        
            }    
            glutPostRedisplay();    
            break;           

        //Le joueur avance
        case TOUCHE_Z :
            
            MAJdirectionGauche();
            MAJboxJoueur();

            Cote *devant = (Cote*)malloc(sizeof(Cote));
            if(devant == NULL){
                printf("erreur d'allocation mémoire pour le segmant devant\n");
                exit(EXIT_FAILURE);
            }
            devant->p1 = DG;
            devant->p2 = DD;

            boolean = verificationColision(devant);
            if(boolean == 0){
                boolean = verificationMur(devant);
            }
            if(boolean == 0){
                boolean = verificationAlien(devant,0);
            }
            free(devant);

            if(boolean == 0){
                xpos += direction.x*VITESSE;
                zpos += direction.z*VITESSE;
                xreg += direction.x*VITESSE;
                zreg += direction.z*VITESSE;           
            }

            glutPostRedisplay();             
            break;
        
        //Le joueur recul
        case TOUCHE_S:         
            MAJdirectionGauche();
            MAJboxJoueur();

            Cote *arriere = (Cote*)malloc(sizeof(Cote));
            if(arriere == NULL){
                printf("erreur d'allocation mémoire pour le segmant arriere\n");
                exit(EXIT_FAILURE);
            }

            arriere->p1 = AG;
            arriere->p2 = AD;

            boolean = verificationColision(arriere);
            if(boolean == 0){
                boolean = verificationMur(arriere);
            }
            if(boolean == 0){
                boolean = verificationAlien(arriere,0);
            }
            free(arriere);

            if(boolean == 0){
                xpos -= direction.x*VITESSE;
                zpos -= direction.z*VITESSE;
                xreg -= direction.x*VITESSE;
                zreg -= direction.z*VITESSE;           
            }
              
            glutPostRedisplay();            
            break;

        case TOUCHE_K :
            anglex = 0.05;

            //création de la matrice rotation selon un angle et un axe quelconque
            vecXx = pow(tete.x,2)*(1-cos(anglex))+cos(anglex);
            vecXz = tete.x*tete.z*(1-cos(anglex))+tete.y*sin(anglex);
            vecXy = tete.x*tete.y*(1-cos(anglex))-tete.z*sin(anglex);

            vecYy = pow(tete.y,2)*(1-cos(anglex))+cos(anglex);
            vecYz = tete.y*tete.z*(1-cos(anglex))+tete.x*sin(anglex);
            vecYx = tete.x*tete.y*(1-cos(anglex))-tete.z*sin(anglex);

            vecZz = pow(tete.z,2)*(1-cos(anglex))+cos(anglex);
            vecZx = tete.x*tete.z*(1-cos(anglex))-tete.y*sin(anglex);
            vecZy = tete.z*tete.y*(1-cos(anglex))+tete.x*sin(anglex);


            //on applique cette rotation au vecteur direction
            direction.x = (vecXx*direction.x)+(vecXy*direction.y)+(vecXz*direction.z);
            direction.y = (vecYx*direction.x)+(vecYy*direction.y)+(vecYz*direction.z);
            direction.z = (vecZx*direction.x)+(vecZy*direction.y)+(vecZz*direction.z);

            //on applique cette rotation au vecteur gauche
            gauche.x = (vecXx*gauche.x)+(vecXy*gauche.y)+(vecXz*gauche.z);
            gauche.y = (vecYx*gauche.x)+(vecYy*gauche.y)+(vecYz*gauche.z);
            gauche.z = (vecZx*gauche.x)+(vecZy*gauche.y)+(vecZz*gauche.z);


            //on applique cette rotation au position du regard
            xreg = (vecXx*xreg)+(vecXy*yreg)+(vecXz*zreg);
            yreg = (vecYx*xreg)+(vecYy*yreg)+(vecYz*zreg);
            zreg = (vecZx*xreg)+(vecZy*yreg)+(vecZz*zreg);
            x+=10;
            glutPostRedisplay();            
            break;

        case TOUCHE_M :
            anglex = -0.05;

            //création de la matrice rotation selon un angle et un axe quelconque
            vecXx = pow(tete.x,2)*(1-cos(anglex))+cos(anglex);
            vecXz = tete.x*tete.z*(1-cos(anglex))+tete.y*sin(anglex);
            vecXy = tete.x*tete.y*(1-cos(anglex))-tete.z*sin(anglex);

            vecYy = pow(tete.y,2)*(1-cos(anglex))+cos(anglex);
            vecYz = tete.y*tete.z*(1-cos(anglex))+tete.x*sin(anglex);
            vecYx = tete.x*tete.y*(1-cos(anglex))-tete.z*sin(anglex);

            vecZz = pow(tete.z,2)*(1-cos(anglex))+cos(anglex);
            vecZx = tete.x*tete.z*(1-cos(anglex))-tete.y*sin(anglex);
            vecZy = tete.z*tete.y*(1-cos(anglex))+tete.x*sin(anglex);


            //on applique cette rotation au vecteur direction
            direction.x = (vecXx*direction.x)+(vecXy*direction.y)+(vecXz*direction.z);
            direction.y = (vecYx*direction.x)+(vecYy*direction.y)+(vecYz*direction.z);
            direction.z = (vecZx*direction.x)+(vecZy*direction.y)+(vecZz*direction.z);

            //on applique cette rotation au vecteur gauche
            gauche.x = (vecXx*gauche.x)+(vecXy*gauche.y)+(vecXz*gauche.z);
            gauche.y = (vecYx*gauche.x)+(vecYy*gauche.y)+(vecYz*gauche.z);
            gauche.z = (vecZx*gauche.x)+(vecZy*gauche.y)+(vecZz*gauche.z);


            //on applique cette rotation au position du regard
            xreg = (vecXx*xreg)+(vecXy*yreg)+(vecXz*zreg);
            yreg = (vecYx*xreg)+(vecYy*yreg)+(vecYz*zreg);
            zreg = (vecZx*xreg)+(vecZy*yreg)+(vecZz*zreg);
            x+=10;
            glutPostRedisplay();            
            break;

        case TOUCHE_ESP:
            MAJdirectionGauche();
            MAJboxJoueur();

            Cote *punch = (Cote*)malloc(sizeof(Cote));
            if(punch == NULL){
                printf("erreur d'allocation mémoire pour le segmant punch\n");
                exit(EXIT_FAILURE);
            }
            punch->p1 = DG;
            punch->p2 = DD;

            boolean = verificationAlien(punch,1);
            free(punch);

            glutPostRedisplay();            
            break;
        
    }
}
