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
    PushEmpty();
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

void BarrageMode::PushEmpty()
{
    Barrage temp=Barrage(0,white);
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage.push_back(temp);
    }
}

Barrage BarrageMode::Setup(SetData data)
{
    Barrage current;
    current.load_img(data.imgPath);
    current.SetDamage(data.damage);
    current.SetMode(data.mode);
    current.set_positon(data.initX,data.initY);

    return current;
}

void BarrageMode::RandomBarrage()
{
    srand((unsigned) time(NULL)); 
    for(int i=0;i<_quantity;i++)
    {
        int temp = rand();
        if(temp%3==0)
        {
            enemyBarrage[i]=Setup(allData[_quantity-_quantity]);
            enemyBarrage[i].set_positon(xPosition[i],allData[_quantity-_quantity].initY);
        }
        else if(temp%3==1)
        {
            enemyBarrage[i]=Setup(allData[_quantity-1]);
            enemyBarrage[i].set_positon(xPosition[i],allData[_quantity-1].initY);
        }
        else if(_quantity>=3)
        {
            enemyBarrage[i]=Setup(allData[_quantity-2]);
            enemyBarrage[i].set_positon(xPosition[i],allData[_quantity-2].initY);
        }
    }
}

void BarrageMode::NormalBarrage()
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i]=Setup(allData[i]);
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

void BarrageMode::MovingBarrage(Move *heart, int speed)
{
    // for(int i=0;i<_quantity;i++)
    // {
    //     enemyBarrage[i].set_show_enable(true);
    //     enemyBarrage[i].damege_hit(heart);//koko
    //     enemyBarrage[i].left_move(speed);
    // }
}