/*
* Draw a cube ... triangles strip + data separated from code
*/
#include <GL/glut.h>

// number of faces
#define NFACES      4
// number of vertices per face
#define NVERTICES   4

// define vertices
GLfloat vertexArray[NFACES*NVERTICES][3] = {
    // first face - v0,v1,v3,v2
    {0.5, -0.5, 0.5}, // v0
    {0.5, 0.5, 0.5}, // v1
    {-0.5, -0.5, 0.5}, // v3
    {-0.5, 0.5, 0.5}, // v2

    // second face - v3,v2,v7,v6
    {-0.5, -0.5, 0.5}, // v3
    {-0.5, 0.5, 0.5}, // v2
    {-0.5, -0.5, -0.5}, // v7
    {-0.5, 0.5, -0.5}, // v6

    // third face - v7,v6,v4,v5
    {-0.5, -0.5, -0.5}, // v7
    {-0.5, 0.5, -0.5}, // v6
    {0.5, -0.5, -0.5}, // v4
    {0.5, 0.5, -0.5}, // v5

    // forth face - v4, v5, v0, v1
    {0.5, -0.5, -0.5}, // v4
    {0.5, 0.5, -0.5}, // v5
    {0.5, -0.5, 0.5}, // v0
    {0.5, 0.5, 0.5} // v1
};

GLfloat colorArray[NFACES*NVERTICES][3] = {
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},
    {0.0, 1.0, 1.0}
};

void display(void)
{
    GLshort indFace, indVertex;

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // store modelview settings
    glPushMatrix();

    // place the cube in the scene
    glTranslatef(0.0, 0.0, -1.5);
    glTranslatef(0.0, -.8, 0.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);
    glRotatef(25.0, 1.0, 0.0, 0.0);

    // here we draw the triangle stripss
    for (indFace=0; indFace<NFACES; indFace++) {
        glBegin(GL_TRIANGLE_STRIP);
        for(indVertex=0; indVertex<NVERTICES; indVertex++) {
            // extract color
            glColor3fv(colorArray[indFace*NVERTICES + indVertex]);
            // extract vertices
            glVertex3fv(vertexArray[indFace*NVERTICES + indVertex]);
        };
        glEnd();
    };

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
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-0.2, 0.2, -0.3, 0.1, 0.1, 5.0);

    // ... it does not hurt to check that everything went OK
    if (glGetError() != 0) {
        exit(-1);
    }

    // Turn on wireframe mode (only for debugging purposes)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
    glutCreateWindow ("My first window");

    // Call initialization routinesx
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
