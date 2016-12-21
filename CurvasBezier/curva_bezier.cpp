#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

#include <stdio.h>
#include <math.h>
#include <string.h>

int i,n,number,count=1000,count1=1,i1,rccount =0,count2=0,valid=0;
float t;

typedef struct
{
	int x,y;
}Point;

Point p[1000],temp[1000],points[101],temp1[1000],temp2[1000];

Point lerp(Point a,Point b, float t)
{
	Point c;
	c.x = (1-t)*a.x + t*b.x;
	c.y = (1-t)*a.y + t*b.y;
	return c;
}

Point final(Point p[],int n,float t)
{
	if(n>1)
	{
		for(i=0;i<n-1;i++)
		{
			p[i]=lerp(p[i],p[i+1],t);
		}
		final(p,n-1,t);
	}
	else
	{
		return p[0];
	}

}

void plotPoint(int a,int b)
{
	glColor3f(1,0,0);
	glPointSize(5);
	glBegin(GL_POINTS);
     	glVertex2i(a,b);
    	glEnd();
    	glFlush();
}

void printPoint(Point a)
{
	printf("(%d,%d)\n",a.x,a.y);
}

void joinPoints(Point a, Point b)
{
	glBegin(GL_LINES);
	glLineWidth(2);
	glColor3f(0,0,1);
      	glVertex2i(a.x, a.y);
      	glVertex2i(b.x, b.y);
    	glEnd();
    	glFlush();
}

void drawCurve()
{
	glColor3f(0,0,0);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for(i=0;i<101;i++)
	{
		glVertex2f(points[i].x,points[i].y);
	}
	glEnd();
}

void equate(Point p[],Point temp[],int n)
{
	for(i=0;i<n;i++)
	{
		temp[i].x = p[i].x ;
		temp[i].y = p[i].y ;
	}
	count = n;
}

void reset(Point p[],Point temp[],int n)
{
	equate(temp,p,n);
	n = count;
}

void draw()
{
	equate(p,temp,n);
	equate(p,temp1,n);

	points[0].x=p[0].x;
	points[0].y=p[0].y;
	points[100].x=p[n-1].x;
	points[100].y=p[n-1].y;

	t=0.01;
	while(t<=0.99)
	{
		points[count1]=final(p,n,t);
		count1++;
		reset(p,temp1,n);
		t+=0.01;
	}

	drawCurve();

	for(i=0;i<n;i++)
	{
		plotPoint(p[i].x,p[i].y);
	}

	for(i=0;i<n-1;i++)
	{
		joinPoints(p[i],p[i+1]);
	}
}

void drawText(char *string, float x, float y, float z)
{
    	char *c;
    	glRasterPos3f(x, y, z);

    	for (c=string; *c != '\0'; c++)
    	{
        	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    	}
}

void myInit()
{
    	glClearColor(1,1,1,1);
	glColor3f(0,0,0);
	glLoadIdentity();
	gluOrtho2D(0,640,0,480);
	glMatrixMode(GL_MODELVIEW);
}

void myMouse(int button, int state, int a, int b)
{
	int i=0;

  	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		p[number].x = a;
		p[number].y = 480-b;
    		number++;

		if(number<=n)
		{
			plotPoint(a,480-b);
		}

		if(number == n)
		{
			equate(p,temp2,n);

			printf("\n Los siguientes son los puntos de control elegidos :\n\n");

			for(i=0;i<n;i++)
			{
				printf(" Punto %d : ",i+1);
				printPoint(p[i]);
			}

			printf("\n");


			printf(" Click derecho en un punto de control y arrastre para moverlo\n\n");

			glClear(GL_COLOR_BUFFER_BIT);

			glColor3d(0,0,0);
			drawText("Click derecho en un punto de control y arrastre",170,460,0);

			draw();

			count = 0;
		}
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if(count == 0)
		{
			for(i=0;i<n;i++)
			{
				if(temp1[i].x-5 <= a && a <= temp1[i].x+5 && temp1[i].y-5 <= 480-b && 480-b <= temp1[i].y+5)
				{
					printf(" El punto seleccionado es el punto de control %d\n",i+1);
					i1=i;
					rccount = 1;
					valid = state == GLUT_DOWN;
					break;
				}
			}
		}
	}

	if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP && rccount == 1)
	{
		rccount = 0;
		count = 0;
		printf(" Ha sido movido a : (%d,%d)\n\n",a,480-b);
	}

}

void myMotion(int a, int b)
{
	if(rccount == 1)
	{
		temp2[i1].x = a;
		temp2[i1].y = 480-b;

		equate(temp2,p,n);

		equate(p,temp,n);
		equate(p,temp1,n);

		points[0].x=p[0].x;
		points[0].y=p[0].y;
		points[100].x=p[n-1].x;
		points[100].y=p[n-1].y;

		t=0.01;
		count1=1;
		while(t<=0.99)
		{
			points[count1]=final(p,n,t);
			count1++;
			reset(p,temp1,n);
			t+=0.01;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glColor3d(0,0,0);
		drawText("Click derecho en un punto de control y arrastre",170,460,0);
		drawCurve();

		for(i=0;i<n;i++)
		{
			plotPoint(p[i].x,p[i].y);
		}

		for(i=0;i<n-1;i++)
		{
			joinPoints(p[i],p[i+1]);
		}
	}
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0,0,0);
	drawText("Ubique los puntos mediante un click izquierdo",130,460,0);
    glFlush();
}

int main(int argc, char** argv)
{
	printf("\n Ingrese el numero de puntos de control : ");
	scanf("%d",&n);

	while(n<=1)
	{
		printf("\n El numero de puntos de control debe ser mayor a 1. Ingrese el nuevo valor : ");
		scanf("%d",&n);
	}

	printf("\n Plotear los %d puntos en pantalla \n",n);

	glutInit(&argc, argv);
  	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
  	glutInitWindowSize(640,480);
	glutInitWindowPosition(700,0);
	glutCreateWindow("Curva de Bezier");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	myInit();
	glutMainLoop();

	return EXIT_SUCCESS;
}
