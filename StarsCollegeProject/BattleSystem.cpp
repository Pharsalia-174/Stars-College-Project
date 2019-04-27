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
int **BattleSystem::getChessOfTeam(int Team) {
    if(Team == 1){ return chessOfTeam1; }
    if(Team == 2){ return chessOfTeam2; }
}

BattleSystem::BattleSystem():TurnCounter(){
    rounds = 0; destroyedMobs = 0; totalTurns = 0; tempTurns = 0;
    chessBoard = new Mob**[10]; tempBoard = new Mob**[10]; visibleBoard = new int*[10];
    chessOfTeam1 = new int*[36]; chessOfTeam2 = new int*[36];
    for(int i = 0;i<36;i++){
        chessOfTeam1[i] = new int[2]; chessOfTeam1[i][0] = 0; chessOfTeam1[i][1] = 0;
        chessOfTeam2[i] = new int[2]; chessOfTeam2[i][0] = 0; chessOfTeam2[i][1] = 0;
    }
    for(int i = 0;i<10;i++){
        chessBoard[i] = new Mob*[10]; tempBoard[i] = new Mob*[10];
        visibleBoard[i] = new int[10];
    }
    for(int i = 0;i < 10;i++){
        for(int j = 0;j<10;j++){
            chessBoard[i][j] = nullptr; tempBoard[i][j] = nullptr;
            visibleBoard[i][j] = 0;
        }
    }
}
BattleSystem::~BattleSystem(){
    TurnCounter.clear();//真的有必要吗(
    for(int i = 0;i<36;i++){ delete [] chessOfTeam1[i]; delete [] chessOfTeam2[i]; }
    for(int x = 0;x<10;x++){ for(int y = 0;y<10;y++){ delete chessBoard[x][y]; } }
    for(int i = 0;i<10;i++){ delete [] chessBoard[i]; delete [] tempBoard[i]; delete [] visibleBoard[i]; }
    delete [] chessOfTeam1; delete [] chessOfTeam2;
    delete [] chessBoard; delete [] tempBoard; delete [] visibleBoard;
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
        TurnCounter.push_front(t);//尾部插入列表
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
Mob* BattleSystem::instantiateMob(int ID, int team) {
    Mob* temp;
    //暂时不启用边缘检测
    /*if(team == 1){ if(chessOfTeam1[ID][1]>=chessOfTeam1[ID][0]) return nullptr; }
    if(team == 2){ if(chessOfTeam2[ID][1]>=chessOfTeam2[ID][0]) return nullptr; }*/
    switch(ID){
        case 1:
            temp = new R_001(); break;
        case 2:
            temp = new R_002(); break;
        case 3:
            temp = new R_003(); break;
		case 4:
			temp = new R_004(); break;
		case 5:
			temp = new R_005(); break;
		case 6:
			temp = new R_006(); break;
		case 7:
			temp = new R_007(); break;
		case 8:
			temp = new R_008(); break;
		case 9:
			temp = new R_009(); break;
		case 10:
			temp = new R_010(); break;
		case 11:
			temp = new R_011(); break;
		case 12:
			temp = new R_012(); break;
		case 13:
			temp = new R_013(); break;
		case 14:
			temp = new R_014(); break;
		case 15:
			temp = new R_015(); break;
		case 16:
			temp = new R_016(); break;
		case 17:
			temp = new R_017(); break;
		case 18:
			temp = new R_018(); break;
		case 19:
			temp = new R_019(); break;
		case 20:
			temp = new R_020(); break;
		case 21:
			temp = new SR_021(); break;
		case 22:
			temp = new SR_022(); break;
		case 23:
			temp = new SR_023(); break;
		case 24:
			temp = new SR_024(); break;
		case 25:
			temp = new SR_025(); break;
		case 26:
			temp = new SR_026(); break;
		case 27:
			temp = new SR_027(); break;
		case 28:
			temp = new SR_028(); break;
		case 29:
			temp = new SR_029(); break;
		case 30:
			temp = new SR_030(); break;
		case 31:
			temp = new UR_031(); break;
		case 32:
			temp = new UR_032(); break;
		case 33:
			temp = new UR_033(); break;
		case 34:
			temp = new UR_034(); break;
		case 35:
			temp = new UR_034(); break;
		default: return nullptr;
    }
    if(team<=1){ temp->setTeam(1); }
    if(team>=2){ temp->setTeam(2); }
    return temp;
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
        std::cout<<(*iterTC).getPointer()<<":"<<(*iterTC).getPointer()->getName()<<","<<(*iterTC).getFlag()<<std::endl;
        iterTC++;
    }
}
void BattleSystem::cmdCoutChessOfTeam(int Team) {
    if(Team == 0){
        std::cout<<"Team1:"<<std::endl;
        for(int i = 0;i<36;i++){
            if(chessOfTeam1[i][0] > 0 || chessOfTeam1[i][1] > 0){
                std::cout<<"ID:"<<i<<" "<<"TotalNums:"<<chessOfTeam1[i][0]<<" "<<"RemainingNums:"<<chessOfTeam1[i][0]-chessOfTeam1[i][1]<<std::endl;
            }
        }
        std::cout<<getRemainingVacancy(1)<<std::endl; std::cout<<getRemainingChess(1)<<std::endl;
        std::cout<<"Team2:"<<std::endl;
        for(int i = 0;i<36;i++){
            if(chessOfTeam2[i][0] > 0 || chessOfTeam2[i][1] > 0){
                std::cout<<"ID:"<<i<<" "<<"TotalNums:"<<chessOfTeam2[i][0]<<" "<<"RemainingNums:"<<chessOfTeam2[i][0]-chessOfTeam2[i][1]<<std::endl;
            }
        }
        std::cout<<getRemainingVacancy(2)<<std::endl; std::cout<<getRemainingChess(2)<<std::endl;
    }
    if(Team == 1){
        std::cout<<"Team1:"<<std::endl;
        for(int i = 0;i<36;i++){
            if(chessOfTeam1[i][0] > 0 || chessOfTeam1[i][1] > 0){
                std::cout<<"ID:"<<i<<" "<<"TotalNums:"<<chessOfTeam1[i][0]<<" "<<"RemainingNums:"<<chessOfTeam1[i][0]-chessOfTeam1[i][1]<<std::endl;
            }
        }
        std::cout<<getRemainingVacancy(1)<<std::endl; std::cout<<getRemainingChess(1)<<std::endl;
    }
    if(Team == 2){
        std::cout<<"Team2:"<<std::endl;
        for(int i = 0;i<36;i++){
            if(chessOfTeam2[i][0] > 0 || chessOfTeam2[i][1] > 0){
                std::cout<<"ID:"<<i<<" "<<"TotalNums:"<<chessOfTeam2[i][0]<<" "<<"RemainingNums:"<<chessOfTeam2[i][0]-chessOfTeam2[i][1]<<std::endl;
            }
        }
        std::cout<<getRemainingVacancy(2)<<std::endl; std::cout<<getRemainingChess(2)<<std::endl;
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
                    destroyedMobs++;
                    /*delete tmp;*/
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
Mob *BattleSystem::getNextTurnCounterPointer() {
    auto tmp = iterTC;
    if(tmp == TurnCounter.end()) return nullptr;
    else if(++tmp == TurnCounter.end()){ return nullptr; }
    else{ return (*tmp).getPointer(); }
}
Mob * BattleSystem::getHeadTurnCounterPointer()
{
	return (*TurnCounter.begin()).getPointer();
}
//重修中...不保证不会出现bug
int BattleSystem::refreshTurnCounterAfterSetChess(bool setTC) {
    if(setTC){
        iterTC = TurnCounter.begin();
        return 0;
    }else{
        TurnCounter.sort(); TurnCounter.reverse();
        return 0;
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

void BattleSystem::battleStart() {
    iterTC = TurnCounter.begin();
    refreshTurnCounter();
    refreshBoard();
}

int BattleSystem::easyConsole(int operateCode0, int operateCode1, int operateCode2, bool operateChessArea[10][10]) {
    int returnTemp = 0;
	if (TurnCounter.empty() && operateCode0 == 3) {  //第一个棋子 特化处理
		Mob* tmp = instantiateMob(operateCode1, operateCode2); //实例化对象
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				if (operateChessArea[x][y]) {
				    setChess(x, y, tmp);
                    if(operateCode2 <= 1){ chessOfTeam1[operateCode1][1]++; }
                    if(operateCode2 >= 2){ chessOfTeam2[operateCode1][1]++; }
				    iterTCpp(); return 0;
				}
			}
		}
		setChess(0, 0, tmp);
        if(operateCode2 <= 1){ chessOfTeam1[operateCode1][1]++; }
        if(operateCode2 >= 2){ chessOfTeam2[operateCode1][1]++; }
		iterTCpp(); return 0;
	}else if(iterTC == TurnCounter.end() && operateCode0 != 3) return -99; //若迭代器丢失指向 返回-99 
 
    if((*iterTC).getFlag() == 1 ){
        iterTC++; refreshIterFromEnd();
        while((*iterTC).getPointer()->getHP()<=0 || (*iterTC).getFlag() == 1){ iterTC++; refreshIterFromEnd(); }
        return -2;
    } //若当前行动的目标已行动过 返回-2 迭代器后移
    switch (operateCode0){
        default: return -1; //若未找到指定operateCode 返回1
        case 0:
            if(operateCode1 < 0 || operateCode1 >9 || operateCode1 == 5) return -1;//未知操作符 返回-1
            //常规移动函数调用
            else if(operateCode1>=1 && operateCode1<=9){
                //常规移动
                returnTemp = (*iterTC).getPointer()->moveMob(operateCode1);
                //未移动 未战斗 返回1 爱咋咋 您继续
                if(returnTemp == 1){ return 1; }
                iterTCpp(); //迭代器相关处理
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
                            iterTCpp(); //迭代器相关处理
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
                iterTCpp(); //迭代器相关处理
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
                                iterTCpp(); //迭代器相关处理
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
                    iterTCpp(); //迭代器相关处理
                    return returnTemp;
                }
            }
        case 2:
            //空过 请
            iterTCpp(); //迭代器相关处理
            return 0;
        case 3:
            Mob* tmp = instantiateMob(operateCode1,operateCode2); //实例化对象
            Mob* currentPoint = (*iterTC).getPointer(); //缓存当前指向 以免加入棋子后的指向丢失
            if(tmp == nullptr){ return -1; }
            returnTemp = -2;
            //检索
            for(int x = 0;x<10;x++) {
                for (int y = 0; y < 10; y++) {
                    if (operateChessArea[x][y]) {
                        returnTemp = setChess(x, y, tmp);
                        if (returnTemp == 0) {
                            iterTC = TurnCounter.begin();
                            while((*iterTC).getPointer() != currentPoint){
                                iterTC++;
                                if((*iterTC).getPointer() == nullptr) return -99;
                            }
                            if(operateCode2 <= 1){ chessOfTeam1[operateCode1][1]++; }
                            if(operateCode2 >= 2){ chessOfTeam2[operateCode1][1]++; }
                            iterTCpp();
                        }
                        return returnTemp;
                    }
                }
            }
    }
}
void BattleSystem::iterTCpp() {
    (*iterTC).setFlag(1);
    totalTurns++;
    tempTurns++;
    iterTC++; refreshIterFromEnd();
    while( (*iterTC).getPointer()->getHP()<=0 || (*iterTC).getFlag() == 1 ){
        iterTC++; refreshIterFromEnd();
    }
    refreshBoard();
}


int BattleSystem::getRemainingVacancy(int Team) {
    int sum = 15;
    if(Team == 1){
        for(int t = 0;t<36;t++){ sum -= chessOfTeam1[t][0]; }
    }else if(Team == 2){
        for(int t = 0;t<36;t++){ sum -= chessOfTeam2[t][0]; }
    }else{ return -1; }
    return sum;
}
int BattleSystem::getRemainingChess(int Team) {
    int sum = 0;
    if(Team == 1){
        for(int t = 0;t<36;t++){ sum += (chessOfTeam1[t][0] - chessOfTeam1[t][1]); }
    }else if(Team == 2){
        for(int t = 0;t<36;t++){ sum += (chessOfTeam2[t][0] - chessOfTeam2[t][1]); }
    }else{ return -1; }
    return sum;
}
int BattleSystem::removeChess(int ID, int Team) {
    if(Team == 1){
        if(chessOfTeam1[ID][0] == 0) return -1;
        chessOfTeam1[ID][0]--;
    }else if(Team == 2){
        if(chessOfTeam2[ID][0] == 0) return -1;
        chessOfTeam2[ID][0]--;
    }else{ return -2; }
    return getRemainingVacancy(Team);
}
int BattleSystem::chooseChess(int ID, int Team) {
    if(getRemainingVacancy(Team) == 0) return -1;
    if(Team == 1){
        if(chessOfTeam1[ID][0] == 3) return -1;
        chessOfTeam1[ID][0]++;
    }else if(Team == 2){
        if(chessOfTeam2[ID][0] == 3) return -1;
        chessOfTeam2[ID][0]++;
    }else{ return -2; }
    return getRemainingVacancy(Team);
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
    return ( this->pointerThis->getDEX() < t.pointerThis->getDEX() );
}

CoolingNode::CoolingNode(Mob *target,int ID) {
    skillID = ID;
    skillFrom = target;
    coolingCounter = skillSystem.getDefaultCoolingCounter(ID);
}
CoolingNode::CoolingNode(CoolingNode &C) {
    skillID = C.skillID;
    skillFrom = C.skillFrom;
    coolingCounter = C.coolingCounter;
}
//未完成部分
int SkillSystem::getDefaultCoolingCounter(int ID) {
    return 0;
}