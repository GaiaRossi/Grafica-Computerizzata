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
#include "window.h"
#include "pianeti.h"
#include "dati.h"

#define N_PLANETS 9
#define SPAZIO 0.00360

static enum object { SUN,
                     MERCURY,
                     VENUS,
                     EARTH,
                     MARS,
                     JUPITER,
                     SATURN,
                     URANUS,
                     NEPTUNE }; // VAO ids.

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
static vec4 sunColors = {245.0/255.0, 210.0/255.0, 11.0/255.0, 1.0};
static vec4 mercuryColors = {159.0/255.0, 131.0/255.0, 51.0/255.0, 1.0};
static vec4 venusColors = {159.0/255.0, 131.0/255.0, 51.0/255.0, 1.0};
static vec4 earthColors = {40.0/255.0, 133.0/255.0, 194.0/255.0, 1.0};
static vec4 marsColors = {185.0/255.0, 59.0/255.0, 16.0/255.0, 1.0};
static vec4 jupiterColors = {185.0/255.0, 59.0/255.0, 16.0/255.0, 1.0};
static vec4 saturnColors = {185.0/255.0, 59.0/255.0, 16.0/255.0, 1.0};
static vec4 uranusColors = {185.0/255.0, 59.0/255.0, 16.0/255.0, 1.0};
static vec4 neptuneColors = {185.0/255.0, 59.0/255.0, 16.0/255.0, 1.0};

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
   sunColorLoc,
   mercuryColorLoc,
   venusColorLoc,
   earthColorLoc,
   marsColorLoc,
   jupiterColorLoc,
   saturnColorLoc,
   uranusColorLoc,
   neptuneColorLoc,
   torColorLoc,
   buffer[N_PLANETS * 2],
   vao[N_PLANETS];

float coordinate[4];

//non funziona
void initialize_buffers(int planet, int buffer_index, Vertex *vertices, const void **indices){
   // ...and associate data with vertex shader.
   glBindVertexArray(vao[planet]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[buffer_index]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[buffer_index + 1]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   glVertexAttribPointer(planet, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);
   glEnableVertexAttribArray(planet);
}

void load_color(GLint colorLoc, GLchar *name, vec4 colors){
   // Obtain color uniform locations and set values.
   colorLoc = glGetUniformLocation(programId, name);
   glUniform4fv(colorLoc, 1, &colors[0]);
}

void draw_planet(int planet, int *counts, void** offset){
   glUniform1ui(objectLoc, planet); 
   glBindVertexArray(vao[planet]);
   glMultiDrawElements(GL_TRIANGLE_STRIP, counts, GL_UNSIGNED_INT, (const void **)offset, HEM_LATS);
   glm_scale(modelViewMat, (vec3){1.0, -1.0, 1.0});                           // Scale to make inverted hemisphere.
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat); // Update modelview matrix.
   glMultiDrawElements(GL_TRIANGLE_STRIP, counts, GL_UNSIGNED_INT, (const void **)offset, HEM_LATS);
}

void aggiorna_angoli(int value){
    angolo_mercurio += SPAZIO/RIVOLUZIONE_MERCURIO;
    angolo_venere += SPAZIO/RIVOLUZIONE_VENERE;
    angolo_terra += SPAZIO/RIVOLUZIONE_TERRA;
    angolo_marte += SPAZIO/RIVOLUZIONE_MARTE;
    angolo_giove += SPAZIO/RIVOLUZIONE_GIOVE;
    angolo_saturno += SPAZIO/RIVOLUZIONE_SATURNO;
    angolo_urano += SPAZIO/RIVOLUZIONE_URANO;
    angolo_nettuno += SPAZIO/RIVOLUZIONE_NETTUNO;
}

