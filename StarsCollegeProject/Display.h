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
	void drawPauseMenu(RECT Rect,int currentTeam);//暂停菜单 最后考虑
	void drawBoard(int ver = -1, int hor = -1,int currentTeam = 1);//绘制棋盘 正在修改逻辑
	void drawBlankCell(int i, int j);//空格子 以方便对某个格子的状态进行修改
	void drawFillCell(int i, int j, COLORREF x);//比空格子略小的一个实心方块 使用颜色名称 例：RED
	void drawFillCell(int i, int j, int R,int G,int B);//比空格子略小的一个实心方块 使用RGB值
	void drawFillCircle(int i, int j, COLORREF x);//用来表示棋子的一个涂色圆形 使用颜色名称
	void drawFillCircle(int i, int j, int R, int G, int B);//用来表示棋子的一个涂色圆形 使用RGB值
	int* pixelToCell(int ver, int hor);//传入点击位置横纵的像素值，返回代表点击位置横纵坐标的数组(注意：必须点在棋盘内)
	void drawChessMenu(int x, int y,Mob *chess);//在选中己方棋子时调用，在画面右边显示一个菜单
	void drawMoveMenu();//常显 输出内容包含当前的操作方、当前应该操作的棋子、下一个应该操作的棋子 并且下面会写出当前操作棋子的稀有度及技能
	void drawButton(int a,int b,int c,int d,const TCHAR *x = nullptr);//四个值分别为左上角xy，右下角xy，x为要在按钮上显示的文字。
	int switchCurrentTeam(int currentTeam);//换队时调用的一个小东西
};

#endif //SUPERCHAT_DISPLAY_H