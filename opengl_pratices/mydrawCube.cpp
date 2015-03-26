#include <iostream>
//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <gl/glut.h>
#include "const.h"
using namespace std;
#ifndef _mydrawCube_ 
GLint vertexArr[] = { -50, 50, 0, -50, -50, 0, 50, -50, 0, 50, 50, 0 };	// �ı��ε��ĸ���������
GLfloat colors[] = { 1.0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 };
GLubyte indexArr[] = { 0, 1, 2, 3 };
GLubyte	indexArr_inv[] = { 3, 2, 1, 0 };
GLint  cube_vertex[] = { -50, 50, 0, -50, -50, 0, 50, -50, 0, 50, 50, 0, 50, 50, -100, 50, -50, 100, -50, -50, 100, -50, 50, 100 };
GLubyte cube_index[] = 
{ 0, 1, 2, 3, 3, 2, 5, 4,
4, 5, 7, 6, 6, 7, 1, 0,
6, 0, 3, 4, 1, 7, 5, 2 };
void dispaly()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-100, -200, -50);
	glutSolidCube(20);
	// ʹ�ö������顣 ���� 1.���ã�2���أ�3 ������
	// �������������ַ�ʽ��һ����arrayelement��һ����drawelement��
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_INT, 0, vertexArr);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glBegin(GL_QUADS);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);
	glEnd();
	glTranslated(100, 0, 0);
	glDrawArrays(GL_QUADS, 0, 4);		// drawArrays

	glTranslated(100, 100, 0);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indexArr);
	// �����±����޳���Ч��  
	glEnable(GL_CULL_FACE);	// Ĭ������� ��ʱ�������棬�����޳���
	glTranslated(100, 100, 0);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indexArr_inv);	// ���Կ���������

	glTranslated(100, 100, 0);
	glFrontFace(GL_CW);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indexArr_inv);// �������������Ķ���֮����Կ���
	glFrontFace(GL_CCW);
	glDisable(GL_CULL_FACE);

	// ��cube
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_INT, 0, cube_vertex);
	glTranslated(-200, 0, 0);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_index);
	//glutSolidCube(50);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glutSwapBuffers();
}
void reshapefun(int w, int h)
{
	glViewport(0,0,640, 480);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-320, 320, -240, 240, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
}
void init()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glShadeModel(GL_SMOOTH);
}
void idle()
{
	dispaly();
}
int main()
{
	int arc = 1;
	char *arcv = "opengl";
	glutInit(&arc, &arcv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("opengl draw cube");
	glutInitWindowPosition(200, 200);
	init();
	glutDisplayFunc(dispaly);
	glutIdleFunc(idle);
	glutReshapeFunc(reshapefun);
	glutMainLoop();
	return 0;
}
#endif