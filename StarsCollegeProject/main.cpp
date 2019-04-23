#include "SuperChat.h"
BattleSystem battleSystem;
SkillSystem skillSystem;
Display display;
int main() {
	initgraph(1280, 960, SHOWCONSOLE);//�ֱ��ʣ�1280*960
	setrop2(R2_BLACK);//��ͼ��ɫ����ɫ����Ԫ��դ�����룩
	/*R2_BLACK ���Ƴ���������ɫ = ��ɫ
	R2_COPYPEN ���Ƴ���������ɫ = ��ǰ��ɫ��Ĭ�ϣ�
	R2_MASKNOTPEN ���Ƴ���������ɫ = ��Ļ��ɫ AND (NOT ��ǰ��ɫ)
	R2_MASKPEN ���Ƴ���������ɫ = ��Ļ��ɫ AND ��ǰ��ɫ
	R2_MASKPENNOT ���Ƴ���������ɫ = (NOT ��Ļ��ɫ) AND ��ǰ��ɫ
	R2_MERGENOTPEN ���Ƴ���������ɫ = ��Ļ��ɫ OR (NOT ��ǰ��ɫ)
	R2_MERGEPEN ���Ƴ���������ɫ = ��Ļ��ɫ OR ��ǰ��ɫ
	R2_MERGEPENNOT ���Ƴ���������ɫ = (NOT ��Ļ��ɫ) OR ��ǰ��ɫ
	R2_NOP ���Ƴ���������ɫ = ��Ļ��ɫ
	R2_NOT ���Ƴ���������ɫ = NOT ��Ļ��ɫ
	R2_NOTCOPYPEN ���Ƴ���������ɫ = NOT ��ǰ��ɫ
	R2_NOTMASKPEN ���Ƴ���������ɫ = NOT (��Ļ��ɫ AND ��ǰ��ɫ)
	R2_NOTMERGEPEN ���Ƴ���������ɫ = NOT (��Ļ��ɫ OR ��ǰ��ɫ)
	R2_NOTXORPEN ���Ƴ���������ɫ = NOT (��Ļ��ɫ XOR ��ǰ��ɫ)
	R2_WHITE ���Ƴ���������ɫ = ��ɫ
	R2_XORPEN ���Ƴ���������ɫ = ��Ļ��ɫ XOR ��ǰ��ɫ */
	//����
	setbkcolor(WHITE);//��ɫ����ɫ
	cleardevice();//������Ϳɫ
    srand( ( unsigned int )time( nullptr ) );
    TestChess t1; t1.setTeam(1);
    TestChess t2; t2.setTeam(1);
	TestChess t3; t3.setTeam(1);
	TestChess t4; t4.setTeam(1);
	TestChess t5; t5.setTeam(2);
	TestChess t6; t6.setTeam(2);
	TestChess t7; t7.setTeam(2);
	TestChess t8; t8.setTeam(2);
	int testTeam = 1;
	
	battleSystem.setChess(0,0, &t1); 
	battleSystem.setChess(0,1, &t2);
	battleSystem.setChess(0,2, &t3);
	battleSystem.setChess(3,3, &t4);
	battleSystem.setChess(7, 6, &t5);
	battleSystem.setChess(8, 1, &t6);
	battleSystem.setChess(4, 2, &t7);
	battleSystem.setChess(6, 6, &t8);
	std::cout << t1.getTeam() << std::endl;
	std::cout << t4.getTeam() << std::endl;
    //iΪ�� jΪ�� ע�����˳��
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << battleSystem.getVisibleBoard()[j][i] << " ";
		}
		std::cout << std::endl;
	}
	display.drawBoard();
    return 0;
}