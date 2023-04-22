#include "stdafx.h"
#include "RoundX.h"

void RoundX::SetAllData()
{
    HandleJsonData("RoundX",allData);
    
    /*
    SetData current;
    
    current.damage=3;
    current.mode=white;
    current.imgPath.push_back("resources/h69bone.bmp");
    //current.imgPath="h69bone";
    current.initX=1000;
    current.initY=795;
    allData.push_back(current);
    current.imgPath.clear();
    
    current.damage=3;
    current.mode=white;
    current.imgPath.push_back("resources/h81bone.bmp");
    //current.imgPath="h81bone";
    current.initX=1150;
    current.initY=783;
    allData.push_back(current);
    current.imgPath.clear();
    
    current.damage=3;
    current.mode=white;
    current.imgPath.push_back("resources/h90bone.bmp");
    //current.imgPath="h90bone";
    current.initX=1300;
    current.initY=774;
    allData.push_back(current);
    current.imgPath.clear();
    */
}

void RoundX::recordXYDamageSpeed()
{
    xPosition[0]=1000;
    xPosition[1]=1150;
    xPosition[2]=1300;
    
    yPosition[0]=795;
    yPosition[1]=783;
    yPosition[2]=774;

    /*
    for(int i=0;i<_quantity;i++)
    {
        allSpeed[i]=3;
    }

    */

}

void RoundX::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].left_move(allSpeed[i]);
    }

    if(enemyBarrage[_quantity-1].GetOnePosition(IMGleft)<665)
    {
        isAttackEnd = true;
    }
}

void RoundX::test()
{
    std::ifstream file("AllRounds.json");
    file >> roundXData;
}

