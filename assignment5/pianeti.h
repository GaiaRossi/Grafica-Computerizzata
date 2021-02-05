#include <GL/glew.h>
#include <GL/glut.h>

#define RIVOLUZIONE_MERCURIO 0.241
#define RIVOLUZIONE_VENERE 0.615
#define RIVOLUZIONE_TERRA 1.0
#define RIVOLUZIONE_MARTE 1.881
#define RIVOLUZIONE_GIOVE 11.87
#define RIVOLUZIONE_SATURNO 29.45
#define RIVOLUZIONE_URANO 84.07
#define RIVOLUZIONE_NETTUNO 164.9

//#define RAGGIO_SOLE 696340
#define RAGGIO_SOLE 100000
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

#define DISTANZA_PIANETI 100

GLfloat coordinate_sole[3] = {
    0.0,
    0.0,
    0.0
};
GLfloat colore_sole[3] = {
    245.0/255.0, 210.0/255.0, 11.0/255.0
};


GLfloat coordinate_mercurio[3] = {
    DISTANZA_PIANETI * MERCURIO,
    0.0,
    0.0
};
GLfloat colore_mercurio[3] = {
    159.0/255.0, 131.0/255.0, 51.0/255.0
};


GLfloat coordinate_venere[3] = {
    DISTANZA_PIANETI * VENERE,
    0.0,
    0.0
};
GLfloat colore_venere[3] = {
    159.0/255.0, 131.0/255.0, 51.0/255.0
};


GLfloat coordinate_terra[3] = {
    DISTANZA_PIANETI * TERRA,
    0.0,
    0.0
};
GLfloat colore_terra[3] = {
    40.0/255.0, 133.0/255.0, 194.0/255.0
};


GLfloat coordinate_marte[3] = {
    DISTANZA_PIANETI * MARTE,
    0.0,
    0.0
};
GLfloat colore_marte[3] = {
    185.0/255.0, 59.0/255.0, 16.0/255.0
};


GLfloat coordinate_giove[3] = {
    DISTANZA_PIANETI * GIOVE,
    0.0,
    0.0
};
GLfloat colore_giove[3] = {
    185.0/255.0, 59.0/255.0, 16.0/255.0
};


GLfloat coordinate_saturno[3] = {
    DISTANZA_PIANETI * SATURNO,
    0.0,
    0.0
};
GLfloat colore_saturno[3] = {
    185.0/255.0, 59.0/255.0, 16.0/255.0
};


GLfloat coordinate_urano[3] = {
    DISTANZA_PIANETI * URANO,
    0.0,
    0.0
};
GLfloat colore_urano[3] = {
    185.0/255.0, 59.0/255.0, 16.0/255.0
};


GLfloat coordinate_nettuno[3] = {
    DISTANZA_PIANETI * NETTUNO,
    0.0,
    0.0
};
GLfloat colore_nettuno[3] = {
    185.0/255.0, 59.0/255.0, 16.0/255.0
};