#include <GL/glew.h>
#include <GL/glut.h>

#include "window.h"
#include "vertex.h"

#define RAGGIO_SOLE 696340
#define RAGGIO_MERCURIO 2439.7
#define RAGGIO_VENERE 6051.8
#define RAGGIO_TERRA 6371
#define RAGGIO_MARTE 3389.5
#define RAGGIO_GIOVE 69911
#define RAGGIO_SATURNO 58232
#define RAGGIO_URANO 25362
#define RAGGIO_NETTUNO 24622

#define SOLE 0
#define MERCURIO 1
#define VENERE 2
#define TERRA 3
#define MARTE 4
#define GIOVE 5
#define SATURNO 6
#define URANO 7
#define NETTUNO 8

GLfloat coordinate_sole[3] = {
    VIEW_WIDTH/2.0, VIEW_HEIGHT/2.0, -VIEW_FAR/2.0
};
GLfloat colore_sole[3] = {
    245.0/255.0, 210.0/255.0, 11.0/255.0
};


GLfloat coordinate_mercurio[3] = {
    VIEW_WIDTH/2.0 - 20,
    VIEW_HEIGHT/2.0,
    -VIEW_FAR/2.0
};
GLfloat colore_mercurio[3] = {
    159.0/255.0, 131.0/255.0, 51.0/255.0
};