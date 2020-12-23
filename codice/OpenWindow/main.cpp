/*
 * This is a simple, introductory OpenGL program.
 */
#include <GL/glut.h>
#include <stdio.h>

//#define SHOWNCALLS

void display(void)
{
    #ifdef SHOWNCALLS
    static int nCalls = 0;
    char windowTitle[100];

    nCalls++;
    snprintf(windowTitle, 100, "nCalls = %d", nCalls);
    glutSetWindowTitle(windowTitle);
    #endif

    // clear buffer
    // glClearColor(0.0, 1.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // flush graphics objects immediately
    glFlush();

    // glClearColor(0.0, -10.0, 0.0, 0.0);
}

void init (void)
{
    // select clearing color
    glClearColor(1.0, 0.0, 0.0, 0.0);
}

// Window size and mode
int main(int argc, char** argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    // GLUT_SINGLE = single buffer window
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow ("My first window");

    // Call initialization routines
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
