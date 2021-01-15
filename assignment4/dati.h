#include <GL/glew.h>
#include <GL/glut.h>

#define NUMERO_PIANETI 9
#define SLICES 100
#define SCALA 650
#define SECONDI_IN_ANNO 31536000
#define TEMPO 10

unsigned int vao[NUMERO_PIANETI];
unsigned int sole_buffers[2];
unsigned int mercurio_buffers[2];
unsigned int venere_buffers[2];
unsigned int terra_buffers[2];
unsigned int marte_buffers[2];
unsigned int giove_buffers[2];
unsigned int saturno_buffers[2];
unsigned int urano_buffers[2];
unsigned int nettuno_buffers[2];

GLfloat sole_vertex[SLICES * 3 + 3];
GLint sole_indices[SLICES + 2];

GLfloat mercurio_vertex[SLICES * 3 + 3];
GLint mercurio_indices[SLICES + 2];

GLfloat venere_vertex[SLICES * 3 + 3];
GLint venere_indices[SLICES + 2];

GLfloat terra_vertex[SLICES * 3 + 3];
GLint terra_indices[SLICES + 2];

GLfloat marte_vertex[SLICES * 3 + 3];
GLint marte_indices[SLICES + 2];

GLfloat giove_vertex[SLICES * 3 + 3];
GLint giove_indices[SLICES + 2];

GLfloat saturno_vertex[SLICES * 3 + 3];
GLint saturno_indices[SLICES + 2];

GLfloat urano_vertex[SLICES * 3 + 3];
GLint urano_indices[SLICES + 2];

GLfloat nettuno_vertex[SLICES * 3 + 3];
GLint nettuno_indices[SLICES + 2];

float angolo_mercurio = 0;
float angolo_venere = 0;
float angolo_terra = 0;
float angolo_marte = 0;
float angolo_giove = 0;
float angolo_saturno = 0;
float angolo_urano = 0;
float angolo_nettuno = 0;