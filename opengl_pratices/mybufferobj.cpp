#include <iostream>
//#include <gl/GL.h>
#include <gl/glew.h>	// 需要加上这个扩展库
#include <gl/glut.h>
#include "const.h"
using namespace std;
#ifndef _mybufferobj_
// 使用缓冲区对象
GLint rect_point[] = { -50, 50, 0, -50, -50, 0, 50, -50, 0, 50, 50, 0 };
GLubyte rect_color[] = { 255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0 };
GLubyte	rect_index[] = { 0, 1, 2, 3 };
GLuint	buffer[3];
#define bufferoffset(bytes) ((GLubyte*)NULL + bytes)
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0, 0, -200);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	// 这里相当于数据已经在服务器上了，只需要发送绘图命令
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bufferoffset(0));
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void init()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glShadeModel(GL_SMOOTH);
	// 上传顶点到服务器端
	glGenBuffers(3, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_point), rect_point, GL_STATIC_DRAW);
	glVertexPointer(3, GL_INT, 0, bufferoffset(0));	// 和顶点数组一样使用了，好比是数据已经上传，只需要指定命令
//	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect_color), rect_color, GL_STATIC_DRAW);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, bufferoffset(0));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect_index), rect_index, GL_STATIC_DRAW);
	
}

void reshape(int x, int y)
{
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-320, 320, -240, 240, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
}

int main()
{
	int arg = 1;
	char * argc[] = { "test" };
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
	glutInit(&arg, argc);
	glutInitWindowSize(640, 480);
	glutCreateWindow("buffertest");	
	glutInitWindowPosition(200, 200);
	glewInit();
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;

}
#endif

