#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "plant.h"
#include "values.h"
/*
*  ��ϰ1
*  �����������ľ���
*/

//��Ļ��ȣ���Ļ�߶�
GLfloat winWidth,winHeight;
//��������
GLfloat x1 = 100.0f,y1 = 150.0f;
//���δ�С
GLsizei rsize = 10;
//�仯����
GLfloat xstep,ystep = xstep = 1.0f;
//����һ����Ⱦ����
void ghRender(void);
//����һ���ߴ�ı�ص�����
void ghReshape(int width,int height);
//����һ����ʱ���ص�����
void ghTimerFuc(int value);
//������ʼ��gl����
void initGL();

void main()
{
	// ˫����ģʽ* ��RGB��ɫģʽ
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);


	//����һ��Windows���ڣ�����gl����
	glutCreateWindow("Bounce");
	//������ʾ�ص�����
	glutDisplayFunc(ghRender);
	//����windows���ڳߴ�ı�ص�����
	glutReshapeFunc(ghReshape);
	//����һ����ʱ���ص�����
	glutTimerFunc(33,ghTimerFuc,1);
	glutMouseFunc(&OnMouse);  //ע������¼�

	glEnable(GL_CULL_FACE);  
	//glPolygonMode(GL_FRONT, GL_LINE);  


	//��ʼ������
	initGL();
	//����ѭ���ȴ��¼�����
	glutMainLoop();
}

/*
֪ʶ�㣺˫���弼��
�κ�ͼ�������Ӧ�þ߱���һ����Ҫ���ܡ�����ԭ���ǽ���Ҫ���Ƶ���������Ļ��Ļ�����������Ⱦ��Ȼ��ͼ��˲�佻������Ļ�ϡ�
˫���弼����������Ҫ��;��
1���㲻�����û�����ͼ����Ⱦ��ϸ��
2����������

��ҪAPI
1��glutInitDisplayMode(unsigned int mode);
��ʼ��GLUT�⣬�����ô�����ʾģʽ

������mode ����ȡ����ֵ
GLUT_SINGLE  ������ģʽ
GLUT_DOUBLE  ˫����ģʽ

GLUT_RGBA    RGBA��ɫģʽ
GLUT_RGB     RGB��ɫģʽ

GLUT_DEPTH   ָ��һ����32λ��Ȼ�����
GLUT_STENCIL ָ��һ����ֽ������
GLUT_ACCUM   ָ��һ���ۼƻ�����
GLUT_ALPHA   ָ��һ��͸���Ȼ�����

������ö��ֵ�����߸��� ���� glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

2��glutCreateWindow(const char *title);
����һ������ʹ��openGL�Ĵ���

������
title  ���ڵı���

3��glutDisplayFunc(void (*func)(void));
���õ�ǰ������ʾ�Ļص������������ڴ����������ƶ�(��ĳ���ڵײ��ܵ��ϲ�)�����ߵ���glutPostRedisplay��ʱ�����á�

������func һ������Ϊvoid������ֵΪvoid�ĺ���ָ��(��������)
ע�⣺�ú�������Ϊ�����glFlush(),glutSwapBuffers();

4��glutReshapeFunc(void (*func)(int width, int height));
���õ�ǰ���ڳߴ�ı�Ļص�����

������fuc һ������Ϊint width, int height����ֵΪvoid�ĺ���������width��height��ʾ�仯�󴰿ڵĿ�Ⱥ͸߶ȡ�

5��glutTimerFunc(unsigned int millis, void (*func)(int value), int value);
����һ����ʱ���ص�������ʵ�ָ�һ��ʱ�����һ��ĳ����

������millis  �ص��ļ��ʱ�䣬��λΪ����
func  һ������Ϊint������ֵΪvoid�Ļص�����
value ���Խ���ֵ�����ص������Ĳ���value

6��glutMainLoop(void);
����GLUT���߳�ѭ�����������ѭ�����ȴ��û��¼�����꣬���̵ȣ�������
*/


