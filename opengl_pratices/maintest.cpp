#include<gl/glut.h>
#include "const.h"
#ifndef _maintest_

void myDisplay(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

int main_maintest(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("first opengl program");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}
#endif