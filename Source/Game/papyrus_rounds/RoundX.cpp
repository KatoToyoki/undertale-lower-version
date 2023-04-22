#include "stdafx.h"
#include "RoundX.h"

void RoundX::SetAllData()
{
    HandleJsonData("RoundXData");
}

void RoundX::MovingBarrage(Move* heart)
{
    for(int i=0;i<_quantity;i++)
    {
        enemyBarrage[i].set_show_enable(true);
        enemyBarrage[i].left_move(allData[i].speed);
    }

    if(LeaveAtLeft()||LastOneDisappear())
    {
        isAttackEnd = true;
    }
}
