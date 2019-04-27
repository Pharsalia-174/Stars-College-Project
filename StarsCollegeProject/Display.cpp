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
	cleardevice(); //清屏重画 必须使用 因为涉及到出现菜单和菜单消失的操作
	//这一部分是把点到棋盘内的像素转化为格子 
	int *temp = pixelToCell(ver,hor);
	xBlock = temp[0];
	yBlock = temp[1];
	int changedX = (xBlock - previousBlockX), changedY = (yBlock - previousBlockY);//记录改变量
	int screen = mouseMonitor(ver, hor);
	switch (screen) {
	case 1:
		//识别改变棋子位置的操作(此为默认情况，godmove另写) 现在你只能操控当前可操控的棋子了
		if (previousBlockX >= 0 && previousBlockY >= 0 && previousBlockX <= 9 && previousBlockY <= 9) {
			if ((((abs(changedX) == 0) || (abs(changedX) == 1)) && ((abs(changedY) == 0) || (abs(changedY) == 1))) && (cb[previousBlockX][previousBlockY] != nullptr) && (battleSystem.getCurrentTurnCounterPointer() == cb[previousBlockX][previousBlockY])) {
				flag = true;
				if (changedX == 0) {
					if (changedY == 0) {
						previousBlockX = xBlock;
						previousBlockY = yBlock;
					}
					else if (changedY == 1) {
						battleSystem.easyConsole(0, 2);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
					else if (changedY == -1) {
						battleSystem.easyConsole(0, 8);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
				}
				else if (changedX == 1) {
					if (changedY == 0) {
						battleSystem.easyConsole(0, 6);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
					else if (changedY == 1) {
						battleSystem.easyConsole(0, 3);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
					else if (changedY == -1) {
						battleSystem.easyConsole(0, 9);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
				}
				else if (changedX == -1) {
					if (changedY == 0) {
						battleSystem.easyConsole(0, 4);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
					else if (changedY == 1) {
						battleSystem.easyConsole(0, 1);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
					else if (changedY == -1) {
						battleSystem.easyConsole(0, 7);
						battleSystem.cmdCoutChessBoard();
						previousBlockX = xBlock;
						previousBlockY = yBlock;
						drawBoard(-100, -100, currentTeam);
					}
				}
			}
		}
		break;
	case 2:
		//远程攻击 逻辑即为一层一层向内部嵌套 即：首先判断该棋子是否可以远程攻击 之后显示该棋子可以远程攻击到的范围，之后捕获鼠标消息，并且判断是否点到了可以攻击的棋子
		if (cb[previousBlockX][previousBlockY] == cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()]) {
			if (cb[previousBlockX][previousBlockY]->getType() == 2) {
				for (int i = 0; i < 10; i++){
					for (int j = 0; j < 10; j++) {
						if (cb[i][j] != nullptr && vb[i][j] == 3 && cb[i][j]->getTeam() != currentTeam) {
							drawFillCell(i, j, RED);
						}
					}
				}
				while (true) {
					if (MouseHit()) {
						MOUSEMSG remoteMessage;
						remoteMessage = GetMouseMsg();
						switch (remoteMessage.uMsg) {
						case WM_LBUTTONDOWN:
							int *temp2;
							temp2 = pixelToCell(remoteMessage.x, remoteMessage.y);
							if (temp2[0] >= X_START_LENGTH && temp[1] >= Y_START_LENGTH && temp[0] <= (X_START_LENGTH + 10 * DEFAULT_BLOCK_SIZE) && temp[1] <= (Y_START_LENGTH + 10 * DEFAULT_BLOCK_SIZE)) {
								if (cb[temp2[0]][temp2[1]] != nullptr && vb[temp2[0]][temp2[1]] == 3 && cb[temp2[0]][temp2[1]]->getTeam() != currentTeam) {//此处判断逻辑与上面显示可攻击的位置类似
									bool fireArea[10][10] = { {false} };
									fireArea[temp2[0]][temp2[1]] = true;
									battleSystem.easyConsole(1, 0, 1, fireArea);
									currentTeam = battleSystem.getCurrentTurnCounterPointer()->getTeam();
									drawBoard(previousBlockX, previousBlockY, currentTeam);
								}
							}
							else {
								drawBoard(previousBlockX, previousBlockY, currentTeam);
							}
							break;
						default: 
							drawBoard(previousBlockX,previousBlockY,currentTeam);
							break;
						}
					}
				}
			}
		}
		break;
	case 3:break;
	case 4:
		if (cb[previousBlockX][previousBlockY] == cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()]) {
			battleSystem.easyConsole(2);
			drawBoard(-100, -100, currentTeam);
		}
		break;
	case 99:break;
	default: break;
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
	//显示一个格子 表现一下当前的可操作棋子所在的格子
	if((cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()] != nullptr) && (cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()]->getTeam() != currentTeam)) {
		Sleep(500);
		cleardevice();
		const TCHAR *x = "请换对手来操作，当换人后，请按任意键继续";
		drawButton(0, 0, 1280, 960,x);
		while (true) {
			if (_kbhit()) {
				int ch = _getch();
				currentTeam = switchCurrentTeam(currentTeam);
				drawBoard(previousBlockX,previousBlockY,currentTeam);
			}
		}
	}else	if ((cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()] != nullptr) && (cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()]->getTeam() == currentTeam)) {
		
		drawFillCell(battleSystem.getCurrentTurnCounterPointer()->getPosition().getX(), battleSystem.getCurrentTurnCounterPointer()->getPosition().getY(),MAGENTA);
	}
	//显示当前棋子的可操控范围
	if (xBlock >= 0 && yBlock >= 0 && xBlock <= 9 && yBlock <= 9 && cb[xBlock][yBlock] != nullptr) {
		drawChessMenu(xBlock, yBlock, cb[xBlock][yBlock]);
		drawMoveMenu();
		if (cb[xBlock][yBlock] == cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()] && cb[xBlock][yBlock]->getTeam() == currentTeam) {
			drawFillCell(xBlock, yBlock, YELLOW);
			//左上
			if (xBlock - 1 >= 0 && yBlock - 1 >= 0 && xBlock - 1 <= 9 && yBlock - 1 <= 9) {
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
			if (xBlock + 1 >= 0 && yBlock - 1 >= 0 && xBlock + 1 <= 9 && yBlock - 1 <= 9) {
				if (cb[xBlock + 1][yBlock - 1] == nullptr) {
					drawFillCell(xBlock + 1, yBlock - 1, GREEN);
				}
				else if (cb[xBlock + 1][yBlock - 1] != nullptr && cb[xBlock + 1][yBlock - 1]->getTeam() != currentTeam) {
					drawFillCell(xBlock + 1, yBlock - 1, RED);
				}
				else;
			}
			//正左
			if (xBlock - 1 >= 0 && yBlock >= 0 && xBlock - 1 <= 9 && yBlock <= 9) {
				if (cb[xBlock - 1][yBlock] == nullptr) {
					drawFillCell(xBlock - 1, yBlock, GREEN);
				}
				else if (cb[xBlock - 1][yBlock] != nullptr && cb[xBlock - 1][yBlock]->getTeam() != currentTeam) {
					drawFillCell(xBlock - 1, yBlock, RED);
				}
				else;
			}
			//正右
			if (xBlock + 1 >= 0 && yBlock >= 0 && xBlock + 1 <= 9 && yBlock <= 9) {
				if (cb[xBlock + 1][yBlock] == nullptr) {
					drawFillCell(xBlock + 1, yBlock, GREEN);
				}
				else if (cb[xBlock + 1][yBlock] != nullptr && cb[xBlock + 1][yBlock]->getTeam() != currentTeam) {
					drawFillCell(xBlock + 1, yBlock, RED);
				}
				else;
			}
			//左下
			if (xBlock - 1 >= 0 && yBlock + 1 >= 0 && xBlock - 1 <= 9 && yBlock + 1 <= 9) {
				if (cb[xBlock - 1][yBlock + 1] == nullptr) {
					drawFillCell(xBlock - 1, yBlock + 1, GREEN);
				}
				else if (cb[xBlock - 1][yBlock + 1] != nullptr && cb[xBlock - 1][yBlock + 1]->getTeam() != currentTeam) {
					drawFillCell(xBlock - 1, yBlock + 1, RED);
				}
				else;
			}
			//正下
			if (xBlock >= 0 && yBlock + 1 >= 0 && xBlock <= 9 && yBlock + 1 <= 9) {
				if (cb[xBlock][yBlock + 1] == nullptr) {
					drawFillCell(xBlock, yBlock + 1, GREEN);
				}
				else if (cb[xBlock][yBlock + 1] != nullptr && cb[xBlock][yBlock + 1]->getTeam() != currentTeam) {
					drawFillCell(xBlock, yBlock + 1, RED);
				}
				else;
			}
			//右下
			if (xBlock + 1 >= 0 && yBlock + 1 >= 0 && xBlock + 1 <= 9 && yBlock + 1 <= 9) {
				if (cb[xBlock + 1][yBlock + 1] == nullptr) {
					drawFillCell(xBlock + 1, yBlock + 1, GREEN);
				}
				else if (cb[xBlock + 1][yBlock + 1] != nullptr && cb[xBlock + 1][yBlock + 1]->getTeam() != currentTeam) {
					drawFillCell(xBlock + 1, yBlock + 1, RED);
				}
				else;
			}
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
					/*std::cout<<pixelToCell(m.x, m.y)[0]<<","<<pixelToCell(m.x, m.y)[1]<<std::endl;*/
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
void Display::drawConcedeButton()
{
	const TCHAR *x = TEXT("投降");
	drawButton(855, 765, 1250, 920,x);
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
void Display::drawChessMenu(int x, int y,Mob *chess) {
	drawButton(855, 75, 1250, 720);
	gettextstyle(&f); //得到当前字体设置
	TCHAR a[100],b[100],c[100],d[100],e[100],g[100],h[100]; //我觉得100够大了
	Mob***cb = battleSystem.getChessBoard();
	_stprintf_s(a, _T("NAME:%s"), cb[x][y]->getName());
	_stprintf_s(b, _T("  ATK:%d"),cb[x][y]->getATK());
	_stprintf_s(c, _T("  HP:%d"),cb[x][y]->getHP());            // ←输出一行加一行
	_stprintf_s(d, _T("  DEF:%d"),cb[x][y]->getDEF());
	_stprintf_s(e, _T("  TEAM:%d"),cb[x][y]->getTeam());
	switch (cb[x][y]->getType()) {
	case 1:
		_stprintf_s(g, _T("  TYPE:近战型"));
		break;
	case 2:
		_stprintf_s(g, _T("  TYPE:远程型"));
		break;
	default:
		_stprintf_s(g, _T("  比起什么类型我更好奇你是如何碰到这个选项的"));
		break;
	}
	if(cb[x][y]->getID()>0&& cb[x][y]->getID() < 21) {
		_stprintf_s(h, _T("  RARITY:R"));
	}
	else if (cb[x][y]->getID() > 20 && cb[x][y]->getID() < 31) {
		_stprintf_s(h, _T("  RARITY:SR"));
	}
	else if (cb[x][y]->getID() > 30 && cb[x][y]->getID() < 36) {
		_stprintf_s(h, _T("  RARITY:UR"));
	}
	else {
		_stprintf_s(h, _T("  比起稀有度我很好奇你是如何得到这个选项的"));
	}
	
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
	outtextxy(865, 90 + 5 * ENTER_CHAR_SIZE, g);
	outtextxy(865, 90 + 6 * ENTER_CHAR_SIZE, h);
	if (chess == cb[battleSystem.getCurrentTurnCounterPointer()->getPosition().getX()][battleSystem.getCurrentTurnCounterPointer()->getPosition().getY()]) {
		const TCHAR *t1 = TEXT("攻击（远程棋子使用）");
		const TCHAR *t2 = TEXT("技能");
		const TCHAR *t3 = TEXT("放弃本次行动");
		drawButton(890, 330, 1210, 390, t1);
		drawButton(890, 410, 1210, 470, t2);
		drawButton(890, 490, 1210, 550, t3);
	}
	else;
}
void Display::drawMoveMenu() {
	drawButton(120, 765, 830, 920);
	RECT moveMenuRect{ 120,765,830,920 };
    const TCHAR *currentName, *nextName;
	currentName = battleSystem.getCurrentTurnCounterPointer()->getName();
	if (battleSystem.getNextTurnCounterPointer()!= nullptr) {
		nextName = battleSystem.getNextTurnCounterPointer()->getName();
	}
	else {
		nextName = battleSystem.getHeadTurnCounterPointer()->getName();
	}
	char* tempK = const_cast<char*>("当前操作棋子：");
	char head[200];
	strcpy(head, tempK);
    char* second = const_cast<char*>(currentName);
	char* third = const_cast<char*>("     ");
	char* fourth = const_cast<char*>("下一个操作的棋子：");
	char* fifth;
	if (battleSystem.getNextTurnCounterPointer() != nullptr) {
		if (battleSystem.getNextTurnCounterPointer()->getTeam() == battleSystem.getCurrentTurnCounterPointer()->getTeam()) {
			fifth = const_cast<char*>(nextName);
		}
		else {
			fifth = const_cast<char*>("（敌方棋子，不可查看）");
		}
	}
	else {
		if (battleSystem.getHeadTurnCounterPointer()->getTeam() == battleSystem.getCurrentTurnCounterPointer()->getTeam()) {
			fifth = const_cast<char*>(nextName);
		}
		else {
			fifth = const_cast<char*>("（敌方棋子，不可查看）");
		}
	}
	strcat(head, second);
	strcat(head, third);
	strcat(head, fourth);
	strcat(head, fifth);
	TCHAR *totalString = new TCHAR[200];
	strcpy(totalString, head);
	gettextstyle(&f); //得到当前字体设置
	settextcolor(BLACK);
	f.lfHeight = 15;
	f.lfWidth = 0;
	f.lfQuality = PROOF_QUALITY;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	settextstyle(&f);
	drawtext(totalString, &moveMenuRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
}
void Display::drawButton(int a, int b, int c, int d,const TCHAR *x){
	RECT buttonRect = { a,b,c,d };
	setrop2(R2_BLACK); //边框:黑色
	rectangle(a, b, c, d);
	gettextstyle(&f);
	settextcolor(BLACK);
	f.lfHeight = 20;
	f.lfWidth = 0;
	f.lfQuality = PROOF_QUALITY;
	_tcscpy_s(f.lfFaceName, _T("黑体"));
	settextstyle(&f);
	drawtext(x,&buttonRect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}
int Display::mouseMonitor(int x, int y)
{
	if ((x >= X_START_LENGTH) && (y >= Y_START_LENGTH) && (x <= X_START_LENGTH + 10 * DEFAULT_BLOCK_SIZE) && (y <= Y_START_LENGTH + 10 * DEFAULT_BLOCK_SIZE)) {
		//点到了棋盘内 返回1
		return 1;
	}
	else if (x >= 890 && y >= 330 && x <= 1210 && y <= 390) {
		//点到了右菜单第一个按钮
		return 2;
	}
	else if (x >= 890 && y >= 410 && x <= 1210 && y <= 470) {
		//点到了右菜单第二个按钮
		return 3;
	}
	else if (x >= 890 && y >= 490 && x <= 1210 && y <= 550) {
		//点到了右菜单第三个按钮 
		return 4;
	}
	else if (x >= 855 && y >= 765 && x <= 1250 && y <= 920) {
		//点到了投降（
		return 99;
	}
	else if (x < 0 && y < 0) {
		//您这单纯的就是什么都没发生
		return 0;
	}
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