#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>

#include "pianeti.h"
#include "window.h"
#include "dati.h"
#include "circle.h"

/*
GLfloat coordinate_test[SLICES * 3 + 3];
unsigned int indici[SLICES + 2];
unsigned int buffers[2];
*/

#define SPAZIO 0.00360

void aggiorna_angoli(int value){
    angolo_mercurio += SPAZIO/RIVOLUZIONE_MERCURIO;
    angolo_venere += SPAZIO/RIVOLUZIONE_VENERE;
    angolo_terra += SPAZIO/RIVOLUZIONE_TERRA;
    angolo_marte += SPAZIO/RIVOLUZIONE_MARTE;
    angolo_giove += SPAZIO/RIVOLUZIONE_GIOVE;
    angolo_saturno += SPAZIO/RIVOLUZIONE_SATURNO;
    angolo_urano += SPAZIO/RIVOLUZIONE_URANO;
    angolo_nettuno += SPAZIO/RIVOLUZIONE_NETTUNO;
    
}

void display(){
    GLint indFace;
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(coordinate_sole[0], coordinate_sole[1], coordinate_sole[2]);
    glColor3fv(colore_sole);
    glBindVertexArray(vao[SOLE]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_mercurio[0] - coordinate_sole[0]) * cos(angolo_mercurio) + coordinate_sole[0],
                 (coordinate_mercurio[0] - coordinate_sole[0]) * sin(angolo_mercurio) + coordinate_sole[1],
                 coordinate_mercurio[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_MERCURIO/SCALA, 4 * RAGGIO_MERCURIO/SCALA, 0.0);
    char *mercurio = "mercurio";
    for(i = 0; i < 9; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, mercurio[i]);
    }
    glPopMatrix();
    glColor3fv(colore_mercurio);
    glBindVertexArray(vao[MERCURIO]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_venere[0] - coordinate_sole[0]) * cos(angolo_venere) + coordinate_sole[0],
                 (coordinate_venere[0] - coordinate_sole[0]) * sin(angolo_venere) + coordinate_sole[1],
                 coordinate_venere[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_VENERE/SCALA, 4 * RAGGIO_VENERE/SCALA, 0.0);
    char *venere = "venere";
    for(i = 0; i < 7; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, venere[i]);
    }
    glPopMatrix();
    glColor3fv(colore_venere);
    glBindVertexArray(vao[VENERE]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_terra[0] - coordinate_sole[0]) * cos(angolo_terra) + coordinate_sole[0],
                 (coordinate_terra[0] - coordinate_sole[0]) * sin(angolo_terra) + coordinate_sole[1],
                 coordinate_terra[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_TERRA/SCALA, 4 * RAGGIO_TERRA/SCALA, 0.0);
    char *terra = "terra";
    for(i = 0; i < 6; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, terra[i]);
    }
    glPopMatrix();
    glColor3fv(colore_terra);
    glBindVertexArray(vao[TERRA]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_marte[0] - coordinate_sole[0]) * cos(angolo_marte) + coordinate_sole[0],
                 (coordinate_marte[0] - coordinate_sole[0]) * sin(angolo_marte) + coordinate_sole[1],
                 coordinate_marte[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_MARTE/SCALA, 4 * RAGGIO_MARTE/SCALA, 0.0);
    char *marte = "marte";
    for(i = 0; i < 6; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, marte[i]);
    }
    glPopMatrix();
    glColor3fv(colore_marte);
    glBindVertexArray(vao[MARTE]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_giove[0] - coordinate_sole[0]) * cos(angolo_giove) + coordinate_sole[0],
                 (coordinate_giove[0] - coordinate_sole[0]) * sin(angolo_giove) + coordinate_sole[1],
                 coordinate_giove[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_GIOVE/SCALA, 4 * RAGGIO_GIOVE/SCALA, 0.0);
    char *giove = "giove";
    for(i = 0; i < 6; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, giove[i]);
    }
    glPopMatrix();
    glColor3fv(colore_giove);
    glBindVertexArray(vao[GIOVE]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_saturno[0] - coordinate_sole[0]) * cos(angolo_saturno) + coordinate_sole[0],
                 (coordinate_saturno[0] - coordinate_sole[0]) * sin(angolo_saturno) + coordinate_sole[1],
                 coordinate_saturno[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_SATURNO/SCALA, 4 * RAGGIO_SATURNO/SCALA, 0.0);
    char *saturno = "saturno";
    for(i = 0; i < 8; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, saturno[i]);
    }
    glPopMatrix();
    glColor3fv(colore_saturno);
    glBindVertexArray(vao[SATURNO]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_urano[0] - coordinate_sole[0]) * cos(angolo_urano) + coordinate_sole[0],
                 (coordinate_urano[0] - coordinate_sole[0]) * sin(angolo_urano) + coordinate_sole[1],
                 coordinate_urano[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_URANO/SCALA, 4 * RAGGIO_URANO/SCALA, 0.0);
    char *urano = "urano";
    for(i = 0; i < 6; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, urano[i]);
    }
    glPopMatrix();
    glColor3fv(colore_urano);
    glBindVertexArray(vao[URANO]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_nettuno[0] - coordinate_sole[0]) * cos(angolo_nettuno) + coordinate_sole[0],
                 (coordinate_nettuno[0] - coordinate_sole[0]) * sin(angolo_nettuno) + coordinate_sole[1],
                 coordinate_nettuno[2]);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_NETTUNO/SCALA, 4 * RAGGIO_NETTUNO/SCALA, 0.0);
    char *nettuno = "nettuno";
    for(i = 0; i < 8; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, nettuno[i]);
    }
    glPopMatrix();
    glColor3fv(colore_nettuno);
    glBindVertexArray(vao[NETTUNO]);
    glDrawElements(GL_TRIANGLE_FAN, SLICES + 2, GL_UNSIGNED_INT, 0);
    glPopMatrix();
    
    glutTimerFunc(TEMPO, aggiorna_angoli, 0);

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
    glOrtho(0.0, VIEW_WIDTH, 0.0, VIEW_HEIGHT, VIEW_NEAR, VIEW_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    glGenVertexArrays(NUMERO_PIANETI, vao);

    glBindVertexArray(vao[SOLE]);
    calcola_coordinate(sole_vertex, SLICES, RAGGIO_SOLE/SCALA);
    genera_indici(sole_indices, SLICES + 2);
    glGenBuffers(2, sole_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, sole_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sole_vertex), sole_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sole_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sole_indices), sole_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glBindVertexArray(vao[MERCURIO]);
    calcola_coordinate(mercurio_vertex, SLICES, RAGGIO_MERCURIO/SCALA);
    genera_indici(mercurio_indices, SLICES + 2);
    glGenBuffers(2, mercurio_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, mercurio_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mercurio_vertex), mercurio_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mercurio_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mercurio_indices), mercurio_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glBindVertexArray(vao[VENERE]);
    calcola_coordinate(venere_vertex, SLICES, RAGGIO_VENERE/SCALA);
    genera_indici(venere_indices, SLICES + 2);
    glGenBuffers(2, venere_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, venere_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(venere_vertex), venere_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, venere_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(venere_indices), venere_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glBindVertexArray(vao[TERRA]);
    calcola_coordinate(terra_vertex, SLICES, RAGGIO_VENERE/SCALA);
    genera_indici(terra_indices, SLICES + 2);
    glGenBuffers(2, terra_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, terra_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(terra_vertex), terra_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terra_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(terra_indices), terra_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glBindVertexArray(vao[MARTE]);
    calcola_coordinate(marte_vertex, SLICES, RAGGIO_MARTE/SCALA);
    genera_indici(marte_indices, SLICES + 2);
    glGenBuffers(2, marte_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, marte_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(marte_vertex), marte_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, marte_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(marte_indices), marte_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindVertexArray(vao[GIOVE]);
    calcola_coordinate(giove_vertex, SLICES, RAGGIO_GIOVE/SCALA);
    genera_indici(giove_indices, SLICES + 2);
    glGenBuffers(2, giove_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, giove_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(giove_vertex), giove_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, giove_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(giove_indices), giove_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glBindVertexArray(vao[SATURNO]);
    calcola_coordinate(saturno_vertex, SLICES, RAGGIO_SATURNO/SCALA);
    genera_indici(saturno_indices, SLICES + 2);
    glGenBuffers(2, saturno_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, saturno_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(saturno_vertex), saturno_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, saturno_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(saturno_indices), saturno_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glBindVertexArray(vao[URANO]);
    calcola_coordinate(urano_vertex, SLICES, RAGGIO_URANO/SCALA);
    genera_indici(urano_indices, SLICES + 2);
    glGenBuffers(2, urano_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, urano_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(urano_vertex), urano_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, urano_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(urano_indices), urano_indices, GL_STATIC_DRAW);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glBindVertexArray(vao[NETTUNO]);
    calcola_coordinate(nettuno_vertex, SLICES, RAGGIO_NETTUNO/SCALA);
    genera_indici(nettuno_indices, SLICES + 2);
    glGenBuffers(2, nettuno_buffers);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, nettuno_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(nettuno_vertex), nettuno_vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nettuno_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(nettuno_indices), nettuno_indices, GL_STATIC_DRAW);
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