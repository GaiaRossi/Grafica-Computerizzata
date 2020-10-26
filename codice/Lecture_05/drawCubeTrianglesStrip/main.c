/*
* Draw a cube ... trianglestrip
*/
#include <GL/glut.h>

void display(void)
{
    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // store modelview settings
    glPushMatrix();

    // place the cube in the scene
    glTranslatef(0.0, 0.0, -1.5);
    glTranslatef(0.0, -.8, 0.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glRotatef(25.0, 1.0, 0.0, 0.0);

    // ---------- Lateral faces of the cube ----------

    // f0
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    // v0-v1-v3
    glVertex3f(0.5, -0.5, 0.5); // v0
    glVertex3f(0.5, 0.5, 0.5); // v1
    glVertex3f(-0.5, -0.5, 0.5); // v3
    // v1-v2-v3
    glVertex3f(-0.5, 0.5, 0.5); // v2
    glEnd();

    // f1
    glBegin(GL_TRIANGLE_STRIP);
    // v3-v2-v7
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5); // v3
    glVertex3f(-0.5, 0.5, 0.5); // v2
    glVertex3f(-0.5, -0.5, -0.5); // v7
    // v2-v6-v7
    glVertex3f(-0.5, 0.5, -0.5); // v6
    glEnd();

    // f2
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.0, 0.0, 1.0);
    // v7-v6-v4
    glVertex3f(-0.5, -0.5, -0.5); // v7
    glVertex3f(-0.5, 0.5, -0.5); // v6
    glVertex3f(0.5, -0.5, -0.5); // v4
    // v6-v5-v4
    glVertex3f(0.5, 0.5, -0.5); // v5
    glEnd();

    //f3
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0, 0.0, 1.0);
    // v4-v5-v0
    glVertex3f(0.5, -0.5, -0.5); // v4
    glVertex3f(0.5, 0.5, -0.5); // v5
    glVertex3f(0.5, -0.5, 0.5); // v0
    // v5-v1-v0
    glVertex3f(0.5, 0.5, 0.5); // v1
    glEnd();

    // restore model view settings
    glPopMatrix();

    // flush graphics objects immediately
    glFinish();
}

void init (void)
{
    // select clearing color
    glClearColor (1.0, 1.0, 1.0, 0.0);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);

    // set viewing frustum
    glFrustum(-0.2, 0.2, -0.3, 0.1, 0.1, 5.0);

    // ... it does not hurt to check that everything went OK
    if (glGetError() != 0) {
        exit(-1);
    }

    // Turn on wireframe mode (only for debugging purposes)
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // IMPORTANT: initialize the depth buffer
    // otherwise things are displayed erratically!
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    // glEnable(GL_CULL_FACE);
}

// Window size and mode
int main(int argc, char** argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    // GLUT_SINGLE = single buffer window
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize (400, 400);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("OpenGL Window");

    // Call initialization routinesx
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
