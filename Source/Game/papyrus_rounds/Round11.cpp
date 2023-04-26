#include "stdafx.h"
#include "Round11.h"

void Round11::SetAllData()
{
    HandleJsonData("Round11Data");
}

void Round11::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].left_move(allData[i].speed);
        
        CompoundBarrage(enemyBarrage[11],enemyBarrage[12],heart);
        CompoundBarrage(enemyBarrage[14],enemyBarrage[13],heart);
    }
    
    UpDownBarrage(enemyBarrage[12],422,522);
    UpDownBarrage(enemyBarrage[13],742,842);
    
    if(LeaveAtLeft()||LastOneDisappear())
    {
        isAttackEnd=true;
    }
}

void Round11::UpDownBarrage(Barrage& barrage, int upLimit, int downLimit)
{
    switch (direction)
    {
    case goUp:
        if(barrage.GetOnePosition(IMGtop)>=upLimit)
        {
            barrage.up_move(2);
        }
        else if(barrage.GetOnePosition(IMGtop)<upLimit)
        {
            direction=goDown;
        }
        break;
        
    case goDown:
        if(barrage.GetOnePosition(IMGtop)<=downLimit)
        {
            barrage.down_move(2);
        }
        else if(barrage.GetOnePosition(IMGtop)>downLimit)
        {
            direction=goUp;
        }
        break;
    }
}

void Round11::CompoundBarrage(Barrage& cover,Barrage& barrage,Move *heart)
{
    if(barrage.GetIsOverlay(heart))
    {
        cover.set_positon(0,0);
    }
}
