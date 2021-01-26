#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

#include "cuboNoIndices.h"

unsigned int vao[1];
unsigned int buffers[2];

void display(){
    GLint indFace;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(10.0, 10.0, -3.0);
    glRotatef(30, 0.0, 1.0, 0.0);
    glRotatef(-20, 1.0, 0.0, 0.0);

    for(indFace=0; indFace<NFACCE; indFace++) {
        glDrawArrays(GL_TRIANGLE_FAN, indFace*NVERTICI, NVERTICI);
    };
    glPopMatrix();

    glFlush();

}

void init(){

    GLenum glErr;
    if ((glErr=glGetError()) != 0) {
            printf("Errore = %d \n", glErr);
            exit(-1);
        }

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glMatrixMode(GL_PROJECTION);
    //glFrustum(0.0, 20.0, 0.0, 20.0, 2.0, 20.0);
    glOrtho(0.0, 20.0, 0.0, 20.0, 0.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    glDisable(GL_CULL_FACE);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);

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