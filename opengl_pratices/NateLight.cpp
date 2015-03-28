//²Î¿¼http://www.codecolony.de/opengl.htm#depthlight
#include <iostream>
#include <GL\glut.h>		//includes gl.h and glu.h
#include "camera.h"
#include "const.h"
using namespace std;
#ifndef _NateLight_
CCamera Camera;
bool LightEnabled = true;
float TorusRotated = 0.0;

static GLfloat MatSpec[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat MatShininess[] = { 45.0 };
static GLfloat LightPos[] = { -2.0, 1.0, 3.0, 0.0 };

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Don't forget the depth buffer!
	glLoadIdentity();	//Load a new modelview matrix -> we can apply new transformations
	Camera.Render();
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glutSolidSphere(1.0, 20, 20);
	glTranslatef(2.0, 0.0, 0.0);
	glutSolidSphere(1.0, 20, 20);
	glPushMatrix();
	glTranslatef(0.0, 2.0, 0.0);
	glutSolidSphere(1.0, 20, 20);
	glPopMatrix();
	glTranslatef(0.0, 0.0, 2.0);
	glutSolidSphere(1.0, 20, 20);
	glTranslatef(-4.0, 0.0, 0.0);
	glRotatef(TorusRotated, 0.0, 1.0, 0.0);
	glutSolidTorus(0.3, 1.0, 8, 16);
	glFlush();			//Finish rendering
	glutSwapBuffers();	//Swap the buffers ->make the result of rendering visible
}
void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering
	//Adjust point size to window size
	glPointSize(GLfloat(x) / 200.0);
}
void KeyDown(unsigned char key, int x, int y)
//Note: because there is an Idle-func, we don't have to call Display here
{
	switch (key)
	{
	case 27:	//ESC
		exit(0);
		break;
	case 97:		//a
		Camera.RotateY(5.0);
		break;
	case 100:		//d
		Camera.RotateY(-5.0);
		break;
	case 119:		//w
		Camera.MoveForwards(-0.1);
		break;
	case 115:		//s
		Camera.MoveForwards(0.1);
		break;
	case 120:		//x
		Camera.RotateX(5.0);
		break;
	case 121:		//y
		Camera.RotateX(-5.0);
		break;
	case 99:		//c
		Camera.StrafeRight(-0.1);
		break;
	case 118:		//v
		Camera.StrafeRight(0.1);
		break;
	case 'l':
		LightEnabled = !LightEnabled;
		if (LightEnabled) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);
		break;
	}
}


void Idle(void)
{
	TorusRotated += 2.0;
	Display();
}

int main(int argc, char **argv)
{
	//Initialize GLUT
	glutInit(&argc, argv);
	//Lets use doublebuffering, RGB(A)-mode and a depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300, 300);
	//Create a window with rendering context and everything else we need
	glutCreateWindow("Lighting and depth testing");
	//Assign the event-handling routines
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyDown);
	glutIdleFunc(Idle);
	Camera.Move(F3dVector(0.0, 0.0, 10.0));
	//Lighting stuff:
	glShadeModel(GL_SMOOTH);	//GL_FLAT would look much worse
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//Let GLUT get the msgs and tell us the ones we need
	glutMainLoop();
	return 0;
}
#endif
