
#include "flight.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>



#define MESH_SIZE 100

double ** mesh;
double speed = 1.;


int main(int argc, char* argv[])
{
	populateMesh();

	glutInit(&argc, (char**)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow ((const char*)"Flight Simulator");

	init();
	
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutTimerFunc(100, update, 60);
	
    glutMainLoop();
    return 0;
}


void init(void)
{
    glClearColor(0.,0.,0.,1.);
    //smooth texturing
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.,1.,1.,40.);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 5, 5, 10, 0, 0, 1);
}

void display(void)
{
	int i, j;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(1.,0.,1.);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for (i=0; i<MESH_SIZE-1; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (j=0; j<MESH_SIZE; j++) {
            glVertex3f(i, j, mesh[i][j]);
            glVertex3f(i+1, j, mesh[i+1][j]);
		}
        glEnd();
	}
	
    glutSwapBuffers();
}



void populateMesh(void) {
	int i, j;
	mesh = (double**)malloc(MESH_SIZE*sizeof(double*));

	printf("Hello world!");

    for (i=0; i<MESH_SIZE; i++) {
    	mesh[i] = (double*)malloc(MESH_SIZE*sizeof(double));
        for (j=0; j<MESH_SIZE; j++) {
            mesh[i][j] = func(i, j);
		}
	}
}


double func(int x, int y) {
    return cos(x/2.) + cos(y/2.);
}
			

void keyboard(unsigned char key, int x, int y)
{
    float * modelview = (float *)malloc(16*sizeof(float));
    switch(key) {
		case 'w':
			glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
			glLoadIdentity();
			glRotatef(-1., 1., 0., 0.);
			glMultMatrixf(modelview);
			break;
		case 'a':
			glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
			glLoadIdentity();
			glRotatef(-5., 0., 0., 1.);
			glMultMatrixf(modelview);
			break;
		case 's':
			glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
			glLoadIdentity();
			glRotatef(1., 1., 0., 0.);
			glMultMatrixf(modelview);
			break;
		case 'd':
			glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
			glLoadIdentity();
			glRotatef(5., 0., 0., 1.);
			glMultMatrixf(modelview);
			break;
		case 'r':
			glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
			glLoadIdentity();
			glRotatef(180., 0., 1., 0.);
			glMultMatrixf(modelview);
			break;
		case 'q':
			speed*=1.33;
			break;
		case 'e':
			speed*=.75;
			break;
	}
	free(modelview);
}

void update(int v)
{
    float * modelview = (float *)malloc(16*sizeof(float));
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
    glLoadIdentity();
    glTranslatef(0., 0., .05*speed);
    glMultMatrixf(modelview);
	free(modelview);

    glutPostRedisplay();
    glutTimerFunc(1000/60, update, v);
}



