#include "SuperChat.h"
#define X_START_LENGTH 130 //第一个格子的左上顶点的X轴坐标
#define Y_START_LENGTH 30 //第一个格子的左上顶点的Y轴坐标
#define DEFAULT_BLOCK_SIZE 70 //每个边框格子的大小
#define COLOR_BLOCK_SHRINK_SIZE 3 //涂色格子向内收缩的像素值	
RECT fullScreenRect = { 0,0,1280,960 };//制造一个大小为窗口大小的矩形
MOUSEMSG m;		// 定义鼠标消息
int mouseCurrentX, mouseCurrentY; //重新绘图时使用的参数，确定鼠标位置
int previousBlockX = 65535, previousBlockY = 65535;
Display::Display(){}
Display::~Display(){}

void Display::drawBoard(int ver, int hor, int currentTeam)
{
	Mob ***cb = battleSystem.getChessBoard();//存放本次绘图需要的棋盘
	int **vb = battleSystem.getVisibleBoard();//存放棋盘可见范围
	int xBlock = 0, yBlock = 0;//本次传入的点击坐标所代表的格子数
	bool flag = false;
	bool flag2 = false;
	//	cleardevice(); 清屏重画 暂时不知道是否用得到
	//这一部分是把点到棋盘内的像素转化为格子
	while (ver >= X_START_LENGTH && hor >= Y_START_LENGTH && ver <= (X_START_LENGTH + 11 * DEFAULT_BLOCK_SIZE) && hor <= (Y_START_LENGTH + 11 * DEFAULT_BLOCK_SIZE)) { //将鼠标点到的像素化为鼠标点到的格子
		if (ver <= (X_START_LENGTH + DEFAULT_BLOCK_SIZE) && hor <= (Y_START_LENGTH + DEFAULT_BLOCK_SIZE)) {
			flag = true;
			break;
		}
		while (ver >= (X_START_LENGTH + DEFAULT_BLOCK_SIZE)) {
			ver -= DEFAULT_BLOCK_SIZE;
			xBlock++;
		}while (hor >= (Y_START_LENGTH + DEFAULT_BLOCK_SIZE)) {
			hor -= DEFAULT_BLOCK_SIZE;
			yBlock++;
		}
	}
	//识别改变棋子位置的操作(暂时没有考虑godmove的情况)     →  糨糊  ←  目前发现的问题：左上角附近的棋子会变得很奇怪
	if (((abs(xBlock - previousBlockX) == 0 || abs(xBlock - previousBlockX) == 1) && (abs(yBlock - previousBlockY) == 0 || abs(yBlock - previousBlockY) == 1)) && (cb[previousBlockX][previousBlockY] != nullptr)) {
		int changedX = (xBlock - previousBlockX), changedY = (yBlock - previousBlockY);//记录改变量
		flag2 = true;
		if (changedX == 0) {
			if (changedY == 0);
			else if (changedY == 1) {
				cb[previousBlockX][previousBlockY]->moveMob(2);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
			else if (changedY == -1) {
				cb[previousBlockX][previousBlockY]->moveMob(8);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
		}
		else if (changedX == 1) {
			if (changedY == 0) {
				cb[previousBlockX][previousBlockY]->moveMob(6);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
			else if (changedY == 1) {
				cb[previousBlockX][previousBlockY]->moveMob(3);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
			else if (changedY == -1) {
				cb[previousBlockX][previousBlockY]->moveMob(9);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
		}
		else if (changedX == -1) {
			if (changedY == 0) {
				cb[previousBlockX][previousBlockY]->moveMob(4);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
			else if (changedY == 1) {
				cb[previousBlockX][previousBlockY]->moveMob(1);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
			else if (changedY == -1) {
				cb[previousBlockX][previousBlockY]->moveMob(7);
				previousBlockX = xBlock;
				previousBlockY = yBlock;
				drawBoard(-1, -1, currentTeam);
			}
		}
	}
	//这里是留给远程攻击用的
/*	if ((cb[previousBlockX][previousBlockY] != nullptr) && (cb[xBlock][yBlock] != nullptr) && (abs(xBlock - previousBlockX) > 1) && (abs(yBlock - previousBlockY) > 1)) {
		flag2 = true;
	}*/
	//如果没有动过棋子的话则传入新点这一次的参数并且不动棋子  ←说的啥玩意
	if (!flag2) {
		previousBlockX = xBlock;
		previousBlockY = yBlock;
	}
	//这一部分是初始化格子
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			setrop2(R2_BLACK);
			rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
		}
	}
	//这一部分是初始化均不可见的迷雾
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (vb[i][j] == 0) {
				setrop2(R2_BLACK);
				rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
				setfillcolor(RGB(96, 96, 96));
				setrop2(R2_COPYPEN);
				solidrectangle((X_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + i * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + j * DEFAULT_BLOCK_SIZE, (X_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (i + 1) * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (j + 1) * DEFAULT_BLOCK_SIZE);
			}
		}
	}
	//根据传入的队伍不同，棋盘的可见范围也不同。
	switch (currentTeam) {
	case 1:
		//打格
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((vb[i][j] == 1 || vb[i][j] == 3)) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					setfillcolor(RGB(255, 255, 255));
					setrop2(R2_COPYPEN);
					solidrectangle((X_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + i * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + j * DEFAULT_BLOCK_SIZE, (X_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (i + 1) * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (j + 1) * DEFAULT_BLOCK_SIZE);
				}
				else if (vb[i][j] == 2) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					setfillcolor(RGB(96, 96, 96));
					setrop2(R2_COPYPEN);
					solidrectangle((X_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + i * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + j * DEFAULT_BLOCK_SIZE, (X_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (i + 1) * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (j + 1) * DEFAULT_BLOCK_SIZE);
				}
			}
		}
		//画棋子
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 1) && ((vb[i][j] == 1) || (vb[i][j] == 3))) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//接下来暂时用一个涂色的圆代表棋子
					setfillcolor(BLUE);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 2)) && (vb[i][j] == 3)) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//接下来暂时用一个涂色的圆代表棋子
					setfillcolor(BLACK);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
			}
		}
		break;
	case 2:
		//打格
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((vb[i][j] == 2 || vb[i][j] == 3)) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					setfillcolor(RGB(255, 255, 255));
					setrop2(R2_COPYPEN);
					solidrectangle((X_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + i * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + j * DEFAULT_BLOCK_SIZE, (X_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (i + 1) * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (j + 1) * DEFAULT_BLOCK_SIZE);
				}
				else if (vb[i][j] == 1) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					setfillcolor(RGB(96, 96, 96));
					setrop2(R2_COPYPEN);
					solidrectangle((X_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + i * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + j * DEFAULT_BLOCK_SIZE, (X_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (i + 1) * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (j + 1) * DEFAULT_BLOCK_SIZE);
				}
			}
		}
		//画棋子
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 2) && ((vb[i][j] == 2) || (vb[i][j] == 3))) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//接下来暂时用一个涂色的圆代表棋子
					setfillcolor(BLACK);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 1)) && (vb[i][j] == 3)) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//接下来暂时用一个涂色的圆代表棋子
					setfillcolor(BLUE);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
			}
		}
		break;
	}
	//监控键盘和鼠标
	while (true) {
		if (_kbhit()) {
			int ch = _getch();
			if (ch == 27) {
				if (currentTeam == 1) {
					currentTeam = 2;
					drawBoard(previousBlockX, previousBlockY, currentTeam);
				}
				else if (currentTeam == 2) {
					currentTeam = 1;
					drawBoard(previousBlockX, previousBlockY, currentTeam);
					//drawPauseMenu(fullScreenRect);
				}
			}
		}
			else if (MouseHit()) {
				m = GetMouseMsg();
				switch (m.uMsg)
				{
				case WM_LBUTTONDOWN:
					mouseCurrentX = m.x;
					mouseCurrentY = m.y;
					drawBoard(mouseCurrentX, mouseCurrentY, currentTeam);
					break;
				}
			}
		}
}