//
// Created by Pharsalia on 2019/4/19.
//

#include "SuperChat.h"
#include "BattleSystem.h"

Mob* ** BattleSystem::getChessBoard(){
    return chessBoard;
}
int** BattleSystem::getVisibleBoard() {
    return visibleBoard;
}

BattleSystem::BattleSystem():TurnCounter(){
    rounds = 0;
    destoryedMobs = 0;
    totalTurns = 0;
    tempTurns = 0;
    chessBoard = new Mob**[10];
    tempBoard = new Mob**[10];
    visibleBoard = new int*[10];
    for(int i = 0;i<10;i++){
        chessBoard[i] = new Mob*[10];
        tempBoard[i] = new Mob*[10];
        visibleBoard[i] = new int[10];
    }
    for(int i = 0;i < 10;i++){
        for(int j = 0;j<10;j++){
            chessBoard[i][j] = nullptr;
            tempBoard[i][j] = nullptr;
            visibleBoard[i][j] = 0;
        }
    }
}
BattleSystem::~BattleSystem(){
    TurnCounter.clear();//真的有必要吗(
    for(int i = 0;i<10;i++){
        delete [] chessBoard[i];
        delete [] tempBoard[i];
        delete [] visibleBoard[i];

    }
    delete [] chessBoard;
    delete [] tempBoard;
    delete [] visibleBoard;
}

int BattleSystem::attackMob(Mob *from, Mob *to) {
    from->setTempOperate(1); to->setTempOperate(2);/*未利用代码*/
    return to->beHurt(from->getATK(),from);
}
int BattleSystem::attackMob(Mob *from, int x, int y) {
    if(x<0 || x>9 || y<0 || y>9) return 1;
    if(chessBoard[x][y] == nullptr) return 1;
    if(chessBoard[x][y]->getTeam() == from->getTeam()) return 1;
    Mob* tmp = chessBoard[x][y];
    tmp->reduceDEF(from->getATK(),from);
    switch (tmp->balanceHD()){
        case 0: return 2;
        case 1: return 0;
        default: return 0;
    }
}

int BattleSystem::setChess(int x, int y, Mob *target) {
    if(chessBoard[x][y] == nullptr){
        //判断能不能放进去
        if( target->setPosition(x,y) != 0){ return 1; }
        //有位置 放入 加入棋盘 加入回合监管
        chessBoard[x][y] = target;
        TurnNode t(target);//实例化一个计数器对象
        t.setFlag(1);//刚刚置入棋盘的都设定为不可行动的棋子
        bool setTC = TurnCounter.empty();
        TurnCounter.push_back(t);//尾部插入列表
        //刷新计数器与棋盘
        refreshTurnCounterAfterSetChess(setTC);
        refreshBoard();
        return 0;
    }else{
        return 1;
    }
}

void BattleSystem::setVB(int x, int y,int team) {
    int teamO = (team == 1)? 2 : 1;//得到team的对手的队伍代码
    if(visibleBoard[x][y] == 3 || visibleBoard[x][y] == team) return;
    if(visibleBoard[x][y] == teamO){ visibleBoard[x][y] = 3; return; }
    if(visibleBoard[x][y] == 0){ visibleBoard[x][y] = team; return; }
}

