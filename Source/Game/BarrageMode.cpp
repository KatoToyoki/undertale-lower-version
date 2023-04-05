#include "stdafx.h"
#include "BarrageMode.h"

void BarrageMode::Init()
{
    xPosition[0]=1000;
    xPosition[1]=1150;
    xPosition[2]=1300;
    
    yPosition[0]=795;
    yPosition[1]=783;
    yPosition[2]=774;
    
    SetAllData();
}

void BarrageMode::SetAllData()
{
    SetData current;
    
    current.damage=3;
    current.mode=white;
    current.imgPath="bone1";
    current.initX=1000;
    current.initY=795;
    allData.push_back(current);
    
    current.damage=3;
    current.mode=white;
    current.imgPath="bone2";
    current.initX=1150;
    current.initY=783;
    allData.push_back(current);
    
    current.damage=3;
    current.mode=white;
    current.imgPath="bone3";
    current.initX=1300;
    current.initY=774;
    allData.push_back(current);
}

void BarrageMode::NewSetup(SetData data)
{
    Barrage current;
    current=Barrage(data.damage,data.mode);
    current.load_img(data.imgPath);
    current.set_positon(data.initX,data.initY);
}

void BarrageMode::RandomBarrage()
{
    srand((unsigned) time(NULL)); 
    for(int i=0;i<_quantity;i++)
    {
        int temp = rand();
        if(temp%3==0)
        {
            NewSetup(allData[_quantity-_quantity]);
            allData[_quantity-_quantity].initX=xPosition[i];
        }
        else if(temp%3==1)
        {
            NewSetup(allData[_quantity-1]);
            allData[_quantity-1].initX=xPosition[i];
        }
        else if(_quantity>3)
        {
            NewSetup(allData[_quantity-2]);
            allData[_quantity-2].initX=xPosition[i];
        }
    }
}

void BarrageMode::ShowBarrage()
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].show_img();
    }
}

void BarrageMode::UnshowBarrage()
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].UnshowIMG();
    }
}

void BarrageMode::MovingBarrage(Move *heart, Barrage current, int speed)
{
    current.set_show_enable(true);
    current.damege_hit(heart);
    current.left_move(speed);
}