#include "../include/vecteur.h"
#include "../include/include.h"


Vecteur initialisation_vecteur_direction(){
    Vecteur* tmp = (Vecteur*)malloc(sizeof(Vecteur));
    tmp->x=1;
    tmp->y=0;
    tmp->z=0;
    return *tmp;
}

Vecteur initialisation_vecteur_gauche(){
    Vecteur* tmp = (Vecteur*)malloc(sizeof(Vecteur));
    tmp->x=0;
    tmp->y=0;
    tmp->z=-1;
    return *tmp;
}

Vecteur initialisation_vecteur_tete(){
    Vecteur* tmp = (Vecteur*)malloc(sizeof(Vecteur));
    tmp->x=0;
    tmp->y=1;
    tmp->z=0;
    return *tmp;
}

Vecteur normalisation(Vecteur v){
    int n= sqrt(pow(v.x,2)+pow(v.z,2)+pow(v.y,2));
            v.x /= n;
            v.z /= n;
            v.y /= n;
    return v;
}

Point initialise_point(){
    Point* tmp = (Point*)malloc(sizeof(Point));
    tmp->x = 0;
    tmp->y = 0;
    return *tmp;
}

// fonction qui renvoie le point d'intersection de deux segments
int intersection(Cote s1, Cote s2) {
    int bool=0;

    float nume = (s1.p1.y - s1.p2.y);
    float deno = (s1.p1.x - s1.p2.x);
    float m = (nume)/(deno);
    float p = s1.p2.y - m * s1.p2.x;

    //Pour s2 :
    // y = ax+b 
    nume = (s2.p1.y - s2.p2.y);
    deno = (s2.p1.x - s2.p2.x);
    float a = (nume)/(deno);
    float b = s2.p2.y - a * s2.p2.x;

    if(m == a && p!=b ){
        //parallèle
        return 0;
    }else{//séquante
        // différents cas de l'intersection
        // on regarde les intervales des deux segement
        // avec tout les cas différents
        if(s1.p1.x > s1.p2.x){
            if(s2.p1.x > s2.p2.x){
                if(s1.p1.x > s2.p1.x){
                    if(s2.p1.x > s1.p2.x)
                        bool = 1;
                }else{
                    if(s1.p1.x > s2.p2.x)
                        bool = 1;
                }
            }else{
                if(s1.p1.x > s2.p2.x){
                    if(s2.p2.x > s1.p2.x)
                        bool = 1;
                }else{
                    if(s1.p1.x > s2.p1.x)
                        bool = 1;
                }
            }
        }else{
            if(s2.p1.x > s2.p2.x){
                if(s1.p2.x > s2.p1.x){
                    if(s2.p1.x > s1.p1.x)
                        bool = 1;
                }else{
                    if(s1.p2.x > s2.p2.x)
                        bool = 1;
                }
            }else{
                if(s1.p1.x > s2.p1.x){
                    if(s2.p2.x > s1.p1.x)
                        bool = 1;
                }else{
                    if(s1.p2.x > s2.p1.x)
                        bool = 1;
                }
            }
        }
        if(bool == 1){
            if(s1.p1.y > s1.p2.y){
                if(s2.p1.y > s2.p2.y){
                    if(s1.p1.y > s2.p1.y){
                        if(s2.p1.y > s1.p2.y)
                            return 1;
                    }else{
                        if(s1.p1.y > s2.p2.y)
                            return 1;
                    }
                }else{
                    if(s1.p1.y > s2.p2.y){
                        if(s2.p2.y > s1.p2.y)
                            return 1;
                    }else{
                        if(s1.p1.y > s2.p1.y)
                            return 1;
                    }
                }
            }else{
                if(s2.p1.y > s2.p2.y){
                    if(s1.p2.y > s2.p1.y){
                        if(s2.p1.y > s1.p1.y)
                            return 1;
                    }else{
                        if(s1.p2.y > s2.p2.y)
                            return 1;
                    }
                }else{
                    if(s1.p1.y > s2.p1.y){
                        if(s2.p2.y > s1.p1.y)
                            return 1;
                    }else{
                        if(s1.p2.y > s2.p1.y)
                            return 1;
                    }
                }
            }
        }
    }
    return 0;
}