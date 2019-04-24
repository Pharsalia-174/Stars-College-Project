#pragma once
#ifndef SUPERCHAT_DISPLAY_H
#define SUPERCHAT_DISPLAY_H
#include <windows.h>
#include <graphics.h>
#include <conio.h>
class Display
{
public:
	Display();
	~Display();
	void drawPauseMenu(RECT Rect);//暂停菜单 最后考虑
	void drawBoard(int ver = -1, int hor = -1,int currentTeam = 1);//绘制棋盘 正在修改逻辑
	void drawBlankCell(int i, int j);//空格子 以方便对某个格子的状态进行修改
	void drawFillCell(int i, int j, COLORREF x);//比空格子略小的一个实心方块 使用颜色名称 例：RED
	void drawFillCell(int i, int j, int R,int G,int B);//比空格子略小的一个实心方块 使用RGB值
	void drawFillCircle(int i, int j, COLORREF x);//用来表示棋子的一个涂色圆形 使用颜色名称
	void drawFillCircle(int i, int j, int R, int G, int B);//用来表示棋子的一个涂色圆形 使用RGB值
	int* pixelToCell(int ver, int hor);//传入点击位置横纵的像素值，返回代表点击位置横纵坐标的数组(注意：必须点在棋盘内)
};

#endif //SUPERCHAT_DISPLAY_H