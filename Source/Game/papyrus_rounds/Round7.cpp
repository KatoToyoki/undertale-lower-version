#include "stdafx.h"
#include "Round7.h"

void Round7::SetAllData()
{
    HandleJsonData("Round7Data");
}

void Round7::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].left_move(allData[i].speed);
    }

    if(LeaveAtLeft()||LastOneDisappear())
    {
        isAttackEnd=true;
    }
}

