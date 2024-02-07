#include "../include/include.h"
#include "../include/vecteur.h"

extern Carre *Objects[4]; 

/*-------------------------------------------------*/
/*|         FONCTIONS pour la 3D                  |*/
/*-------------------------------------------------*/
/*Generation de la map*/

void sphere(float xc, float yc, float zc, float rayon, float r, float b, float v) { 
    int i, j;
    GLfloat theta1, theta2, phi, x, y, z;
    int slices = 20;
    int stacks = 20;
    float ratio = 1.2;
    
    glColor3f(r, b, v);
    for (i = 0; i < slices/2; i++) {
        theta1 = i * 2.0 * M_PI / slices;
        theta2 = (i + 1) * 2.0 * M_PI / slices;

        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= stacks; j++) {
            phi = j * M_PI / stacks;

            x = rayon * cos(theta2) * sin(phi)  * ratio + xc;
            y = rayon * sin(theta2) * sin(phi) + yc;
            z = rayon * cos(phi) + zc;
            glVertex3f(x, y, z);

            x = rayon * cos(theta1) * sin(phi) * ratio + xc;
            y = rayon * sin(theta1) * sin(phi) + yc;
            z = rayon * cos(phi) + zc;
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

void generation_ovni(float xf, float yf, float zf) {
	glColor3f(0.6f, 0.6f, 0.6f); // Couleur gris clair
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++) {
		float angle = i * 3.14159f / 180.0f;
		float x = xf + 20 * cos(angle); // Centre x: 0, Rayon: 60
		float z = zf + 20 * sin(angle); // Centre z: 0, Rayon: 40
		glVertex3f(x, 20, z);
	}
	glEnd();
	
	sphere(xf,20,zf,8,0,1,0);

	glBegin(GL_QUADS); // Début de la définition de la ligne
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex3f(xf, 20, zf-0.5);
    glVertex3f(xf, 20, zf+0.5);
	glVertex3f(xf-2, 0, zf+3);
    glVertex3f(xf-2, 0, zf-3);

	glVertex3f(xf, 20, zf+0.5);
    glVertex3f(xf+0.5, 20, zf+0.5);
	glVertex3f(xf+2, 0, zf+3);
    glVertex3f(xf-2, 0, zf+3);

	glVertex3f(xf, 20, zf-0.5);
    glVertex3f(xf+0.5, 20, zf-0.5);
	glVertex3f(xf-2, 0, zf-3);
    glVertex3f(xf+2, 0, zf-3);

	glVertex3f(xf+0.5, 20, zf-0.5);
    glVertex3f(xf+0.5, 20, zf+0.5);
	glVertex3f(xf+2, 0, zf+3);
    glVertex3f(xf+2, 0, zf-3);
	glEnd();
	
}

void generation_axe(float x, float y, float z, float taille){
	glBegin(GL_LINES); // Début de la définition de la ligne
        glColor3f(1.0f, 0.0f, 0.0f); // Rouge x
        glVertex3f(x, y, z);
        glVertex3f(x+taille, y, z);

        glColor3f(0.0f, 1.0f, 0.0f); // Vert y
        glVertex3f(x, y, z);
        glVertex3f(x, y+taille, z);

        glColor3f(0.0f, 0.0f, 1.0f); // Bleu z
        glVertex3f(x, y, z);
        glVertex3f(x, y, z+taille);
    	glEnd(); // Fin de la définition de la ligne
}


void generation_cube(float x, float y, float z, float dimension, float r, float g, float b){
	glBegin(GL_QUADS);
	glColor3f(r,g,b);
	glVertex3f(x,y,z);
	glVertex3f(x,y+dimension,z);
	glVertex3f(x,y+dimension,z+dimension);
	glVertex3f(x,y,z+dimension);

	glVertex3f(x,y,z+dimension);
	glVertex3f(x,y+dimension,z+dimension);
	glVertex3f(x+dimension,y+dimension,z+dimension);
	glVertex3f(x+dimension,y,z+dimension);

	glVertex3f(x+dimension,y,z+dimension);
	glVertex3f(x+dimension,y+dimension,z+dimension);
	glVertex3f(x+dimension,y+dimension,z);
	glVertex3f(x+dimension,y,z);
	
	glVertex3f(x+dimension,y,z);
	glVertex3f(x+dimension,y+dimension,z);
	glVertex3f(x,y+dimension,z);
	glVertex3f(x,y,z);
	
	glVertex3f(x,y+dimension,z);
	glVertex3f(x+dimension,y+dimension,z);
	glVertex3f(x+dimension,y+dimension,z+dimension);
	glVertex3f(x,y+dimension,z+dimension);
	
	glVertex3f(x,y,z);
	glVertex3f(x+dimension,y,z);
	glVertex3f(x+dimension,y,z+dimension);
	glVertex3f(x,y,z+dimension);
	glEnd();
}

void generation_hexa(float x, float y, float z, float dimension, float r, float g, float b){
	glBegin(GL_QUADS);

	glColor3f(r-0.03,g-0.03,b-0.03);
	glVertex3f(x,y,z+1*dimension);
	glVertex3f(x,y,z+3*dimension);
	glVertex3f(x,y+4*dimension,z+3*dimension);
	glVertex3f(x,y+4*dimension,z+1*dimension);

	glVertex3f(x+1*dimension,y,z);
	glVertex3f(x+3*dimension,y,z);
	glVertex3f(x+3*dimension,y+4*dimension,z);
	glVertex3f(x+1*dimension,y+4*dimension,z);

	glVertex3f(x+4*dimension,y,z+1*dimension);
	glVertex3f(x+4*dimension,y,z+3*dimension);
	glVertex3f(x+4*dimension,y+4*dimension,z+3*dimension);
	glVertex3f(x+4*dimension,y+4*dimension,z+1*dimension);

	glVertex3f(x+1*dimension,y,z+4*dimension);
	glVertex3f(x+3*dimension,y,z+4*dimension);
	glVertex3f(x+3*dimension,y+4*dimension,z+4*dimension);
	glVertex3f(x+1*dimension,y+4*dimension,z+4*dimension);

	glColor3f(r,g,b);
	glVertex3f(x+1*dimension,y,z);
	glVertex3f(x,y,z+1*dimension);
	glVertex3f(x,y+4*dimension,z+1*dimension);
	glVertex3f(x+1*dimension,y+4*dimension,z);

	glVertex3f(x,y,z+3*dimension);
	glVertex3f(x+1*dimension,y,z+4*dimension);
	glVertex3f(x+1*dimension,y+4*dimension,z+4*dimension);
	glVertex3f(x,y+4*dimension,z+3*dimension);

	glVertex3f(x+3*dimension,y,z+4*dimension);
	glVertex3f(x+4*dimension,y,z+3*dimension);
	glVertex3f(x+4*dimension,y+4*dimension,z+3*dimension);
	glVertex3f(x+3*dimension,y+4*dimension,z+4*dimension);

	glVertex3f(x+3*dimension,y,z);
	glVertex3f(x+4*dimension,y,z+1*dimension);
	glVertex3f(x+4*dimension,y+4*dimension,z+1*dimension);
	glVertex3f(x+3*dimension,y+4*dimension,z);

	glEnd();


	glBegin(GL_POLYGON);
		glColor3f(r-0.03,g-0.03,b-0.03);
		glVertex3f(x,y,z+1*dimension);
		glVertex3f(x,y,z+3*dimension);
		glVertex3f(x+1*dimension,y,z+4*dimension);
		glVertex3f(x+3*dimension,y,z+4*dimension);
		glVertex3f(x+4*dimension,y,z+3*dimension);
		glVertex3f(x+4*dimension,y,z+1*dimension);
		glVertex3f(x+3*dimension,y,z);
		glVertex3f(x+1*dimension,y,z);
	glEnd();
}


void generation_arbre(float x, float z, int indiceObject){
	Objects[indiceObject] = (Carre*)malloc(sizeof(Carre));
	if(Objects[indiceObject] == NULL){
		printf("erreur d'allocation mémoire pour l'arbre : %d\n",indiceObject);
		exit(EXIT_FAILURE);
	}

	Objects[indiceObject]->C1.p1.x = x-2;
	Objects[indiceObject]->C1.p1.y = z-2;
	Objects[indiceObject]->C1.p2.x = x-2;
	Objects[indiceObject]->C1.p2.y = z+6;
	
	Objects[indiceObject]->C2.p1.x = x-2;
	Objects[indiceObject]->C2.p1.y = z+6;
	Objects[indiceObject]->C2.p2.x = x+6;
	Objects[indiceObject]->C2.p2.y = z+6;

	Objects[indiceObject]->C3.p1.x = x+6;
	Objects[indiceObject]->C3.p1.y = z+6;
	Objects[indiceObject]->C3.p2.x = x+6;
	Objects[indiceObject]->C3.p2.y = z-2;

	Objects[indiceObject]->C4.p1.x = x+2;
	Objects[indiceObject]->C4.p1.y = z-2;
	Objects[indiceObject]->C4.p2.x = x+6;
	Objects[indiceObject]->C4.p2.y = z-2;

	//generation_axe(x+2,0,z+2,2);
	generation_hexa(x,0,z,1,0.30f, 0.13f, 0.04f);
	generation_hexa(x,4,z,1,0.30f, 0.13f, 0.04f);
	generation_hexa(x,8,z,1,0.30f, 0.13f, 0.04f);
	generation_hexa(x,12,z,1,0.30f, 0.13f, 0.04f);
	int xf = x-4;
	int zf = z-4;
	generation_hexa(xf,12,zf,3,0.0f, 0.5f, 0.0f);
}

void generation_mur(){
	glColor3f(0.16f,0.07f,0.16f);
	glBegin(GL_QUADS);
	glVertex3f(100.0f,0.0f,-100.0f);
	glVertex3f(100.0f,10.0f,-100.0f);
	glVertex3f(100.0f,10.0f,100.0f);
	glVertex3f(100.0f,0.0f,100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-100.0f,0.0f,-100.0f);
	glVertex3f(-100.0f,10.0f,-100.0f);
	glVertex3f(100.0f,10.0f,-100.0f);
	glVertex3f(100.0f,0.0f,-100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-100.0f,0.0f,100.0f);
	glVertex3f(-100.0f,10.0f,100.0f);
	glVertex3f(-100.0f,10.0f,-100.0f);
	glVertex3f(-100.0f,0.0f,-100.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(100.0f,0.0f,100.0f);
	glVertex3f(100.0f,10.0f,100.0f);
	glVertex3f(-100.0f,10.0f,100.0f);
	glVertex3f(-100.0f,0.0f,100.0f);
	glEnd();
}


void generation_sol(){
	glColor3f(0.0f, 0.39f, 0.0f);
	glBegin(GL_QUADS);

	glVertex3f(-100.0f,0.0f,-100.0f);
	glVertex3f(-100.0f,0.0f,100.0f);
	glVertex3f(100.0f,0.0f,100.0f);
	glVertex3f(100.0f,0.0f,-100.0f);

	glEnd();
}

void generation_creature(float x, float y, float z, float dimension, float r, float g, float b){
	
	generation_cube(x+0.5,y,z+0.5,dimension-1,r,g,b);
	generation_cube(x+0.5,y+1,z+0.5,dimension-1,r,g,b);

	generation_cube(x+0.5, y+dimension, z+0.5, dimension-1, r, g, b);
	generation_cube(x+0.5, y+dimension+1, z+0.5, dimension-1, r, g, b);

	//tete
	generation_cube(x, y+(2*dimension), z, dimension, r, g, b);


}
