#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>


/*   ��ϰ5.1
*   �ı��εĻ��ƣ�ת����������
*/


//����һ����ʾ����
void ghRender(void);
//����һ����ʼ������
void ghInitGL(void);


//��Ļ���
int winWidth = 640;
int winHeight = 480;


int main(int argc, char ** argv)
{
	//��ʼ��glut��
	glutInit(&argc, argv);
	//��ʼ����ʾģʽ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//��ʼ�����ڴ�С
	glutInitWindowSize(winWidth, winHeight);
	//��ʼ������λ��
	glutInitWindowPosition(100, 150);
	//��ʼ������
	glutCreateWindow("Բ׶�Ļ���");
	//ע����ʾ�ص�����
	glutDisplayFunc(ghRender);
	//
	glutIdleFunc(ghRender);
	//��ʼ������
	ghInitGL();
	//����ѭ���ȴ�ʱ��
	glutMainLoop();


	return 0;
}


void ghInitGL(void)
{
	//��ɫ����
	glClearColor(0, 0, 0, 1);
	//����Ϊ��ɫ
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
	//ǰ��
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);


	//����
	glColor3f(0, 0, 1);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);


	//����
	glColor3f(1, 0, 0);
	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, -y, -z);
	glVertex3f(-x, -y, -z);

	//����
	glColor3f(1, 1, 0);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, -y, -z);


	//����
	glColor3f(1, 0, 1);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);

	//����
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
�ı��ε�����ģʽ
GL_GUADS��ÿ��ѡ�ĸ�����Ϊһ�飬����һ���ı��Σ����һ�鲻���ĸ�����ܹ����ı����򲻻���
�����а˸��㣬����������ı���


GL_GUAD_STRIP��ÿ��ȡ��ǰ��͵�ǰ�����һ����͵�ǰ���ǰ������������ı��Σ���ע����˳����Ʒ���


��ϸ��ͼ
*/