#include "GL/gl.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <time.h>

#define TOUCHE_Z 122
#define TOUCHE_D 100
#define TOUCHE_S 115
#define TOUCHE_Q 113
#define TOUCHE_M 109
#define TOUCHE_K 107
#define TOUCHE_ESP 32

#define VITESSE 0.5
#define LARGEUR_FENETRE 1580
#define HAUTEUR_FENETRE 1000
#define TAILLEMAX 500

extern int nombreAliens;
extern int currentTime;
extern int gameDuration;
extern int finPartie;
