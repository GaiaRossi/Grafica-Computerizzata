//scopo esercizio
//sapere la dipendenza tra i refresh al secondo e il numero di linee mostrare
//controllare poi se il colore incide

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Number of elements in the circular buffer
#define NELS    10

#define MAXPUNTI 100
#define DIM 1.0
#define BORDERSIZE 0.01
#define INCREMENTO 100

typedef struct{
    float x;
    float y;
} PuntoGrafico;

PuntoGrafico punti[MAXPUNTI];
// circular buffer used to compute frame rate
float circularBuffer[NELS];
int firstInd = 0, nEls = 0;

int curLines = 1000;
int j = 0;

//massimi fps
float maxfps = 0.0;

// function to get the number of elapsed ticks
uint32_t getTick()
{
    struct timespec ts;
    unsigned theTick = 0U;
    clock_gettime( CLOCK_REALTIME, &ts );
    theTick  = ts.tv_nsec / 1000000;
    theTick += ts.tv_sec * 1000;
    return theTick;
}

// Function to compute real modulus and NOT remained as % does
int modulo(int a, int b) {
    const int result = a % b;
    return result >= 0 ? result : result + b;
}

// Compute sum of the elements in the circular buffer
float sumCircularBuffer()
{
    int ind;
    float sum = 0;

    if (nEls > 0) {
        for (ind=1; ind<=nEls; ind++) {
            sum = sum + circularBuffer[modulo(firstInd-ind, NELS)];
        }
    }

    return sum;
}

// accumulate buffer and update window title
void computeAndShowFrameRate(void)
{
    static float lastTime = 0.0f;
    static unsigned int frameCount = 0;
    char windowTitle[100];
    float sumFPS;

    float currentTime = (float)getTick() * 0.001f;
    // Initialize lastTime to the current time
    if (lastTime == 0) {
        lastTime = currentTime;
    }

    // increase frame count
    frameCount++;
    if (currentTime - lastTime > 1.0f) {
        // insert the current fps in the circular buffer
        circularBuffer[firstInd] = ((float)frameCount) / (currentTime - lastTime);

        // update variable lastTime
        lastTime = currentTime;

        //circularBuffer[firstInd] = (float)frameCount;
        firstInd = ((firstInd+1)%NELS);
        if (nEls < NELS) {
            nEls++;
        }
        frameCount = 0;

        // sum elements in circular buffer
        sumFPS = sumCircularBuffer();
        snprintf(windowTitle, 100, "FPS = %6.2f", sumFPS/nEls);
        
        // update window title
        glutSetWindowTitle(windowTitle);

        //salvataggio coordinate punti grafico

        if(j < MAXPUNTI){
            punti[j].x = curLines;
            punti[j].y = sumFPS/(nEls);
            
            //controllo massimo
            if(punti[j].y > maxfps){
                maxfps = punti[j].y;
            }

            printf("linee disegnate: %f\t fps: %f\n", punti[j].x, sumFPS/nEls);
            j++;
            curLines += INCREMENTO;
        }
    }
}

void display(){
    int i;

    if(j < MAXPUNTI){
        computeAndShowFrameRate();

        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINES);
        
        for(i = 0; i < curLines; i++){
            glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
            glVertex2f((float) rand()/RAND_MAX * DIM, (float) rand()/RAND_MAX * DIM);
            glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
            glVertex2f((float) rand()/RAND_MAX * DIM, (float) rand()/RAND_MAX * DIM);
        }

        glEnd();

        glFlush();
        /*
        glutpostredisplay dice alla opengl che la finestra corrente
        necessita di essere nuovamente mostrata, quindi verra richiamata
        la funzione display
        */
        glutPostRedisplay();
    }
    else{

        printf("Test ended\n");
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINES);

            glColor3d(1.0, 1.0, 1.0);
            //asse y
            glVertex2f(0.0, 0.0);
            glVertex2f(0.0, DIM);
            //asse x
            glVertex2f(0.0, 0.0);
            glVertex2f(DIM, 0.0);
        glEnd();

        glBegin(GL_LINE_STRIP);

            glColor3f(1.0, 0.0, 0.0);
            for(j = 0; j < MAXPUNTI; j++){
                printf("x: %f\ty: %f\n", (float) punti[j].x/curLines, punti[j].y / maxfps);
                glVertex2f((float) punti[j].x/curLines, punti[j].y / maxfps);
            }

        glEnd();

        glFlush();
        
    }
}

void init(){

    glClearColor(0.0, 0.0, 0.0, 0.0);

    srand(time(NULL));

    glMatrixMode(GL_PROJECTION);

    glOrtho(-BORDERSIZE, DIM + BORDERSIZE, -BORDERSIZE, DIM + BORDERSIZE, -1.0, 1.0);

}

int main(int argc, char** argv){

    printf("Testing...\n");

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(600, 400);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Programma grafica");


    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}