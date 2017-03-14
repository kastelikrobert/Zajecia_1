//Program 5 (zadanie domowe)*.Opracowaæ program w którym u¿ytkownik wskazuje punkty w oknie – wierzcho³ki wielok¹ta, który buduje siê.Dalej za pomoc¹ menu wydostaje siê iloœæ wierzcho³ków w wielok¹cie.Program buduje wielok¹t

#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

vector< float > points;
string text = "Liczba wierzcholkow: ";

void Text()
{
	string fullText = text;
	string str = to_string(points.size()/2);
	fullText += str;
	glRasterPos2f(10, 10);
	for (int i = 0; i < fullText.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, fullText[i]);
	}
}

void myDisplay(void)
{

	glClearColor(0.6f, 0.4f, 0.12f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (size_t i = 0; i < points.size(); i += 2)
	{
		glVertex2d(points[i], points[i + 1]);
	}
	glEnd();

	Text();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (size_t i = 0; i < points.size(); i += 2)
	{
		glVertex2f(points[i], points[i + 1]);
	}
	glEnd();
	glFlush();
}

void myMouse(int button, int state, int x, int y)
{
	int yy;
	yy = glutGet(GLUT_WINDOW_HEIGHT);
	y = yy - y;
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
	{
		points.push_back(x);
		points.push_back(y);
	}
	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Zadanie 5");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMainLoop();
}