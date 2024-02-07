
#include "../include/include.h"
#include "../include/souris.h"
#include "../include/vecteur.h"

int Xd=0,Yd=0;
int vecXprec=0;

extern float zpos,xpos,ypos;
extern float zreg,xreg,yreg;

extern Vecteur direction;
extern Vecteur gauche;
extern Vecteur tete;

extern int miseAJourAffichage;

void GererSouris(int button,int state,int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        miseAJourAffichage = 0;
    // Si clic gauche on stocke les positions de la souris
        Xd = x;
        Yd = y;
    }
    

}

void GererDepla(int x, int y){
    miseAJourAffichage = 0;
    //Matrice de rotation
    float vecXx,vecXy,vecXz;
    float vecYx,vecYy,vecYz;
    float vecZx,vecZy,vecZz;

    //distance parcourue de la souris
    int vecX;
    //int vecY;

    vecX = Xd-x;
    //vecY = Yd-y;

    //changement de sens en plein clic
    if( (vecXprec > vecX && vecX>0) || (vecXprec < vecX && vecX<0) ){
        Xd = x;
        Yd = y;
        vecX = Xd-x;
        //vecY = Yd-y;
    }

    //angle crée par la souris
    float anglex = (vecX*M_PI_4)/LARGEUR_FENETRE;
   // float angley = (vecY*M_PI_4)/HAUTEUR_FENETRE;

    //Calibrage de l'angle pour ne pas avoir de grand mouvement
    anglex = -(anglex/10);
    if(anglex > 0 ){
        anglex = 0.04;
    }else{
        anglex = -0.04;
    }
    //angley = -(angley/10);
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
    zreg += 10;

    vecXprec = vecX;
    glutPostRedisplay();
}
