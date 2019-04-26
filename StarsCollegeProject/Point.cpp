//
// Created by Pharsalia on 2019/4/21.
//

#include "SuperChat.h"
#include "Point.h"

Point::Point(int x,int y){
    if(x>9 || x<0) this->x = 0;
    if(x<=9 && x>=0) this->x = x;
    if(y>9 || y<0) this->y = 0;
    if(y<=9 && y>=0) this->y = y;
}
Point::Point(Point &p) {
    this->x = p.x;
    this->y = p.y;
}
int Point::getX() { return x; }
int Point::getY() { return y; }
Point& Point::getPoint() { return *this; }
int Point::setX(int x) {
    if(x<=9 && x>=0 && battleSystem.getChessBoard()[x][y] == nullptr){
        this->x = x;
        return 0;
    }else{
        this->x = -1;
        return -1;
    }
}
int Point::setY(int y) {
    if(y<=9 && y>=0 && battleSystem.getChessBoard()[x][y] == nullptr){
        this->y = y;
        return 0;
    }else{
        this->y = -1;
        return -1;
    }
}
int Point::setXY(int x, int y) {
    if( (x<=9 && x>=0) && (y<=9 && y>=0) && battleSystem.getChessBoard()[x][y] == nullptr){
        this->x = x; this->y = y; return 0;
    }
    else{
        this->x = -1; this->y = -1; return -1;
    }
}
Mob* Point::getMob(int toward) {
    Mob*** tmp = battleSystem.getChessBoard();
    switch (toward){
        case 2:
            if(y <= 8 && y >= 0){
                return tmp[x][y+1];
            }else{ return nullptr; }
        case 4:
            if(x >= 1 && x <= 9){
                return tmp[x-1][y];
            }else{ return nullptr; }
        case 6:
            if(x <= 8 && x >= 0){
                return tmp[x+1][y];
            }else{ return nullptr; }
        case 8:
            if(y >= 1 && y <= 9){
                return tmp[x][y-1];
            }else{ return nullptr; }
        case 1:
            if( (x>=1 && x<=9)&&(y>=0 && y<=8) ){
                return tmp[x-1][y+1];
            }else{ return nullptr; }
        case 3:
            if( (x>=0 && x<=8)&&(y>=0 && y<=8) ){
                return tmp[x+1][y+1];
            }else{ return nullptr; }
        case 7:
            if( (x>=1 && x<=9)&&(y>=1 && y<=9) ){
                return tmp[x-1][y-1];
            }else{ return nullptr; }
        case 9:
            if( (x>=0 && x<=8)&&(y>=1 && y<=9) ){
                return tmp[x+1][y-1];
            }else{ return nullptr; }
        default: return tmp[x][y];
    }
}
int Point::moveMob(int toward) {
    Mob* tmp = getMob(toward);
    int flag = 0;
    switch (toward){
        default:
            flag = 1; break;
        case 2:
            //Խ�� ���ö� Ҳ����ˢ��
            if(y == 9){ flag = 1; break; }
            //�жϸ�λ���Ƿ�������
            if(tmp == nullptr){ this->y ++; flag = 0; break; }
            //�� Ĭ�Ϸ���һ��ս��
            else{
                //���� �������ƶ�
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    //�з� Ĭ�Ϸ������� ����ս��������ƶ����ø� ��Զ�������򲻻��ƶ� �����жϽ���ˢ������
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->y ++; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }
        case 4:
            if(x == 0){ flag = 1; break; }
            if(tmp == nullptr){ this->x --; flag = 0; break; }
            else{
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->x --; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }
        case 6:
            if(x == 9){ flag = 1; break; }
            if(tmp == nullptr){ this->x ++; flag = 0; break; }
            else{
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->x ++; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }
        case 8:
            if(y == 0){ flag = 1; break; }
            if(tmp == nullptr){ this->y --; flag = 0; break; }
            else{
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->y --; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }


        case 1:
            if(x == 0 || y == 9){ flag = 1; break; }
            if(tmp == nullptr){ this->y++; this->x--; flag = 0; break; }
            else{
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->y++; this->x--; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }
        case 3:
            if(x == 9 || y == 9){ flag = 1; break; }
            if(tmp == nullptr){ this->y++; this->x++; flag = 0; break; }
            else{
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->y++; this->x++; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }
        case 7:
            if(x == 0 || y == 0){ flag = 1; break; }
            if(tmp == nullptr){ this->y--; this->x--; flag = 0; break; }
            else{
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->y--; this->x--; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }
        case 9:
            if(x == 9 || y == 0){ flag = 1; break; }
            if(tmp == nullptr){ this->y--; this->x++; flag = 0; break; }
            else{
                if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; break; }
                else{
                    if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->y--; this->x++; }
                    if(tmp->getHP()>0)flag = 2;
                    else flag = 3;
                    break;
                }
            }
    }
    if(flag != 1){
        battleSystem.refreshBoard();
    }
    return flag;
}
int Point::godMove(int x, int y) {
    Mob* tmp = battleSystem.getChessBoard()[x][y];
    int flag = 0;
    if(x<0 || x>9 || y<0 || y>9){ flag = 1; }
    else {
        if (tmp == nullptr){
            this->x = x; this->y = y;
        }else{
            if(tmp->getTeam() == getMob(5)->getTeam()){ flag = 1; }
            else{
                if(battleSystem.attackMob(getMob(5),tmp) == 2 && getMob(5)->getType() == 1){ this->x = x; this->y = y; }
                if(tmp->getHP()>0) flag = 2;
                else flag = 3;
            }
        }
    }
    if(flag != 1){
        battleSystem.refreshBoard();
    }
    return flag;
}