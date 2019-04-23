//
// Created by Pharsalia on 2019/4/19.
//

#ifndef SUPERCHAT_MOB_H
#define SUPERCHAT_MOB_H
class Point;
//���� ���򼰸��������
class Mob {
protected:
    Mob* pointerThis;//��¼�Լ���ַ��ָ��
    Point* position;//��������
    int tmpOperate;//�����ж��Ƿ����˿��Ӳ�������
    char* NM; //����
    int ID;   //���
    int HP;   //Ѫ
    int maxHp;//Ѫ����
    int ATK;  //��
    int defaultATK;
    int DEX;  //��
    int defaultDEX;
    int DEF;  //��
    int Team; //��Ӫ 0 1 2    0��δ����״̬
public:
    //���� ���� ����
    explicit Mob(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    Mob(const Mob& m);
    virtual~Mob();
    //�ӿ�
    virtual int setPosition(Point& p);//����������
    virtual int setPosition(int x,int y);//����������
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
    //����ӿ�
    virtual int getLV() = 0;
    virtual int getType() = 0;
    //����API
    virtual int reduceHP(int num,Mob* from);//0���ܵ��˺����Դ�� 1���ܵ��˺����ƻ� �򴩶�ֱ�������
    virtual int reduceDEF(int num,Mob* from);//0:�Ƴ�ָ����ֵ�����ж��� 1:�Ƴ�ָ����ֵ�����С�ڻ����0 ͨ���˺������������
    virtual int balanceHD();//������ֵ ���Խ�ֱ�Ӽ���Ķ���Ѫ������Ϊ�������� ����˺��� ���Ժ������к����ж��ı�׼
    //0:�������� ���Ӵ�� 1:���Ϻ�õ�HP<0��DEF=0 2:��ʼ״̬HP<0��DEF>0 3:��ʼHP<0��DEF<0
    virtual int beHurt(int num,Mob* from) = 0;
    virtual int hitBack(Mob* from) = 0;
    virtual int moveMob(int toward);//�ӿ� ����0ͨ���ƶ� 1û���ƶ�Ҳû��ˢ�� 2����ս�� ˢ�� ��һ���ƶ�
};

//ϡ������ ��������� LEVEL��1 �ȼ�ϵͳ����
class MobR:virtual public Mob{
protected:
    int SkillList[1];
public:
    explicit MobR(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MobR(MobR& r);
    virtual ~MobR();
    int getLV() override;
};
//SR���� ��������� LEVEL��2 �ȼ�ϵͳ����
class MobSR:virtual public Mob{
protected:
    int SkillList[2];
public:
    explicit MobSR(int ID  = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MobSR(MobSR& r);
    virtual ~MobSR();
    int getLV() override;
};
//UR���� ��������� LEVEL��3 �ȼ�ϵͳ����
class MobUR:virtual public Mob{
protected:
    int SkillList[4];
public:
    explicit MobUR(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MobUR(MobUR& r);
    virtual ~MobUR();
    int getLV() override;
};

//��ս�� ƫ������
class MeleeMob:virtual public Mob{
public:
    explicit MeleeMob(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    MeleeMob(MeleeMob& M);
    virtual ~MeleeMob();
    int getType() override;
    virtual int beHurt(int num,Mob* from);//����0Ϊ��� �����ɹ� ����1Ϊ��� ����ʧ�� ����2 Ϊ���ƻ�
    virtual int hitBack(Mob* from);//���� ����0�������� ����1��������ʧ��
};
//Զ���� ƫ������
class RemoteMob:virtual public Mob{
public:
    explicit RemoteMob(int ID = 0,const char* NM = nullptr,int maxHP = 0,int defaultATK = 0,int defaultDEX = 0);
    RemoteMob(RemoteMob& R);
    virtual ~RemoteMob();
    int getType() override;
    virtual int beHurt(int num,Mob* from);//����0��� ����2���ƻ�
    virtual int hitBack(Mob* from);//ռλ�ú��� û��ʵ�ʹ��� Ĭ�Ϸ���1
};
//����� ƫ������
class MixMob:virtual public Mob{
    /*
     * ���� ��ʱ����˵��
     */
};

#endif //SUPERCHAT_MOB_H