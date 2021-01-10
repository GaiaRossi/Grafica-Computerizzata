#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

#include "pianeti.h"
#include "window.h"
#include "dati.h"
#include "circle.h"

GLfloat coordinate_test[10 * 3];
unsigned int indici[11] = {0, 7, 4, 1, 8, 5, 2, 9, 6, 3, 7};
unsigned int buffers[2];

void display(){
    GLint indFace;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    //sole
    glTranslatef(coordinate_sole[0], coordinate_sole[1], coordinate_sole[2]);
    glColor3fv(colore_sole);
    
    int i;
    for(i = 0; i < 10; i++){
        printf("x: %f, y: %f, z: %f\n", coordinate_test[i * 3],
                                        coordinate_test[i * 3 + 1],
                                        coordinate_test[i * 3 + 2]);
    }


    glDrawElements(GL_TRIANGLE_FAN, 11, GL_UNSIGNED_INT, 0);


    glPopMatrix();


    glFinish();
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
    glOrtho(0.0, VIEW_WIDTH, 0.0, VIEW_HEIGHT, VIEW_NEAR, VIEW_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    calcola_coordinate(coordinate_test, 10, 10.0);
    glGenBuffers(2, buffers);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordinate_test), coordinate_test, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indici), indici, GL_STATIC_DRAW);

    glVertexPointer(3, GL_FLOAT, 0, 0);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitWindowPosition(200, 700);
    glutCreateWindow("assignment 4");

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