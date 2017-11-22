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
	//设定画笔颜色
	glColor3f(0.137f,0.87f,0.87f);
	//绘制矩形
	int x1, x2, y1, y2;
	glRectf(x1 = floorMiddlex - stairDis / 2 - stairRectw - stairWallBlank, y1 = height - (upBlank + stairWallBlank * 2 + stairRectl),
		x2 = floorMiddlex + stairDis / 2 + stairRectw + stairWallBlank, y2 = height - downBlank);
	y2 = y1 - floorBlank;
	glRectf(x1, y1 = y2 - (stairWallBlank * 2 + stairRectw * 2 + stairDis), 
		x2, y2);
	y2 = y1 - floorBlank;
	glRectf(floorMiddlex - floorBlank / 2 - stairWallBlank * 2 - stairRectl, y1 = y2 - stairWallBlank * 2 - stairRectw * 2 - stairDis, 
		floorMiddlex - floorBlank / 2, y2);
	glRectf(floorMiddlex + floorBlank / 2, y1, floorMiddlex + floorBlank / 2 + stairWallBlank * 2 + stairRectl, y2);

}
