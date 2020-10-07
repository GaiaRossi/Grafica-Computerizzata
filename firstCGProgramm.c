#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>

void display(){
    /*
    serve per pulire il buffer specificato come
    parametro con il colore specificato in
    glClearColor.
    */
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    tra glBegin e glEnd vengono creati i vertici della figura che
    voglio disegnare;
    come argomento di glBegin si specifica la primitiva grafica
    da utilizzare
    */
    glBegin(GL_TRIANGLE_STRIP);

        /*
        glColor3f serve per specificare il colore del o dei vertici che
        seguono;
        glVertex2f specifica le coordinate 2D di un vertice
        */
        glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glVertex2f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glVertex2f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX);

        glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glVertex2f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glVertex2f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX);

        glColor3f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX, (float) rand()/RAND_MAX);
        glVertex2f((float) rand()/RAND_MAX, (float) rand()/RAND_MAX);

    glEnd();

    /*
    forza l esecuzione dei comandi precedentemente
    definiti
    */
    glFlush();
}

void init(){
    /*
    setta il colore utilizzato quando verra chiamata glclear
    */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    srand(time(NULL));

    /*
    specifica la matrice da utilizzare nelle successive
    operazioni matriciali
    */
    glMatrixMode(GL_PROJECTION);

    /*
    specifica la proiezione usata per mostrare le figure
    */
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    //proiezione prospettica che non ho ben capito
    //glFrustum(0.0, 1.0, 0.0, 1.0, 0.0, -2.0);
}

int main(int argc, char** argv){

    /*
    serve per inizializzare le librerie GLUT
    e aprire una sessione con il window system
    bisogna passargli come parametri il numero di 
    parametri (come puntatore perche andra a cambiarci
    valore) e il vettore dei parametri non modificato perche
    potrebbero esserci argomenti che servono a GLUT, che verranno
    tolti
    */
    glutInit(&argc, argv);

    /*
    serve per definire la modalita con cui verra mostrata
    la nuova finestra
    */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    /*
    servono per definire la dimensione e la posizione della
    finestra sullo schermo
    */
    glutInitWindowSize(400, 400);

    glutInitWindowPosition(100, 100);

    /*
    serve per sapere l identificatore della finestra appena create
    la finestra non e pero mostrata finche non si chiama
    glutmainloop che chiamera display
    */
    glutCreateWindow("Programma grafica");


    init();
    /*
    serve per far saper a glut qual e la funzione
    display che deve chiamare
    */
    glutDisplayFunc(display);
    /*
    entra nel main loop da cui non torna indietro
    */
    glutMainLoop();
    return 0;
}