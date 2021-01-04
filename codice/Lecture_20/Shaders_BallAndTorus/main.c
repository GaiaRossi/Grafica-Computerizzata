/*
 * OpenGL: shaders. Render a sphere and a torus
 * Original C++ code from Guha's book: Computer graphics through OpenGL 2nd edition
 * Translated into C by Antonino Casile
 * Use x, X, y, Y, z and Z to rotate the scene
 * space bar toggle animation on and off
 */

// standard includes
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <math.h>

// application specific includes
#include "shader.h"
#include "hemisphere.h"
#include "torus.h"

static enum object { HEMISPHERE,
                     TORUS }; // VAO ids.
static enum buffer { HEM_VERTICES,
                     HEM_INDICES,
                     TOR_VERTICES,
                     TOR_INDICES }; // VBO ids.

// Globals.
static float latAngle = 0.0;                           // Latitudinal angle.
static float longAngle = 0.0;                          // Longitudinal angle.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static int isAnimate = 0;                              // Animated?
static int animationPeriod = 100;                      // Time interval between frames.

// Hemisphere data.
static Vertex hemVertices[(HEM_LONGS + 1) * (HEM_LATS + 1)];
static unsigned int hemIndices[HEM_LATS][2 * (HEM_LONGS + 1)];
static int hemCounts[HEM_LATS];
static void *hemOffsets[HEM_LATS];
static vec4 hemColors = {HEM_COLORS};

// Torus data.
static Vertex torVertices[(TOR_LONGS + 1) * (TOR_LATS + 1)];
static unsigned int torIndices[TOR_LATS][2 * (TOR_LONGS + 1)];
static int torCounts[TOR_LATS];
static void *torOffsets[TOR_LATS];
static vec4 torColors = {TOR_COLORS};

//static mat4 modelViewMat = glm_mat4_identity();
mat4 modelViewMat = GLM_MAT4_IDENTITY_INIT;
static mat4 projMat = GLM_MAT4_IDENTITY_INIT;

// OpenGL global variables
static unsigned int
   programId,
   vertexShaderId,
   fragmentShaderId,
   modelViewMatLoc,
   projMatLoc,
   objectLoc,
   hemColorLoc,
   torColorLoc,
   buffer[4],
   vao[2];

// Drawing routine.
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);

   glm_translate(modelViewMat, (vec3){0.0, 0.0, -25.0});
   glm_rotate(modelViewMat, Zangle, (vec3){0.0, 0.0, 1.0});
   glm_rotate(modelViewMat, Yangle, (vec3){0.0, 1.0, 0.0});
   glm_rotate(modelViewMat, Xangle, (vec3){1.0, 0.0, 0.0});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);

   // Draw torus.
   glUniform1ui(objectLoc, TORUS); // Update object name.
   glBindVertexArray(vao[TORUS]);
   glMultiDrawElements(GL_TRIANGLE_STRIP, torCounts, GL_UNSIGNED_INT,
                       (const void **)torOffsets, TOR_LATS);

   // Calculate and update modelview matrix.
   glm_rotate(modelViewMat, longAngle, (vec3){0.0, 0.0, 1.0});
   glm_translate(modelViewMat, (vec3){12.0, 0.0, 0.0});
   glm_rotate(modelViewMat, latAngle, (vec3){0.0, 1.0, 0.0});
   glm_translate(modelViewMat, (vec3){-12.0, 0.0, 0.0});
   glm_translate(modelViewMat, (vec3){20.0, 0.0, 0.0});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);

   // Draw ball as two hemispheres.
   glUniform1ui(objectLoc, HEMISPHERE); // Update object name.
   glBindVertexArray(vao[HEMISPHERE]);
   glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);
   glm_scale(modelViewMat, (vec3){1.0, -1.0, 1.0});                           // Scale to make inverted hemisphere.
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat); // Update modelview matrix.
   glMultiDrawElements(GL_TRIANGLE_STRIP, hemCounts, GL_UNSIGNED_INT, (const void **)hemOffsets, HEM_LATS);

   // swap framebuffers
   glutSwapBuffers();
}