void BattleSystem::cmdCoutChessBoard() {
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            if(chessBoard[j][i] != nullptr){
                std::cout<<chessBoard[j][i]->getTeam()<<" ";
            }else{
                std::cout<<"0 ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
void BattleSystem::cmdCoutTurnCounter() {
    if(TurnCounter.empty()) return;
    auto endIT = TurnCounter.end();
    auto iterTC = TurnCounter.begin();
    while(iterTC != endIT){
        std::cout<<(*iterTC).getPointer()<<":"<<(*iterTC).getFlag()<<std::endl;
        iterTC++;
    }
}

int BattleSystem::refreshChessBoard() {
    //转置缓存所有原棋子的指针 清空棋盘
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            tempBoard[i][j] = chessBoard[i][j];
            chessBoard[i][j] = nullptr;
        }
    }
    Mob* tmp;
    int x,y; int flag = 0;
    //检索缓存区
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            tmp = tempBoard[i][j];
            //找到棋子
            if(tmp != nullptr){
                //判断是否属于被摧毁棋子
                if(tmp->getHP() > 0){
                    //获取当前坐标
                    x = tmp->getPosition().getX();
                    y = tmp->getPosition().getY();
                    //存入
                    chessBoard[x][y] = tmp;
                }else{
                    //这里进行亡语（不是
                    destoryedMobs++;
                    flag = 1;
                }
            }
        }
    }
    return flag;
}
int BattleSystem::refreshVisibleBoard() {
    //清空
    int tmp;
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            visibleBoard[i][j] = 0;
        }
    }
    //录入棋子信息
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            if(chessBoard[i][j] == nullptr) continue;
            tmp = chessBoard[i][j]->getTeam();
            setVB(i,j,tmp);
            if(i == 0 && j == 0){ setVB(i+1,j+1,tmp); setVB(i+1,j,tmp); setVB(i,j+1,tmp); }
            if(i == 0 && j == 9){ setVB(i+1,j-1,tmp); setVB(i+1,j,tmp); setVB(i,j-1,tmp); }
            if(i == 9 && j == 0){ setVB(i-1,j+1,tmp); setVB(i-1,j,tmp); setVB(i,j+1,tmp); }
            if(i == 9 && j == 9){ setVB(i-1,j-1,tmp); setVB(i-1,j,tmp); setVB(i,j-1,tmp); }
            if(i == 0 && ( j>=1 && j<=8 )){ setVB(i,j+1,tmp); setVB(i,j-1,tmp); setVB(i+1,j+1,tmp); setVB(i+1,j-1,tmp); setVB(i+1,j,tmp); }
            if(i == 9 && ( j>=1 && j<=8 )){ setVB(i,j+1,tmp); setVB(i,j-1,tmp); setVB(i-1,j+1,tmp); setVB(i-1,j-1,tmp); setVB(i-1,j,tmp); }
            if(j == 0 && ( i>=1 && i<=8 )){ setVB(i+1,j,tmp); setVB(i-1,j,tmp); setVB(i+1,j+1,tmp); setVB(i-1,j+1,tmp); setVB(i,j+1,tmp); }
            if(j == 9 && ( i>=1 && i<=8 )){ setVB(i+1,j,tmp); setVB(i-1,j,tmp); setVB(i+1,j-1,tmp); setVB(i-1,j-1,tmp); setVB(i,j-1,tmp); }
            if( (i>=1 && i<=8) && (j>=1 && j<=8)){
                setVB(i-1,j-1,tmp); setVB(i,j-1,tmp); setVB(i+1,j-1,tmp);
                setVB(i-1,j,tmp);                       setVB(i+1,j,tmp);
                setVB(i-1,j+1,tmp); setVB(i,j+1,tmp); setVB(i+1,j+1,tmp);
            }
        }
    }
    //加录位于错误棋盘的棋子 Team1场地为0-4 Team2场地为5-9
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            if(chessBoard[i][j] == nullptr) continue;
            tmp = chessBoard[i][j]->getTeam();
            if(tmp == 1 && j >= 5 && (visibleBoard[i][j] != 3) ){ visibleBoard[i][j] = 3; }
            if(tmp == 2 && j <= 4 && (visibleBoard[i][j] != 3) ){ visibleBoard[i][j] = 3; }
        }
    }
    return 0;//还没想到需要特殊返回的内容
}
int BattleSystem::refreshBoard() {
    return refreshChessBoard() + refreshVisibleBoard();
}
int BattleSystem::refreshTurnCounter(int type) {
    if(TurnCounter.empty()) return 1;
    auto endIT = TurnCounter.end();//创建一个缓存 用以判断指向相当于nullptr的迭代器
    auto iterTC = TurnCounter.begin();//刷新用迭代器指向头项
    //遍历列表
    while(iterTC != endIT){
        if( (*iterTC).getPointer()->getHP() <= 0){
            //将被破坏的棋子从容器中删除
            iterTC = TurnCounter.erase(iterTC);
            continue;
        }else{
            //默认刷新类型为0 会重置整个列表
            if(type == 0){
                //重置仍剩余的棋子的行动次数
                (*iterTC).setFlag(0);
            }
            //迭代器后移
            iterTC++;
        }
    }
}

Mob *BattleSystem::getCurrentTurnCounterPointer() {
    if(iterTC == TurnCounter.end()) return nullptr;
    else{ return (*iterTC).getPointer(); }
}
int BattleSystem::refreshTurnCounterAfterSetChess(bool setTC) {
    if(setTC){
        iterTC = TurnCounter.begin();
        return 0;
    }else{
        //当前为尾迭代器 此时迭代器已经位移至下一项
        if(++iterTC == TurnCounter.end()){
            //直接排序 倒序
            TurnCounter.sort(); TurnCounter.reverse();
            iterTC = TurnCounter.begin();
        }else{
            //缓存当前指向
            auto tmp = (*iterTC).getPointer();
            //排序 倒序-->按照DEX从大到小排序
            TurnCounter.sort(); TurnCounter.reverse();
            iterTC = TurnCounter.begin();
            while(true){
                //检索列表 找到之前的缓存项 用以下一行动回
                if((*iterTC).getPointer() == tmp){ break; }
                iterTC++;
                //如果出现了特殊情况 导致原有内容丢失 返回1
                if(iterTC == TurnCounter.end()){ return 1; }
            }
            return 0;
        }
    }
}
int BattleSystem::refreshIterFromEnd() {
    if(iterTC == TurnCounter.end()){
        refreshTurnCounter();
        rounds++;
        tempTurns = 0;
        iterTC = TurnCounter.begin();
        return 0;
    }else{ return 1; }
}


