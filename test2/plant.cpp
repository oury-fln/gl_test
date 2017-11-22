#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "plant.h"
#include "values.h"
#include <iostream>

using namespace std;

//¥�ݿ�Ⱥͳ���
int stairRectw = 15, stairRectl = 30;
//����ͼ�����¿��
int upBlank = 30, downBlank = 30;
//һ���¥�ݺ͸ò��ǽ�ľ���
int stairWallBlank = 10;
//ÿ��¥֮��ľ���
int floorBlank = 10;
//����ͼ��������
int floorMiddlex = 250;
//¥��֮��Ŀ��
int stairDis = 55;

void printPlant() {
	//�趨������ɫ
	glColor3f(0.137f,0.87f,0.87f);
	//���ƾ���
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
