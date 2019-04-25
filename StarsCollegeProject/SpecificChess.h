//
// Created by Pharsalia on 2019/4/22.
//

#ifndef SUPERCHAT_SPECIFICCHESS_H
#define SUPERCHAT_SPECIFICCHESS_H

#include "Mob.h"

class TestChess :public MeleeMob,public MobR{
public:
    TestChess():MeleeMob(1,"test",10,5,10),MobR(1,"test",10,5,10),Mob(1,"test",10,5,10){};
};


#endif //SUPERCHAT_SPECIFICCHESS_H