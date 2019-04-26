//
// Created by Pharsalia on 2019/4/19.
//

#ifndef SUPERCHAT_BATTLESYSTEM_H
#define SUPERCHAT_BATTLESYSTEM_H

#include <list>
#include <algorithm>
//监管战斗的核心类 仅会实例化出一个全局对象 并接手所有棋子的交互过程
class Mob;
class TurnNode{
protected:
    Mob* pointerThis;//指向该节点代表的棋子
    int flag;//是否行动过
public:
    explicit TurnNode(Mob* pointer);
    ~TurnNode();
    TurnNode(const TurnNode& t);
    int getFlag();
    Mob* getPointer();
    void setFlag(int f);
    bool operator <(TurnNode & t);//重载< 用以处理sort
};
class BattleSystem {
protected:
    //我也很绝望啊 dd怎么改都过不去 全用指针算了(
    Mob* ** chessBoard;//棋盘数组 每个位置会有一个指向棋子的指针 若该处nullptr 则为空
    Mob* ** tempBoard;//缓存用数组 用以刷新等状态下的缓存
    int** visibleBoard;//可见点的数组表示 1为1号队伍可见 2为二号队伍可见 0为均不可见 3为均可见（或许没有存在的必要）
    bool** helpOperateor;//辅助的操作板 相当于内置了一个输入坐标即可标记坐标的

    //全局数据统计
    int rounds;//回合数 某方完全行动一轮为一回合 默认奇数为team1 偶数为team2
    int totalTurns;//全局记录行动次数 用以传递给技能系统 每进行一次操作++一次 全局存储
    int tempTurns;//每回合中的缓存 进入下一回合时会被清0
    int destoryMobs;//记录全局被破坏的棋子数量

    //行动列表
    std::list<TurnNode> TurnCounter;//列表 用以初始化过程队列
    std::list<TurnNode>::iterator iterTC;//列表迭代器

    /*被封装的接口*/
    int refreshChessBoard();//刷新棋盘数组
    int refreshVisibleBoard();//刷新可视点数组
    void setVB(int x,int y,int team);//刷新可视数组的子函数
    int refreshTurnCounterAfterSetChess(bool setTC);//放置棋子后的操作列表重设
    int refreshIterFromEnd();//迭代器抵达末尾时的处理
    Mob* instantiateMob(int ID,int team);//根据ID实例化对象
    void iterTCpp();//easyConsole后的迭代器操作集成
    int setChess(int x,int y,Mob* target);//放置棋子 不通过这个方式放置的棋子将不会显示在棋盘上 即该方法将棋子置入监管区
public:
    int** getVisibleBoard();
    Mob* ** getChessBoard();//返回棋子/技能系统用以进行交互前牌判断的完整棋盘
    //得到的是指向（包含着棋子指针的）二维数组的指针 直接使用[][]就能得到Mob* 之后->调用即可

    explicit BattleSystem();
    ~BattleSystem();

    int refreshBoard();//刷新棋盘 (包含上两个)
    int refreshTurnCounter(int type = 0);//刷新计数器
    //type == 0 将所有被破坏退场的棋子移除 将所有flag置于1 迭代器回到起始位置 用以下一回合(CIV5)
    //type == 1 仅将被破坏棋子退场
    //额外说明 若返回1 证明计数器为空 或许代表棋盘上没棋了 这种状态应该可以用以判定胜负

    //攻击函数
    int attackMob(Mob* from,Mob* to);//返回0为to存活 返回2 为to被破坏 返回1 反击发动失败(远程)
    int attackMob(Mob* from,int x,int y);//攻击指定坐标的函数(提供给远程以及技能系统) 不会触发反击的行为
    //返回0 攻击成功 目标被破坏 返回1 攻击的目标为空或无法攻击 返回2 攻击成功 目标未破坏 返回99 返回了未知数据 可能发生了及其严重的错误

    void battleStart();//启动函数 在布置初始棋盘后应调用的函数
    Mob* getCurrentTurnCounterPointer();
    //返回当前计数器迭代器指向的棋子
    Mob* getNextTurnCounterPointer();
   //返回下一项迭代器指向的棋子

    /*简易控制台：
     *  实现内容：
     *      1.行动    Code0:0 Code1:toward ,Code1==0时 读取operateChessArea 调用GodMove
     *      2.攻击    Code0:1 Code1:toward ,Code1==0时 读取operateChessArea 默认为一个10*10二维数组 内存数据代表要攻击的坐标
     *                此时Code2代表读取的数量 默认为1 若读取数量大于内存T数量 按照T数量处理 且多棋子处理只会返回是否有棋子被伤害(0/1)
     *      3.空过    Code0:2
     *      4.步棋    Code0:3 Code1:ID Code2:Team operateChessArea:Position 当该数组中存在多个T时 默认按照从左到右从上到下的第一项步棋
     */
    /*注意 即使code1要设置成0 也请显示输入 因为缺省只接受从左往右的依次缺省*/
    int easyConsole(int operateCode0,int operateCode1 = 0,int operateCode2 = 0,bool operateChessArea[10][10] = nullptr);

    void cmdCoutChessBoard();//调试用 输出棋盘上棋子的位置 该数字代表的为其队伍编号
    void cmdCoutTurnCounter();//调试用 输出行动力列表的数据 格式为 Mob*:flag
};

#endif //SUPERCHAT_BATTLESYSTEM_H