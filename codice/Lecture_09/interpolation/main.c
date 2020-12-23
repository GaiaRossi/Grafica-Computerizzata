/*
 * OpenGL: position and angle interpolation
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

// define and initialize initial and final
// points for the position interpolation
GLfloat startEndPoints[2][3] =
{{0.0, 0.0, 0.0}, {1.0, 1.0, -1.0}};

// center and radius of circular trajectory
GLfloat centerPoint[3] = {0.0, 0.0, -3.0};
GLfloat radius = 1.0;

// define and initialize initial and final
// points for the position interpolation
GLfloat startEndAngles[2][3] =
{{0.0, 60.0, 0.0}, {0.0, 0.0, 0.0}};

// define and initialize initial and final
// points for the position interpolation
// (alpha,beta,gamma) is equivalent to (180+alpha, -beta+180, 180+gamma)
GLfloat startEndAngles1[2][3] =
{{180.0, 120.0, 180.0}, {0.0, 0.0, 0.0}};


// number of steps for the interpolation
#define DELTA   (1.0/20.0)
//current step of the interpolation
static float currAlpha = 0;

// Setting one or the other value determines which code is compiled
typedef enum {LINEAR, CIRCULAR, ANGLES_DO_NOT_COMMUTE, ANGLES_INITIAL_POSITION} exampleType;
exampleType example = ANGLES_INITIAL_POSITION;

// display routine
void display(void)
{
    int currInd;
    // current position and angle.
    GLfloat currPos[3], currAngle[3], currAngle1[3], currPos2D[2];

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    // push initial Modelview matrix
    glPushMatrix();

    // place objects in the scene
    switch (example) {
        // interpolate position along a linear trajectory
        case LINEAR:
            // update
            for(currInd = 0; currInd < 3; currInd++) {
                currPos[currInd] = (1-currAlpha)*startEndPoints[0][currInd] +
                currAlpha * startEndPoints[1][currInd];
            };

            // Place object into the scene
            glTranslatef(0.0+currPos[0], 0.0+currPos[1], -3.0+currPos[2]);

            // place cube
            glutWireTeapot(1.0);
            break;

        // interpolate position along a circular trajectory
        case CIRCULAR:
            // compute position in the XY plane
            currPos2D[0] = radius*cos(currAlpha * 2 * M_PI);
            currPos2D[1] = radius*sin(currAlpha * 2 * M_PI);

            // Place object into the scene
            glTranslatef(0.0+currPos2D[0], 0.0+currPos2D[1], -3.0);

            // place object
            glutWireTeapot(1.0);
            break;

        // show that rotations do not commute
        case ANGLES_DO_NOT_COMMUTE:
            glPushMatrix();
            // Place object into the scene
            glTranslatef(0.0, 0.0, -3.0);
            glRotatef(45.0, 1.0, 0.0, 0.0);
            glRotatef(45.0, 0.0, 1.0, 0.0);

            // place object
            glColor3f(1.0, 0.0, 0.0);
            glutWireTeapot(1.0);

            // get back to the initial position
            glPopMatrix();

            // Place object into the scene
            glTranslatef(0.0, 0.0, -3.0);
            glRotatef(45.0, 0.0, 1.0, 0.0);
            glRotatef(45.0, 1.0, 0.0, 0.0);

            // place object
            glColor3f(0.0, 1.0, 0.0);
            glutWireTeapot(1.0);
            break;

        // interpolate angles between two different sets of
        // Euler angles in which the first position is represented
        // in two different ways.
        case ANGLES_INITIAL_POSITION:
            // update
            for(currInd = 0; currInd < 3; currInd++) {
                // interpolate first angle
                currAngle[currInd] = (1-currAlpha)*startEndAngles[0][currInd] +
                    currAlpha * startEndAngles[1][currInd];
                // interpolate second angle
                currAngle1[currInd] = (1-currAlpha)*startEndAngles1[0][currInd] +
                    currAlpha * startEndAngles1[1][currInd];
            };

            glPushMatrix();
            // place object into the scene
            glTranslatef(0.0, 0.0, -3.0);
            // ... and rotate it with the Euler angles
            // the order is X, then Y, then Z
            glRotatef(currAngle[0], 1.0, 0.0, 0.0);
            glRotatef(currAngle[1], 0.0, 1.0, 0.0);
            glRotatef(currAngle[2], 0.0, 0.0, 1.0);
            glColor3f(1.0, 0.0, 0.0);
            glutWireTeapot(1.0);
            glPopMatrix();

            // place object into the scene
            glTranslatef(0.0, 0.0, -3.0);
            // ... and rotate it with the Euler angles
            // the order is X, then Y, then Z
            glRotatef(currAngle1[0], 1.0, 0.0, 0.0);
            glRotatef(currAngle1[1], 0.0, 1.0, 0.0);
            glRotatef(currAngle1[2], 0.0, 0.0, 1.0);
            glColor3f(0.0, 1.0, 0.0);
            glutWireTeapot(1.0);

            break;

        default:
            break;
    };

    // pop initial Modelview matrix
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


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key) {
        case 27:
            // ESC
            exit(0);
            break;
        case '1':
            // Key 1
            // update alpha and display
            currAlpha += DELTA;
            if (currAlpha > 1.0) currAlpha = 0.0;
            glutPostRedisplay();
            break;
        default:
            // do nothing
            break;
    }
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

    // keyboard handling function
    glutKeyboardFunc(keyInput);

    // Here we add support for GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    } else {
        printf("GLEW init success\n");
    };

    // print message in console
    if (example != ANGLES_DO_NOT_COMMUTE)
        printf("Press 1 to update position/angle \n");

    // Call initialization routines
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

