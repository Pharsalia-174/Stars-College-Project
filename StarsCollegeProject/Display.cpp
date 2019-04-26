#include "SuperChat.h"
RECT fullScreenRect = { 0,0,1280,960 };//制造一个大小为窗口大小的矩形 
MOUSEMSG m;		// 定义鼠标消息
int mouseCurrentX, mouseCurrentY; //重新绘图时使用的参数，确定鼠标位置
int previousBlockX = 200, previousBlockY = 200;
LOGFONT f;//一个存放当前字体设置的地址
Display::Display(){}
Display::~Display(){}

void Display::drawBoard(int ver, int hor, int currentTeam)
{
	Mob ***cb = battleSystem.getChessBoard();//存放本次绘图需要的棋盘
	int **vb = battleSystem.getVisibleBoard();//存放棋盘可见范围
	int xBlock = 0, yBlock = 0;//本次传入的点击坐标所代表的格子数
	bool flag = false;
	setfillcolor(WHITE);//把。。。菜单涂掉。。。
	fillrectangle(855, 75, 1250, 720);
	//cleardevice(); //清屏重画 必须使用 因为涉及到出现菜单和菜单消失的操作
	//这一部分是把点到棋盘内的像素转化为格子 
	int *temp = pixelToCell(ver,hor);
	xBlock = temp[0];
	yBlock = temp[1];
	int changedX = (xBlock - previousBlockX), changedY = (yBlock - previousBlockY);//记录改变量
	//识别改变棋子位置的操作(此为默认情况，godmove另写) 现在你只能操控本队的棋子了
	if (previousBlockX >= 0 && previousBlockY >= 0 && previousBlockX <= 9 && previousBlockY <= 9) {
		if ((((abs(changedX) == 0) || (abs(changedX) == 1)) && ((abs(changedY) == 0) || (abs(changedY) == 1))) && (cb[previousBlockX][previousBlockY] != nullptr) && (cb[previousBlockX][previousBlockY]->getTeam() == currentTeam)) {
			flag = true;
			if (changedX == 0) {
				if (changedY == 0) {
					previousBlockX = xBlock;
					previousBlockY = yBlock;
				}
				else if (changedY == 1) {
					cb[previousBlockX][previousBlockY]->moveMob(2);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
				else if (changedY == -1) {
					cb[previousBlockX][previousBlockY]->moveMob(8);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
			}
			else if (changedX == 1) {
				if (changedY == 0) {
					cb[previousBlockX][previousBlockY]->moveMob(6);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
				else if (changedY == 1) {
					cb[previousBlockX][previousBlockY]->moveMob(3);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
				else if (changedY == -1) {
					cb[previousBlockX][previousBlockY]->moveMob(9);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
			}
			else if (changedX == -1) {
				if (changedY == 0) {
					cb[previousBlockX][previousBlockY]->moveMob(4);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
				else if (changedY == 1) {
					cb[previousBlockX][previousBlockY]->moveMob(1);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
				else if (changedY == -1) {
					cb[previousBlockX][previousBlockY]->moveMob(7);
					previousBlockX = xBlock;
					previousBlockY = yBlock;
					drawBoard(-100, -100, currentTeam);
				}
			}
		}
	}
	//这里是留给远程攻击用的
/*	if ((cb[previousBlockX][previousBlockY] != nullptr) && (cb[xBlock][yBlock] != nullptr) && (abs(xBlock - previousBlockX) > 1) && (abs(yBlock - previousBlockY) > 1)) {
		flag2 = true;
	}*/
	//如果没有动过棋子的话则传入新点这一次的参数并且不动棋子  ←说的啥玩意
	if (!flag) {
		previousBlockX = xBlock;
		previousBlockY = yBlock;
	}
	//这一部分是初始化格子
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			drawBlankCell(i, j);
		}
	}
	//这一部分是初始化均不可见的迷雾
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (vb[i][j] == 0) {
				drawBlankCell(i, j);
				drawFillCell(i, j, LIGHTGRAY);
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
					drawBlankCell(i, j);
					drawFillCell(i, j, 255, 255, 255);
				}
				else if (vb[i][j] == 2) {
					drawBlankCell(i, j);
					drawFillCell(i, j, LIGHTGRAY);
				}
			}
		}
		//画棋子
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 1) && ((vb[i][j] == 1) || (vb[i][j] == 3))) {
					drawBlankCell(i, j);
					//接下来暂时用一个涂色的圆代表棋子
					drawFillCircle(i, j, BLUE);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 2)) && (vb[i][j] == 3)) {
					drawBlankCell(i, j);
					//接下来暂时用一个涂色的圆代表棋子
					drawFillCircle(i, j, BLACK);
				}
			}
		}
		break;
	case 2:
		//打格
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((vb[i][j] == 2 || vb[i][j] == 3)) {
					drawBlankCell(i, j);
					drawFillCell(i, j, 255, 255, 255);
				}
				else if (vb[i][j] == 1) {
					drawBlankCell(i, j);
					drawFillCell(i, j, LIGHTGRAY);
				}
			}
		}
		//画棋子
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 2) && ((vb[i][j] == 2) || (vb[i][j] == 3))) {
					drawBlankCell(i, j);
					//接下来暂时用一个涂色的圆代表棋子
					drawFillCircle(i, j, BLACK);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 1)) && (vb[i][j] == 3)) {
					drawBlankCell(i, j);
					//接下来暂时用一个涂色的圆代表棋子
					drawFillCircle(i, j, BLUE);
				}
			}
		}
		break;
	}
	//显示当前棋子的可操控范围
	if (xBlock >= 0 && yBlock >= 0 && xBlock <= 9 && yBlock <= 9 && cb[xBlock][yBlock] != nullptr && cb[xBlock][yBlock]->getTeam() == currentTeam) {
		drawFillCell(xBlock, yBlock, YELLOW);
		drawChessMenu(xBlock, yBlock);
		//左上
		if (xBlock - 1 >= 0 && yBlock - 1 >= 0 &&xBlock - 1 <= 9 && yBlock - 1 <= 9) {
			if (cb[xBlock - 1][yBlock - 1] == nullptr) {
				drawFillCell(xBlock - 1, yBlock - 1, GREEN);
			}
			else if (cb[xBlock - 1][yBlock - 1] != nullptr && cb[xBlock - 1][yBlock - 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock - 1, yBlock - 1, RED);
			}
			else;
		}
		//正上
		if (xBlock >= 0 && yBlock - 1 >= 0 && xBlock <= 9 && yBlock - 1 <= 9) {
			if (cb[xBlock][yBlock - 1] == nullptr) {
				drawFillCell(xBlock, yBlock - 1, GREEN);
			}
			else if (cb[xBlock][yBlock - 1] != nullptr && cb[xBlock][yBlock - 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock, yBlock - 1, RED);
			}
			else;
		}
		//右上
		if (xBlock + 1 >= 0 && yBlock - 1 >= 0&& xBlock + 1 <= 9 && yBlock - 1 <= 9) {
			if (cb[xBlock + 1][yBlock - 1] == nullptr) {
				drawFillCell(xBlock + 1, yBlock - 1, GREEN);
			}
			else if (cb[xBlock + 1][yBlock - 1] != nullptr && cb[xBlock + 1][yBlock - 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock + 1, yBlock - 1, RED);
			}
			else;
		}
		//正左
		if (xBlock - 1 >= 0 && yBlock >= 0&& xBlock - 1 <= 9 && yBlock <= 9) {
			if (cb[xBlock - 1][yBlock] == nullptr) {
				drawFillCell(xBlock - 1, yBlock, GREEN);
			}
			else if (cb[xBlock - 1][yBlock] != nullptr && cb[xBlock - 1][yBlock]->getTeam() != currentTeam) {
				drawFillCell(xBlock - 1, yBlock, RED);
			}
			else;
		}
		//正右
		if (xBlock + 1 >= 0 && yBlock >= 0&& xBlock + 1 <= 9 && yBlock <= 9) {
			if (cb[xBlock + 1][yBlock] == nullptr) {
				drawFillCell(xBlock + 1, yBlock, GREEN);
			}
			else if (cb[xBlock + 1][yBlock] != nullptr && cb[xBlock + 1][yBlock]->getTeam() != currentTeam) {
				drawFillCell(xBlock + 1, yBlock, RED);
			}
			else;
		}
		//左下
		if (xBlock - 1 >= 0 && yBlock + 1 >= 0&& xBlock - 1 <= 9 && yBlock + 1 <= 9) {
			if (cb[xBlock - 1][yBlock + 1] == nullptr) {
				drawFillCell(xBlock - 1, yBlock + 1, GREEN);
			}
			else if (cb[xBlock - 1][yBlock + 1] != nullptr && cb[xBlock - 1][yBlock + 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock - 1, yBlock + 1, RED);
			}
			else;
		}
		//正下
		if (xBlock >= 0 && yBlock + 1 >= 0&& xBlock <= 9 && yBlock + 1 <= 9) {
			if (cb[xBlock][yBlock + 1] == nullptr) {
				drawFillCell(xBlock, yBlock + 1, GREEN);
			}
			else if (cb[xBlock][yBlock + 1] != nullptr && cb[xBlock][yBlock + 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock, yBlock + 1, RED);
			}
			else;
		}
		//右下
		if (xBlock + 1 >= 0 && yBlock + 1 >= 0&&xBlock + 1 <= 9 && yBlock + 1 <= 9) {
			if (cb[xBlock + 1][yBlock + 1] == nullptr) {
				drawFillCell(xBlock + 1, yBlock + 1, GREEN);
			}
			else if (cb[xBlock + 1][yBlock + 1] != nullptr && cb[xBlock + 1][yBlock + 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock + 1, yBlock + 1, RED);
			}
			else;
		}
	}
	//监控键盘和鼠标
	while (true) {
		if (_kbhit()) {
			int ch = _getch();
			if (ch == 67 || ch== 99) {
				currentTeam = switchCurrentTeam(currentTeam);
				drawBoard(previousBlockX, previousBlockY, currentTeam);
				}else if(ch == 27){
				drawPauseMenu(fullScreenRect,currentTeam);
			}
		}
			else if (MouseHit()) {
				m = GetMouseMsg();
				switch (m.uMsg)
				{
				case WM_LBUTTONDOWN:
					mouseCurrentX = m.x;
					mouseCurrentY = m.y;
					std::cout << m.x << "," << m.y << std::endl;
					std::cout<<pixelToCell(m.x, m.y)[0]<<","<<pixelToCell(m.x, m.y)[1]<<std::endl;
					drawBoard(mouseCurrentX, mouseCurrentY, currentTeam);
					break;
				}
			}
		}
}
void Display::drawBlankCell(int i, int j) {
	setrop2(R2_BLACK);
	rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
}
void Display::drawFillCell(int i, int j, COLORREF x) {
	setfillcolor(x);
	setrop2(R2_COPYPEN);
	solidrectangle((X_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + i * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + j * DEFAULT_BLOCK_SIZE, (X_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (i + 1) * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (j + 1) * DEFAULT_BLOCK_SIZE);
}
void Display::drawFillCell(int i,int j,int R,int G,int B) {
	setfillcolor(RGB(R,G,B));
	setrop2(R2_COPYPEN);
	solidrectangle((X_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + i * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH + COLOR_BLOCK_SHRINK_SIZE) + j * DEFAULT_BLOCK_SIZE, (X_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (i + 1) * DEFAULT_BLOCK_SIZE, (Y_START_LENGTH - COLOR_BLOCK_SHRINK_SIZE) + (j + 1) * DEFAULT_BLOCK_SIZE);
}
void Display::drawFillCircle(int i, int j, COLORREF x){
	setfillcolor(x);
	setrop2(R2_COPYPEN);
	fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
}
void Display::drawFillCircle(int i, int j, int R, int G, int B){
	setfillcolor(RGB(R,G,B));
	setrop2(R2_COPYPEN);
	fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
}
int *Display::pixelToCell(int ver, int hor) {
	int x = 0, y = 0;
	int temp[2];
	if ((ver >= X_START_LENGTH) && (hor >= Y_START_LENGTH) && (ver <= (X_START_LENGTH + 10 * (DEFAULT_BLOCK_SIZE))) && (hor <= (Y_START_LENGTH + 10 * (DEFAULT_BLOCK_SIZE)))) {
		while (ver >= X_START_LENGTH + DEFAULT_BLOCK_SIZE) {
			ver -= DEFAULT_BLOCK_SIZE;
			x++;
		}
		while (hor >= Y_START_LENGTH + DEFAULT_BLOCK_SIZE) {
			hor -= DEFAULT_BLOCK_SIZE;
			y++;
		}
		temp[0] = x;
		temp[1] = y;
		return temp;
	}
	else {
		temp[0] = 100;
		temp[1] = 100;
		return temp;
	}
	
}
void Display::drawChessMenu(int x, int y) {
	RECT controlBoard = { 855,75,1250,720 };//这个。。。似乎没什么用
	setrop2(R2_BLACK); //边框用的黑色
	rectangle(855, 75, 1250, 720); //绘制边框
	gettextstyle(&f); //得到当前字体设置
	TCHAR a[100],b[100],c[100],d[100],e[100]; //我觉得100够大了
	Mob***cb = battleSystem.getChessBoard();
	_stprintf_s(a, _T("NAME:%s"), cb[x][y]->getName());
	_stprintf_s(b, _T("  ATK:%d"),cb[x][y]->getATK());
	_stprintf_s(c, _T("  HP:%d"),cb[x][y]->getHP());            // ←输出一行加一行
	_stprintf_s(d, _T("  DEF:%d"),cb[x][y]->getDEF());
	_stprintf_s(e, _T("  TEAM:%d"),cb[x][y]->getTeam());
	settextcolor(BLACK);
	f.lfHeight = 20;
	f.lfWidth = 0;
	f.lfQuality = PROOF_QUALITY;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	settextstyle(&f);
	outtextxy(865,90,a);
	outtextxy(865, 90+ENTER_CHAR_SIZE, b);
	outtextxy(865, 90 + 2*ENTER_CHAR_SIZE, c);            //   ←同上
	outtextxy(865, 90 + 3 * ENTER_CHAR_SIZE, d);
	outtextxy(865, 90 + 4 * ENTER_CHAR_SIZE, e);
}
int Display::switchCurrentTeam(int currentTeam)
{
	if (currentTeam == 1) {
		currentTeam = 2;
	}
	else if (currentTeam == 2) {
		currentTeam = 1;
	}
	return currentTeam;
}
void Display::drawPauseMenu(RECT rect,int currentTeam) {
	gettextstyle(&f); //得到当前字体设置
	settextcolor(BLACK);
	f.lfHeight = 50;
	f.lfWidth = 0;
	f.lfQuality = PROOF_QUALITY;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	settextstyle(&f);
	cleardevice();
	drawtext(_T("\n\n\n\n\n\n\nNow Pause......\n\nPress ANY key to resume."), &rect, DT_CENTER | DT_VCENTER);
	while (true) {
		if (_kbhit()) {
			int ch = _getch();
			if (ch) {
				cleardevice();
				drawBoard(previousBlockX,previousBlockY,currentTeam);
			}
		}
		else;
	}
}