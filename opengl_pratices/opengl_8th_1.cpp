#include <iostream>
#include <gl/glew.h>
#include <gl/glut.h>
#include "LoadShaders.h"
#include "vmath.h"
#include "const.h"
#ifndef _opengl_8th_1_
#define buffer_offset(bytes) ((GLubyte*)NULL + bytes)
using namespace std;

enum VAO_IDs{
	Triangles, NumVao
};
enum Buffer_IDs
{
	ArrayBuffer, NumBuffers
};
enum Attrib_IDs
{
	vPosition=0
};
GLuint Vao[NumVao];
GLuint Buffer[NumBuffers];
const GLuint NumVertice = 6;
GLint render_model_matrix_loc;
GLint render_projection_matrix_loc;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -1, 1, 1.0f, 500.0f));
	// 近截面的 左下角和右上角
	//glUniformMatrix4fv(render_projection_matrix_loc, 4, GL_FALSE, projection_matrix);
	vmath::vecN<float, 3> temp1 = vmath::vecN<float, 3>(0);
	temp1[2] = 2;
	vmath::vecN<float, 3> temp2 = vmath::vecN<float, 3>(0);
	temp2[2] = -1;
	vmath::vecN<float, 3> temp3 = vmath::vecN<float, 3>(0);
	temp3[1] = 1;
	vmath::mat4 modelview(vmath::lookat(temp1,temp2,temp3));
//	projection_matrix = vmath::mat4::identity();
//	modelview = vmath::mat4::identity();
	glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, modelview);
	glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, projection_matrix);
	// 参数：location，count =1， true：行主序，false:列主序,   
	glBindVertexArray(Vao[Triangles]);
 	glDrawArrays(GL_TRIANGLES, 0, NumVertice);
	glutSwapBuffers();
	glFlush();
}
void init()
{
	glClearColor(0, 0, 0, 0);
	glClearDepth(1);
	glShadeModel(GL_SMOOTH);


	glGenVertexArrays(NumVao, Vao);
	glBindVertexArray(Vao[Triangles]);
	GLfloat vertices3[NumVertice][3] = {
		{ -200, 200, 0 }, { -300, -200, 0 }, {-100,-200,0},
		{ 200, 200, 0 }, { 100, -200, 0 }, {300,-200,0}
	};
	GLfloat vertices[NumVertice][3] = {
		{ -0.9, -0.9,0 }, { 0.85, -0.9,0 }, { -0.9, 0.85 ,0},
		{ 0.9, -0.85,0 }, { 0.9, 0.9 ,0}, { -0.85, 0.9,0 } };
	glGenBuffers(NumBuffers, Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glVertexPointer(3, GL_FLOAT, 0, buffer_offset(0));			// 这句话指定各个属性类型的数据
	//glEnableClientState(GL_VERTEX_ARRAY);						// 开启顶点数组,不适用shader时候需要，使用shader时候不需要
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{GL_NONE,NULL}
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	render_model_matrix_loc = glGetUniformLocation(program, "model_matrix");
 	render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, buffer_offset(0));
	glEnableVertexAttribArray(vPosition);

}


void reshapefun(int x, int y)
{
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-320, 320, -240, 240, 0, 1000);
	//gluPerspective(40, 640 / 480, 0, 1000);
	glFrustum(-1, 1, -1, 1, 5.99, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 1, 0, 0, -1, 0, 1, 0);	
//---------------------------------------------------------------------------------
	//o 0000000000000 这里怎么设置都不起作用，因为使用shader的时候这里应该被shader使用，
	// 而此时shader 根本就没用这些参数
	// glew32.lib 用在固定管线中， glut32s.lib 用在非固定管线中
//------------------------------------------------------------------------------------
	//glViewport(0, 0, 640, 480);
	//glMatrixMode(GL_PROJECTION);
	//glOrtho(-1, 1, -1, 1, 0, 10);
	//glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0, 0, 1, 0, 0, -1, 0, 1, 0);
}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("first");	
	if (glewInit())
	{
		cout << "error";
	}
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshapefun);
	glutMainLoop();
	return 1;
	

}
#endif