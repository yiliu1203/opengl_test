#include <iostream>
#include <gl/glut.h>
#include <gl/glew.h>
#include "const.h"
using namespace std;
#ifndef _myvao_
// É¾³ývao£¿£¿£¿
enum MyVao	{cube,cone,NumVao};
enum MyVbo	{Vertex,Color,Elements,NumVbo};
GLuint Vao[NumVao];
GLuint Vbo[NumVbo];
GLint  cube_vertex[] = { -50, 50, 0, -50, -50, 0, 50, -50, 0, 50, 50, 0, 50, 50, -100, 50, -50, 100, -50, -50, 100, -50, 50, 100 };
GLubyte cube_index[] =
{ 0, 1, 2, 3, 3, 2, 5, 4,
4, 5, 7, 6, 6, 7, 1, 0,
6, 0, 3, 4, 1, 7, 5, 2 };
GLfloat cube_color[] = { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0.5, 0, 0, 1, 0, 0.5, 0.5, 0.5, 0.5 };
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void init()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glShadeModel(GL_SMOOTH);
}
void reshape(int x, int y)
{
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-320, 320, -240, 240, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, -1, 0, 0, 1, 0);

}
int main()
{
	int agrc = 1;
	char *argv[] = { "test" };
	glutInit(&agrc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("myvao");
	glutInitWindowPosition(200, 200);
	glewInit();
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
#endif