void initGL()
{
	//���Ʊ���ɫΪ��ɫ
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

/*
��ҪAPI
1��glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
��ָ����ɫ��͸���������ɫ����������ɫֵ��alphaֵ

������GLclampf ʵ��Ϊfloat����
red  ��ɫ�ɷ�
green  ��ɫ�ɷ�
blue   ��ɫ�ɷ�
alpha  ͸����
����ȡֵ��Ϊ[0.0f,1.0f]
*/

//��windows���ڳߴ�ı�ʱ��������
void ghReshape(int width,int height)
{
	if (height == 0)
	{
		height = 1;
	}
	//���ÿɻ�������
	glViewport(0,0,width,height);
	//���õ�ǰ����ΪͶӰ����
	glMatrixMode(GL_PROJECTION);
	//���õ�ǰ����Ϊ��λ����
	glLoadIdentity();
	winHeight = 600.0f;
	winWidth = 800.0f;
	
	
	//���Ϊ250���߶�����Ӧ
	/*if(width <= height)
	{
		winHeight = 250.0f * height / width;
		winWidth = 250.0f;
	}
	else
	{
		winWidth = 250.0f * width / height;
		winHeight = 250.0f;
	}
	*/
	//������ά����ϵ
	glOrtho(0.0f,winWidth,0.0f,winHeight,1.0f,-1.0f);
	//�趨��ǰ����Ϊ�Ӿ�����
	glMatrixMode(GL_MODELVIEW);
	//
	glLoadIdentity();
}


/*
��ҪAPI
1��glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
���ô�����gl�Ļ�������

������GLintʵ��Ϊint GLsizeiʵ��Ϊint
x   ��������λ�ڴ�����ߵľ���
y   ��������λ�ڴ��ڵײ��ľ��루����ڴ������½�Ϊ��ԭ��OpenGL���������ԭ�����꣨�����½�Ϊԭ�㣩��
width  ����������
height  ��������߶�

2��glMatrixMode (GLenum mode);
���õ�ǰ�������־���֮��ľ�����������Ըľ���Ϊ���������

������GLenum ʵ��Ϊint
mode����ȡ����ֵ
GL_MODELVIEW   �Ӿ�����
GL_PROJECTION  ͶӰ����
GL_TEXTURE  �������

3��glLoadIdentity (void);
���õ�ǰ����Ϊ��λ����

4��glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
���û��޸Ĳü��ռ�ķ�Χ����3D�ѿ��������У��������Ϊ����һ����ά����ϵ��һ�ηֱ��ʾx,y,z��ȡ�������Сֵ
GLdoubleʵ��Ϊdouble
*/

void ghTimerFuc(int value)
{
	//������Ļ�ͷ���
	/*if (x1 > winWidth - rsize || x1 < 0)
	{
		xstep = -xstep;
	}
	if (y1 > winHeight - rsize || y1 < 0)
	{
		ystep = -ystep;
	}

	if (x1 > winWidth - rsize)
	{
		x1 = winWidth - rsize - 1;
	}

	if (y1 > winHeight - rsize)
	{
		y1 = winHeight - rsize - 1;
	}

	x1 += xstep;
	y1 += ystep;*/

	//�ػ�
	glutPostRedisplay();
	//������ʱ���ص�����
	glutTimerFunc(33,ghTimerFuc,1);
}

/*
��ҪAPI
1��glutPostRedisplay(void);
֪ͨGLUT���»��ƣ����µ�ˢ��δ��ɣ���ε�������Ч�ģ���ͬһʱ���ε���ִֻ��һ��
*/

void ghRender()
{
	//������ɫ����
	glClear(GL_COLOR_BUFFER_BIT);
	
	printPlant();


	//������������ֵ
	glutSwapBuffers();
	//ˢ��
	glFlush();
}

/*
��ҪAPI
1��glClear (GLbitfield mask);
��ָ������������

����:GLbitfield ʵ��Ϊunsigned int
mask ��ȡ����ֵ
GL_DEPTH_BUFFER_BIT ��Ȼ���
GL_ACCUM_BUFFER_BIT �ۻ�����
GL_STENCIL_BUFFER_BIT ģ�建�� 

2��glColor3f (GLfloat red, GLfloat green, GLfloat blue);
�趨������ɫ�����кܶ����

3��glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
����һ����ƽ���Σ����кܶ����

������
x1,y1  ���Ͻǵ�����
x2,y2  ���½ǵ�����

4��glutSwapBuffers(void);
˫����ʱ�����л������Ľ���

5��glFlush();
ˢ����ͼ��gl����ʱ�ı�Ҫ������
*/