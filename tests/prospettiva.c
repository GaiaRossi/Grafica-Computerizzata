#include <GL/glut.h>
#include <stdlib.h>

void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);        
        glTranslatef(0.5, 0.5, -1.7);
        glRotatef(45.0, 1.0, 1.0, 0.0);
        //glutWireSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);        
        glTranslatef(0.5, 0.5, -3.7);
        glRotatef(45.0, 1.0, 1.0, 0.0);
        glutWireSphere(0.3, 20, 20);
    glPopMatrix();

    glFlush();

}

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);

    //prospettiva
    glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 5.0);
    //glFrustum(-1.0, 2.0, -3.0, 2.0, 1.0, 5.0);

}

int main(int argc, char** argv){

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(400, 400);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Prospettiva");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}