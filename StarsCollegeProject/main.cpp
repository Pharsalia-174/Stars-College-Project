#include "SuperChat.h"
BattleSystem battleSystem;
SkillSystem skillSystem;
Display display;
int main() {
	initgraph(1280, 960, SHOWCONSOLE);//分辨率：1280*960
	setbkcolor(WHITE);//底色：白色
	cleardevice();//背景板涂色
    srand( ( unsigned int )time( nullptr ) );
    R_001 t1; t1.setTeam(1);
	UR_031 t2; t2.setTeam(1);
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
    //i为列 j为行 注意输出顺序
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << battleSystem.getVisibleBoard()[j][i] << " ";
		}
		std::cout << std::endl;
	}
	display.drawBoard();
    return 0;
}