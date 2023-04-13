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
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h163boneB";
    current.initX=1500;
    current.initY=701;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h143boneB";
    current.initX=1600;
    current.initY=721;
    allData.push_back(current);
    
    current.damage=3;
    current.mode=blue;
    current.imgPath="h210boneB";
    current.initX=1700;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h128boneB";
    current.initX=1800;
    current.initY=736;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h143boneB";
    current.initX=1900;
    current.initY=721;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h210boneB";
    current.initX=2000;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h169boneB";
    current.initX=2100;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h204boneB";
    current.initX=2200;
    current.initY=575;
    allData.push_back(current);

    current.damage=3;
    current.mode=blue;
    current.imgPath="h234boneB";
    current.initX=2300;
    current.initY=622;
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
    allSpeed[6]=9;
    allSpeed[7]=5;
    allSpeed[8]=7;
    allSpeed[9]=10;
    
    allSpeed[10]=5;
    allSpeed[11]=7;
    allSpeed[12]=5;
    allSpeed[13]=8;
    
    allSpeed[14]=9;
}

void Round0::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        if(i==_quantity-1)
        {
            enemyBarrage[i].right_move(allSpeed[i]);
        }
        enemyBarrage[i].left_move(allSpeed[i]);
    }
}