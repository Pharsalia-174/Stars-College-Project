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
	void drawPauseMenu(RECT Rect);//��ͣ�˵� �����
	void drawBoard(int ver = -1, int hor = -1,int currentTeam = 1);//�������� �����޸��߼�
	void drawBlankCell(int i, int j);//�ո��� �Է����ĳ�����ӵ�״̬�����޸�
	void drawFillCell(int i, int j, COLORREF x);//�ȿո�����С��һ��ʵ�ķ��� ʹ����ɫ���� ����RED
	void drawFillCell(int i, int j, int R,int G,int B);//�ȿո�����С��һ��ʵ�ķ��� ʹ��RGBֵ
	void drawFillCircle(int i, int j, COLORREF x);//������ʾ���ӵ�һ��ͿɫԲ�� ʹ����ɫ����
	void drawFillCircle(int i, int j, int R, int G, int B);//������ʾ���ӵ�һ��ͿɫԲ�� ʹ��RGBֵ
	int* pixelToCell(int ver, int hor);//������λ�ú��ݵ�����ֵ�����ش�����λ�ú������������(ע�⣺�������������)
};

#endif //SUPERCHAT_DISPLAY_H