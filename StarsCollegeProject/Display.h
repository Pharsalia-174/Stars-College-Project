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
	void drawPauseMenu(RECT Rect);
	void drawBoard(int ver = -1, int hor = -1,int currentTeam = 1);
};

#endif //SUPERCHAT_DISPLAY_H