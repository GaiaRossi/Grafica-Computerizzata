#include <GL/glew.h>
#include <GL/glut.h>

#define NFACCE 4
#define NVERTICI 8
#define LATO 3.0

GLfloat vertices[24 * 3] = {

    //vertici esterni
    0.0, 0.0, 0.0,
    0.0, LATO, 0.0,
    LATO, LATO, 0.0,
    LATO, 0.0, 0.0,
    LATO, LATO, LATO,
    LATO, 0.0, LATO,
    0.0, LATO, LATO,
    0.0, 0.0, LATO,
      
    //buchi
    LATO/3, LATO/3, 0.0, //8
    LATO/3, LATO * 2/3, 0.0,
    LATO * 2/3, LATO * 2/3, 0.0,
    LATO * 2/3, LATO/3, 0.0,
    
    LATO, LATO/3, LATO/3,
    LATO, LATO * 2/3, LATO/3,
    LATO, LATO * 2/3, LATO * 2/3,
    LATO, LATO/3, LATO * 2/3,

    LATO/3, LATO/3, LATO,
    LATO/3, LATO * 2/3, LATO,
    LATO * 2/3, LATO * 2/3, LATO,
    LATO * 2/3, LATO/3, LATO,

    0.0, LATO/3, LATO/3,
    0.0, LATO * 2/3, LATO/3,
    0.0, LATO * 2/3, LATO * 2/3,
    0.0, LATO/3, LATO * 2/3

};

GLfloat indices[] = {
    //prima faccia
    0, 1, 9, 8, 11, 3,
    2, 3, 11, 10, 9, 1,

    //seconda faccia
    
};