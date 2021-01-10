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

    glBindVertexArray(vao[0]);

    for (indFace=0; indFace<NFACCE; indFace++) {
        glDrawArrays(GL_TRIANGLE_FAN, indFace*NVERTICI, NVERTICI);
    };

    glPopMatrix();

    glFinish();
    glutPostRedisplay();

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

    /* inizializzazione vao */
    glGenVertexArrays(1, vao);

    glBindVertexArray(vao[0]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glGenBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    int i;
    for(i = 0; i < NFACCE * NVERTICI; i++){
        indices[i] = i;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColorPointer(3, GL_FLOAT, 0, (GLvoid *)(sizeof(vertices)));
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