#include "circle.h"

/* creo cerchio con triangle fan */
/* x^2 + y^2 = r^2 */

void calcola_coordinate(GLfloat coord[], int slices, float radius){
    int i;
    coord[0] = 0.0;
    coord[1] = 0.0;
    coord[2] = 0.0;
    for(i = 3; i < slices * 3; i += 3){
        coord[i] = radius * cos(i * 2*M_PI/slices);
        coord[i + 1] = radius * sin(i * 2*M_PI/slices);
        coord[i + 2] = -50.0;
    }
}