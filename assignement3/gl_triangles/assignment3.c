#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

#include "cubo.h"

unsigned int vao[1];
unsigned int buffers[2];

void display(){
    GLint indFace;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(10.0, 10.0, -3.0);
    glRotatef(30, 0.0, 1.0, 0.0);
    glRotatef(-20, 1.0, 0.0, 0.0);

    //prima faccia
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(LATO, 0.0, 0.0);
        glVertex3f(LATO * 2/3, LATO/3, 0.0);
        glVertex3f(LATO/3, LATO/3, 0.0);
        glVertex3f(LATO/3, LATO * 2/3, 0.0);
        glVertex3f(0.0, LATO, 0.0);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(LATO, LATO, 0.0);
        glVertex3f(LATO, 0.0, 0.0);
        glVertex3f(LATO * 2/3, LATO/3, 0.0);
        glVertex3f(LATO * 2/3, LATO * 2/3, 0.0);
        glVertex3f(LATO/3, LATO * 2/3, 0.0);
        glVertex3f(0.0, LATO, 0.0);
    glEnd();

    //seconda faccia
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(LATO, 0.0, 0.0);
        glVertex3f(LATO, LATO, 0.0);
        glVertex3f(LATO, LATO * 2/3, LATO/3);
        glVertex3f(LATO, LATO/3, LATO/3);
        glVertex3f(LATO, LATO/3, LATO * 2/3);
        glVertex3f(LATO, 0.0, LATO);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(LATO, LATO, LATO);
        glVertex3f(LATO, LATO, 0.0);
        glVertex3f(LATO, LATO * 2/3, LATO/3);
        glVertex3f(LATO, LATO * 2/3, LATO * 2/3);
        glVertex3f(LATO, LATO/3, LATO * 2/3);
        glVertex3f(LATO, 0.0, LATO);
    glEnd();

    //terza faccia
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(LATO, 0.0, LATO);
        glVertex3f(0.0, 0.0, LATO);
        glVertex3f(LATO/3, LATO/3, LATO);
        glVertex3f(LATO * 2/3, LATO/3, LATO);
        glVertex3f(LATO * 2/3, LATO * 2/3, LATO);
        glVertex3f(LATO, LATO, LATO);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, LATO, LATO);
        glVertex3f(0.0, 0.0, LATO);
        glVertex3f(LATO/3, LATO/3, LATO);
        glVertex3f(LATO/3, LATO * 2/3, LATO);
        glVertex3f(LATO * 2/3, LATO * 2/3, LATO);
        glVertex3f(LATO, LATO, LATO);
    glEnd();

    //quarta faccia
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, LATO);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, LATO/3, LATO/3);
        glVertex3f(0.0, LATO/3, LATO * 2/3);
        glVertex3f(0.0, LATO * 2/3, LATO * 2/3);
        glVertex3f(0.0, LATO, LATO);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0, LATO, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, LATO/3, LATO/3);
        glVertex3f(0.0, LATO * 2/3, LATO/3);
        glVertex3f(0.0, LATO * 2/3, LATO * 2/3);
        glVertex3f(0.0, LATO, LATO);
    glEnd();
    

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