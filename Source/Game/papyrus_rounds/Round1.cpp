#include "stdafx.h"
#include "Round1.h"

void Round1::SetAllData()
{
    SetData current;
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h45bone";
    current.initX=1250;
    current.initY=819;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h45bone";
    current.initX=1550;
    current.initY=819;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h90bone";
    current.initX=1850;
    current.initY=774;
    allData.push_back(current);
}

void Round1::recordXYDamageSpeed()
{
    for(int i=0; i<_quantity; i++)
    {
        allSpeed[i]=3;
    }
}

void Round1::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].left_move(allSpeed[i]);
    }

    if(enemyBarrage[_quantity-1].GetOnePosition(IMGleft)<665)
    {
        isAttackEnd = true;
    }
}