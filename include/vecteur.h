typedef struct{
    float x;
    float y;
    float z;
}Vecteur;

typedef struct{
    float x;
    float y;
}Point;

typedef struct{
    Point p1;
    Point p2;
}Cote;

typedef struct{
    Cote C1;
    Cote C2;
    Cote C3;
    Cote C4;
}Carre;

Vecteur initialisation_vecteur_direction();
Vecteur initialisation_vecteur_gauche();
Vecteur initialisation_vecteur_tete();
Vecteur normalisation(Vecteur v);
Point initialise_point();
int intersection(Cote s1, Cote s2) ;