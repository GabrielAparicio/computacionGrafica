#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14159

//Esta es la funcion que recibe el numero de lados y el radio de la circunferencia
void my_polygon(int sides,double radius)
{
    int i,inc_angle=360/sides;
    double angle;
    for(i=0;i<360;i+=inc_angle)
    {
        angle=i*PI/180.0;
        glVertex3f(radius*cos(angle),radius*sin(angle),0);
        angle=(i+inc_angle)*PI/180.0;
        glVertex3f(radius*cos(angle),radius*sin(angle),0);

    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glLoadIdentity();

    glBegin(GL_LINES);
    //Aqui se llama a la funcion con los parametros que el usuario desee
        my_polygon(4,0.5);
    glEnd();
    glFlush();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Poligonos");
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
