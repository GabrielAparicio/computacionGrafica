#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 480, 0, 640);
}

void display() {
	GLfloat midY = 240;
	GLfloat midX = 200;

	GLfloat y = 0;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		for(GLfloat x = -300; x <= 300; x+=0.05) {
			y = x*x;
			glVertex2f(midX + x, midY + y);
		}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(200, 400);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Parabola");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return EXIT_SUCCESS;
}
