#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define radius 0.5

double** create_matrix(int fil,int col)
{
      double **p = new double*[fil];
      for(int i=0;i<fil;i++)
      {
              p[i] = new double[col];
      }
      return p;
}

void delete_matrix(double** p,int fil,int col)
{
     if(p)
     {
          for(int i=0;i<fil;i++)
          {
                  if(p[i])
                  delete p[i];
          }
          delete p;
     }
}

void fill_mat_points(double **p)
{

     p[0][0]= -0.2;
     p[0][1]= 0.2;
     p[0][2]= 0.2;
     p[0][3]= -0.2;

     p[1][0]= -0.2;
     p[1][1]= -0.2;
     p[1][2]= 0.2;
     p[1][3]= 0.2;

     p[2][0]= 1.0;
     p[2][1]= 1.0;
     p[2][2]= 1.0;
     p[2][3]= 1.0;
}

void fill_matrix(double** p,int fil,int col)
{
     for(int i=0;i<fil;i++)
     {
             for(int j=0;j<col;j++)
             {
                     if(i==j)
                     *(*(p+i)+j)=1.0;
                     else
                     *(*(p+i)+j)=0;
             }
     }
}

double** multiply_matrix(double** m1,int f1,int c1,double** m2,int f2,int c2)
{
    double **result;
    if(c1==f2)
    {
              result=create_matrix(f1,c2);
              double acc = 0;
              for(int i=0;i<f1;i++)
              {
                      for(int j=0;j<c2;j++)
                      {
                              for(int k=0;k<c1;k++)
                              {
                                      acc += m1[i][k]*m2[k][j];
                              }
                              result[i][j]=acc;
                              acc=0.0;
                      }
              }
    }
    return result;
}

double** points_matrix = create_matrix(3,4);
double** translation_mat = create_matrix(3,3);
double** scaling_mat = create_matrix(3,3);
double** rotation_mat = create_matrix(3,3);


void fill_matrices()
{
    fill_mat_points(points_matrix);
    fill_matrix(translation_mat,3,3);
    fill_matrix(scaling_mat,3,3);
    fill_matrix(rotation_mat,3,3);
}


void set_translation(double dx,double dy)
{
    translation_mat[0][2]=dx;
    translation_mat[1][2]=dy;
}

void set_rotation(double angle)
{
    rotation_mat[0][0]=cos(angle*(PI/180));
    rotation_mat[0][1]=-sin(angle*(PI/180));
    rotation_mat[1][0]=sin(angle*(PI/180));
    rotation_mat[1][1]=cos(angle*(PI/180));
}

void set_scaling(double dx,double dy)
{
    scaling_mat[0][0]=dx;
    scaling_mat[1][1]=dy;
}

double** translate_matrix(double** points_matrix,double dx,double dy)
{
    set_translation(dx,dy);
    double** p = multiply_matrix(translation_mat,3,3,points_matrix,3,4);
    delete_matrix(points_matrix,3,4);
    return p;
}

double** rotate_matrix(double** points_matrix,double ang)
{
    set_rotation(ang);
    double** p = multiply_matrix(rotation_mat,3,3,points_matrix,3,4);
    delete_matrix(points_matrix,3,4);
    return p;
}

double** scale_matrix(double** points_matrix,double dx,double dy)
{
    set_scaling(dx,dy);
    double** p = multiply_matrix(scaling_mat,3,3,points_matrix,3,4);
    delete_matrix(points_matrix,3,4);
    return p;
}

void show_matrix(double** my_matrix)
{
    glBegin(GL_QUADS);
        glVertex3f(my_matrix[0][0],my_matrix[1][0],my_matrix[2][0]);
        glVertex3f(my_matrix[0][1],my_matrix[1][1],my_matrix[2][1]);
        glVertex3f(my_matrix[0][2],my_matrix[1][2],my_matrix[2][2]);
        glVertex3f(my_matrix[0][3],my_matrix[1][3],my_matrix[2][3]);
    glEnd();
}
/////////////////////////////////////////////////////////////
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glLoadIdentity();
    fill_matrices();
/*
    points_matrix = scale_matrix(points_matrix,1,2);
    points_matrix = rotate_matrix(points_matrix,45);
    points_matrix = translate_matrix(points_matrix,0.5,0.5);
*/
    points_matrix = translate_matrix(points_matrix,0.5,0);
    points_matrix = scale_matrix(points_matrix,1,2);
    points_matrix = rotate_matrix(points_matrix,45);

    show_matrix(points_matrix);
    glFlush();
}

void init()
{
    glClearColor(0,0,0,0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Transformaciones");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return EXIT_SUCCESS;
}
