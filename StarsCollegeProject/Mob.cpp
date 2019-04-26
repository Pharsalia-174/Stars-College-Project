//
// Created by Pharsalia on 2019/4/19.
//
#include "SuperChat.h"

Mob::Mob(int ID ,const char *NM, int maxHP, int defaultATK, int defaultDEX) : DEF(0),Team(0) {
    if (NM == nullptr) {
        this->NM = nullptr;
    } else {
        this->NM = new char[strlen(NM) + 1];
        strcpy(this->NM, NM);
    }
    this->ID = ID;
    this->HP = maxHP; this->maxHp = maxHP;
    this->ATK = defaultATK; this->defaultATK = defaultATK;
    this->DEX = defaultDEX; this->defaultDEX = defaultDEX;
    position = new Point(0,0);
    pointerThis = this;
    tmpOperate = 0;
}
Mob::Mob(const Mob &m) {
    if (m.NM == nullptr) {
        this->NM = nullptr;
    } else {
        this->NM = new char[strlen(m.NM) + 1];
        strcpy(this->NM, m.NM);
    }
    this->ID = m.ID;
    this->HP = m.HP; this->maxHp = m.maxHp;
    this->ATK = m.ATK; this->defaultATK = m.defaultATK;
    this->DEX = m.DEX; this->defaultDEX = m.defaultDEX;
    this->DEF = m.DEF; this->Team = m.Team;
    this->pointerThis = this;
    this->tmpOperate = m.tmpOperate;
    this->position = new Point(*m.position);
}
Mob::~Mob() {
    delete[] NM;
    pointerThis = nullptr;
}

void Mob::addDEF(int num){ DEF += num; }

void Mob::setTempOperate(int t) { this->tmpOperate = t; }

int Mob::setPosition(Point& p){
    int tmp = position->setXY(p.getX(),p.getY());
    battleSystem.refreshBoard();
    return tmp;
}
int Mob::setPosition(int x,int y) {
    int tmp = position->setXY(x,y);
    battleSystem.refreshBoard();
    return tmp;
}

void Mob::setTeam(int Team){ this->Team = Team; }

const char *Mob::getName() { return NM; }
int Mob::getID() { return ID; }
int Mob::getHP() { return HP; }
int Mob::getMaxHP() { return maxHp; }
int Mob::getATK() { return ATK; }
int Mob::getDefaultATK() { return defaultATK; }
int Mob::getDEX() { return DEX; }
int Mob::getDefaultDEX() { return defaultDEX; }
int Mob::getDEF() { return DEF; }
int Mob::getTeam(){ return Team;}
Point& Mob::getPosition() { return *position; }
Mob* Mob::getPointerThis() { return pointerThis; }
int Mob::getTempOperate() { return tmpOperate; }

int Mob::reduceHP(int num,Mob* from){
    HP -= num;
    if(HP > 0) return 0;
    else return 1;
}//0：受到伤害后仍存活 1：受到伤害后被破坏
int Mob::reduceDEF(int num, Mob *from) {
    DEF -= num;
    if(DEF>0) return 0;
    else return 1;
}//0:移除指定数值后仍有盾量 1:移除指定数值后盾量小于或等于0
int Mob::balanceHD(){
    if(HP > 0 && DEF >= 0) return 0;//无需整合 棋子存活
    else{
        if(DEF < 0 && HP > 0){
            HP -= (-DEF); DEF = 0;
            return HP>0 ? 0 : 1;//整合后存活返回0 被破坏返回1
        }else if(DEF >= 0 && HP <= 0){ HP = 0; return 2; }//带盾死返回2
        else if(DEF < 0 && HP <= 0){ HP = 0; return 3; }//穿盾迁血返回3(欠了命的那种？ 不知道会不会发生)
    }
}//整合数值 可以将直接计算的盾量血量整合为合理数据

int Mob::moveMob(int toward) { return position->moveMob(toward); }

MobR::MobR(int ID,const char* NM,int maxHP,int defaultATK,int defaultDEX):Mob(ID,NM,maxHP,defaultATK,defaultDEX) {}
MobR::MobR(MobR& r):Mob(r) {}
int MobR::getLV(){ return 1; }

MobSR::MobSR(int ID,const char* NM,int maxHP,int defaultATK,int defaultDEX):Mob(ID,NM,maxHP,defaultATK,defaultDEX){}
MobSR::MobSR(MobSR& s):Mob(s){}
int MobSR::getLV(){ return 2; }

MobUR::MobUR(int ID,const char* NM,int maxHP,int defaultATK,int defaultDEX):Mob(ID,NM,maxHP,defaultATK,defaultDEX){}
MobUR::MobUR(MobUR& u):Mob(u){}
int MobUR::getLV(){ return 3; }

MeleeMob::MeleeMob(int ID,const char* NM,int maxHP,int defaultATK,int defaultDEX):Mob(ID,NM,maxHP,defaultATK,defaultDEX){}
MeleeMob::MeleeMob(MeleeMob& M):Mob(M) {}

int MeleeMob::getType() { return 1; }
int MeleeMob::hitBack(Mob *from) {
    if(from->getType() == 1){
        //检测是否为近战单位
        from->reduceDEF(this->ATK,this);
        from->balanceHD();
        return 0;//反击发动成功
    }else{
        return 1;//反击发动失败
    }
}
int MeleeMob::beHurt(int num,Mob* from){
    reduceDEF(num,from);//移除盾量
    if(balanceHD() == 0){ return hitBack(from); }//整合数据 若该棋子存活则发动反击 返回反击函数得到结果
    else return 2;//代表该棋子死亡
}

RemoteMob::RemoteMob(int ID,const char* NM,int maxHP,int defaultATK,int defaultDEX):Mob(ID,NM,maxHP,defaultATK,defaultDEX){}
RemoteMob::RemoteMob(RemoteMob& R):Mob(R) {}

int RemoteMob::getType() { return 2; }
int RemoteMob::hitBack(Mob *from) { return 1; }
int RemoteMob::beHurt(int num,Mob* from){
    reduceDEF(num,from);
    if(balanceHD() == 0){ return hitBack(from); }
    else return 2;
}

MobR::~MobR() = default;
MobSR::~MobSR() = default;
MobUR::~MobUR() = default;
MeleeMob::~MeleeMob() = default;
RemoteMob::~RemoteMob() = default;