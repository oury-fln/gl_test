#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "plant.h"
#include "values.h"
#include <iostream>

using namespace std;

//楼梯宽度和长度
int stairRectw = 15, stairRectl = 30;
//整张图的上下宽度
int upBlank = 30, downBlank = 30;
//一层的楼梯和该层的墙的距离
int stairWallBlank = 10;
//每层楼之间的距离
int floorBlank = 10;
//整张图的中轴线
int floorMiddlex = 250;
//楼梯之间的宽度
int stairDis = 55;

void printPlant() {
	//draw the wall
	//设定画笔颜色
	glColor3f(r0, g0, b0);
	//绘制矩形
	int x1, x2, y1, y2, x3, x4, y3, y4;
	int floorRect[7][4];  //1 -- floor; 2 -- 0x1 1y1 2x2 3y2
	glRectf(floorRect[0][0] = x1 = floorMiddlex - stairDis / 2 - stairRectw - stairWallBlank, floorRect[0][1] = y1 = height - (upBlank + stairWallBlank * 2 + stairRectl),
		floorRect[0][2] = x2 = floorMiddlex + stairDis / 2 + stairRectw + stairWallBlank, floorRect[0][3] = y2 = height - downBlank);
	y2 = y1 - floorBlank;
	glRectf(floorRect[1][0] = x1, floorRect[1][1] = y1 = y2 - (stairWallBlank * 2 + stairRectw * 2 + stairDis),
		floorRect[1][2] = x2, floorRect[1][3] = y2);
	y2 = y1 - floorBlank;
	glRectf(floorRect[2][0] = x1 = floorMiddlex - floorBlank / 2 - stairWallBlank * 2 - stairRectl, floorRect[2][1] = y1 = y2 - stairWallBlank * 2 - stairRectw * 2 - stairDis,
		floorRect[2][2] = x3 = floorMiddlex - floorBlank / 2, floorRect[2][3] = y2);
	glRectf(floorRect[3][0] = x2 = floorMiddlex + floorBlank / 2, floorRect[3][1] = y1, 
		floorRect[3][2] = x4 = floorMiddlex + floorBlank / 2 + stairWallBlank * 2 + stairRectl, floorRect[3][3] = y2);
	y2 = y1 - floorBlank;
	glRectf(floorRect[4][0] = x1, floorRect[4][1] = y1 = y2 - stairWallBlank * 2 - stairRectw * 2 - stairDis,
		floorRect[4][2] = x3, floorRect[4][3] = y2);
	glRectf(floorRect[5][0] = x2, floorRect[5][1] = y1, floorRect[5][2] = x4, floorRect[5][3] = y2);
	y2 = y1 - floorBlank;
	glRectf(floorRect[6][0] = floorMiddlex - stairRectl / 2 - stairWallBlank, floorRect[6][1] = y2 - stairWallBlank * 2 - stairRectw * 2 - stairDis,
		floorRect[6][2] = floorMiddlex + stairRectl / 2 + stairWallBlank, floorRect[6][3] = y2);

	//draw the stair
	//1
	glColor3f(r4,g4,b4);
	glRectf(x1 = floorRect[0][0] + stairWallBlank, y1 = floorRect[0][1] + stairWallBlank, 
		x2 = floorRect[0][0] + stairWallBlank + stairRectw, y2 = floorRect[0][3] - stairWallBlank);
	glRectf(x1, y3 = floorRect[1][1] + stairWallBlank + stairRectw + (stairDis - stairRectl) / 2, x2,
		y4 = floorRect[1][3] - stairWallBlank - stairRectw - (stairDis - stairRectl) / 2);
	//2
	glColor3f(r5, g5, b5);
	glRectf(x1 = floorRect[0][2] - stairWallBlank - stairRectw, y1, x2 = floorRect[0][2] - stairWallBlank, y2);
	glRectf(x1, y3, x2, y4);

	//3
	glColor3f(r6, g6, b6);
	y2 = floorRect[1][3] - stairWallBlank;
	glRectf(x1 = floorRect[1][0] + stairWallBlank + stairRectw + (stairDis - stairRectl) / 2, y1 = y2 - stairRectw, 
		x2 = floorMiddlex + stairRectl / 2, y2);
	y2 = floorRect[2][3] - stairWallBlank;
	glRectf(x3 = floorRect[2][0] + stairWallBlank, y1 = y2 - stairRectw, x4 = floorRect[2][2] - stairWallBlank, y2);

	//4
	glColor3f(r7, g7, b7);
	y3 = floorRect[1][1] + stairWallBlank;
	glRectf(x1, y3, x2, y4 = y3 + stairRectw);
	y3 = floorRect[3][1] + stairWallBlank;
	glRectf(x1 = floorRect[3][0] + stairWallBlank, y3, x2 = floorRect[3][2] - stairWallBlank, y4 = y3 + stairRectw);

	//5
	glColor3f(r8, g8, b8);
	glRectf(x3, y3, x4, y4);
	y3 = floorRect[4][1] + stairWallBlank;
	glRectf(x3, y3, x4, y4 = y3 + stairRectw);

	//6
	glColor3f(r9, g9, b9);
	glRectf(x1, y1, x2, y2);
	y2 = floorRect[5][3] - stairWallBlank;
	glRectf(x1, y1 = y2 - stairRectw, x2, y2);

	//8
	glColor3f(r10, g10, b10);
	glRectf(x3, y1, x4, y2);
	y2 = floorRect[6][3] - stairWallBlank;
	glRectf(x3 = floorRect[6][0] + stairWallBlank, y2 - stairRectw, x4 = floorRect[6][2] - stairWallBlank, y2);

	//7
	glColor3f(r11, g11, b11);
	glRectf(x1, y3, x2, y4);
	y3 = floorRect[6][1] + stairWallBlank;
	glRectf(x3, y3, x4, y3 + stairRectw);

}
