#include "SuperChat.h"
BattleSystem battleSystem;
SkillSystem skillSystem;
Display display;
int main() {
	initgraph(1280, 960, SHOWCONSOLE);//分辨率：1280*960
	setrop2(R2_BLACK);//绘图颜色：黑色（二元光栅操作码）
	/*R2_BLACK 绘制出的像素颜色 = 黑色
	R2_COPYPEN 绘制出的像素颜色 = 当前颜色（默认）
	R2_MASKNOTPEN 绘制出的像素颜色 = 屏幕颜色 AND (NOT 当前颜色)
	R2_MASKPEN 绘制出的像素颜色 = 屏幕颜色 AND 当前颜色
	R2_MASKPENNOT 绘制出的像素颜色 = (NOT 屏幕颜色) AND 当前颜色
	R2_MERGENOTPEN 绘制出的像素颜色 = 屏幕颜色 OR (NOT 当前颜色)
	R2_MERGEPEN 绘制出的像素颜色 = 屏幕颜色 OR 当前颜色
	R2_MERGEPENNOT 绘制出的像素颜色 = (NOT 屏幕颜色) OR 当前颜色
	R2_NOP 绘制出的像素颜色 = 屏幕颜色
	R2_NOT 绘制出的像素颜色 = NOT 屏幕颜色
	R2_NOTCOPYPEN 绘制出的像素颜色 = NOT 当前颜色
	R2_NOTMASKPEN 绘制出的像素颜色 = NOT (屏幕颜色 AND 当前颜色)
	R2_NOTMERGEPEN 绘制出的像素颜色 = NOT (屏幕颜色 OR 当前颜色)
	R2_NOTXORPEN 绘制出的像素颜色 = NOT (屏幕颜色 XOR 当前颜色)
	R2_WHITE 绘制出的像素颜色 = 白色
	R2_XORPEN 绘制出的像素颜色 = 屏幕颜色 XOR 当前颜色 */
	//备用
	setbkcolor(WHITE);//底色：白色
	cleardevice();//背景板涂色
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