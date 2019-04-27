//
// Created by Pharsalia on 2019/4/22.
//

#ifndef SUPERCHAT_SPECIFICCHESS_H
#define SUPERCHAT_SPECIFICCHESS_H

#include "Mob.h"
//具体信息请自己对照名单文档
class R_001 :public MeleeMob, public MobR {
public:
	R_001() :MeleeMob(1, "一般通过门卫", 5, 3, 5), MobR(1, "一般通过门卫", 5, 3, 5), Mob(1, "一般通过门卫", 5, 3, 5) {};
};

class R_002 :public MeleeMob, public MobR {
public:
	R_002() :MeleeMob(2, "围墙", 12, 0, 0), MobR(2,"围墙", 12, 0, 0), Mob(2, "围墙", 12, 0, 0) {};
};

class R_003 :public MeleeMob, public MobR {
public:
	R_003() :MeleeMob(3, "非自律型战斗机器人", 2, 3, 7), MobR(3, "非自律型战斗机器人", 2, 3, 7), Mob(3, "非自律型战斗机器人", 2, 3, 7) {};
};

class R_004 :public RemoteMob, public MobR {
public:
	R_004() :RemoteMob(4, "火力压制队员", 1, 2, 3), MobR(4, "火力压制队员", 1, 2, 3), Mob(4, "火力压制队员", 1, 2, 3) {};
};

class R_005 :public RemoteMob, public MobR {
public:
	R_005() :RemoteMob(5, "熔岩城初级法师", 3, 1, 3), MobR(5, "熔岩城初级法师", 3, 1, 3), Mob(5, "熔岩城初级法师", 3, 1, 3) {};
};

class R_006 :public MeleeMob, public MobR {
public:
	R_006() :MeleeMob(6, "黑灵的仆从", 1, 3, 15), MobR(6, "黑灵的仆从", 1, 3, 15), Mob(6, "黑灵的仆从", 1, 3, 15) {};
};

class R_007 :public MeleeMob, public MobR {
public:
	R_007() :MeleeMob(7, "土傀儡", 6, 4, 2), MobR(7, "土傀儡", 6, 4, 2), Mob(7, "土傀儡", 6, 4, 2) {};
};

class R_008 :public MeleeMob, public MobR {
public:
	R_008() :MeleeMob(8, "防御矩阵", 5, 0, 0), MobR(8, "防御矩阵", 5, 0, 0), Mob(8, "防御矩阵", 5, 0, 0) {};
};

class R_009 :public MeleeMob, public MobR {
public:
	R_009() :MeleeMob(9, "西塔尔的骷髅", 1, 1, 1), MobR(9, "西塔尔的骷髅", 1, 1, 1), Mob(9, "西塔尔的骷髅", 1, 1, 1) {};
};

class R_010 :public RemoteMob, public MobR {
public:
	R_010() :RemoteMob(10, "熔岩城印记", 1, 1, 1), MobR(10, "熔岩城印记", 1, 1, 1), Mob(10, "熔岩城印记", 1, 1, 1) {};
};

class R_011 :public RemoteMob, public MobR {
public:
	R_011() :RemoteMob(11, "科技组仓库看守机器人", 2, 4, 1), MobR(11, "科技组仓库看守机器人", 2, 4, 1), Mob(11, "科技组仓库看守机器人", 2, 4, 1) {};
};

class R_012 :public MeleeMob, public MobR {
public:
	R_012() :MeleeMob(12, "学院斥候", 1, 2, 6), MobR(12, "学院斥候", 1, 2, 6), Mob(12, "学院斥候", 1, 2, 6) {};
};

class R_013 :public RemoteMob, public MobR {
public:
	R_013() :RemoteMob(13, "迫击炮小队", 6, 0, 1), MobR(13, "迫击炮小队", 6, 0, 1), Mob(13, "迫击炮小队", 6, 0, 1) {};
};

class R_014 :public RemoteMob, public MobR {
public:
	R_014() :RemoteMob(14, "熔岩元素", 1, 0, 1), MobR(14, "熔岩元素", 1, 0, 1), Mob(14, "熔岩元素", 1, 0, 1) {};
};

class R_015 :public RemoteMob, public MobR {
public:
	R_015() :RemoteMob(15, "", 0 ,0 ,0 ), MobR(15, "", 0, 0, 0), Mob(15, "", 0, 0, 0){};
};

class R_016 :public RemoteMob, public MobR {
public:
	R_016() :RemoteMob(16, "", 0, 0, 0), MobR(16, "", 0, 0, 0), Mob(16, "", 0, 0, 0) {};
};

class R_017 :public RemoteMob, public MobR {
public:
	R_017() :RemoteMob(17, "", 0, 0, 0), MobR(17, "", 0, 0, 0), Mob(17, "", 0, 0, 0) {};
};

