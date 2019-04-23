//
// Created by Pharsalia on 2019/4/21.
//

#ifndef SUPERCHAT_POINT_H
#define SUPERCHAT_POINT_H

class Mob;
//������������ĵ��� ������һ����API ��������ƶ� ��ȡ��Χ��Ϣ��
class Point{
protected:
    int x;
    int y;
public:
    explicit Point(int x = 0,int y = 0);
    Point(Point& p);
    int getX();//����X
    int getY();//����Y
    Point& getPoint();//���ظõ������ �������ӵ����򷵻س�����
    int setX(int x);//����Y 0:�ɹ� 1:ʧ�� ʧ��ʱ�Ὣ��������-1
    int setY(int y);//����X 0:�ɹ� 1:ʧ�� ʧ��ʱ�Ὣ��������-1
    int setXY(int x,int y);//�������� ����0�ɹ� ����һ��ʧ���򷵻�1 ������ʧ�ܾͷ���2
    int godMove(int x,int y);//�����������õķ�Χֱ�Ӹı�����λ�� �ɽ��������������� ����0 �ƶ��ɹ� 1û�ƶ� 2 ս���� ˢ������ ��һ���ƶ�
    int moveMob(int toward);//Ĭ���ƶ����� ����Ϊ1 ����Ϊ 2�� 4�� 6�� 8�� ����0 �ƶ��ɹ� 1û�ƶ� 2 ս���� ˢ������ ��һ���ƶ�
    Mob* getMob(int toward);//2�� 4�� 6�� 8�� ��Ӧ�����Եõ�1379λ�õ����� ����Ϊ5
    // �㵱Ȼ�����������ȡ������ӵ�ָ�� ����(   �㲻�������ﲻ����
    // ��Ȼû�� ���Ǵ�Point�ڲ��ҵ�����ı�Ҫ����
};


#endif //SUPERCHAT_POINT_H