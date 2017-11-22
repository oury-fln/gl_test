#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>


/*   练习5.1
*   四边形的绘制，转动的立方体
*/


//声明一个显示函数
void ghRender(void);
//声明一个初始化函数
void ghInitGL(void);


//屏幕宽高
int winWidth = 640;
int winHeight = 480;


int main(int argc, char ** argv)
{
	//初始化glut库
	glutInit(&argc, argv);
	//初始化显示模式
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//初始化窗口大小
	glutInitWindowSize(winWidth, winHeight);
	//初始化窗口位置
	glutInitWindowPosition(100, 150);
	//初始化窗口
	glutCreateWindow("圆锥的绘制");
	//注册显示回调函数
	glutDisplayFunc(ghRender);
	//
	glutIdleFunc(ghRender);
	//初始化函数
	ghInitGL();
	//进入循环等待时间
	glutMainLoop();


	return 0;
}


void ghInitGL(void)
{
	//黑色背景
	glClearColor(0, 0, 0, 1);
	//画笔为绿色
	glColor3f(0, 1, 0);


	GLfloat nRange = 100.0f;
	glViewport(0, 0, winWidth, winHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-nRange * winWidth / winHeight, nRange * winWidth / winHeight, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


float xRot, yRot, zRot;


void ghRender(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float x, y, z = y = x = 30;
	glPushMatrix();
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glRotatef(zRot, 0, 0, 1);


	glBegin(GL_QUADS);
	//前面
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);


	//右面
	glColor3f(0, 0, 1);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);


	//底面
	glColor3f(1, 0, 0);
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);

	//后面
	glColor3f(1, 1, 0);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, -y, -z);


	//左面
	glColor3f(1, 0, 1);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);

	//顶面
	glColor3f(0, 1, 1);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glEnd();


	glPopMatrix();


	glutSwapBuffers();
	glFlush();
	xRot = yRot = zRot = zRot + 1;
}


/*
四边形的两种模式
GL_GUADS：每次选四个顶点为一组，绘制一个四边形，如果一组不够四个点或不能构成四边形则不绘制
例如有八个点，则绘制两个四边形


GL_GUAD_STRIP：每次取当前点和当前点的下一个点和当前点的前两个个点绘制四边形，（注意点的顺序和绕法）


详细见图
*/