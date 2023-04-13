#include "stdafx.h"
#include "RoundX.h"

void RoundX::SetAllData()
{
    SetData current;
    
    current.damage=3;
    current.mode=white;
    current.imgPath="h69bone";
    current.initX=1000;
    current.initY=795;
    allData.push_back(current);
    
    current.damage=322;
    current.mode=white;
    current.imgPath="h81bone";
    current.initX=1150;
    current.initY=783;
    allData.push_back(current);
    
    current.damage=3;
    current.mode=white;
    current.imgPath="h90bone";
    current.initX=1300;
    current.initY=774;
    allData.push_back(current);
}

void RoundX::PushXYDamage()
{
    xPosition[0]=1000;
    xPosition[1]=1150;
    xPosition[2]=1300;
    
    yPosition[0]=795;
    yPosition[1]=783;
    yPosition[2]=774;

}