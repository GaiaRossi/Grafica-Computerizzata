/*
 * OpenGL: multitexturing
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "readBMP.h"

// Array of texture indices.
static unsigned int textureID[2];
// Interpolation parameter.
static float alpha = 0.5;
// Constant texture environment color.
static float envColor[4];

// Local storage for bmp image data.
#define NIMAGES 2
static struct BitMapFile *image[NIMAGES]= {NULL, NULL};

// file containing the bmp image
char *fileName[NIMAGES] = {"sky.bmp", "nightSky.bmp"};

// Vertices of the triangle (indices 0-2)
// lines of the normals (indices 3-8)
GLfloat tVertices[4*3] =
{
    1.0, -1.0, 0.0,
    1.0, 1.0, 0.0,
    -1.0, -1.0, 0.0,
    -1.0, 1.0, 0.0
};

// Color of the vertices
GLfloat tColors[4*3] =
{
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 0.0, 1.0
};

// texture coordinates
GLfloat tTextureCoords[4*2] =
{
    1.0, 0.0,
    1.0, 1.0,
    0.0, 0.0,
    0.0, 1.0,
};

// normals
GLfloat tNormals[4*3] =
{
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0
};

// Drawing routine.
void display(void) {
    unsigned int currInd;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the interpolation parameter
    for (currInd=0; currInd<4; currInd++) {
        envColor[currInd] = alpha;
    }
    // Specify the constant texture environment color.
    glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor);

    // Push initial state on the stack
    glPushMatrix();

    // Position the polygon in the scene
    glTranslatef(0.0, 0.0, -2.0);

    // draw square
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // pop initial state from the stack
    glPopMatrix();
    glutSwapBuffers();
}

// Initialization routine.
void init(void) {
    unsigned int currInd;

    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Create texture ids.
    glGenTextures(2, textureID);

    // Load external textures
    for(currInd=0; currInd<NIMAGES; currInd++) {
        image[currInd] = readBMP(fileName[currInd]);
    }

    // Bind sky image to texture index[0].
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    // Bind night sky image to texture index[1]
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Select texture unit 0 as the currently active texture unit
    // and specify its texture states.
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[0]);
    // Unit 0 REPLACES the current pixels.
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Select texture unit 1 as the currently active texture
    // unit and specify its texture states.
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID[1]);
    // Unit 1 COMBINES with unit 0 in a manner
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

    // Perche' se si scommenta questa riga non si ha piu' un mixing
    // delle due textures?
    // Domanda correlata: Quale e' il default di GL_COMBINE nel caso
    // in cui non si definisca alcun paramentro?
    // glActiveTexture(GL_TEXTURE0);

    // Define how RGB components are computed
    // Interpolate RGB with RGB
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_INTERPOLATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB, GL_PREVIOUS);
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB, GL_TEXTURE);
    // GL_CONSTANT refers to the call we make with
    // glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor)
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_RGB, GL_CONSTANT);
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB, GL_SRC_COLOR);
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB, GL_SRC_COLOR);
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_RGB, GL_SRC_COLOR);

    // Define how Alpha component is computed
    // Interpolate ALPHA with ALPHA
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_INTERPOLATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_PREVIOUS);
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_ALPHA, GL_TEXTURE);
    // GL_CONSTANT refers to the call we make with
    // glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, envColor)
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE2_ALPHA, GL_CONSTANT);
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_ALPHA, GL_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND2_ALPHA, GL_SRC_ALPHA);

    // Enable vertex arrays for coordinates, normals and texture coordinates
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, tVertices);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, tNormals);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, tColors);

    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, tTextureCoords);

    glClientActiveTexture(GL_TEXTURE1);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, tTextureCoords);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-.5, .5, -.5, .5, .7, 8.0);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    int currInd;

    switch(key) {
    case 27:
        // free allocated memory
        for(currInd=0; currInd<NIMAGES; currInd++) {
            if (image[currInd] != NULL) {
                free(image[currInd]->data);
            }
        }
        exit(0);
        break;
    case '1':
        if (alpha < 1.0) alpha += 0.02;
        glutPostRedisplay();
        break;
    case '2':
        if (alpha > 0) alpha -= 0.02;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    // print instructions
    printf("Interaction:\n");
    printf("Press 1 and 2 to transform the sky.\n");

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("multitexture.cpp");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    init();

    glutMainLoop();
}

