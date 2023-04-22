#include "stdafx.h"
#include "BarrageMode.h"

void BarrageMode::Init()
{
    SetAllData();
    PushEmpty();
    recordXYDamageSpeed();
}

void BarrageMode::PushEmpty()
{
    Barrage temp=Barrage(0,white);
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage.push_back(temp);
        xPosition.push_back(0);
        yPosition.push_back(0);
        allDamage.push_back(0);
        allSpeed.push_back(0);
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

bool BarrageMode::GetIsAttackEnd()
{
    
    return isAttackEnd;
}

int BarrageMode::GetMinusHP_M(Move *heart)
{
    int damage=0;
    for(int i=0;i<_quantity;i++)
    {
        //enemyBarrage[i].set_show_enable(true);
        damage+=enemyBarrage[i].damege_hit(heart);
    }

    return damage;
}
