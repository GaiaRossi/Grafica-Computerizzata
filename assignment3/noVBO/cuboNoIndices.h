/*
    usare GL_TRIANGLES_FAN per mostrare
*/

#include <GL/glew.h>
#include <GL/glut.h>

#define NFACCE 8
#define NVERTICI 6
#define LATO 3.0

GLfloat vertices[NFACCE * NVERTICI * 3] = {

        0.0, 0.0, 0.0,
        LATO, 0.0, 0.0,
        LATO * 2/3, LATO/3, 0.0,
        LATO/3, LATO/3, 0.0,
        LATO/3, LATO * 2/3, 0.0,
        0.0, LATO, 0.0,

        LATO, LATO, 0.0,
        LATO, 0.0, 0.0,
        LATO * 2/3, LATO/3, 0.0,
        LATO * 2/3, LATO * 2/3, 0.0,
        LATO/3, LATO * 2/3, 0.0,
        0.0, LATO, 0.0,

        LATO, 0.0, 0.0,
        LATO, LATO, 0.0,
        LATO, LATO * 2/3, LATO/3,
        LATO, LATO/3, LATO/3,
        LATO, LATO/3, LATO * 2/3,
        LATO, 0.0, LATO,

        LATO, LATO, LATO,
        LATO, LATO, 0.0,
        LATO, LATO * 2/3, LATO/3,
        LATO, LATO * 2/3, LATO * 2/3,
        LATO, LATO/3, LATO * 2/3,
        LATO, 0.0, LATO,

        LATO, 0.0, LATO,
        0.0, 0.0, LATO,
        LATO/3, LATO/3, LATO,
        LATO * 2/3, LATO/3, LATO,
        LATO * 2/3, LATO * 2/3, LATO,
        LATO, LATO, LATO,

        0.0, LATO, LATO,
        0.0, 0.0, LATO,
        LATO/3, LATO/3, LATO,
        LATO/3, LATO * 2/3, LATO,
        LATO * 2/3, LATO * 2/3, LATO,
        LATO, LATO, LATO,

        0.0, 0.0, LATO,
        0.0, 0.0, 0.0,
        0.0, LATO/3, LATO/3,
        0.0, LATO/3, LATO * 2/3,
        0.0, LATO * 2/3, LATO * 2/3,
        0.0, LATO, LATO,

        0.0, LATO, 0.0,
        0.0, 0.0, 0.0,
        0.0, LATO/3, LATO/3,
        0.0, LATO * 2/3, LATO/3,
        0.0, LATO * 2/3, LATO * 2/3,
        0.0, LATO, LATO,

};

GLfloat colors[NFACCE * NVERTICI * 3] = {
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,

    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0    
};