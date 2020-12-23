#include <GL/glut.h>

#define NFACCE 4
#define NVERTICIPERFACCIA 4

//per mantenere i riferimenti ai buffers
unsigned int buffers[2];

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

GLubyte indici[NFACCE * NVERTICIPERFACCIA] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

int first = 1;

void display(){
    
    int indiceFaccia, indiceVertice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(first == 1){
        //ogni volta che viene chiamata la funzione display si
        //fa ruotare il sistema dalla OpenGL, facendo ruotare il
        //cubo all'infinito se usa postredisplay
        //
        //con questo if non si gira piu il cubo
        glRotatef(-45.0, 1.0, 0.0, 0.0);
        glRotatef(30.0, 0.0, 1.0, 0.0);
        first = 0;
    }
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

    //questo ciclo e da usare quando si sono creati gli
    //array per vertici e colori e si sono attivati gli array
    //vertex e color
    /*
    for(indiceFaccia = 0; indiceFaccia < NFACCE; indiceFaccia++){
        glBegin(GL_TRIANGLE_STRIP);
        for(indiceVertice = 0; indiceVertice < NVERTICIPERFACCIA; indiceVertice ++){
            glArrayElement(indiceVertice + indiceFaccia * NVERTICIPERFACCIA);
        }
        glEnd();
    }
    */

    //usando i VAO e VBO
    //un buffer contiene sia i vertici sia i colori
    //questo buffer sta in buffers[0]
    //nel secondo buffer ci sono gli indici
    //si necessita di glvertexpointer e glcolorpointer

    for(indiceFaccia = 0; indiceFaccia < NFACCE; indiceFaccia++){
        glDrawElements(GL_TRIANGLE_STRIP, NVERTICIPERFACCIA, GL_UNSIGNED_BYTE, (GLvoid*)(indiceFaccia * NVERTICIPERFACCIA * sizeof(GLbyte)));
    }

    glFlush();

    glutPostRedisplay();
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
    //glColorPointer(3, GL_FLOAT, 0, colori);
    //glVertexPointer(3, GL_FLOAT, 0, vertici);

    //uso vao e vbo
    //necessita di vertex e color array attivi
    glGenBuffers(2, buffers);
    //buffer per vertici e colori
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertici) + sizeof(colori), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertici), vertici);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertici), sizeof(colori), colori);

    //buffer per gli indici
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indici), indici, GL_STATIC_DRAW);

    //specifica l'array contenente i vertici
    glVertexPointer(3, GL_FLOAT, 0, 0);
    //specifica l'array contenente i colori
    glColorPointer(3, GL_FLOAT, 0, (GLvoid*)sizeof(vertici));
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