class R_018 :public RemoteMob, public MobR {
public:
	R_018() :RemoteMob(18, "", 0, 0, 0), MobR(18, "", 0, 0, 0), Mob(18, "", 0, 0, 0) {};
};

class R_019 :public RemoteMob, public MobR {
public:
	R_019() :RemoteMob(19, "", 0, 0, 0), MobR(19, "", 0, 0, 0), Mob(19, "", 0, 0, 0) {};
};

class R_020 :public RemoteMob, public MobR {
public:
	R_020() :RemoteMob(20, "", 0, 0, 0), MobR(20, "", 0, 0, 0), Mob(20, "", 0, 0, 0) {};
};

class SR_021 :public MeleeMob, public MobSR {
public:
	SR_021() :MeleeMob(21, "幻梦境蠕虫", 4, 8, 6), MobSR(21, "幻梦境蠕虫", 4, 8, 6), Mob(21, "幻梦境蠕虫", 4, 8, 6) {};
};

class SR_022 :public MeleeMob, public MobSR {
public:
	SR_022() :MeleeMob(22, "学院守护者", 4, 2, 8), MobSR(22, "学院守护者", 4, 2, 8), Mob(22, "学院守护者", 4, 2, 8) {};
};

class SR_023 :public MeleeMob, public MobSR {
public:
	SR_023() :MeleeMob(23, "墨菲斯托", 3, 3, 3), MobSR(23, "墨菲斯托", 3, 3, 3), Mob(23, "墨菲斯托", 3, 3, 3) {};
};

class SR_024 :public MeleeMob, public MobSR {
public:
	SR_024() :MeleeMob(24, "廷达洛斯猎犬", 4, 2, 6), MobSR(24, "廷达洛斯猎犬", 4, 2, 6), Mob(24, "廷达洛斯猎犬", 4, 2, 6) {};
};

class SR_025 :public MeleeMob, public MobSR {
public:
	SR_025() :MeleeMob(25, "", 0, 0, 0), MobSR(25, "", 0, 0, 0), Mob(25, "", 0, 0, 0) {};
};

class SR_026 :public MeleeMob, public MobSR {
public:
	SR_026() :MeleeMob(26, "", 0, 0, 0), MobSR(26, "", 0, 0, 0), Mob(26, "", 0, 0, 0) {};
};

class SR_027 :public MeleeMob, public MobSR {
public:
	SR_027() :MeleeMob(27, "", 0, 0, 0), MobSR(27, "", 0, 0, 0), Mob(27, "", 0, 0, 0) {};
};

class SR_028 :public MeleeMob, public MobSR {
public:
	SR_028() :MeleeMob(28, "", 0, 0, 0), MobSR(28, "", 0, 0, 0), Mob(28, "", 0, 0, 0) {};
};

class SR_029 :public MeleeMob, public MobSR {
public:
	SR_029() :MeleeMob(29, "", 0, 0, 0), MobSR(29, "", 0, 0, 0), Mob(29, "", 0, 0, 0) {};
};

class SR_030 :public MeleeMob, public MobSR {
public:
	SR_030() :MeleeMob(30, "", 0, 0, 0), MobSR(30, "", 0, 0, 0), Mob(30, "", 0, 0, 0) {};
};

class UR_031 :public MeleeMob, public MobUR {
public:
	UR_031() :MeleeMob(31, "林语.狂战士", 1, 10, 12), MobUR(31, "林语.狂战士", 1, 10, 12), Mob(31, "林语.狂战士", 1, 10, 12) {};
};

class UR_032 :public RemoteMob, public MobUR {
public:
	UR_032() :RemoteMob(32, "灵语.血魔法师", 5, 4, 4), MobUR(32, "灵语.血魔法师", 5, 4, 4), Mob(32, "灵语.血魔法师", 5, 4, 4) {};
};

class UR_033 :public MeleeMob, public MobUR {
public:
	UR_033() :MeleeMob(33, "梦(A)", 6, 6, 6), MobUR(33, "梦(A)", 6, 6, 6), Mob(33, "梦(A)", 6, 6, 6) {};
};

class UR_034 :public RemoteMob, public MobUR {
public:
	UR_034() :RemoteMob(34, "梦(B)", 6, 4, 3), MobUR(34, "梦(B)", 6, 4, 3), Mob(34, "梦(B)", 6, 4, 3) {};
};

class UR_035 :public RemoteMob, public MobUR {
public:
	UR_035() :RemoteMob(34, "法尔", 2, 0, 1), MobUR(34, "法尔", 2, 0, 1), Mob(34, "法尔", 2, 0, 1) {};
};
#endif //SUPERCHAT_SPECIFICCHESS_H