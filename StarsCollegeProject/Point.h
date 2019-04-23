//
// Created by Pharsalia on 2019/4/21.
//

#ifndef SUPERCHAT_POINT_H
#define SUPERCHAT_POINT_H

class Mob;
//代表棋子坐标的点类 内置了一万种API 可以完成移动 获取周围信息等
class Point{
protected:
    int x;
    int y;
public:
    explicit Point(int x = 0,int y = 0);
    Point(Point& p);
    int getX();//返回X
    int getY();//返回Y
    Point& getPoint();//返回该点的引用 若从棋子调用则返回常引用
    int setX(int x);//重设Y 0:成功 1:失败 失败时会将棋子置于-1
    int setY(int y);//重设X 0:成功 1:失败 失败时会将棋子置于-1
    int setXY(int x,int y);//重设坐标 返回0成功 若有一个失败则返回1 两个都失败就返回2
    int godMove(int x,int y);//可以跳出设置的范围直接改变棋子位置 可将棋子置于棋盘外 返回0 移动成功 1没移动 2 战斗后 刷新棋盘 不一定移动
    int moveMob(int toward);//默认移动函数 步长为1 方向为 2↓ 4← 6→ 8↑ 返回0 移动成功 1没移动 2 战斗后 刷新棋盘 不一定移动
    Mob* getMob(int toward);//2↓ 4← 6→ 8↑ 相应还可以得到1379位置的棋子 自身为5
    // 你当然可以用这个获取这个棋子的指针 不过(   你不觉得哪里不对吗
    // 当然没有 这是从Point内部找到自身的必要方法
};


#endif //SUPERCHAT_POINT_H