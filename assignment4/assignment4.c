#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "window.h"
#include "dati.h"
#include "pianeti.h"

#define SPAZIO 0.00360

/**
 * funzione chiamata ogni TEMPO per cambiare l'angolo che forma il pianeta
 * con l'asse centrale
*/
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

/**
 * funzione che si occupa di disegnare il pianeta e mettere l'etichetta ad esso
*/
void disegna_pianeta(int pianeta, float* colore, float* coordinate, char* nome, int lunghezza_nome, int raggio){
    /**
     * la radice della struttura gerarchica è il sole, da li mi muovo per mettere i pianeti
    */
    glPushMatrix();
    glTranslatef(coordinate[0],
                 coordinate[1],
                 coordinate[2]);
    glColor3fv(colore);
    glutSolidSphere(raggio/SCALA, 20, 20);
    
    /**
     * da dove si trova il pianeta disegno l'etichetta
    */
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glScalef(1/9.0, 1/9.0, 1/9.0);
    glRotatef(-INCLINAZIONE, 1.0, 0.0, 0.0);
    glTranslatef(-2 * raggio/SCALA, -20 * raggio/SCALA, 0.0);
    int i;
    for(i = 0; i < lunghezza_nome; i++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, nome[i]);
    }
    glPopMatrix();

    glPopMatrix();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    disegna_pianeta(SOLE, colore_sole, coordinate_sole, "sole", 5, RAGGIO_SOLE);
    
    /**
     * inclino il sistema cosi si vede meglio
    */
    glRotatef(INCLINAZIONE, 1.0, 0.0, 0.0);
    float coordinate[3] = {
        (coordinate_mercurio[0] - coordinate_sole[0]) * cos(angolo_mercurio) + coordinate_sole[0],
        coordinate_sole[1],
        (coordinate_mercurio[0] - coordinate_sole[0]) * sin(angolo_mercurio) + coordinate_sole[1]
    };;
    disegna_pianeta(MERCURIO, colore_mercurio, coordinate, "mercurio", 9, RAGGIO_MERCURIO);

    coordinate[0] = (coordinate_venere[0] - coordinate_sole[0]) * cos(angolo_venere) + coordinate_sole[0];
    coordinate[2] = (coordinate_venere[0] - coordinate_sole[0]) * sin(angolo_venere) + coordinate_sole[1];
    disegna_pianeta(VENERE, colore_venere, coordinate, "venere", 7, RAGGIO_VENERE);

    coordinate[0] = (coordinate_terra[0] - coordinate_sole[0]) * cos(angolo_terra) + coordinate_sole[0];
    coordinate[2] = (coordinate_terra[0] - coordinate_sole[0]) * sin(angolo_terra) + coordinate_sole[1];
    disegna_pianeta(TERRA, colore_terra, coordinate, "terra", 6, RAGGIO_TERRA);

    coordinate[0] = (coordinate_marte[0] - coordinate_sole[0]) * cos(angolo_marte) + coordinate_sole[0];
    coordinate[2] = (coordinate_marte[0] - coordinate_sole[0]) * sin(angolo_marte) + coordinate_sole[1];
    disegna_pianeta(MARTE, colore_marte, coordinate, "marte", 6, RAGGIO_MARTE);

    coordinate[0] = (coordinate_giove[0] - coordinate_sole[0]) * cos(angolo_giove) + coordinate_sole[0];
    coordinate[2] = (coordinate_giove[0] - coordinate_sole[0]) * sin(angolo_giove) + coordinate_sole[1];
    disegna_pianeta(GIOVE, colore_giove, coordinate, "giove", 6, RAGGIO_GIOVE);

    coordinate[0] = (coordinate_saturno[0] - coordinate_sole[0]) * cos(angolo_saturno) + coordinate_sole[0];
    coordinate[2] = (coordinate_saturno[0] - coordinate_sole[0]) * sin(angolo_saturno) + coordinate_sole[1];
    disegna_pianeta(SATURNO, colore_saturno, coordinate, "saturno", 8, RAGGIO_SATURNO);

    coordinate[0] = (coordinate_urano[0] - coordinate_sole[0]) * cos(angolo_urano) + coordinate_sole[0];
    coordinate[2] = (coordinate_urano[0] - coordinate_sole[0]) * sin(angolo_urano) + coordinate_sole[1];
    disegna_pianeta(URANO, colore_urano, coordinate, "urano", 6, RAGGIO_URANO);

    coordinate[0] = (coordinate_nettuno[0] - coordinate_sole[0]) * cos(angolo_nettuno) + coordinate_sole[0];
    coordinate[2] = (coordinate_nettuno[0] - coordinate_sole[0]) * sin(angolo_nettuno) + coordinate_sole[1];
    disegna_pianeta(NETTUNO, colore_nettuno, coordinate, "nettuno", 8, RAGGIO_NETTUNO);
    glPopMatrix();
    
    glutTimerFunc(TEMPO, aggiorna_angoli, 0);

    glFinish();
    glutPostRedisplay();
}

void init(){

    const GLfloat light_ambient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
    const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat light_position[] = { 0.0f, 0.0f, 100.0f, 1.0f };

    const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 50.0f };

    glClearColor(0,0,0,0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glShadeModel(GL_SMOOTH);

    GLenum glErr;
    if ((glErr = glGetError()) != 0) {
            printf("Errore = %d \n", glErr);
            exit(-1);
        }

    glMatrixMode(GL_PROJECTION);
    glOrtho(-VIEW_WIDTH, VIEW_WIDTH, -VIEW_HEIGHT, VIEW_HEIGHT, VIEW_NEAR, VIEW_FAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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