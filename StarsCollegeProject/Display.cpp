#include "SuperChat.h"
#define X_START_LENGTH 130 //��һ�����ӵ����϶����X������
#define Y_START_LENGTH 30 //��һ�����ӵ����϶����Y������
#define DEFAULT_BLOCK_SIZE 70 //ÿ���߿���ӵĴ�С
#define COLOR_BLOCK_SHRINK_SIZE 3 //Ϳɫ������������������ֵ	
RECT fullScreenRect = { 0,0,1280,960 };//����һ����СΪ���ڴ�С�ľ���
MOUSEMSG m;		// ���������Ϣ
int mouseCurrentX, mouseCurrentY; //���»�ͼʱʹ�õĲ�����ȷ�����λ��
int previousBlockX = 65535, previousBlockY = 65535;
Display::Display(){}
Display::~Display(){}

void Display::drawBoard(int ver, int hor, int currentTeam)
{
	Mob ***cb = battleSystem.getChessBoard();//��ű��λ�ͼ��Ҫ������
	int **vb = battleSystem.getVisibleBoard();//������̿ɼ���Χ
	int xBlock = 0, yBlock = 0;//���δ���ĵ������������ĸ�����
	bool flag = false;
	bool flag2 = false;
	//	cleardevice(); �����ػ� ��ʱ��֪���Ƿ��õõ�
	//��һ�����ǰѵ㵽�����ڵ�����ת��Ϊ����
	while (ver >= X_START_LENGTH && hor >= Y_START_LENGTH && ver <= (X_START_LENGTH + 11 * DEFAULT_BLOCK_SIZE) && hor <= (Y_START_LENGTH + 11 * DEFAULT_BLOCK_SIZE)) { //�����㵽�����ػ�Ϊ���㵽�ĸ���
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
	//ʶ��ı�����λ�õĲ���(��ʱû�п���godmove�����)     ��  �ݺ�  ��  Ŀǰ���ֵ����⣺���ϽǸ��������ӻ��ú����
	if (((abs(xBlock - previousBlockX) == 0 || abs(xBlock - previousBlockX) == 1) && (abs(yBlock - previousBlockY) == 0 || abs(yBlock - previousBlockY) == 1)) && (cb[previousBlockX][previousBlockY] != nullptr)) {
		int changedX = (xBlock - previousBlockX), changedY = (yBlock - previousBlockY);//��¼�ı���
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
	//����������Զ�̹����õ�
/*	if ((cb[previousBlockX][previousBlockY] != nullptr) && (cb[xBlock][yBlock] != nullptr) && (abs(xBlock - previousBlockX) > 1) && (abs(yBlock - previousBlockY) > 1)) {
		flag2 = true;
	}*/
	//���û�ж������ӵĻ������µ���һ�εĲ������Ҳ�������  ��˵��ɶ����
	if (!flag2) {
		previousBlockX = xBlock;
		previousBlockY = yBlock;
	}
	//��һ�����ǳ�ʼ������
	for (int i = 0; i <= 9; i++) {
		for (int j = 0; j <= 9; j++) {
			setrop2(R2_BLACK);
			rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
		}
	}
	//��һ�����ǳ�ʼ�������ɼ�������
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
	//���ݴ���Ķ��鲻ͬ�����̵Ŀɼ���ΧҲ��ͬ��
	switch (currentTeam) {
	case 1:
		//���
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
		//������
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 1) && ((vb[i][j] == 1) || (vb[i][j] == 3))) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//��������ʱ��һ��Ϳɫ��Բ��������
					setfillcolor(BLUE);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 2)) && (vb[i][j] == 3)) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//��������ʱ��һ��Ϳɫ��Բ��������
					setfillcolor(BLACK);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
			}
		}
		break;
	case 2:
		//���
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
		//������
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) {
				if ((cb[i][j] != nullptr) && (cb[i][j]->getTeam() == 2) && ((vb[i][j] == 2) || (vb[i][j] == 3))) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//��������ʱ��һ��Ϳɫ��Բ��������
					setfillcolor(BLACK);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
				else if (((cb[i][j] != nullptr)) && ((cb[i][j]->getTeam() == 1)) && (vb[i][j] == 3)) {
					setrop2(R2_BLACK);
					rectangle(X_START_LENGTH + i * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + j * DEFAULT_BLOCK_SIZE, X_START_LENGTH + (i + 1) * DEFAULT_BLOCK_SIZE, Y_START_LENGTH + (j + 1) * DEFAULT_BLOCK_SIZE);
					//��������ʱ��һ��Ϳɫ��Բ��������
					setfillcolor(BLUE);
					setrop2(R2_COPYPEN);
					fillcircle((X_START_LENGTH + (i  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), (Y_START_LENGTH + (j  * DEFAULT_BLOCK_SIZE) + 0.5*DEFAULT_BLOCK_SIZE), 0.5*DEFAULT_BLOCK_SIZE - COLOR_BLOCK_SHRINK_SIZE);
				}
			}
		}
		break;
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
					drawBoard(mouseCurrentX, mouseCurrentY, currentTeam);
					break;
				}
			}
		}
}