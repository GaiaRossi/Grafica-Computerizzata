#include "circle.h"

/* creo cerchio con triangle fan */
/* x^2 + y^2 = r^2 */

void calcola_coordinate(GLfloat coord[], int slices, float radius){
    int i;
    int slice = 0;
    coord[0] = 0.0;
    coord[1] = 0.0;
    coord[2] = 0.0;
    for(i = 3; i <= slices * 3; i += 3, slice++){
        coord[i] = radius * cos(slice * 2*M_PI/slices);
        coord[i + 1] = radius * sin(slice * 2*M_PI/slices);
        coord[i + 2] = -50.0;
    }
}

void genera_indici(unsigned int indici[], int numero_indici){
    indici[0] = 0;
    int i;
    for(i = 1; i < numero_indici - 1; i++){
        indici[i] = i;
    }
    indici[numero_indici - 1] = indici[1];
}