/*
* Simple example of how to use mouse, keyboard and fonts
*/

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>


// global variables keeping the state of the mouse
int mouseX=0, mouseY=0;

// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
   char *c;
   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Routine to draw a stroke character string.
void writeStrokeString(void *font, char *string)
{
   char *c;
   for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

// OpenGL display function
void display(void)
{
    char mousePos[20];

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // store model view settings
    glPushMatrix();


    // --------------- BITMAP characters ---------------
    // Here we write a bitmap string
    glRasterPos3f(-0.3, 1.0, -0.5);
    writeBitmapString(GLUT_BITMAP_8_BY_13, "GLUT_BITMAP - z=-0.5");

    glRasterPos3f(-0.3, 1.0, -0.3);
    writeBitmapString(GLUT_BITMAP_8_BY_13, "GLUT_BITMAP - z=-0.3");

    // show mouse position in bitmap characters
    snprintf(mousePos, 20, "x=%d - y=%d", mouseX, mouseY);
    glRasterPos3f(-1.3, 1.3, -0.3);
    writeBitmapString(GLUT_BITMAP_8_BY_13, mousePos);

    // --------------- STROKE characters ---------------
    glPushMatrix();
    glTranslatef(-3.0, -3.0, -1.0);
    glScalef(0.003, 0.003, 0.003);
    writeStrokeString(GLUT_STROKE_ROMAN, "GLUT_STROKE");
    glPopMatrix();

    // draw string at different z value to show perspective
    glPushMatrix();
    glTranslatef(-1.0, -3.0, -2.0);
    glScalef(0.003, 0.003, 0.003);
    writeStrokeString(GLUT_STROKE_ROMAN, "GLUT_STROKE_Z");
    glPopMatrix();

    // draw string at different z value to show perspective
    glPushMatrix();
    glTranslatef(-3.0, -3.0, -1.0);
    glRotatef(45.0, 0.0, 1.0, 0.0);
    glScalef(0.003, 0.003, 0.003);
    writeStrokeString(GLUT_STROKE_ROMAN, "GLUT_STROKE_deg");
    glPopMatrix();

    // restore model view settings
    glPopMatrix();

    // flush graphics objects immediately
    glFinish();
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
            glColor3f(1.0, 0.0, 0.0);
            glutPostRedisplay();
            break;
        case '2':
            // Key 2
            glColor3f(0.0, 1.0, 0.0);
            glutPostRedisplay();
            break;
        case '3':
            // Key 3
            glColor3f(0.0, 0.0, 1.0);
            glutPostRedisplay();
            break;
        default:
            // do nothing
            break;
    }
}


// mouse movement routine while pressing a button
void mouseMotionFunc(int x, int y)
{
    // update global variables
    mouseX = x;
    mouseY = y;

    // ... and update the display
    glutPostRedisplay();
}


// The top menu callback function.
void top_menu(int id)
{
    // Exit if the user selected the "quit" option
    if (id == 1) exit(0);
}

// The sub-menu callback function.
void color_menu(int id)
{
    switch (id) {
    case 2:
        // menu "Rosso"
        glColor3f(1.0, 0.0, 0.0);
        glutPostRedisplay();
        break;
    case 3:
        // menu "Verde"
        glColor3f(0.0, 1.0, 0.0);
        glutPostRedisplay();
        break;
    case 4:
        // menu "Blu"
        glColor3f(0.0, 0.0, 1.0);
        glutPostRedisplay();
        break;
    };

    glutPostRedisplay();
}

// Routine to make the menu.
void makeMenu(void)
{
   // The sub-menu is created first (because it should be
   // visible when the top menu is created): its callback
   // function is registered and menu entries added.
   int sub_menu;
   sub_menu = glutCreateMenu(color_menu);
   glutAddMenuEntry("Rosso", 2);
   glutAddMenuEntry("Verde", 3);
   glutAddMenuEntry("Blu", 4);

   // The top menu is created: its callback function is
   // registered and menu entries, including a submenu, added.
   glutCreateMenu(top_menu);
   glutAddSubMenu("Color", sub_menu);
   glutAddMenuEntry("Quit",1);

   // The menu is attached to a mouse button.
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init (void)
{
    // select clearing color
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // setup menus
    makeMenu();

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-0.5, 0.5, -0.5, 0.5, 0.1, 5.0);

    // ... it does not hurt to check that everything went OK
    if (glGetError() != 0) {
        exit(-1);
    }

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
    glutCreateWindow ("OpenGL window");

    // set OpenGL functions
    glutDisplayFunc(display);

    // keyboard handling function
    glutKeyboardFunc(keyInput);

    // mouse movement function
    glutMotionFunc(mouseMotionFunc);

    // Here we add support for GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    } else {
        printf("GLEW init success\n");
    };

    // Call initialization routinesx
    init();

    // OpenGL main loop
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}
