output: main.c hemisphere.o shader.o
	gcc -o output main.c hemisphere.o shader.o -lGL -LGLUT -lglut -lGLEW -lX11 -lm

hemisphere.o: hemisphere.c
	gcc -c hemisphere.c -lGL -LGLUT -lglut -lGLEW -lX11 -lm

shader.o: shader.c
	gcc -c shader.c -lGL -LGLUT -lglut -lGLEW -lX11 -lm


