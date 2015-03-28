#include <iostream>
#include <gl/glut.h>
#include "const.h"
using  namespace std;
GLfloat diffuseMat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ambientMat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_spec[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_pos[] = { 0, 0, 100, 1 };
void display()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	// 犯了个低级错误，gl_depth_buffer_bit
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, light_spec);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat);
	glMaterialf(GL_FRONT, GL_SHININESS, 25);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseMat);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientMat);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT_FACE, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0, 0, -50);
	glColor4b(255, 255, 255, 255);
	//glColor3b(10, 255, 100);
	glutSolidSphere(50, 20, 16);
	//glutSolidCube(20);
	glPopMatrix();
	glutSwapBuffers();
//	glFlush();


}
void reshape(int x, int y)
{
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	//gluPerspective(50, 640.0 / 480, 0, 1000);
	glOrtho(-320, 320, -240, 240, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
}
void init()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);		//  这里cleardepth 1
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}
void idle()
{
	glutPostRedisplay();
}
void keyboard(unsigned char  key ,int x, int y)
{
	switch (key)
	{
	case 'a':diffuseMat[0] += 0.1;
		diffuseMat[0] = diffuseMat[0] > 0.99 ? 0 : diffuseMat[0];
		break;
	case 's':diffuseMat[1] += 0.1;
		diffuseMat[1] = diffuseMat[1] > 0.99 ? 0 : diffuseMat[1];
		break;
	case 'd':diffuseMat[2] += 0.1;
		diffuseMat[2] = diffuseMat[2] > 0.99 ? 0 : diffuseMat[2];
		break;
	default:
		break;
	}
}
int main()
{
	int argc = 1;
	char *argv[] = { "test" };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutCreateWindow("colorMatertial");
	glutInitWindowPosition(200, 200);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;

}