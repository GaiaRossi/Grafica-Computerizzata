#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();

}

void init(){

    glClearColor(0.0, 0.0, 0.0, 0.0);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(600, 400);
    glutInitWindowPosition(200, 700);
    glutCreateWindow("assignment 3");

    GLenum err = glewInit();
    if(err != GLEW_OK){
        fprintf(stderr, "Errore inizializzazione GLEW: %s\n", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    else{
        printf("GLEW init success\n");
    }

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}