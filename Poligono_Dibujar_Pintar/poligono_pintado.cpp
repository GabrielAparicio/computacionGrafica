#include "Polygon.h"
using namespace std;

vector<Shapes::Polygon*> Polygons;
Shapes::Polygon * currentPolygon;


void InitializeScene(){
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode (GL_PROJECTION);
}
void WindowsSizeChangedEvent(int w, int h){
{

		GLfloat nRange = 100.0f;
		if(h == 0)
			h = 1;

		glViewport(0, 0, w, h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (w <= h)
			glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
		else
			glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}
void MouseEvent(int button,int state,int x,int y){

	double worldX=0, worldY=0, worldZ=0;


	GLint view[4];
	GLdouble  projMatrix[16];
	GLdouble  modelMatrix[16];

	glGetDoublev (GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev (GL_PROJECTION_MATRIX,projMatrix);
	glGetIntegerv( GL_VIEWPORT, view );

	gluUnProject(x,view[3]-y,0.5,modelMatrix,projMatrix,view, &worldX, &worldY, &worldZ);


	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		glutDetachMenu(GLUT_RIGHT_BUTTON);

		currentPolygon->addVertex(worldX,worldY);


	}
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		glutAttachMenu(GLUT_RIGHT_BUTTON);
		currentPolygon->finishPolygon();
		Polygons.push_back(currentPolygon);
		currentPolygon=new Shapes::Polygon();
	}

	glutPostRedisplay();

}
void RenderGrid(int distance)
{
	glEnable(GL_POLYGON_STIPPLE);
	glColor3ub(64,64,64);
	for(int i=-400;i<=400;i+=distance){
		glBegin(GL_LINES);
		glVertex2i(i,-300);
		glVertex2i(i,300);
		glEnd();
	}
	for(int i=-300;i<=300;i+=distance){
		glBegin(GL_LINES);
		glVertex2i(-400, i);
		glVertex2i(400,i);
		glEnd();
	}
	glDisable(GL_POLYGON_STIPPLE);

}
void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(6);
	using namespace Shapes;

	RenderGrid(5);

	if(currentPolygon){
		currentPolygon->Render();
	}

	for(int i=0;i<Polygons.size();i++)
	{
		Polygons[i]->Render();
	}


	glFlush();
}

int main(int argc, char* argv[])
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("Dibujar y pintar poligono");
	glutReshapeFunc(WindowsSizeChangedEvent);
	glutMouseFunc(MouseEvent);
	InitializeScene();

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	currentPolygon=new Shapes::Polygon();
	glutDisplayFunc(RenderScene);
	glutMainLoop();

	return EXIT_SUCCESS;
}
