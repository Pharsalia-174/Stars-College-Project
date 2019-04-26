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
    bool** helpOperateor;//�����Ĳ����� �൱��������һ���������꼴�ɱ�������

    //ȫ������ͳ��
    int rounds;//�غ��� ĳ����ȫ�ж�һ��Ϊһ�غ� Ĭ������Ϊteam1 ż��Ϊteam2
    int totalTurns;//ȫ�ּ�¼�ж����� ���Դ��ݸ�����ϵͳ ÿ����һ�β���++һ�� ȫ�ִ洢
    int tempTurns;//ÿ�غ��еĻ��� ������һ�غ�ʱ�ᱻ��0
    int destoryMobs;//��¼ȫ�ֱ��ƻ�����������

    //�ж��б�
    std::list<TurnNode> TurnCounter;//�б� ���Գ�ʼ�����̶���
    std::list<TurnNode>::iterator iterTC;//�б������

    /*����װ�Ľӿ�*/
    int refreshChessBoard();//ˢ����������
    int refreshVisibleBoard();//ˢ�¿��ӵ�����
    void setVB(int x,int y,int team);//ˢ�¿���������Ӻ���
    int refreshTurnCounterAfterSetChess(bool setTC);//�������Ӻ�Ĳ����б�����
    int refreshIterFromEnd();//�������ִ�ĩβʱ�Ĵ���
    Mob* instantiateMob(int ID,int team);//����IDʵ��������
    void iterTCpp();//easyConsole��ĵ�������������
    int setChess(int x,int y,Mob* target);//�������� ��ͨ�������ʽ���õ����ӽ�������ʾ�������� ���÷�����������������
public:
    int** getVisibleBoard();
    Mob* ** getChessBoard();//��������/����ϵͳ���Խ��н���ǰ���жϵ���������
    //�õ�����ָ�򣨰���������ָ��ģ���ά�����ָ�� ֱ��ʹ��[][]���ܵõ�Mob* ֮��->���ü���

    explicit BattleSystem();
    ~BattleSystem();

    int refreshBoard();//ˢ������ (����������)
    int refreshTurnCounter(int type = 0);//ˢ�¼�����
    //type == 0 �����б��ƻ��˳��������Ƴ� ������flag����1 �������ص���ʼλ�� ������һ�غ�(CIV5)
    //type == 1 �������ƻ������˳�
    //����˵�� ������1 ֤��������Ϊ�� �������������û���� ����״̬Ӧ�ÿ��������ж�ʤ��

    //��������
    int attackMob(Mob* from,Mob* to);//����0Ϊto��� ����2 Ϊto���ƻ� ����1 ��������ʧ��(Զ��)
    int attackMob(Mob* from,int x,int y);//����ָ������ĺ���(�ṩ��Զ���Լ�����ϵͳ) ���ᴥ����������Ϊ
    //����0 �����ɹ� Ŀ�걻�ƻ� ����1 ������Ŀ��Ϊ�ջ��޷����� ����2 �����ɹ� Ŀ��δ�ƻ� ����99 ������δ֪���� ���ܷ����˼������صĴ���

    void battleStart();//�������� �ڲ��ó�ʼ���̺�Ӧ���õĺ���
    Mob* getCurrentTurnCounterPointer();
    //���ص�ǰ������������ָ�������
    Mob* getNextTurnCounterPointer();
   //������һ�������ָ�������

    /*���׿���̨��
     *  ʵ�����ݣ�
     *      1.�ж�    Code0:0 Code1:toward ,Code1==0ʱ ��ȡoperateChessArea ����GodMove
     *      2.����    Code0:1 Code1:toward ,Code1==0ʱ ��ȡoperateChessArea Ĭ��Ϊһ��10*10��ά���� �ڴ����ݴ���Ҫ����������
     *                ��ʱCode2�����ȡ������ Ĭ��Ϊ1 ����ȡ���������ڴ�T���� ����T�������� �Ҷ����Ӵ���ֻ�᷵���Ƿ������ӱ��˺�(0/1)
     *      3.�չ�    Code0:2
     *      4.����    Code0:3 Code1:ID Code2:Team operateChessArea:Position ���������д��ڶ��Tʱ Ĭ�ϰ��մ����Ҵ��ϵ��µĵ�һ���
     */
    /*ע�� ��ʹcode1Ҫ���ó�0 Ҳ����ʾ���� ��Ϊȱʡֻ���ܴ������ҵ�����ȱʡ*/
    int easyConsole(int operateCode0,int operateCode1 = 0,int operateCode2 = 0,bool operateChessArea[10][10] = nullptr);

    void cmdCoutChessBoard();//������ ������������ӵ�λ�� �����ִ����Ϊ�������
    void cmdCoutTurnCounter();//������ ����ж����б������ ��ʽΪ Mob*:flag
};

#endif //SUPERCHAT_BATTLESYSTEM_H