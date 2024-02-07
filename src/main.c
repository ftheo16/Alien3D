#include "../include/include.h"
#include "../include/generation.h"
#include "../include/souris.h"
#include "../include/clavier.h"
#include "../include/glut.h"
#include "../include/creature.h"

/*-------------------------------------------------*/
/*|        Variables Globales                     |*/
/*-------------------------------------------------*/
//position et regard nécessaire pour lookat
float zpos=0,xpos=0,ypos=5;
float zreg=20,xreg=20,yreg=1;

//quatre position de la hitbox du personnage
Point DG,DD,AG,AD;

//Tbleau de tout les aliens
Creature* tableau_creature;

//les trois vecteur du joueur
Vecteur direction;
Vecteur gauche;
Vecteur tete;

//savoir s'il faut mettre a jour les aliens
int miseAJourAffichage = 1;

//savoir le nombre d'aliens qu'il y a
int nombreAliens = 10;

int startTime;
int currentTime;
int gameDuration = 5 * 60 * 1000;
int finPartie = 0;
int generation;

/*-------------------------------------------------*/
/*|                 MAIN                           |*/
/*-------------------------------------------------*/

//fonction qui permet de refresh les 1000ms (1 fois par seconde)
void temporisation(int valeur) {
    currentTime = glutGet(GLUT_ELAPSED_TIME) - startTime;
    miseAJourAffichage = 1;
    glutPostRedisplay();
    glutTimerFunc(1000, temporisation, 0);
}

int main(int argc, char *argv[]){
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(LARGEUR_FENETRE, HAUTEUR_FENETRE);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("ALIEN AIZNÀFDAPUBZOFPÇAUOZNIFA");

    glEnable(GL_DEPTH_TEST);
    glutSetCursor(GLUT_CURSOR_INFO);
    
    startTime = glutGet(GLUT_ELAPSED_TIME);
    generation = 0;
    //on initialise les vecteurs
    direction = initialisation_vecteur_direction();
    gauche = initialisation_vecteur_gauche();
    tete = initialisation_vecteur_tete();

    //initialise les points
    DG = initialise_point();
    DD = initialise_point();
    AG = initialise_point();
    AD = initialise_point();


    
    //fonction pour gerer les touches du clavier
    glutKeyboardFunc(GererClavier);

    //création du tableau des créatures
    tableau_creature = creerTableauCreature(TAILLEMAX);
    //for(int i =0; i<nombreAliens;i++){
      //  fprintf(stdout,"Alien numéro %d X:%f Y:%f Z:%f Etat:%d Enfant:%d\n",i,tableau_creature[i].pos_x,tableau_creature[i].pos_y,tableau_creature[i].pos_z,tableau_creature[i].etat,tableau_creature[i].enfant);
    //}
    
    glutDisplayFunc(affichage);


    if(finPartie == 0){
        //foncion pour gerer le deplacement et clic de la souris
        glutMouseFunc(GererSouris);
        glutMotionFunc(GererDepla);

        //fonction pour gerer les touches du clavier
        glutKeyboardFunc(GererClavier);
    }
    

    //permet d'avoir un refresh automatiquement
    glutTimerFunc(1000, temporisation, 0);

    glutMainLoop();
    return 0;
}