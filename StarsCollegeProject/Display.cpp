#include "SuperChat.h"
#define X_START_LENGTH 130 //��һ�����ӵ����϶����X������
#define Y_START_LENGTH 30 //��һ�����ӵ����϶����Y������
#define DEFAULT_BLOCK_SIZE 70 //ÿ���߿���ӵĴ�С
#define COLOR_BLOCK_SHRINK_SIZE 3 //Ϳɫ������������������ֵ	
RECT fullScreenRect = { 0,0,1280,960 };//����һ����СΪ���ڴ�С�ľ���
MOUSEMSG m;		// ���������Ϣ
int mouseCurrentX, mouseCurrentY; //���»�ͼʱʹ�õĲ�����ȷ�����λ��
int previousBlockX = 200, previousBlockY = 200;
Display::Display(){}
Display::~Display(){}

void Display::drawBoard(int ver, int hor, int currentTeam)
{
	Mob ***cb = battleSystem.getChessBoard();//��ű��λ�ͼ��Ҫ������
	int **vb = battleSystem.getVisibleBoard();//������̿ɼ���Χ
	int xBlock = 0, yBlock = 0;//���δ���ĵ������������ĸ�����
	bool flag = false;
	cleardevice(); //�����ػ� ����ʹ�� ��Ϊ�漰�����ֲ˵��Ͳ˵���ʧ�Ĳ���
	//��һ�����ǰѵ㵽�����ڵ�����ת��Ϊ���� 
	int *temp = pixelToCell(ver,hor);
	xBlock = temp[0];
	yBlock = temp[1];
	int changedX = (xBlock - previousBlockX), changedY = (yBlock - previousBlockY);//��¼�ı���
	//ʶ��ı�����λ�õĲ���(��ΪĬ�������godmove��д) ������ֻ�ܲٿر��ӵ�������
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
	//����������Զ�̹����õ�
/*	if ((cb[previousBlockX][previousBlockY] != nullptr) && (cb[xBlock][yBlock] != nullptr) && (abs(xBlock - previousBlockX) > 1) && (abs(yBlock - previousBlockY) > 1)) {
		flag2 = true;
	}*/
	//���û�ж������ӵĻ������µ���һ�εĲ������Ҳ�������  ��˵��ɶ����
	if (!flag) {
		previousBlockX = xBlock;
		previousBlockY = yBlock;
	}
	//��һ�����ǳ�ʼ������
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			drawBlankCell(i, j);
		}
	}
	//��һ�����ǳ�ʼ�������ɼ�������
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			if (vb[i][j] == 0) {
				drawBlankCell(i, j);
				drawFillCell(i, j, LIGHTGRAY);
			}
		}
	}
	//���ݴ���Ķ��鲻ͬ�����̵Ŀɼ���ΧҲ��ͬ��
	switch (currentTeam) {
	case 1:
		//���
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
		//������
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 1) && ((vb[i][j] == 1) || (vb[i][j] == 3))) {
					drawBlankCell(i, j);
					//��������ʱ��һ��Ϳɫ��Բ��������
					drawFillCircle(i, j, BLUE);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 2)) && (vb[i][j] == 3)) {
					drawBlankCell(i, j);
					//��������ʱ��һ��Ϳɫ��Բ��������
					drawFillCircle(i, j, BLACK);
				}
			}
		}
		break;
	case 2:
		//���
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
		//������
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 2) && ((vb[i][j] == 2) || (vb[i][j] == 3))) {
					drawBlankCell(i, j);
					//��������ʱ��һ��Ϳɫ��Բ��������
					drawFillCircle(i, j, BLACK);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 1)) && (vb[i][j] == 3)) {
					drawBlankCell(i, j);
					//��������ʱ��һ��Ϳɫ��Բ��������
					drawFillCircle(i, j, BLUE);
				}
			}
		}
		break;
	}
	//��ʾ��ǰ���ӵĿɲٿط�Χ
	if (xBlock >= 0 && yBlock >= 0 && xBlock <= 9 && yBlock <= 9 && cb[xBlock][yBlock] != nullptr && cb[xBlock][yBlock]->getTeam() == currentTeam) {
		drawFillCell(xBlock, yBlock, YELLOW);
		drawChessMenu(xBlock, yBlock);
		//����
		if (xBlock - 1 >= 0 && yBlock - 1 >= 0) {
			if (cb[xBlock - 1][yBlock - 1] == nullptr) {
				drawFillCell(xBlock - 1, yBlock - 1, GREEN);
			}
			else if (cb[xBlock - 1][yBlock - 1] != nullptr && cb[xBlock - 1][yBlock - 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock - 1, yBlock - 1, RED);
			}
			else;
		}
		//����
		if (xBlock >= 0 && yBlock - 1 >= 0) {
			if (cb[xBlock][yBlock - 1] == nullptr) {
				drawFillCell(xBlock, yBlock - 1, GREEN);
			}
			else if (cb[xBlock][yBlock - 1] != nullptr && cb[xBlock][yBlock - 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock, yBlock - 1, RED);
			}
			else;
		}
		//����
		if (xBlock + 1 >= 0 && yBlock - 1 >= 0) {
			if (cb[xBlock + 1][yBlock - 1] == nullptr) {
				drawFillCell(xBlock + 1, yBlock - 1, GREEN);
			}
			else if (cb[xBlock + 1][yBlock - 1] != nullptr && cb[xBlock + 1][yBlock - 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock + 1, yBlock - 1, RED);
			}
			else;
		}
		//����
		if (xBlock - 1 >= 0 && yBlock >= 0) {
			if (cb[xBlock - 1][yBlock] == nullptr) {
				drawFillCell(xBlock - 1, yBlock, GREEN);
			}
			else if (cb[xBlock - 1][yBlock] != nullptr && cb[xBlock - 1][yBlock]->getTeam() != currentTeam) {
				drawFillCell(xBlock - 1, yBlock, RED);
			}
			else;
		}
		//����
		if (xBlock + 1 >= 0 && yBlock >= 0) {
			if (cb[xBlock + 1][yBlock] == nullptr) {
				drawFillCell(xBlock + 1, yBlock, GREEN);
			}
			else if (cb[xBlock + 1][yBlock] != nullptr && cb[xBlock + 1][yBlock]->getTeam() != currentTeam) {
				drawFillCell(xBlock + 1, yBlock, RED);
			}
			else;
		}
		//����
		if (xBlock - 1 >= 0 && yBlock + 1 >= 0) {
			if (cb[xBlock - 1][yBlock + 1] == nullptr) {
				drawFillCell(xBlock - 1, yBlock + 1, GREEN);
			}
			else if (cb[xBlock - 1][yBlock + 1] != nullptr && cb[xBlock - 1][yBlock + 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock - 1, yBlock + 1, RED);
			}
			else;
		}
		//����
		if (xBlock >= 0 && yBlock + 1 >= 0) {
			if (cb[xBlock][yBlock + 1] == nullptr) {
				drawFillCell(xBlock, yBlock + 1, GREEN);
			}
			else if (cb[xBlock][yBlock + 1] != nullptr && cb[xBlock][yBlock + 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock, yBlock + 1, RED);
			}
			else;
		}
		//����
		if (xBlock + 1 >= 0 && yBlock + 1 >= 0) {
			if (cb[xBlock + 1][yBlock + 1] == nullptr) {
				drawFillCell(xBlock + 1, yBlock + 1, GREEN);
			}
			else if (cb[xBlock + 1][yBlock + 1] != nullptr && cb[xBlock + 1][yBlock + 1]->getTeam() != currentTeam) {
				drawFillCell(xBlock + 1, yBlock + 1, RED);
			}
			else;
		}
	}
	//��ؼ��̺����
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
					/*std::cout << m.x << "," << m.y << std::endl;
					std::cout<<pixelToCell(m.x, m.y)[0]<<","<<pixelToCell(m.x, m.y)[1]<<std::endl;*/
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

void Display::drawChessMenu(int x, int y) {//��Ҫ�о��ַ�����ת��
	RECT controlBoard = { 910,80,1250,720 };
	rectangle(910, 80, 1250, 720);
	TCHAR p[100];
	Mob***cb = battleSystem.getChessBoard();
	_stprintf_s(p, _T("NAME:%s ATK:%d HP:%d DEF:%d TEAM:%d"), cb[x][y]->getName(),cb[x][y]->getATK(),cb[x][y]->getHP(),cb[x][y]->getDEF(),cb[x][y]->getTeam());
	settextcolor(BLACK);
	outtextxy(910,80,p);
}