int BattleSystem::easyConsole(int operateCode0, int operateCode1, int operateCode2, bool operateChessArea[10][10]) {
    if(iterTC == TurnCounter.end()) return -99; //若迭代器丢失指向 返回-99
    if((*iterTC).getFlag() == 1){
        iterTC++;
        refreshIterFromEnd();
        return -2;
    } //若当前行动的目标已行动过 返回-2 迭代器后移
    int returnTemp = 0;
    switch (operateCode0){
        case 0:
            if(operateCode1 < 0 || operateCode1 > 9 || operateCode1 == 5) return -1;//未知操作符 返回-1
            //常规移动函数调用
            else if(operateCode1>=1 && operateCode1<=9){
                //常规移动
                returnTemp = (*iterTC).getPointer()->moveMob(operateCode1);
                //未移动 未战斗 返回1 爱咋咋 您继续
                if(returnTemp == 1){ return 1; }
                (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++; refreshIterFromEnd(); //迭代器相关处理
                return returnTemp;//返回移动结果
            }else if(operateCode1 == 0){
                //调用GodMove
                if(operateChessArea == nullptr) return -3;//你在耍我？ 又是不给操作码又是不给操作区的 NMSL？
                //检索移动坐标 默认从左往右从上往下第一个出现的T
                for(int x = 0;x<10;x++){
                    for(int y = 0;y<10;y++){
                        if(operateChessArea[x][y]){
                            //调用GodMove
                            returnTemp = (*iterTC).getPointer()->getPosition().godMove(x,y);
                            //判断移动结果
                            if(returnTemp == 1){ return 1; }
                            (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++; refreshIterFromEnd();//迭代器相关处理
                            return returnTemp;//返回移动结果
                        }
                    }
                }
            }
        case 1:
            if(operateCode1 < 0 || operateCode1 >9 || operateCode1 == 5) return -1;//未知操作符 返回-1
            //常规攻击函数调用
            else if(operateCode1>=1 && operateCode1<=9){
                Mob* fromTmp = (*iterTC).getPointer();
                Mob* toTmp = fromTmp->getPosition().getMob(operateCode1);
                //空目标 返回1
                if(toTmp == nullptr){ return 1; }
                //若攻击目标为己方 返回1
                if(fromTmp->getTeam() == toTmp->getTeam()){ return 1; }
                //根据返回的战斗结果确定对应的反馈数据
                switch (attackMob(fromTmp,toTmp)){
                    case 0: returnTemp = 2; break;
                    case 1: returnTemp = 3; break;
                    case 2: returnTemp =  0; break;
                    default: returnTemp = 99; break;
                }
                (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++;  //迭代器处理
                refreshIterFromEnd(); refreshBoard(); refreshTurnCounter(); //刷新棋盘 计数器
                return returnTemp;
            }else if(operateCode1 == 0){
                //针对远程的函数调用以及当有技能发动时的行动
                if(operateChessArea == nullptr) return -3;//同上
                if(operateCode2 == 1 || operateCode2 == 0){
                    //目标单项 或缺省值状态
                    for(int x = 0;x<10;x++){
                        for(int y = 0;y<10;y++){
                            if(operateChessArea[x][y]){
                                returnTemp = attackMob((*iterTC).getPointer(),x,y);
                                (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++;//迭代器处理
                                refreshIterFromEnd(); refreshBoard(); refreshTurnCounter();//刷新棋盘 计数器
                                return returnTemp;
                            }
                        }
                    }
                }else if(operateCode2>1){
                    returnTemp = 1;
                    Mob* fromTmp = (*iterTC).getPointer();
                    int tmp;
                    for(int x = 0;x<10 && operateCode2>0;x++){
                        for(int y = 0;y<10 && operateCode2>0;y++){
                            if(operateChessArea[x][y]){
                                operateCode2--;
                                tmp = attackMob(fromTmp,x,y);
                                if(returnTemp == 1 && (tmp == 0 || tmp == 2) ){ returnTemp = 0; }
                            }
                        }
                    }
                    (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++;//迭代器处理
                    refreshIterFromEnd(); refreshBoard(); refreshTurnCounter();//刷新棋盘 计数器
                    return returnTemp;
                }
            }
        case 2:
            //空过 请
            (*iterTC).setFlag(1);
            totalTurns++;
            tempTurns++;
            iterTC++;
            refreshIterFromEnd();
            return 0;
        case 3:

        default: return -1; //若未找到指定operateCode 返回1
    }
}

TurnNode::TurnNode(Mob *pointer) {
    pointerThis = pointer;
    flag = 0;
}
TurnNode::~TurnNode()  = default;
TurnNode::TurnNode(const TurnNode &t) {
    pointerThis = t.pointerThis;
    flag = t.flag;
}

int TurnNode::getFlag() { return flag; }
void TurnNode::setFlag(int f) {
    flag = f<=0? 0 : 1;//以01为分界的设置数据方式
}

Mob* TurnNode::getPointer() { return pointerThis; }

bool TurnNode::operator<(TurnNode &t) {
    return this->pointerThis->getDEX() < t.pointerThis->getDEX();
}