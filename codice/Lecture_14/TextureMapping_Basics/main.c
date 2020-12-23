/*
 * OpenGL: example of texture mapping
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#include "readBMP.h"

// Local storage for bmp image data.
struct BitMapFile *image=NULL;

// file containing the bmp image
char *fileName = "launch.bmp";

// texture ID objects
static GLenum textureID[2];

// chessboard image
static GLubyte chessboard[64][64][4]; // Storage for chessboard image.

// display routine
void display(void)
{
    // push initial state on the stack
    glPushMatrix();

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Activate texture object.
    // Uncomment one of the two following lines to set which
    // texture is used
    glBindTexture(GL_TEXTURE_2D, textureID[0]); // bitmap image
    // glBindTexture(GL_TEXTURE_2D, textureID[1]); // checkerboard

    // place objects in the scene
    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(20.0, 0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-1.0, 1.0, 0.0);
    glTexCoord2f(1.0, 2.0);
    glVertex3f(1.0, 1.0, 0.0);
    glEnd();

    // flush graphics objects immediately
    glFlush();

    // pop initial state on the stack
    glPopMatrix();
}

// Create 64 x 64 RGBA image of a chessboard.
void createChessboard(void)
{
    int i, j;
    for (i = 0; i < 64; i++)
        for (j = 0; j < 64; j++)
            if ( ( ((i/8)%2) && ((j/8)%2) ) || ( !((i/8)%2) && !((j/8)%2) ) )
            {
                chessboard[i][j][0] = 0x00;
                chessboard[i][j][1] = 0x00;
                chessboard[i][j][2] = 0x00;
                chessboard[i][j][3] = 0xFF;
            }
            else
            {
                chessboard[i][j][0] = 0xA0;
                chessboard[i][j][1] = 0xA0;
                chessboard[i][j][2] = 0xA0;
                chessboard[i][j][3] = 0xFF;
            }
}

// init routine
void init (void)
{
    GLenum glErr;

    // initialize texture ID
    glGenTextures(2, textureID);

    // ---------------- Create texture object texture[0] ----------------
    // Activate texture object
    glBindTexture(GL_TEXTURE_2D, textureID[0]);

    // Specify image data for currently active texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->data);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // ---------------- Create texture object texture[1] ----------------
    createChessboard();
    glBindTexture(GL_TEXTURE_2D, textureID[1]);

    // Specify image data for currently active texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, chessboard);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);
    // ----------------------------------------------------------

    // select clearing color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-.7, .7, -.7, .7, 0.5, 5.0);

    // ... it does not hurt to check that everything went OK
    if ((glErr=glGetError()) != 0)
    {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:
        // ESC
        if (image != NULL)
        {
            // free pixel data
            free(image->data);
        }
        exit(0);
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

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("OpenGL Window");

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

    // read bitmap image
    image = readBMP(fileName);
    if (image == NULL) {
        printf("readBMP: Could not openfile: %s \n", fileName);
        exit(1);
    } else {
        printf("File %s has size %d x %d \n", fileName, image->sizeX, image->sizeY);
    }

    // Call initialization routines
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

