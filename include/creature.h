#include "vecteur.h"
typedef struct{
    float pos_x;
    float pos_y;
    float pos_z;
    Vecteur deplacement;
    /* État de recherche d'une autre créature, bool */
    int etat;
    int enfant;
}Creature;

Creature* creerTableauCreature(int taille);
Creature* obtenirTableauCreature();
int trouverCreaturePlusProche(Creature* creature, int indexCreature);
void mettreAJourAlienEnfant(Creature* creature, int indice);
void deplacerCreature(Creature* creature,float distanceDeplacement);