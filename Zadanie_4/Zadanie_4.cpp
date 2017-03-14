//4. Program 4. Opracowaæ program, w którym wielok¹t obraca siê wokó³ niektórej osi


#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

GLfloat x_1 = 150.0f;
GLfloat y_1 = 150.0f;
GLsizei rsize = 75;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	const double PI = 3.14159265358979323846;
	int sides = 7;
	float angle = 0;

	glPushMatrix();
	glTranslatef(x_1, y_1, 0);
	glRotatef(-1, 0, 0, 1);
	glTranslatef(-x_1, -y_1, 0);

	glBegin(GL_POLYGON);
	for (int i = 0; i<sides; i++) 
	{
		double angle = i * 2 * PI / sides;
		glVertex2d(x_1 + rsize*sin(angle), y_1 + rsize*cos(angle));
	}
	glPopMatrix();
	glEnd();
	glutSwapBuffers();
}

void TimerFunction(int value) {
	if (x_1 > windowWidth - rsize || x_1 < 0 + rsize)
		xstep = -xstep;
	if (y_1 > windowHeight - rsize || y_1 < 0 + rsize)
		ystep = -ystep;

	if (x_1 > windowWidth - rsize)
		x_1 = windowWidth - rsize - 1;

	if (y_1 > windowHeight - rsize)
		y_1 = windowHeight - rsize - 1;

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
void SetupRC(void) 
{
	glClearColor(0.6f, 0.4f, 0.12f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Zadanie 4");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
