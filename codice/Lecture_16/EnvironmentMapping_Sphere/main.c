/*
 * OpenGL: environment mapping: Spherical
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "readBMP.h"

// Local storage for bmp image data.
static struct BitMapFile *image= NULL;

// file containing the bmp image
char *fileName = "mountains_sphere.bmp";

// Positional offset for the object
static float posOffset = 0.0;

// Array of texture indices.
static unsigned int textureID;

// select which object we show
enum object {sphere, cylinder, cube} myObject = cube;

// Vertices of the square
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
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0
};

// Drawing routine.
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Push initial state on the stack
    glPushMatrix();

    // draw plane with texture
    glTranslatef(0.0, 0.0, -1.5);
    glRotatef(posOffset, 0.0, 1.0, 0.0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // Activate texture object and sphere mapping
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    // Position the polygon in the scene and draw it
    switch (myObject) {
        case sphere:
            glTranslatef(0.0, 0.0, .4);
            glutSolidSphere(.5, 100.0, 100.0);
            break;
        case cylinder:
            glTranslatef(0.0, 0.5, .4);
            glRotatef(90.0, 1.0, 0.0, 0.0);
            glutSolidCylinder(.4, 1.0, 100.0, 100.0);
            break;
        case cube:
            glTranslatef(0.0, 0.0, .4);
            glScalef(1.0, 1.7, 1.0);
            glutSolidCube(.6);
        default:
            break;
    }

    // Disable automatic texture generation.
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    // pop initial state from the stack
    glPopMatrix();
    glutSwapBuffers();
}

// Initialization routine.
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Create texture ids.
    glGenTextures(1, &textureID);

    // Load external textures
    image = readBMP(fileName);
    if(image == NULL) {
        printf("Could not open file %s\n", fileName);
    }

    // Bind sky image to texture index[0].
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Enable two vertex arrays: coordinates, normals and texture coordinates
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, tVertices);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, tNormals);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, tColors);

    // glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, tTextureCoords);

    // Specify automatic texture generation for a sphere map.
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-.3, .3, -.3, .3, .2, 4.0);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch(key) {
    case 27:
        if (image!=NULL) {
            // freee allocated memory
            free(image->data);
        }
        exit(0);
        break;
    case '1':
        if (posOffset < 80.0) posOffset += 0.5;
        glutPostRedisplay();
        break;
    case '2':
        if (posOffset > -80.0) posOffset -= 0.5;
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

    printf("Interaction:\n");
    printf("Press 1 and 2 to rotate the sphere.\n");

    // Some standard initializations
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("multitexture.cpp");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyInput);
    glewInit();

    init();
    glutMainLoop();
    exit(0);
}

