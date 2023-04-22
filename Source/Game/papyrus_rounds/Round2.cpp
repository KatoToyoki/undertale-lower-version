#include "stdafx.h"
#include "Round2.h"

void Round2::SetAllData()
{
    SetData current;
    
    current.damage=3;
    current.mode=white;
    current.imgPath="h45bone";
    current.initX=1000;
    current.initY=819;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h90bone";
    current.initX=1230;
    current.initY=774;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h90bone";
    current.initX=1460;
    current.initY=774;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h90bone";
    current.initX=1690;
    current.initY=774;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h135bone";
    current.initX=1800;
    current.initY=727;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h135bone";
    current.initX=2100;
    current.initY=727;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h135bone";
    current.initX=2400;
    current.initY=727;
    allData.push_back(current);
}

void Round2::recordXYDamageSpeed()
{
    for(int i=0; i<_quantity-3; i++)
    {
        allSpeed[i]=5;
    }
    for(int i=_quantity-3; i<_quantity; i++)
    {
        allSpeed[i]=4;
    }
}

void Round2::MovingBarrage(Move* heart)
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