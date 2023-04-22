#include "stdafx.h"
#include "Round0.h"

void Round0::SetAllData()
{
    SetData current;
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h210boneB";
    current.initX=1000;
    current.initY=654;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h110boneB";
    current.initX=1100;
    current.initY=754;
    allData.push_back(current);
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h163boneB";
    current.initX=1200;
    current.initY=701;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h110boneB";
    current.initX=1300;
    current.initY=754;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h210boneB";
    current.initX=1400;
    current.initY=575;
    allData.push_back(current);

    //
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h143boneB";
    current.initX=1550;
    current.initY=721;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h210boneB";
    current.initX=1650;
    current.initY=654;
    allData.push_back(current);
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h169boneB";
    current.initX=1750;
    current.initY=695;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h234boneB";
    current.initX=1850;
    current.initY=630;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h204boneB";
    current.initX=1950;
    current.initY=660;
    allData.push_back(current);

    //
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h210boneB";
    current.initX=2050;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h169boneB";
    current.initX=2150;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h204boneB";
    current.initX=2250;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h234boneB";
    current.initX=2350;
    current.initY=630;
    allData.push_back(current);
    
    current.damage=3;
    current.mode=white;
    current.imgPath="h45bone";
    current.initX=600;
    current.initY=819;
    allData.push_back(current);
}

void Round0::recordXYDamageSpeed()
{
    allSpeed[0]=4;
    allSpeed[1]=7;
    allSpeed[2]=4;
    allSpeed[3]=5;
    allSpeed[4]=7;
    
    allSpeed[5]=5;
    allSpeed[6]=6;
    allSpeed[7]=5;
    allSpeed[8]=6;
    allSpeed[9]=7;
    
    allSpeed[10]=6;
    allSpeed[11]=7;
    allSpeed[12]=6;
    allSpeed[13]=7;
    
    allSpeed[14]=9;
}

void Round0::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity-1;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].left_move(allSpeed[i]);
    }

    if(enemyBarrage[_quantity-2].GetOnePosition(IMGleft)<665 && enemyBarrage[_quantity-3].GetOnePosition(IMGleft)<665)
    {
        enemyBarrage[_quantity-1].set_show_enable(true);
        enemyBarrage[_quantity-1].right_move(allSpeed[_quantity-1]);
    }

    if(enemyBarrage[_quantity-1].GetOnePosition(IMGleft)>1270)
    {
        isAttackEnd = true;
    }
}