#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "plant.h"
#include "values.h"
/*
*  练习1
*  带反弹动画的矩形
*/

//屏幕宽度，屏幕高度
GLfloat winWidth,winHeight;
//矩形坐标
GLfloat x1 = 100.0f,y1 = 150.0f;
//矩形大小
GLsizei rsize = 10;
//变化步长
GLfloat xstep,ystep = xstep = 1.0f;
//声明一个渲染函数
void ghRender(void);
//声明一个尺寸改变回调函数
void ghReshape(int width,int height);
//声明一个定时器回调函数
void ghTimerFuc(int value);
//声明初始化gl操作
void initGL();

void main()
{
	// 双缓冲模式* 和RGB颜色模式
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

	
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);


	//创建一个Windows窗口，用于gl绘制
	glutCreateWindow("Bounce");
	//设置显示回调函数
	glutDisplayFunc(ghRender);
	//设置windows窗口尺寸改变回调函数
	glutReshapeFunc(ghReshape);
	//设置一个定时器回调函数
	glutTimerFunc(33,ghTimerFuc,1);
	glutMouseFunc(&OnMouse);  //注册鼠标事件

	glEnable(GL_CULL_FACE);  
	//glPolygonMode(GL_FRONT, GL_LINE);  


	//初始化操作
	initGL();
	//进入循环等待事件发生
	glutMainLoop();
}

/*
知识点：双缓冲技术
任何图形软件都应该具备的一个重要功能。它的原理是将你要绘制的内容在屏幕外的缓冲区进行渲染，然后将图形瞬间交换到屏幕上。
双缓冲技术有两个重要用途：
1、你不想让用户看到图像渲染的细节
2、制作动画

重要API
1、glutInitDisplayMode(unsigned int mode);
初始化GLUT库，并设置窗口显示模式

参数：mode 可以取以下值
GLUT_SINGLE  单缓冲模式
GLUT_DOUBLE  双缓冲模式

GLUT_RGBA    RGBA颜色模式
GLUT_RGB     RGB颜色模式

GLUT_DEPTH   指定一个持32位深度缓冲区
GLUT_STENCIL 指定一个蜡纸缓冲区
GLUT_ACCUM   指定一个累计缓冲区
GLUT_ALPHA   指定一个透明度缓冲区

如果设置多个值用竖线隔开 例如 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

2、glutCreateWindow(const char *title);
创建一个允许使用openGL的窗口

参数：
title  窗口的标题

3、glutDisplayFunc(void (*func)(void));
设置当前窗口显示的回调函数，当窗口创建，窗口移动(从某窗口底部跑到上层)，或者调用glutPostRedisplay的时候会调用。

参数：func 一个参数为void，返回值为void的函数指针(函数变量)
注意：该函数不会为你调用glFlush(),glutSwapBuffers();

4、glutReshapeFunc(void (*func)(int width, int height));
设置当前窗口尺寸改变的回调函数

参数：fuc 一个参数为int width, int height返回值为void的函数变量。width和height表示变化后窗口的宽度和高度。

5、glutTimerFunc(unsigned int millis, void (*func)(int value), int value);
设置一个定时器回调函数，实现隔一段时间调用一次某函数

参数：millis  回调的间隔时间，单位为毫米
func  一个参数为int，返回值为void的回调函数
value 可以将该值传给回到函数的参数value

6、glutMainLoop(void);
启动GLUT主线程循环，程序进入循环，等待用户事件（鼠标，键盘等）发生。
*/


void initGL()
{
	//绘制背景色为蓝色
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

/*
重要API
1、glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
用指定颜色和透明度清除颜色缓冲区的颜色值和alpha值

参数：GLclampf 实质为float类型
red  红色成分
green  绿色成分
blue   蓝色成分
alpha  透明度
以上取值均为[0.0f,1.0f]
*/

//当windows窗口尺寸改变时，将调用
void ghReshape(int width,int height)
{
	if (height == 0)
	{
		height = 1;
	}
	//设置可绘制区域
	glViewport(0,0,width,height);
	//设置当前矩阵为投影矩阵
	glMatrixMode(GL_PROJECTION);
	//重置当前矩阵为单位矩阵
	glLoadIdentity();
	winHeight = 600.0f;
	winWidth = 800.0f;
	
	
	//宽度为250，高度自适应
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
	//构建三维坐标系
	glOrtho(0.0f,winWidth,0.0f,winHeight,1.0f,-1.0f);
	//设定当前矩阵为视景矩阵
	glMatrixMode(GL_MODELVIEW);
	//
	glLoadIdentity();
}


/*
重要API
1、glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
设置窗口中gl的绘制区域

参数：GLint实质为int GLsizei实质为int
x   绘制区域位于窗口左边的距离
y   绘制区域位于窗口底部的距离（相对于窗口左下角为的原点OpenGL绘制区域的原点坐标（以左下角为原点））
width  绘制区域宽度
height  绘制区域高度

2、glMatrixMode (GLenum mode);
设置当前采用哪种矩阵，之后的矩阵操作都是以改矩阵为操作对象的

参数：GLenum 实质为int
mode可以取以下值
GL_MODELVIEW   视景矩阵
GL_PROJECTION  投影矩阵
GL_TEXTURE  纹理矩阵

3、glLoadIdentity (void);
重置当前矩阵为单位矩阵

4、glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
设置或修改裁剪空间的范围，在3D笛卡尔坐标中，可以理解为勾践一个三维坐标系，一次分别表示x,y,z可取的最大最小值
GLdouble实质为double
*/

void ghTimerFuc(int value)
{
	//超出屏幕就反向
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

	//重绘
	glutPostRedisplay();
	//创建定时器回调函数
	glutTimerFunc(33,ghTimerFuc,1);
}

/*
重要API
1、glutPostRedisplay(void);
通知GLUT重新绘制，在新的刷新未完成，多次调用是无效的，即同一时间多次调用只执行一次
*/

void ghRender()
{
	//清理颜色缓冲
	glClear(GL_COLOR_BUFFER_BIT);
	
	printPlant();


	//交换缓冲区的值
	glutSwapBuffers();
	//刷新
	glFlush();
}

/*
重要API
1、glClear (GLbitfield mask);
按指定类型清理缓冲

参数:GLbitfield 实质为unsigned int
mask 可取以下值
GL_DEPTH_BUFFER_BIT 深度缓冲
GL_ACCUM_BUFFER_BIT 累积缓冲
GL_STENCIL_BUFFER_BIT 模板缓冲 

2、glColor3f (GLfloat red, GLfloat green, GLfloat blue);
设定画笔颜色，其有很多变种

3、glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
绘制一个扁平矩形，其有很多变种

参数：
x1,y1  左上角的坐标
x2,y2  右下角的坐标

4、glutSwapBuffers(void);
双缓冲时，进行缓冲区的交换

5、glFlush();
刷新视图，gl绘制时的必要操作。
*/