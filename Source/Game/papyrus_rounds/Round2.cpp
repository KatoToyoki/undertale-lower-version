#include "stdafx.h"
#include "Round2.h"

void Round2::SetAllData()
{
    HandleJsonData("Round2Data");
}

void Round2::MovingBarrage(Move* heart)
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