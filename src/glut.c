#include "../include/creature.h"
#include "../include/generation.h"
#include "../include/glut.h"
#include "../include/include.h"

extern float zpos,xpos,ypos;
extern float zreg,xreg,yreg;

Carre *Objects[24];
float distanceDeplacement;
int Arbres[10];
extern int generation;
extern int finPartie;

/*-------------------------------------------------*/
/*|    FONCTIONS Pour GLUT                        |*/
/*-------------------------------------------------*/

/*Fonction d'affichage*/
void affichage(){
    int ji;
    int indice_arbre = 0;
    if(finPartie == 1){
        const char* messageTemplate = "Temps ecoule ! Partie terminee ! Score = %d";
        char message[100]; // Choisir une taille appropriée pour la chaîne de message
        int score = nombreAliens - 4;
        sprintf(message, messageTemplate, score);

        glColor3f(1.0f, 1.0f, 1.0f); // Couleur du texte (blanc)

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, LARGEUR_FENETRE, 0, HAUTEUR_FENETRE);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glRasterPos2f(LARGEUR_FENETRE / 2 - strlen(message) * 8, HAUTEUR_FENETRE / 2);
        for (int i = 0; i < strlen(message); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        glutSwapBuffers();

        return;
    }
    //fprintf(stdout,"%d > %d\n",currentTime, gameDuration);
    if (currentTime >= gameDuration) {
        finPartie = 1;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-5,5, -3,3, 5,500);
    gluLookAt(xpos,ypos,zpos, xreg,yreg,zreg, 0,1,0);
        
    //Récuperation du tableau des créatures
    Creature* tableau_creature = obtenirTableauCreature();

    //si on bouge pas on met a jour les créatures
    if(miseAJourAffichage){
        distanceDeplacement = 0.5;

    //sinon si on bouge pas besoin de mettre a jour les créatures
    }else{
        distanceDeplacement = 0;
    }
    deplacerCreature(tableau_creature,distanceDeplacement);

    //génération des créatures (GRAPHIQUE)
    for(int i = 0; i<nombreAliens; i++){
        if(tableau_creature[i].etat == 1){
            generation_creature(tableau_creature[i].pos_x,tableau_creature[i].pos_y,tableau_creature[i].pos_z,2,1,0,0);
        }else if(tableau_creature[i].enfant == 1){
            generation_creature(tableau_creature[i].pos_x,tableau_creature[i].pos_y,tableau_creature[i].pos_z,2,0,0,1);
        }else{
            generation_creature(tableau_creature[i].pos_x,tableau_creature[i].pos_y,tableau_creature[i].pos_z,2,0,1,0);
        }
        glColor3f(1.0, 1.0, 0.0);

        glBegin(GL_LINES);
        glVertex3f(tableau_creature[i].pos_x, tableau_creature[i].pos_y, tableau_creature[i].pos_z);
        glVertex3f(tableau_creature[i].pos_x + tableau_creature[i].deplacement.x * 10, tableau_creature[i].pos_y + tableau_creature[i].deplacement.y * 10, tableau_creature[i].pos_z + tableau_creature[i].deplacement.z * 10);
        glEnd();

        generation_axe(tableau_creature[i].pos_x,tableau_creature[i].pos_y,tableau_creature[i].pos_z,6);
    }

    //axe monde
    // generation_axe(0,0,0,500);
    generation_sol();
    generation_mur();

    generation_ovni(110,0,100);
    generation_ovni(110,0,-100);
    generation_ovni(110,0,0);
    generation_ovni(15,0,-25);


    //generation des arbres aleatoires
    if(generation == 0){
        for(ji = 0; ji<10;ji++){
            Arbres[ji] = rand()%(100 +100)-100;
        }
        generation = 1;
    }

    for(ji = 0;ji<10;ji++){
        generation_arbre(Arbres[ji],Arbres[ji+1],indice_arbre);
        ji++;
        indice_arbre++;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutSwapBuffers();
}
