#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include "hemisphere.h"
#include "window.h"
#include "dati.h"
#include "pianeti.h"

#define SPAZIO 0.00360

unsigned int buffers[2];

static Vertex hemVertices[(HEM_LONGS + 1) * (HEM_LATS + 1)];
static unsigned int hemIndices[HEM_LATS][2 * (HEM_LONGS + 1)];
static int hemCounts[HEM_LATS];
static void *hemOffsets[HEM_LATS];
static vec4 hemColors = {HEM_COLORS};

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
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(coordinate_sole[0], coordinate_sole[1], 60.0);
    glColor3fv(colore_sole);
    glBindVertexArray(vao[SOLE]);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_mercurio[0] - coordinate_sole[0]) * cos(angolo_mercurio) + coordinate_sole[0],
                 (coordinate_mercurio[0] - coordinate_sole[0]) * sin(angolo_mercurio) + coordinate_sole[1],
                 60.0);
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
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_venere[0] - coordinate_sole[0]) * cos(angolo_venere) + coordinate_sole[0],
                 (coordinate_venere[0] - coordinate_sole[0]) * sin(angolo_venere) + coordinate_sole[1],
                 60.0);
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
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_terra[0] - coordinate_sole[0]) * cos(angolo_terra) + coordinate_sole[0],
                 (coordinate_terra[0] - coordinate_sole[0]) * sin(angolo_terra) + coordinate_sole[1],
                 60.0);
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
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_marte[0] - coordinate_sole[0]) * cos(angolo_marte) + coordinate_sole[0],
                 (coordinate_marte[0] - coordinate_sole[0]) * sin(angolo_marte) + coordinate_sole[1],
                 60.0);
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
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_giove[0] - coordinate_sole[0]) * cos(angolo_giove) + coordinate_sole[0],
                 (coordinate_giove[0] - coordinate_sole[0]) * sin(angolo_giove) + coordinate_sole[1],
                 60.0);
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
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_saturno[0] - coordinate_sole[0]) * cos(angolo_saturno) + coordinate_sole[0],
                 (coordinate_saturno[0] - coordinate_sole[0]) * sin(angolo_saturno) + coordinate_sole[1],
                 60.0);
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
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_urano[0] - coordinate_sole[0]) * cos(angolo_urano) + coordinate_sole[0],
                 (coordinate_urano[0] - coordinate_sole[0]) * sin(angolo_urano) + coordinate_sole[1],
                 60.0);
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
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    glPushMatrix();
    glTranslatef((coordinate_nettuno[0] - coordinate_sole[0]) * cos(angolo_nettuno) + coordinate_sole[0],
                 (coordinate_nettuno[0] - coordinate_sole[0]) * sin(angolo_nettuno) + coordinate_sole[1],
                 60.0);
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * RAGGIO_NETTUNO/SCALA, 4 * RAGGIO_NETTUNO/SCALA, 0.0);
    char *nettuno = "nettuno";
    for(i = 0; i < 8; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, nettuno[i]);
    }
    glPopMatrix();
    glColor3fv(colore_urano);
    glBindVertexArray(vao[URANO]);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
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
    glOrtho(0.0, VIEW_WIDTH, 0.0, VIEW_HEIGHT, VIEW_NEAR, VIEW_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    glGenVertexArrays(NUMERO_PIANETI, vao);

    glBindVertexArray(vao[SOLE]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_SOLE/SCALA);
    glGenBuffers(2, sole_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, sole_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sole_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[MERCURIO]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_MERCURIO/SCALA);
    glGenBuffers(2, mercurio_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, mercurio_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mercurio_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[VENERE]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_VENERE/SCALA);
    glGenBuffers(2, venere_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, venere_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, venere_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[TERRA]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_TERRA/SCALA);
    glGenBuffers(2, terra_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, terra_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terra_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[MARTE]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_MARTE/SCALA);
    glGenBuffers(2, marte_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, marte_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, marte_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[GIOVE]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_GIOVE/SCALA);
    glGenBuffers(2, giove_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, giove_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, giove_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[SATURNO]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_SATURNO/SCALA);
    glGenBuffers(2, saturno_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, saturno_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, saturno_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[URANO]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_URANO/SCALA);
    glGenBuffers(2, urano_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, urano_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, urano_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vao[NETTUNO]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_NETTUNO/SCALA);
    glGenBuffers(2, nettuno_buffers);
    glBindBuffer(GL_ARRAY_BUFFER, nettuno_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nettuno_buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitWindowPosition(0, 0);
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