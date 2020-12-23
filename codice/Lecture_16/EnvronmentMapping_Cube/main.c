/*
 * OpenGL: environment mapping: Cube Mapping
 * textures downloaded from: https://learnopengl.com/Advanced-OpenGL/Cubemaps
 */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "readBMP.h"

// Local storage for bmp image data for the six faces of the cube
#define NFACES  6
static struct BitMapFile *images[NFACES];

// file containing the bmp image
char *fileName[NFACES] = {"right.bmp", "left.bmp", "top.bmp", "bottom.bmp", "front.bmp", "back.bmp"};

// parameters to bind the textures
GLenum facePos[NFACES] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};

// Positional offset for the object
static float posOffset = 0.0;

// Array of texture index
static GLuint textureID;

// select which object we show
enum object {teapot, cylinder, cube} myObject = teapot;

// Drawing routine.
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Push initial state on the stack
    glPushMatrix();

    glEnable(GL_TEXTURE_CUBE_MAP);
    // Activate texture object.
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Enable automatic generation of s,t and r coordinates
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);

    // Position the object in the scene and render it
    switch(myObject) {
        case teapot:
            glTranslatef(0.0, 0.0, -1.0);
            glRotatef(posOffset, 1.0, 1.0, 0.0);
            glutSolidTeapot(.3);
            break;
        case cube:
            glTranslatef(0.0, 0.0, -1.0);
            glScalef(1.0, 1.7, 1.0);
            glRotatef(posOffset, 0.0, 1.0, 0.0);
            glutSolidCube(.6);
            break;
        case cylinder:
            glTranslatef(0.0, 0.3, -1.0);
            glRotatef(90.0, .2, 0.0, 0.0);
            glRotatef(posOffset, 1.0, 0.0, 0.0);
            glutSolidCylinder(.4, 0.6, 100.0, 100.0);
            break;
        default:
            break;
    }

    // Enable automatic generation of s,t and r coordinates
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);

    // pop initial state from the stack
    glPopMatrix();
    glutSwapBuffers();
}

// Initialization routine.
void init(void) {
    // local variables
    int currInd;
    GLenum glErr;

    glClearColor(1.0, 1.0, 1.0, 0.0);

    // Create texture ids.
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    //glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for(currInd=0; currInd<NFACES; currInd++) {
        // Load external textures
        images[currInd] = readBMP(fileName[currInd]);
        if(images[currInd] == NULL) {
            printf("Could not open file %s\n", fileName[currInd]);
        } else {
            printf("Loaded image %s - %d x %d pixels \n", fileName[currInd],
                images[currInd]->sizeX, images[currInd]->sizeY);
        }

        // generate textures
        glTexImage2D(facePos[currInd], 0, GL_RGBA, images[currInd]->sizeX,
            images[currInd]->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, images[currInd]->data);

    }
    // set parameters to generate s, t, and r texture mapping coordinates
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // ... it does not hurt to check that everything went OK
    if ((glErr=glGetError()) != 0) {
        printf("Errore = %d \n", glErr);
        exit(-1);
    }

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // set viewing frustum
    glFrustum(-.2, .2, -.2, .2, .2, 4.0);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    int currInd;

    switch(key) {
    case 27:
        for(currInd=0; currInd<NFACES; currInd++) {
            if (images[currInd] != NULL) {
                // freee allocated memory
                free(images[currInd]->data);
            }
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
    printf("Press 1 and 2 to move the sphere.\n");

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

