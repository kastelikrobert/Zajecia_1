//1. Program 1. Opracować program który tworzy w GLUT standardowe okno interfejsu GUI z nagłówkiem "Mój pierwszy program w GLUT"  i pustym brązowym tłem.
//2. Program 2. Narysować w oknie programu Program1 wielokąt.Dodatkowo uzyskać możliwość zmiany położenia i rozmiaru okna, tak żeby kod renderujący odpowiednio reagował na te zmiany.
//3. Program 3. Opracować dla Programu 2 efekt animacji, żeby wielokąt  odbijałby się od ram okna.Przygotować pętlę, w której zmieniać współrzędne obiektu przed wywołaniem funkcji RenderScene.Obiekt musi sprawiać wrażenie ruchu wewnątrz okna wzdłuż obwodu(zadanie domowe)*


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
GLsizei rsize = 50;

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
	
	glBegin(GL_POLYGON);
	for (int i = 0; i<sides; i++) 
	{
		double angle = i * 2 * PI / sides;
		glVertex2d(x_1 + rsize*sin(angle), y_1 + rsize*cos(angle));
	}
	glEnd();
	glutSwapBuffers();
}

void TimerFunction(int value) {
	if (x_1 > windowWidth - rsize || x_1 < 0 + rsize)
		xstep = -xstep;

	if (y_1 > windowHeight - rsize|| y_1 < -5 + rsize)
			ystep = -ystep;

	if (x_1 > windowWidth - rsize)
		x_1 = windowWidth - rsize - 1;

	if (y_1 > windowHeight - rsize)
		y_1 = windowHeight - rsize - 1;

	x_1 += xstep/2.0;
	y_1 += ystep/2.0;
	
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}


void SetupRC(void) 
{
	glClearColor(0.6f, 0.4f, 0.12f, 0.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
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
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
