main : obj/clavier.o obj/creature.o obj/generation.o obj/glut.o obj/souris.o obj/vecteur.o src/main.c 
	gcc -Wall src/main.c obj/clavier.o obj/creature.o obj/generation.o obj/glut.o obj/souris.o obj/vecteur.o -o main -lglut -lm -lGLU -lGL

obj/clavier.o : src/clavier.c include/clavier.h
	gcc -c -Wall src/clavier.c -o obj/clavier.o -lglut -lm -lGLU -lGL

obj/creature.o : src/creature.c include/creature.h
	gcc -c -Wall src/creature.c -o obj/creature.o -lglut -lm -lGLU -lGL

obj/generation.o : src/generation.c include/generation.h
	gcc -c -Wall src/generation.c -o obj/generation.o -lglut -lm -lGLU -lGL

obj/glut.o : src/glut.c include/glut.h
	gcc -c -Wall src/glut.c -o obj/glut.o -lglut -lm -lGLU -lGL

obj/souris.o : src/souris.c include/souris.h
	gcc -c -Wall src/souris.c -o obj/souris.o -lglut -lm -lGLU -lGL

obj/vecteur.o : src/vecteur.c include/vecteur.h
	gcc -c -Wall src/vecteur.c -o obj/vecteur.o -lglut -lm -lGLU -lGL

clean :
	rm -f main obj/*.o
