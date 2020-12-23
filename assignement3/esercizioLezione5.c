//scopo esercizio
//imparare la frustum
// e i vertex buffer e vertex array objects

/*
    la frustum non modifica come e inclinato
    il tronco di piramide che e la visuale
    della camera, cambia solo le dimesioni

    Il cubo disegnato dal prof si vedeva cosi
    perche aveva spostato e ruotato il cubo 
    nella scena
*/

#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/glx.h>

#define NFACCE 1
#define NVERTICIPERFACCIA 16

unsigned int buffers[1];

GLfloat vertici[NFACCE * NVERTICIPERFACCIA * 3] = {

    //prima faccia
    0.0, 0.0, 0.0,
    0.9, 0.0, 0.0,
    0.6, 0.3, 0.0,
    0.3, 0.3, 0.0,
    0.9, 0.0, 0.0,
    0.9, 0.9, 0.0,
    0.6, 0.6, 0.0,
    0.6, 0.3, 0.0,
    0.9, 0.9, 0.0,
    0.0, 0.9, 0.0,
    0.3, 0.6, 0.0,
    0.6, 0.6, 0.0,
    0.0, 0.9, 0.0,
    0.0, 0.0, 0.0,
    0.3, 0.3, 0.0,
    0.3, 0.6, 0.0

};

void useTriangles(){

    //prima faccia

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 1.0, 0.0);
        // v0
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.9, 0.0, 0.0);
        glVertex3f(0.6, 0.3, 0.0);
        glVertex3f(0.3, 0.3, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v1
        glVertex3f(0.9, 0.0, 0.0);
        glVertex3f(0.9, 0.9, 0.0);
        glVertex3f(0.6, 0.6, 0.0);
        glVertex3f(0.6, 0.3, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v2
        glVertex3f(0.9, 0.9, 0.0);
        glVertex3f(0.0, 0.9, 0.0);
        glVertex3f(0.3, 0.6, 0.0);
        glVertex3f(0.6, 0.6, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v3
        glVertex3f(0.0, 0.9, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.3, 0.3, 0.0);
        glVertex3f(0.3, 0.6, 0.0);
    glEnd();

    //seconda faccia

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0.0, 0.0);
        // v0
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.9);
        glVertex3f(0.0, 0.3, 0.6);
        glVertex3f(0.0, 0.3, 0.3);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v1
        glVertex3f(0.0, 0.0, 0.9);
        glVertex3f(0.0, 0.9, 0.9);
        glVertex3f(0.0, 0.6, 0.6);
        glVertex3f(0.0, 0.3, 0.6);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v2
        glVertex3f(0.0, 0.9, 0.9);
        glVertex3f(0.0, 0.9, 0.0);
        glVertex3f(0.0, 0.6, 0.3);
        glVertex3f(0.0, 0.6, 0.6);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v3
        glVertex3f(0.0, 0.9, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.3, 0.3);
        glVertex3f(0.0, 0.6, 0.3);
    glEnd();

    //terza faccia

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 1.0, 0.0);
        // v0
        glVertex3f(0.0, 0.0, 0.9);
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.6, 0.3, 0.9);
        glVertex3f(0.3, 0.3, 0.9);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v1
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.9, 0.9);
        glVertex3f(0.6, 0.6, 0.9);
        glVertex3f(0.6, 0.3, 0.9);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v2
        glVertex3f(0.9, 0.9, 0.9);
        glVertex3f(0.0, 0.9, 0.9);
        glVertex3f(0.3, 0.6, 0.9);
        glVertex3f(0.6, 0.6, 0.9);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v3
        glVertex3f(0.0, 0.9, 0.9);
        glVertex3f(0.0, 0.0, 0.9);
        glVertex3f(0.3, 0.3, 0.9);
        glVertex3f(0.3, 0.6, 0.9);
    glEnd();

    //quarta faccia

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 0.0, 1.0);
        // v0
        glVertex3f(0.9, 0.0, 0.0);
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.3, 0.6);
        glVertex3f(0.9, 0.3, 0.3);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v1
        glVertex3f(0.9, 0.0, 0.9);
        glVertex3f(0.9, 0.9, 0.9);
        glVertex3f(0.9, 0.6, 0.6);
        glVertex3f(0.9, 0.3, 0.6);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v2
        glVertex3f(0.9, 0.9, 0.9);
        glVertex3f(0.9, 0.9, 0.0);
        glVertex3f(0.9, 0.6, 0.3);
        glVertex3f(0.9, 0.6, 0.6);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        // v3
        glVertex3f(0.9, 0.9, 0.0);
        glVertex3f(0.9, 0.0, 0.0);
        glVertex3f(0.9, 0.3, 0.3);
        glVertex3f(0.9, 0.6, 0.3);
    glEnd();

    glPopMatrix();

    glFinish();
}

void useVBO(){
    int indiceFaccia;

    for(indiceFaccia = 0; indiceFaccia < NFACCE; indiceFaccia++){
        glDrawElements(GL_TRIANGLE_FAN, NVERTICIPERFACCIA, GL_UNSIGNED_BYTE, (GLvoid*)(indiceFaccia * NVERTICIPERFACCIA * sizeof(GLbyte)));
    }

    glFlush();
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glTranslatef(0.0, 0.0, -1.5);
    glTranslatef(-.5, -.8, 0.0);
    glRotatef(25.0, 0.0, 1.0, 0.0);
    glRotatef(25.0, 1.0, 0.0, 0.0);

    //useTriangles();

    useVBO();


    glPopMatrix();

    glFinish();
}

void init (void)
{
    // select clearing color
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);

    // set viewing frustum
    glFrustum(-0.2, 0.2, -0.3, 0.1, 0.1, 5.0);
    //glOrtho(0.0, 2.0, 0.0, 2.0, -1.0, 2.0);

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
    glEnableClientState(GL_VERTEX_ARRAY);

    glGenBuffers(1, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertici), vertici, GL_STATIC_DRAW);

    glVertexPointer(3, GL_FLOAT, 0, 0);
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

    //per output su secondo schermo
    glutInitWindowPosition (2000, 1500);
    glutCreateWindow ("OpenGL Window");

    // Call initialization routinesx
    init();
    //glutDisplayFunc(display);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
