//
// Created by Pharsalia on 2019/4/19.
//
#include "SuperChat.h"
/*������ ��ô���Լ�Ӧ�ö�*/
void Dice(int n,int range,int *from){
    for(int i = 0;i<n;i++){
        *from = ( rand() % range )+ 1;
        from++;
    }
}