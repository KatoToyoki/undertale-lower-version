#include "stdafx.h"
#include "Round3.h"

void Round3::SetAllData()
{
    HandleJsonData("Round3Data");
}

void Round3::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].damege_hit(heart,disappear);
        enemyBarrage[i].right_move(allData[i].speed);
    }

    if(LeaveAtRight()||LastOneDisappear())
    {
        isAttackEnd = true;
    }
}
