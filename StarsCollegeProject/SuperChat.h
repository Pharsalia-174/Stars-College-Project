//
// Created by Pharsalia on 2019/4/19.
//
// Super Chat to Ms.MorinagaMiu,Please.
// 莫里纳加米女士、许多苏佩尔奇特请。
//

#ifndef SUPERCHAT_SUPERCHAT_H
#define SUPERCHAT_SUPERCHAT_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include "BattleSystem.h"
#include "Point.h"
#include "Mob.h"
#include "SpecificChess.h"
#include "SkillSystem.h"
#include "Display.h"
extern BattleSystem battleSystem;
extern SkillSystem skillSystem;
extern Display display;
void Dice(int n,int range,int *from);


#endif //SUPERCHAT_SUPERCHAT_H