// Drawing routine.
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   
   glm_translate(modelViewMat, (vec3){coordinate_sole[0], coordinate_sole[1], coordinate_sole[2]});
   glm_rotate(modelViewMat, Zangle, (vec3){0.0, 0.0, 1.0});
   glm_rotate(modelViewMat, Yangle, (vec3){0.0, 1.0, 0.0});
   glm_rotate(modelViewMat, Xangle, (vec3){1.0, 0.0, 0.0});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(SUN, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_mercurio[0] - coordinate_sole[0]) * cos(angolo_mercurio) + coordinate_sole[0];
   coordinate[1] = coordinate_sole[1];
   coordinate[2] = (coordinate_mercurio[0] - coordinate_sole[0]) * sin(angolo_mercurio) + coordinate_sole[1];
   coordinate[3] = 1.0;

   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(MERCURY, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_venere[0] - coordinate_sole[0]) * cos(angolo_venere) + coordinate_sole[0];
   coordinate[2] = (coordinate_venere[0] - coordinate_sole[0]) * sin(angolo_venere) + coordinate_sole[1];
   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(VENUS, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_terra[0] - coordinate_sole[0]) * cos(angolo_terra) + coordinate_sole[0];
   coordinate[2] = (coordinate_terra[0] - coordinate_sole[0]) * sin(angolo_terra) + coordinate_sole[1];
   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(EARTH, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_marte[0] - coordinate_sole[0]) * cos(angolo_marte) + coordinate_sole[0];
   coordinate[2] = (coordinate_marte[0] - coordinate_sole[0]) * sin(angolo_marte) + coordinate_sole[1];
   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(MARS, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_giove[0] - coordinate_sole[0]) * cos(angolo_giove) + coordinate_sole[0];
   coordinate[2] = (coordinate_giove[0] - coordinate_sole[0]) * sin(angolo_giove) + coordinate_sole[1];
   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(JUPITER, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_saturno[0] - coordinate_sole[0]) * cos(angolo_saturno) + coordinate_sole[0];
   coordinate[2] = (coordinate_saturno[0] - coordinate_sole[0]) * sin(angolo_saturno) + coordinate_sole[1];
   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(SATURN, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_urano[0] - coordinate_sole[0]) * cos(angolo_urano) + coordinate_sole[0];
   coordinate[2] = (coordinate_urano[0] - coordinate_sole[0]) * sin(angolo_urano) + coordinate_sole[1];
   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(URANUS, hemCounts, hemOffsets);

   coordinate[0] = (coordinate_nettuno[0] - coordinate_sole[0]) * cos(angolo_nettuno) + coordinate_sole[0];
   coordinate[2] = (coordinate_nettuno[0] - coordinate_sole[0]) * sin(angolo_nettuno) + coordinate_sole[1];
   // Calculate and update modelview matrix.
   glm_mat4_identity(modelViewMat);
   // Calculate and update modelview matrix.
   glm_translate(modelViewMat, (vec3){coordinate[0], coordinate[1], coordinate[2]});
   glUniformMatrix4fv(modelViewMatLoc, 1, GL_FALSE, (GLfloat *)modelViewMat);
   draw_planet(NEPTUNE, hemCounts, hemOffsets);

   glutTimerFunc(TEMPO, aggiorna_angoli, 0);

   // swap framebuffers
   glutSwapBuffers();
   glutPostRedisplay();
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

   // Create VAOs and VBOs...
   glGenVertexArrays(N_PLANETS, vao);
   glGenBuffers(N_PLANETS * 2, buffer);

   // /initialize_buffers(SUN, 0, hemVertices, hemIndices);

   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_SOLE/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[SUN]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(SUN, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(SUN);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_MERCURIO/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[MERCURY]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[3]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(MERCURY, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(MERCURY);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_VENERE/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[VENUS]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[4]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[5]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(VENUS, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(VENUS);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_TERRA/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[EARTH]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[6]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[7]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(EARTH, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(EARTH);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_MARTE/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[MARS]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[8]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[9]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(MARS, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(MARS);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_GIOVE/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[JUPITER]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[10]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[11]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(JUPITER, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(JUPITER);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_SATURNO/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[SATURN]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[12]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[13]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(SATURN, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(SATURN);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_URANO/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[URANUS]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[14]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[15]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(URANUS, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(URANUS);


   // Initialize hemishpere and torus.
   fillHemisphere(hemVertices, hemIndices, hemCounts, hemOffsets, RAGGIO_NETTUNO/SCALA);

   // ...and associate data with vertex shader.
   glBindVertexArray(vao[NEPTUNE]);
   glBindBuffer(GL_ARRAY_BUFFER, buffer[16]);
   glBufferData(GL_ARRAY_BUFFER, sizeof(hemVertices), hemVertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[17]);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hemIndices), hemIndices, GL_STATIC_DRAW);
   glVertexAttribPointer(NEPTUNE, 4, GL_FLOAT, GL_FALSE, sizeof(hemVertices[0]), 0);
   glEnableVertexAttribArray(NEPTUNE);

   // Obtain projection matrix uniform location and set value.
   projMatLoc = glGetUniformLocation(programId, "projMat");
   glm_ortho(-VIEW_WIDTH, VIEW_WIDTH, -VIEW_HEIGHT, VIEW_HEIGHT, VIEW_NEAR, VIEW_FAR, projMat);
   glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, (GLfloat *)projMat);

   load_color(sunColorLoc, "sunColor", sunColors);
   load_color(mercuryColorLoc, "mercuryColor", mercuryColors);
   load_color(venusColorLoc, "venusColor", venusColors);
   load_color(earthColorLoc, "earthColor", earthColors);
   load_color(marsColorLoc, "marsColor", marsColors);
   load_color(jupiterColorLoc, "jupiterColor", jupiterColors);
   load_color(saturnColorLoc, "saturnColor", saturnColors);
   load_color(uranusColorLoc, "uranusColor", uranusColors);
   load_color(neptuneColorLoc, "neptuneColor", neptuneColors);

   // Obtain modelview matrix uniform and object uniform locations.
   modelViewMatLoc = glGetUniformLocation(programId, "modelViewMat");
   objectLoc = glGetUniformLocation(programId, "object");

   // pick polygon mode
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   // set background color
   glClearColor(0.0, 0.0, 0.0, 0.0);
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
   glutInitWindowSize(W_WIDTH, W_HEIGHT);
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
