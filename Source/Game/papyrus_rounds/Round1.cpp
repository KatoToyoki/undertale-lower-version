#include "stdafx.h"
#include "Round1.h"

#include "../Character.h"

void Round1::SetAllData()
{
    HandleJsonData("Round1Data");
}

void Round1::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].left_move(allData[i].speed);
    }

    if(LeaveAtLeft()||LastOneDisappear())
    {
        isAttackEnd = true;
    }
}