/*
    usare GL_TRIANGLES_FAN per mostrare
*/

#include <GL/glew.h>
#include <GL/glut.h>

#define NFACCE 8
#define NVERTICI 6
#define LATO 3.0

GLfloat vertices[24 * 3] = {

    //vertici esterni
    0.0, 0.0, 0.0,
    0.0, LATO, 0.0,
    LATO, LATO, 0.0,
    LATO, 0.0, 0.0,
    LATO, LATO, LATO, //4
    LATO, 0.0, LATO,
    0.0, LATO, LATO,
    0.0, 0.0, LATO,
      
    //buchi
    LATO/3, LATO/3, 0.0, //8
    LATO/3, LATO * 2/3, 0.0,
    LATO * 2/3, LATO * 2/3, 0.0,
    LATO * 2/3, LATO/3, 0.0,
    
    LATO, LATO/3, LATO/3, //12
    LATO, LATO * 2/3, LATO/3,
    LATO, LATO * 2/3, LATO * 2/3,
    LATO, LATO/3, LATO * 2/3,

    LATO/3, LATO/3, LATO, //16
    LATO/3, LATO * 2/3, LATO,
    LATO * 2/3, LATO * 2/3, LATO,
    LATO * 2/3, LATO/3, LATO,

    0.0, LATO/3, LATO/3, //20
    0.0, LATO * 2/3, LATO/3,
    0.0, LATO * 2/3, LATO * 2/3,
    0.0, LATO/3, LATO * 2/3

};

GLint indices[] = {
    //prima faccia
    0, 3, 11, 8, 9, 1,
    2, 3, 11, 10, 9, 1,

    //seconda faccia
    3, 2, 13, 12, 15, 5,
    4, 2, 13, 14, 15, 5,

    //terza faccia
    5, 7, 16, 19, 18, 4,
    6, 7, 16, 17, 18, 4,

    //quarta faccia
    7, 0, 20, 23, 22, 6,
    1, 0, 20, 21, 22, 6
};

GLfloat colors[] = {
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,

    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 1.0
};