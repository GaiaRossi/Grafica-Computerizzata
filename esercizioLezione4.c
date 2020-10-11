//scopo esercizio
//sapere la dipendenza tra i refresh al secondo e il numero di linee mostrare
//controllare poi se il colore incide

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Number of elements in the circular buffer
#define NELS    10

// circular buffer used to compute frame rate
float circularBuffer[NELS];
int firstInd = 0, nEls = 0;

//massimo numero che il mio pc sopporta
int curLines = 1;

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

        printf("%d\t%f\n", curLines, sumFPS/nEls);

        // update window title
        glutSetWindowTitle(windowTitle);
    }
}

void display(){
    int i;

    computeAndShowFrameRate();

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    
    for(i = 0; i < curLines; i++){
        glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glVertex2f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glVertex2f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
    }

    curLines += 10;

    glEnd();

    glFlush();
    /*
    glutpostredisplay dice alla opengl che la finestra corrente
    necessita di essere nuovamente mostrata, quindi verra richiamata
    la funzione display
    */
    glutPostRedisplay();
}

void init(){

    glClearColor(0.0, 0.0, 0.0, 0.0);

    srand(time(NULL));

    glMatrixMode(GL_PROJECTION);

    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

int main(int argc, char** argv){

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(400, 400);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Programma grafica");


    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}