/*
 * OpenGL: spatial transformations
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

// Setting one or the other value determines which code is compiled
typedef enum {CUBESPHERE, HIERARCHY} exampleType;
exampleType example = CUBESPHERE;

void display(void)
{
    // int example = 1;

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    // see what happens if you comment out this line and the
    // corresponding glPopMatrix at the end of this function
    glPushMatrix();

    // place objects in the scene

    switch (example) {
        // cube and sphere
        case CUBESPHERE:
            // Uncomment this line to make objects appear
            // on the screen
            glTranslatef(0.0, 0.0, -3.0);
            glTranslatef(1.0, 0.0, 0.0);

            // Uncomment this line to rotate scene
            glRotatef(45, 0.0, 0.0, 1.0);

            // place cube
            glutWireCube(1.0);
            glTranslatef(0.0, 2.0, 0.0);

            // place sphere
            glutWireSphere (0.5, 20.0, 20.0);
            break;

        // Hierarchical representations
        case HIERARCHY:

            // move objects into the scene
            glTranslatef(0.0, 0.5, -2.0);
            glPushMatrix();

            // place body
            glRotatef(90.0, 1.0, 0.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
            glutWireCylinder(0.5, 1.0, 20.0, 8.0);

            // place head
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0, 0.3, 0.0);
            glColor3f(0.0, 1.0, 0.0);
            glutWireSphere(0.4, 20, 20);

            // place right arm
            glPopMatrix();
            glPushMatrix();
            glTranslatef(-0.5, 0.0, 0.0);
            glRotatef(90.0, 1.0, 0.0, 0.0);
            glRotatef(-45.0, 0.0, 1.0, 0.0);

            glColor3f(0.0, 0.0, 1.0);
            glutWireCylinder(0.2, 0.7, 20.0, 8.0);

            // place right forearm
            glTranslatef(0.0, 0.0, 0.75);
            glColor3f(0.0, 1.0, 1.0);
            glutWireCylinder(0.2, 0.5, 20.0, 8);

            // place left arm
            glPopMatrix();
            glTranslatef(0.5, 0.0, 0.0);
            glRotatef(90.0, 1.0, 0.0, 0.0);
            // Uncomment this line to see how this affect the WHOLE
            // chain starting from here!
            glRotatef(45.0, 0.0, 1.0, 0.0);
            glColor3f(0.0, 0.0, 1.0);
            glutWireCylinder(0.2, 0.7, 20.0, 8.0);

            // place right forearm
            glTranslatef(0.0, 0.0, 0.75);
            glColor3f(0.0, 1.0, 1.0);
            glutWireCylinder(0.2, 0.5, 20.0, 8);

        default:
        break;
    };

    glPopMatrix();

    // flush graphics objects immediately
    glFlush();

}

void init (void)
{
    GLenum glErr;

    // select clearing color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1, 10.0);

    // ... it does not hurt to check that everything went OK
    if ((glErr=glGetError()) != 0) {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Turn on wireframe mode (only for debugging purposes)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


// Window size and mode
int main(int argc, char** argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    // GLUT_SINGLE = single buffer window
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow ("OpenGL Window");

    // Here we add support for GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    } else {
        printf("GLEW init success\n");
    };

    // Call initialization routines
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

