output: main.c hemisphere.o shader.o torus.o
	gcc -o output main.c hemisphere.o shader.o torus.o -lGL -LGLUT -lglut -lGLEW -lX11 -lm

hemisphere.o: hemisphere.c
	gcc -c hemisphere.c -lGL -LGLUT -lglut -lGLEW -lX11 -lm

shader.o: shader.c
	gcc -c shader.c -lGL -LGLUT -lglut -lGLEW -lX11 -lm

torus.o: torus.c
	gcc -c torus.c -lGL -LGLUT -lglut -lGLEW -lX11 -lm

