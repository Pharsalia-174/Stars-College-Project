//
// Created by Pharsalia on 2019/4/19.
//

#ifndef SUPERCHAT_BATTLESYSTEM_H
#define SUPERCHAT_BATTLESYSTEM_H

#include <list>
#include <algorithm>
//���ս���ĺ����� ����ʵ������һ��ȫ�ֶ��� �������������ӵĽ�������
class Mob;
class TurnNode{
protected:
    Mob* pointerThis;//ָ��ýڵ���������
    int flag;//�Ƿ��ж���
public:
    explicit TurnNode(Mob* pointer);
    ~TurnNode();
    TurnNode(const TurnNode& t);
    int getFlag();
    Mob* getPointer();
    void setFlag(int f);
    bool operator <(TurnNode & t);//����< ���Դ���sort
};
class BattleSystem {
protected:
    //��Ҳ�ܾ����� dd��ô�Ķ�����ȥ ȫ��ָ������(
    Mob* ** chessBoard;//�������� ÿ��λ�û���һ��ָ�����ӵ�ָ�� ���ô�nullptr ��Ϊ��
    Mob* ** tempBoard;//���������� ����ˢ�µ�״̬�µĻ���
    int** visibleBoard;//�ɼ���������ʾ 1Ϊ1�Ŷ���ɼ� 2Ϊ���Ŷ���ɼ� 0Ϊ�����ɼ� 3Ϊ���ɼ�������û�д��ڵı�Ҫ��
    int rounds;//�غ��� ĳ����ȫ�ж�һ��Ϊһ�غ� Ĭ������Ϊteam1 ż��Ϊteam2
    int totalTurns;//ȫ�ּ�¼�ж����� ���Դ��ݸ�����ϵͳ ÿ����һ�β���++һ�� ȫ�ִ洢
    int tempTurns;//ÿ�غ��еĻ��� ������һ�غ�ʱ�ᱻ��0

    std::list<TurnNode> TurnCounter;//�б� ���Գ�ʼ�����̶���
    std::list<TurnNode>::iterator iterTC;//�б������
public:
    int** getVisibleBoard();
    Mob* ** getChessBoard();//��������/����ϵͳ���Խ��н���ǰ���жϵ���������
    // �õ�����ָ�򣨰���������ָ��ģ���ά�����ָ�� ֱ��ʹ��[][]���ܵõ�Mob* ֮��->���ü���
    explicit BattleSystem();
    ~BattleSystem();
    int refreshChessBoard();//ˢ����������
    int refreshVisibleBoard();//ˢ�¿��ӵ�����  ����ѭ��ϵͳδ�깤 Ŀǰֻ֧����ʾ����λ��
    int refreshBoard();//ˢ������ (����������)
    int attackMob(Mob* from,Mob* to);//����0Ϊto��� ����2 Ϊto���ƻ�
    int setChess(int x,int y,Mob* target);//�������� ��ͨ�������ʽ���õ����ӽ�������ʾ�������� ���÷�����������������
    void setVB(int x,int y,int team);//ˢ�¿���������Ӻ���
    int refreshTurnCounter(int type = 0);//ˢ�¼�����
    //type == 0 �����б��ƻ��˳��������Ƴ� ������flag����1 �������ص���ʼλ�� ������һ�غ�(CIV5)
    //type == 1 �������ƻ������˳�
    //����˵�� ������1 ֤��������Ϊ�� �������������û���� ����״̬Ӧ�ÿ��������ж�ʤ��
    Mob* getCurrentTurnCounterPointer();
    int refreshTurnCounterAfterSetChess(bool setTC);
    int refreshIterFromEnd();
    //���ص�ǰ������������ָ�������

    /*���׿���̨��
     *  ʵ�����ݣ�
     *      1.�ж�    Code0:0 Code1:toward ,Code1==0ʱ ��ȡoperateChessArea ����GodMove
     *      2.����    Code0:1 Code1:toward ,Code1==0ʱ ��ȡoperateChessArea Ĭ��Ϊһ��10*10��ά���� �ڴ����ݴ���Ҫ����������
     *      3.�չ�    Code0:2
     *      4.����    Code0:3 Code1:ID Code2:Team operateChessArea:Position ���������д��ڶ��Tʱ Ĭ�ϰ��մ����Ҵ��ϵ��µĵ�һ���
     */
    int easyConsole(int operateCode0,int operateCode1 = 0,int operateCode2 = 0,bool** operateChessArea = nullptr);
    void cmdCoutChessBoard();//������ ������������ӵ�λ�� �����ִ����Ϊ�������
    void cmdCoutTurnCounter();//������ ����ж����б������ ��ʽΪ Mob*:flag
};

#endif //SUPERCHAT_BATTLESYSTEM_H