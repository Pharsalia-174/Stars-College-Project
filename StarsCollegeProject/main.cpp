#include "SuperChat.h"
BattleSystem battleSystem;
SkillSystem skillSystem;
Display display;
int main() {
	initgraph(1280, 960, SHOWCONSOLE);//分辨率：1280*960
	setbkcolor(WHITE);//底色：白色
	cleardevice();//背景板涂色
	srand((unsigned int)time(nullptr));
	int testTeam = 1;
	bool tempX[10][10] = { {false} };
	tempX[1][1] = true; battleSystem.easyConsole(3,3,1,tempX); tempX[1][1] = false;
	tempX[2][3] = true; battleSystem.easyConsole(3, 12, 1, tempX); tempX[2][3] = false;
	tempX[7][6] = true; battleSystem.easyConsole(3, 33, 1, tempX); tempX[7][6] = false;
	tempX[4][2] = true; battleSystem.easyConsole(3, 6, 1, tempX); tempX[4][2] = false;
	tempX[3][4] = true; battleSystem.easyConsole(3, 8, 2, tempX); tempX[3][4] = false;
	tempX[9][1] = true; battleSystem.easyConsole(3, 34, 2, tempX); tempX[9][1] = false;
	tempX[1][6] = true; battleSystem.easyConsole(3, 21, 2, tempX); tempX[1][6] = false;
	tempX[2][8] = true; battleSystem.easyConsole(3, 1, 2, tempX); tempX[2][8] = false;
	battleSystem.battleStart();
	display.drawBoard();
    return 0;
}