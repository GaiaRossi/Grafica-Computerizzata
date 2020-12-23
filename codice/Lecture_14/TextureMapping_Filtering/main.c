/*
 * OpenGL: example of texture mapping
 * with filtering and mipmapping
 * Use keys 1 and 2 to move toward or away from the texture plane respectively
 * Press ESC to exit
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "readBMP.h"


// Local storage for bmp image data.
#define NIMAGES 2
struct BitMapFile *image[NIMAGES];

// texture ID objects
static GLenum textureID[2];

// Distance parameter
static GLfloat d = 0.0;

// delta step to update d
#define DELTA   .01

// filtering type
enum filterType {nearest, linear, mipmap} currFilterType = nearest;

// vertex coordinates
GLfloat vertexCoords[4*3] =
{
    -2.0, -1.0, 0.0,
    2.0, -1.0, 0.0,
    -2.0, 1.0, 0.0,
    2.0, 1.0, 0.0
};

// texture coordinates
GLfloat textCoords[4*2] =
{
    0.0, 0.0,
    1.0, 0.0,
    0.0, 1.0,
    1.0, 1.0,
};

// display routine
void display(void)
{
    // push initial state on the stack
    glPushMatrix();

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // place objects in the scene
    glTranslatef(0.0, -1.0, -1.0+d);

    // Activate texture object - textureID[0] = grass
    glBindTexture(GL_TEXTURE_2D, textureID[0]);

    // draw "grass" square with texture
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Activate texture object - textureID[1] = sky
    glBindTexture(GL_TEXTURE_2D, textureID[1]);

    // draw "sky" square with texture
    glTranslatef(0.0, 2.0, 0.0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // pop initial state on the stack
    glPopMatrix();

    // swap frame buffer (we are in double buffer mode)
    glutSwapBuffers();
}

// Load external textures.
void loadExternalTextures()
{
    // Load the images.
    image[0] = readBMP("grass.bmp");
    image[1] = readBMP("sky.bmp");

    if (image[0] == NULL || image[1] == NULL) {
        printf("ERROR: Could not load images");
        exit(0);
    }

    // define parameters for texture[0] (the grass)
    // Bind grass image to texture object texture[0].
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Select which type of filtering we apply in case of minification
    switch (currFilterType) {
        case nearest:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case linear:
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            break;
        case mipmap:
            // Generate MipMaps
            glGenerateMipmap(GL_TEXTURE_2D);
            // Options here are: GL_NEAREST_MIPMAP_NEAREST GL_NEAREST_MIPMAP_LINEAR
            // GL_LINEAR_MIPMAP_NEAREST GL_LINEAR_MIPMAP_LINEAR
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
    }

    // define parameters for texture[1] (the sky)
    // Bind sky image to texture object texture[1]
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Enable vertex arrays for coordinates and texture mapping
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexCoords);

    // glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, textCoords);
}

// init routine
void init (void)
{
    GLenum glErr;

    // initialize texture ID
    glGenTextures(2, textureID);

    // Load external textures.
    loadExternalTextures();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Turn on OpenGL texturing.
    glEnable(GL_TEXTURE_2D);

    // Cull back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // ----------------------------------------------------------

    // select clearing color
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-0.5, 0.5, -0.5, 0.5, 0.2, 5.0);

    // ... it does not hurt to check that everything went OK
    if ((glErr=glGetError()) != 0)
    {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    printf("init routine: success\n");

}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    int currInd;

    switch(key) {
    case 27:
        // ESC
        for (currInd=0; currInd<NIMAGES; currInd++) {
            if (image[currInd] != NULL) {
                // free pixel data
                free(image[currInd]->data);
            }
        }
        exit(0);
        break;
    case '1':
        // Key 1
        // update alpha and display
        d += DELTA;
        if (d > 0.5) d = 0.5;
        glutPostRedisplay();
        break;
    case '2':
        // Key 2
        // update alpha and display
        d -= DELTA;
        if (d < -1.5) d = -1.5;
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
    // print instructions
    printf("Interaction: \n");
    printf("Use keys 1 and 2 to move toward or away from the texture plane respectively.\n");
    printf("Press ESC to exit\n");

    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("OpenGL Window");

    // keyboard handling function
    glutKeyboardFunc(keyInput);

    // Here we add support for GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("GLEW init failed: %s\n", glewGetErrorString(err));
        exit(1);
    }
    else {
        printf("GLEW init success\n");
    };

    // Call initialization routines
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;   /* ANSI C requires main to return int. */
}

