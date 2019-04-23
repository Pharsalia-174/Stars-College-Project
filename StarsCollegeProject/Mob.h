//
// Created by Pharsalia on 2019/4/19.
//

#ifndef SUPERCHAT_MOB_H
#define SUPERCHAT_MOB_H
class Point;
//总类 程序及概念抽象类
class Mob {
protected:
    Mob* pointerThis;//记录自己地址的指针
    Point* position;//棋盘坐标
    int tmpOperate;//用以判断是否发生了可视操作的项
    char* NM; //名字
    int ID;   //编号
    int HP;   //血
    int maxHp;//血上限
    int ATK;  //攻
    int defaultATK;
    int DEX;  //速
    int defaultDEX;
    int DEF;  //盾
    int Team; //阵营 0 1 2    0：未定义状态
public:
    //构造 拷贝 析构
    explicit Mob(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    Mob(const Mob& m);
    virtual~Mob();
    //接口
    virtual int setPosition(Point& p);//重设置坐标
    virtual int setPosition(int x,int y);//重设置坐标
    virtual void setTeam(int Team);
    virtual void setTempOperate(int t);
    virtual void addDEF(int num);
    virtual const char* getName();
    virtual int getID();
    virtual int getHP();
    virtual int getMaxHP();
    virtual int getATK();
    virtual int getDefaultATK();
    virtual int getDEX();
    virtual int getDefaultDEX();
    virtual int getDEF();
    virtual int getTeam();
    virtual Point& getPosition();
    virtual Mob* getPointerThis();
    virtual int getTempOperate();
    //特殊接口
    virtual int getLV() = 0;
    virtual int getType() = 0;
    //常规API
    virtual int reduceHP(int num,Mob* from);//0：受到伤害后仍存活 1：受到伤害后被破坏 打穿盾直伤用这个
    virtual int reduceDEF(int num,Mob* from);//0:移除指定数值后仍有盾量 1:移除指定数值后盾量小于或等于0 通常伤害调用这个就行
    virtual int balanceHD();//整合数值 可以将直接计算的盾量血量整合为合理数据 造成伤害后 用以后续进行函数判定的标准
    //0:正常整合 棋子存活 1:整合后得到HP<0、DEF=0 2:初始状态HP<0、DEF>0 3:初始HP<0、DEF<0
    virtual int beHurt(int num,Mob* from) = 0;
    virtual int hitBack(Mob* from) = 0;
    virtual int moveMob(int toward);//接口 返回0通常移动 1没有移动也没有刷新 2发生战斗 刷新 不一定移动
};

//稀有总类 概念抽象类 LEVEL：1 等级系统留空
class MobR:virtual public Mob{
protected:
    int SkillList[1];
public:
    explicit MobR(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MobR(MobR& r);
    virtual ~MobR();
    int getLV() override;
};
//SR总类 概念抽象类 LEVEL：2 等级系统留空
class MobSR:virtual public Mob{
protected:
    int SkillList[2];
public:
    explicit MobSR(int ID  = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MobSR(MobSR& r);
    virtual ~MobSR();
    int getLV() override;
};
//UR总类 概念抽象类 LEVEL：3 等级系统留空
class MobUR:virtual public Mob{
protected:
    int SkillList[4];
public:
    explicit MobUR(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MobUR(MobUR& r);
    virtual ~MobUR();
    int getLV() override;
};

//近战类 偏具现类
class MeleeMob:virtual public Mob{
public:
    explicit MeleeMob(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MeleeMob(MeleeMob& M);
    virtual ~MeleeMob();
    int getType() override;
    virtual int beHurt(int num,Mob* from);//返回0为存活 反击成功 返回1为存活 反击失败 返回2 为被破坏
    virtual int hitBack(Mob* from);//反击 返回0反击发动 返回1反击发动失败
};
//远程类 偏具现类
class RemoteMob:virtual public Mob{
public:
    explicit RemoteMob(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    RemoteMob(RemoteMob& R);
    virtual ~RemoteMob();
    int getType() override;
    virtual int beHurt(int num,Mob* from);//返回0存活 返回2被破坏
    virtual int hitBack(Mob* from);//占位用函数 没有实际功能 默认返回1
};
//混合类 偏具现类
class MixMob:virtual public Mob{
    /*
     * 留空 到时候再说吧
     */
};

#endif //SUPERCHAT_MOB_H