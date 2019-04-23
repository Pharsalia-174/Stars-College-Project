//
// Created by Pharsalia on 2019/4/19.
//

#include "SuperChat.h"
Mob* ** BattleSystem::getChessBoard(){
    return chessBoard;
}
int** BattleSystem::getVisibleBoard() {
    return visibleBoard;
}
BattleSystem::BattleSystem():TurnCounter(){
    rounds = 0;
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
    from->setTempOperate(1); to->setTempOperate(2);
    return to->beHurt(from->getATK(),from);
}
int BattleSystem::setChess(int x, int y, Mob *target) {
    if(chessBoard[x][y] == nullptr){
        //�ж��ܲ��ܷŽ�ȥ
        if( target->setPosition(x,y) != 0){ return 1; }
        //��λ�� ���� �������� ����غϼ��
        chessBoard[x][y] = target;
        TurnNode t(target);//ʵ����һ������������
        TurnCounter.push_back(t);//�����б�
        TurnCounter.sort(); TurnCounter.reverse();//����(  dex�Ӵ�С
        refreshBoard();
        return 0;
    }else{
        return 1;
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
                    flag = 1;
                }
            }
        }
    }
    return flag;
}
void BattleSystem::setVB(int x, int y,int team) {
    int teamO = (team == 1)? 2 : 1;//�õ�team�Ķ��ֵĶ������
    if(visibleBoard[x][y] == 3 || visibleBoard[x][y] == team) return;
    if(visibleBoard[x][y] == teamO){ visibleBoard[x][y] = 3; return; }
    if(visibleBoard[x][y] == 0){ visibleBoard[x][y] = team; return; }
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