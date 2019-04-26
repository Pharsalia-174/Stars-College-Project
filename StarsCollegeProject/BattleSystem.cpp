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
    TurnCounter.clear();//����б�Ҫ��(
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
    from->setTempOperate(1); to->setTempOperate(2);/*δ���ô���*/
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
        //�ж��ܲ��ܷŽ�ȥ
        if( target->setPosition(x,y) != 0){ return 1; }
        //��λ�� ���� �������� ����غϼ��
        chessBoard[x][y] = target;
        TurnNode t(target);//ʵ����һ������������
        t.setFlag(1);//�ո��������̵Ķ��趨Ϊ�����ж�������
        bool setTC = TurnCounter.empty();
        TurnCounter.push_back(t);//β�������б�
        //ˢ�¼�����������
        refreshTurnCounterAfterSetChess(setTC);
        refreshBoard();
        return 0;
    }else{
        return 1;
    }
}

void BattleSystem::setVB(int x, int y,int team) {
    int teamO = (team == 1)? 2 : 1;//�õ�team�Ķ��ֵĶ������
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
    //ת�û�������ԭ���ӵ�ָ�� �������
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            tempBoard[i][j] = chessBoard[i][j];
            chessBoard[i][j] = nullptr;
        }
    }
    Mob* tmp;
    int x,y; int flag = 0;
    //����������
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            tmp = tempBoard[i][j];
            //�ҵ�����
            if(tmp != nullptr){
                //�ж��Ƿ����ڱ��ݻ�����
                if(tmp->getHP() > 0){
                    //��ȡ��ǰ����
                    x = tmp->getPosition().getX();
                    y = tmp->getPosition().getY();
                    //����
                    chessBoard[x][y] = tmp;
                }else{
                    //��������������
                    destoryedMobs++;
                    flag = 1;
                }
            }
        }
    }
    return flag;
}
int BattleSystem::refreshVisibleBoard() {
    //���
    int tmp;
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            visibleBoard[i][j] = 0;
        }
    }
    //¼��������Ϣ
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
    //��¼λ�ڴ������̵����� Team1����Ϊ0-4 Team2����Ϊ5-9
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            if(chessBoard[i][j] == nullptr) continue;
            tmp = chessBoard[i][j]->getTeam();
            if(tmp == 1 && j >= 5 && (visibleBoard[i][j] != 3) ){ visibleBoard[i][j] = 3; }
            if(tmp == 2 && j <= 4 && (visibleBoard[i][j] != 3) ){ visibleBoard[i][j] = 3; }
        }
    }
    return 0;//��û�뵽��Ҫ���ⷵ�ص�����
}
int BattleSystem::refreshBoard() {
    return refreshChessBoard() + refreshVisibleBoard();
}
int BattleSystem::refreshTurnCounter(int type) {
    if(TurnCounter.empty()) return 1;
    auto endIT = TurnCounter.end();//����һ������ �����ж�ָ���൱��nullptr�ĵ�����
    auto iterTC = TurnCounter.begin();//ˢ���õ�����ָ��ͷ��
    //�����б�
    while(iterTC != endIT){
        if( (*iterTC).getPointer()->getHP() <= 0){
            //�����ƻ������Ӵ�������ɾ��
            iterTC = TurnCounter.erase(iterTC);
            continue;
        }else{
            //Ĭ��ˢ������Ϊ0 �����������б�
            if(type == 0){
                //������ʣ������ӵ��ж�����
                (*iterTC).setFlag(0);
            }
            //����������
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
        //��ǰΪβ������ ��ʱ�������Ѿ�λ������һ��
        if(++iterTC == TurnCounter.end()){
            //ֱ������ ����
            TurnCounter.sort(); TurnCounter.reverse();
            iterTC = TurnCounter.begin();
        }else{
            //���浱ǰָ��
            auto tmp = (*iterTC).getPointer();
            //���� ����-->����DEX�Ӵ�С����
            TurnCounter.sort(); TurnCounter.reverse();
            iterTC = TurnCounter.begin();
            while(true){
                //�����б� �ҵ�֮ǰ�Ļ����� ������һ�ж���
                if((*iterTC).getPointer() == tmp){ break; }
                iterTC++;
                //���������������� ����ԭ�����ݶ�ʧ ����1
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
    if(iterTC == TurnCounter.end()) return -99; //����������ʧָ�� ����-99
    if((*iterTC).getFlag() == 1){
        iterTC++;
        refreshIterFromEnd();
        return -2;
    } //����ǰ�ж���Ŀ�����ж��� ����-2 ����������
    int returnTemp = 0;
    switch (operateCode0){
        case 0:
            if(operateCode1 < 0 || operateCode1 > 9 || operateCode1 == 5) return -1;//δ֪������ ����-1
            //�����ƶ���������
            else if(operateCode1>=1 && operateCode1<=9){
                //�����ƶ�
                returnTemp = (*iterTC).getPointer()->moveMob(operateCode1);
                //δ�ƶ� δս�� ����1 ��զզ ������
                if(returnTemp == 1){ return 1; }
                (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++; refreshIterFromEnd(); //��������ش���
                return returnTemp;//�����ƶ����
            }else if(operateCode1 == 0){
                //����GodMove
                if(operateChessArea == nullptr) return -3;//����ˣ�ң� ���ǲ������������ǲ����������� NMSL��
                //�����ƶ����� Ĭ�ϴ������Ҵ������µ�һ�����ֵ�T
                for(int x = 0;x<10;x++){
                    for(int y = 0;y<10;y++){
                        if(operateChessArea[x][y]){
                            //����GodMove
                            returnTemp = (*iterTC).getPointer()->getPosition().godMove(x,y);
                            //�ж��ƶ����
                            if(returnTemp == 1){ return 1; }
                            (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++; refreshIterFromEnd();//��������ش���
                            return returnTemp;//�����ƶ����
                        }
                    }
                }
            }
        case 1:
            if(operateCode1 < 0 || operateCode1 >9 || operateCode1 == 5) return -1;//δ֪������ ����-1
            //���湥����������
            else if(operateCode1>=1 && operateCode1<=9){
                Mob* fromTmp = (*iterTC).getPointer();
                Mob* toTmp = fromTmp->getPosition().getMob(operateCode1);
                //��Ŀ�� ����1
                if(toTmp == nullptr){ return 1; }
                //������Ŀ��Ϊ���� ����1
                if(fromTmp->getTeam() == toTmp->getTeam()){ return 1; }
                //���ݷ��ص�ս�����ȷ����Ӧ�ķ�������
                switch (attackMob(fromTmp,toTmp)){
                    case 0: returnTemp = 2; break;
                    case 1: returnTemp = 3; break;
                    case 2: returnTemp =  0; break;
                    default: returnTemp = 99; break;
                }
                (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++;  //����������
                refreshIterFromEnd(); refreshBoard(); refreshTurnCounter(); //ˢ������ ������
                return returnTemp;
            }else if(operateCode1 == 0){
                //���Զ�̵ĺ��������Լ����м��ܷ���ʱ���ж�
                if(operateChessArea == nullptr) return -3;//ͬ��
                if(operateCode2 == 1 || operateCode2 == 0){
                    //Ŀ�굥�� ��ȱʡֵ״̬
                    for(int x = 0;x<10;x++){
                        for(int y = 0;y<10;y++){
                            if(operateChessArea[x][y]){
                                returnTemp = attackMob((*iterTC).getPointer(),x,y);
                                (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++;//����������
                                refreshIterFromEnd(); refreshBoard(); refreshTurnCounter();//ˢ������ ������
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
                    (*iterTC).setFlag(1); totalTurns++; tempTurns++; iterTC++;//����������
                    refreshIterFromEnd(); refreshBoard(); refreshTurnCounter();//ˢ������ ������
                    return returnTemp;
                }
            }
        case 2:
            //�չ� ��
            (*iterTC).setFlag(1);
            totalTurns++;
            tempTurns++;
            iterTC++;
            refreshIterFromEnd();
            return 0;
        case 3:

        default: return -1; //��δ�ҵ�ָ��operateCode ����1
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
    flag = f<=0? 0 : 1;//��01Ϊ�ֽ���������ݷ�ʽ
}

Mob* TurnNode::getPointer() { return pointerThis; }

bool TurnNode::operator<(TurnNode &t) {
    return this->pointerThis->getDEX() < t.pointerThis->getDEX();
}