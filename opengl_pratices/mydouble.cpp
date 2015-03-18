#include<gl/glut.h>
#include <iostream>
#include <fstream>
#include "const.h"
#ifndef _mydouble_
using namespace std;
void output2file(char* filename, float *glf, int row, int col);
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);
	glPopMatrix();
	
	glutSwapBuffers();
}

void init()
{
	glClearColor(0, 0, 0,0);
	glShadeModel(GL_FLAT);
}

void mouse_Click(int button, int state, int x, int y)
{
	float  modelview[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	output2file("mydouble_temp.txt", modelview, 4, 4);
	glGetFloatv(GL_PROJECTION_MATRIX, modelview);
	output2file("mydouble_temp.txt", modelview, 4, 4);
}

void reshape(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50, 50, -50, 50, 0, 500);
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void output2file(char * filename, GLfloat * glf, int row,int col)
{
	ofstream fout;
	fout.open(filename, ios::app);
	static int firsttime = true;
	fout << endl;
	if (fout.is_open())
	{
		for (int  i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				fout << glf[i*col + j] << " ";
			}
			fout << endl;
		}
	}
	fout.close();
	
}

int main(int argc, char *argv[])
{
	int tempn = 1;
	char *tempchar[] = {"1231"};
	glutInit(&tempn, tempchar);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("mydouble");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(mouse_Click);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;


}
#endif