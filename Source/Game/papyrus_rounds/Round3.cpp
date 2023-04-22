#include "stdafx.h"
#include "Round3.h"

void Round3::SetAllData()
{
    SetData current;
    
    current.damage=3;
    current.mode=white;
    current.imgPath="h135bone";
    current.initX=650;
    current.initY=729;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h221bone";
    current.initX=550;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h45bone";
    current.initX=450;
    current.initY=819;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h45bone";
    current.initX=350;
    current.initY=819;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h45bone";
    current.initX=250;
    current.initY=819;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h111bone";
    current.initX=150;
    current.initY=753;
    allData.push_back(current);

    current.damage=3;
    current.mode=white;
    current.imgPath="h221bone";
    current.initX=50;
    current.initY=575;
    allData.push_back(current);

    //135 221(up) 45 45 45 111 221(up)
}

void Round3::recordXYDamageSpeed()
{
    for(int i=0; i<_quantity; i++)
    {
        allSpeed[i]=4;
    }
}

void Round3::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].right_move(allSpeed[i]);
    }

    if(enemyBarrage[_quantity-1].GetOnePosition(IMGleft)>1270)
    {
        isAttackEnd = true;
    }
}
