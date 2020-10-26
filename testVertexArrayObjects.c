#include <GL/glut.h>

#define NFACCE 4
#define NVERTICIPERFACCIA 4

GLfloat vertici[NFACCE * NVERTICIPERFACCIA * 3] = {
    // first face - v0,v1,v3,v2
    0.5, -0.5, 0.5, // v0
    0.5, 0.5, 0.5, // v1
    -0.5, -0.5, 0.5, // v3
    -0.5, 0.5, 0.5, // v2

    // second face - v3,v2,v7,v6
    -0.5, -0.5, 0.5, // v3
    -0.5, 0.5, 0.5, // v2
    -0.5, -0.5, -0.5, // v7
    -0.5, 0.5, -0.5, // v6

    // third face - v7,v6,v4,v5
    -0.5, -0.5, -0.5, // v7
    -0.5, 0.5, -0.5, // v6
    0.5, -0.5, -0.5, // v4
    0.5, 0.5, -0.5, // v5

    // forth face - v4, v5, v0, v1
    0.5, -0.5, -0.5, // v4
    0.5, 0.5, -0.5, // v5
    0.5, -0.5, 0.5, // v0
    0.5, 0.5, 0.5 // v1
};

GLfloat colori[NFACCE * NVERTICIPERFACCIA * 3] = {
    //colore prima faccia
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    //colore seconda faccia
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    //colore terza faccia
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    //colore quarta faccia
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    0.0, 1.0, 1.0
};

void display(){
    
    int indiceFaccia, indiceVertice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(-45.0, 1.0, 0.0, 0.0);
    glRotatef(30.0, 0.0, 1.0, 0.0);

    //questo ciclo e da usare se si voglio scorrere
    //gli array dei vertici e dei colori
    //come si farebbe nella programmazione classica
    //i vettori di colori e vertici devono essere bidimensionali
    //per usare questo ciclo
    /*
    for(indiceFaccia = 0; indiceFaccia < NFACCE; indiceFaccia++){
        glBegin(GL_TRIANGLE_STRIP);
        for(indiceVertice = 0; indiceVertice < NVERTICIPERFACCIA; indiceVertice++){
            glColor3fv(colori[indiceVertice + indiceFaccia * NVERTICIPERFACCIA]);
            glVertex3fv(vertici[indiceVertice + indiceFaccia * NVERTICIPERFACCIA]);
        }
        glEnd();
    }
    */

    for(indiceFaccia = 0; indiceFaccia < NFACCE; indiceFaccia++){
        glBegin(GL_TRIANGLE_STRIP);
        for(indiceVertice = 0; indiceVertice < NVERTICIPERFACCIA; indiceVertice ++){
            glArrayElement(indiceVertice + indiceFaccia * NVERTICIPERFACCIA);
        }
        glEnd();
    }

    glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 5.0, 0.0, 3.0, 0.0, 5.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //serve per dire alla gl di 
    //comparare le coordinate su z
    //per decidere quale figura e piu
    //lontana
    glEnable(GL_DEPTH_TEST);
    //il buffer va pero pulito
    glClear(GL_DEPTH_BUFFER_BIT);
    //indica come valutare la profondita
    //dei pixel
    glDepthFunc(GL_LESS);

    //se non chiamo queste funzioni non funzionano
    //glarrayelements o gldrawarray
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    //bisogna dirgli quali sono questi array
    glColorPointer(3, GL_FLOAT, 0, colori);
    glVertexPointer(3, GL_FLOAT, 0, vertici);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 300);
    glutCreateWindow("test VAO e VBO");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}