// initialization routine
void init(void)
{
   glEnable(GL_DEPTH_TEST);

   // Create shader program executable.
   vertexShaderId = setShader("vertex", "vertexShader.glsl");
   fragmentShaderId = setShader("fragment", "fragmentShader.glsl");
   programId = glCreateProgram();
   glAttachShader(programId, vertexShaderId);
   glAttachShader(programId, fragmentShaderId);
   glLinkProgram(programId);
   glUseProgram(programId);

   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets);
   fillTorus(torVertices, torIndices, torCounts, torOffsets);

   // Create VAOs and VBOs...
   glGenVertexArrays(2, vao);
   glGenBuffers(4, buffer);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[HEMISPHERE]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[HEM_VERTICES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[HEM_INDICES]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(0);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[TORUS]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[TOR_VERTICES]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(torVertices), torVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[TOR_INDICES]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(torIndices), torIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(torVertices[0]), 0);
   glEnableVertexAttribArray(1);

   // Obtain projection matrix uniform location and set value.
   projMatLoc = glGetUniformLocation(programId, "projMat");
   glm_frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0, projMat);
   glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, (GLfloat *)projMat);

   // Obtain color uniform locations and set values.
   hemColorLoc = glGetUniformLocation(programId, "hemColor");
   glUniform4fv(hemColorLoc, 1, &hemColors[0]);
   torColorLoc = glGetUniformLocation(programId, "torColor");
   glUniform4fv(torColorLoc, 1, &torColors[0]);

   // Obtain modelview matrix uniform and object uniform locations.
   modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");
   objectLoc = glGetUniformLocation(programId, "object");

   // pick polygon mode
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   // set background color
   glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
}

// Timer function.
void animate(int value)
{
   if (isAnimate)
   {
      latAngle += (5.0 / 360.0) * (2.0 * M_PI);
      if (latAngle > (2.0 * M_PI))
         latAngle -= 2.0 * M_PI;
      longAngle += (1.0 / 360.0) * (2 * M_PI);
      if (longAngle > 360.0)
         longAngle -= 2.0 * M_PI;

      glutPostRedisplay();
      glutTimerFunc(animationPeriod, animate, 1);
   }
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 27:
      exit(0);
      break;
   case ' ':
      if (isAnimate) 
      {
         isAnimate = 0;
         animate(0);
      }
      else
      {
         isAnimate = 1;
         animate(1);
      }
      break;
   case 'x':
      Xangle += (5.0 / 360.0) * (2.0 * M_PI);
      if (Xangle > (2.0 * M_PI))
         Xangle -= 2.0 * M_PI;
      glutPostRedisplay();
      break;
   case 'X':
      Xangle -= (5.0 / 360.0) * (2.0 * M_PI);
      if (Xangle < 0.0)
         Xangle += 2.0 * M_PI;
      glutPostRedisplay();
      break;
   case 'y':
      Yangle += (5.0 / 360.0) * (2.0 * M_PI);
      if (Yangle > 2.0 * M_PI)
         Yangle -= 2.0 * M_PI;
      glutPostRedisplay();
      break;
   case 'Y':
      Yangle -= (5.0 / 360.0) * (2.0 * M_PI);
      if (Yangle < 0.0)
         Yangle += 2.0 * M_PI;
      glutPostRedisplay();
      break;
   case 'z':
      Zangle += (5.0 / 360.0) * (2.0 * M_PI);
      if (Zangle > 2.0 * M_PI)
         Zangle -= 2.0 * M_PI;
      glutPostRedisplay();
      break;
   case 'Z':
      Zangle -= (5.0 / 360.0) * (2.0 * M_PI);
      if (Zangle < 0.0)
         Zangle += 2.0 * M_PI;
      glutPostRedisplay();
      break;
   default:
      break;
   }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
   if (key == GLUT_KEY_DOWN)
      animationPeriod += 5;
   if (key == GLUT_KEY_UP)
      if (animationPeriod > 5)
         animationPeriod -= 5;
   glutPostRedisplay();
}

// main routine
int main(int argc, char *argv[])
{
   // print instructions
   printf("Interaction: \n");
   printf("Press space to toggle between animation on and off.\n");
   printf("Press the up/down arrow keys to speed up/slow down animation.\n");
   printf("Press the x, X, y, Y, z, Z keys to rotate the scene.\n");

   glutInit(&argc, argv);

   // set OpenGL version
   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_CORE_PROFILE);
   glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Scene with a Ball and a Torus");
   glutDisplayFunc(display);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutSpecialFunc(specialKeyInput);

   glewInit();

   init();
   glutMainLoop();

   // ANSI C requires a return value
   return 0;
}
