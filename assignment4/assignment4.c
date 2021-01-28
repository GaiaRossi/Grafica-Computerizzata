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

void inizializza_buffer_pianeta(int pianeta, int raggio, unsigned int *buffers){
    glBindVertexArray(vao[pianeta]);
    fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, raggio/SCALA);
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
    glEnableVertexAttribArray(0);
}

void disegna_pianeta(int pianeta, float* colore, float* coordinate, char* nome, int lunghezza_nome, int raggio){
    int i;
    float matAmbAndDif[4];

    glPushMatrix();
    glTranslatef(coordinate[0],
                 coordinate[1],
                 60.0);
    glPushMatrix();
    for(i = 0; i < 4; i++){
        matAmbAndDif[i] = 1.0;
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glScalef(1/3.0, 1/3.0, 1/3.0);
    glTranslatef(-2 * raggio/SCALA, 4 * raggio/SCALA, 0.0);
    for(i = 0; i < lunghezza_nome; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, nome[i]);
    }
    glPopMatrix();
    for(i = 0; i < 4; i++){
        if(i != 3)
            matAmbAndDif[i] = colore[i];
        else
            matAmbAndDif[i] = 0.0;
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glBindVertexArray(vao[pianeta]);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();
    
}

void display(){
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* materiali */
    float matAmbAndDif[4];

    /* posizione luce */
    GLfloat coordinate_luce[] = {0.0, 0.0, 0.0};

    /* luce */
    glLightfv(GL_LIGHT0, GL_POSITION, coordinate_luce);

    /* attivazione della luce */
    glEnable(GL_LIGHT0);

    glPushMatrix();
    glTranslatef(coordinate_sole[0], coordinate_sole[1], 60.0);
    for(i = 0; i < 4; i++){
        if(i != 3)
            matAmbAndDif[i] = colore_sole[i];
        else
            matAmbAndDif[i] = 0.0;
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glBindVertexArray(vao[SOLE]);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glRotatef(180, 0.0, 0.0, 1.0);
    glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
    glPopMatrix();

    float coordinate[3] = {
        (coordinate_mercurio[0] - coordinate_sole[0]) * cos(angolo_mercurio) + coordinate_sole[0],
        (coordinate_mercurio[0] - coordinate_sole[0]) * sin(angolo_mercurio) + coordinate_sole[1],
        60.0
    };
    disegna_pianeta(MERCURIO, colore_mercurio, coordinate, "mercurio", 9, RAGGIO_MERCURIO);

    coordinate[0] = (coordinate_venere[0] - coordinate_sole[0]) * cos(angolo_venere) + coordinate_sole[0];
    coordinate[1] = (coordinate_venere[0] - coordinate_sole[0]) * sin(angolo_venere) + coordinate_sole[1];
    disegna_pianeta(VENERE, colore_venere, coordinate, "venere", 7, RAGGIO_VENERE);

    coordinate[0] = (coordinate_terra[0] - coordinate_sole[0]) * cos(angolo_terra) + coordinate_sole[0];
    coordinate[1] = (coordinate_terra[0] - coordinate_sole[0]) * sin(angolo_terra) + coordinate_sole[1];
    disegna_pianeta(TERRA, colore_terra, coordinate, "terra", 6, RAGGIO_TERRA);

    coordinate[0] = (coordinate_marte[0] - coordinate_sole[0]) * cos(angolo_marte) + coordinate_sole[0];
    coordinate[1] = (coordinate_marte[0] - coordinate_sole[0]) * sin(angolo_marte) + coordinate_sole[1];
    disegna_pianeta(MARTE, colore_marte, coordinate, "marte", 6, RAGGIO_MARTE);

    coordinate[0] = (coordinate_giove[0] - coordinate_sole[0]) * cos(angolo_giove) + coordinate_sole[0];
    coordinate[1] = (coordinate_giove[0] - coordinate_sole[0]) * sin(angolo_giove) + coordinate_sole[1];
    disegna_pianeta(GIOVE, colore_giove, coordinate, "giove", 6, RAGGIO_GIOVE);

    coordinate[0] = (coordinate_saturno[0] - coordinate_sole[0]) * cos(angolo_saturno) + coordinate_sole[0];
    coordinate[1] = (coordinate_saturno[0] - coordinate_sole[0]) * sin(angolo_saturno) + coordinate_sole[1];
    disegna_pianeta(SATURNO, colore_saturno, coordinate, "saturno", 8, RAGGIO_SATURNO);

    coordinate[0] = (coordinate_urano[0] - coordinate_sole[0]) * cos(angolo_urano) + coordinate_sole[0];
    coordinate[1] = (coordinate_urano[0] - coordinate_sole[0]) * sin(angolo_urano) + coordinate_sole[1];
    disegna_pianeta(URANO, colore_urano, coordinate, "urano", 6, RAGGIO_URANO);

    coordinate[0] = (coordinate_nettuno[0] - coordinate_sole[0]) * cos(angolo_nettuno) + coordinate_sole[0];
    coordinate[1] = (coordinate_nettuno[0] - coordinate_sole[0]) * sin(angolo_nettuno) + coordinate_sole[1];
    disegna_pianeta(NETTUNO, colore_nettuno, coordinate, "nettuno", 8, RAGGIO_NETTUNO);

    glutTimerFunc(TEMPO, aggiorna_angoli, 0);

    glFinish();
    glutPostRedisplay();
}

void init(){

    /* luce */
    // global ambient light
    float globAmb[] = {0.0, 0.0, 0.0, 1.0};

    // Light property vectors.
    float lightAmb[] = {0.5, 0.5, 0.5, 1.0};
    float lightDif[] = {1.0, 1.0, 1.0, 1.0};
    float lightSpec[] = {0.0, 0.0, 0.0, 1.0};

    /* attiva la luce */
    glEnable(GL_LIGHTING);

    // Set properties of light number 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

    // Global ambient light.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

    // Enable two-sided lighting.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    // Enable local viewpoint.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // set shading model
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

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

    inizializza_buffer_pianeta(SOLE, RAGGIO_SOLE, sole_buffers);
    inizializza_buffer_pianeta(MERCURIO, RAGGIO_MERCURIO, mercurio_buffers);
    inizializza_buffer_pianeta(VENERE, RAGGIO_VENERE, venere_buffers);
    inizializza_buffer_pianeta(TERRA, RAGGIO_TERRA, terra_buffers);
    inizializza_buffer_pianeta(MARTE, RAGGIO_MARTE, marte_buffers);
    inizializza_buffer_pianeta(GIOVE, RAGGIO_GIOVE, giove_buffers);
    inizializza_buffer_pianeta(SATURNO, RAGGIO_SATURNO, saturno_buffers);
    inizializza_buffer_pianeta(URANO, RAGGIO_URANO, urano_buffers);
    inizializza_buffer_pianeta(NETTUNO, RAGGIO_NETTUNO, nettuno_buffers);
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